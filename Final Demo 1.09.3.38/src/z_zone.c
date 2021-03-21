// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// This file is in the public domain.
// Written by Graue in 2006.
//
//-----------------------------------------------------------------------------
/// \file
/// \brief Zone memory allocation.

#include "doomdef.h"
#include "doomstat.h"
#include "i_system.h" // I_GetFreeMem
#include "i_video.h" // rendermode
#include "z_zone.h"

#ifdef HWRENDER
#include "hardware/hw_main.h" // For hardware memory info
#endif

#define ZONEID 0xa441d13d

struct memblock_s;

typedef struct
{
	struct memblock_s *block; // Describing this memory
	unsigned int id; // Should be ZONEID
} memhdr_t;

// Some code might want aligned memory. Assume it wants memory n bytes
// aligned -- then we allocate n-1 extra bytes and return a pointer to
// the first byte aligned as requested.
// Thus, "real" is the pointer we get from malloc() and will free()
// later, but "hdr" is where the memhdr_t starts.
// For non-aligned allocations they will be the same.
typedef struct memblock_s
{
	void *real;
	memhdr_t *hdr;

	void **user;
	int tag; // purgelevel

	size_t size; // including the header and blocks

#ifdef ZDEBUG
	char *ownerfile;
	int ownerline;
#endif

	struct memblock_s *next, *prev;
} memblock_t;

static memblock_t head;

static void Command_Memfree_f(void);

void Z_Init(void)
{
	ULONG total, memfree;

	head.next = head.prev = &head;

	memfree = I_GetFreeMem(&total)>>20;
	CONS_Printf("system memory %dMB free %dMB\n", total>>20, memfree);

	// Note: This allocates memory. Watch out.
	COM_AddCommand("memfree", Command_Memfree_f);
}

#ifdef ZDEBUG
void Z_Free2(void *ptr, char *file, int line)
#else
void Z_Free(void *ptr)
#endif
{
	memhdr_t *hdr;
	memblock_t *block;

#ifdef ZDEBUG2
	CONS_Printf("Z_Free %s:%d\n", file, line);
#endif

	if (ptr == NULL)
		return;
	hdr = (memhdr_t *)((byte *)ptr - sizeof *hdr);
	if (hdr->id != ZONEID)
	{
#ifdef ZDEBUG
		I_Error("Z_Free: wrong id from %s:%d", file, line);
#else
		I_Error("Z_Free: wrong id");
#endif
	}
	block = hdr->block;

#ifdef ZDEBUG
	// Write every Z_Free call to a debug file.
	DEBFILE(va("Z_Free at %s:%d\n", file, line));
#endif

	// TODO: if zdebugging, make sure no other block has a user
	// that is about to be freed.

	// Clear the user's mark.
	if (block->user != NULL)
		*block->user = NULL;

	// Free the memory and get rid of the block.
	free(block->real);
	block->prev->next = block->next;
	block->next->prev = block->prev;
	free(block);
}

static void *xm(size_t size)
{
	void *p = malloc(size);
	if (p == NULL)
		I_Error("Out of memory allocating %lu bytes",
			(unsigned long)size);
	return p;
}

// Z_Malloc
// You can pass Z_Malloc() a NULL user if the tag is less than
// PU_PURGELEVEL.

// TODO: Currently blocks >= PU_PURGELEVEL are freed every
// CLEANUPCOUNT Z_Malloc()s. It might be better to keep track of
// the total size of all purgable memory and free it when the
// size exceeds some value.

#define CLEANUPCOUNT 2000

typedef unsigned long u_intptr_t; // Integer long enough to hold pointer

#ifdef ZDEBUG
void *Z_Malloc2(size_t size, int tag, void *user, int alignbits,
	char *file, int line)
#else
void *Z_MallocAlign(size_t size, int tag, void *user, int alignbits)
#endif
{
	size_t extrabytes = (1<<alignbits) - 1;
	static int nextcleanup = 0;
	memblock_t *block;
	void *ptr;
	memhdr_t *hdr;
	void *given;

#ifdef ZDEBUG2
	CONS_Printf("Z_Malloc %s:%d\n", file, line);
#endif

	if (nextcleanup-- == 0)
	{
		nextcleanup = CLEANUPCOUNT;
		Z_FreeTags(PU_PURGELEVEL, MAXINT);
	}

	block = xm(sizeof *block);
	ptr = xm(extrabytes + sizeof *hdr + size);
	hdr = (memhdr_t *)((u_intptr_t)((byte *)ptr + extrabytes) & ~extrabytes);

	block->next = head.next;
	block->prev = &head;
	block->next->prev = head.next = block;

	block->real = ptr;
	block->hdr = hdr;
	block->tag = tag;
	block->user = NULL;
#ifdef ZDEBUG
	block->ownerline = line;
	block->ownerfile = file;
#endif
	block->size = size + extrabytes + sizeof *hdr;

	hdr->id = ZONEID;
	hdr->block = block;

	given = ((byte *)hdr + sizeof *hdr);

	if (user != NULL)
	{
		block->user = user;
		*(void **)user = given;
	}
	else if (tag >= PU_PURGELEVEL)
		I_Error("Z_Malloc: attempted to allocate purgable block "
			"(size %lu) with no user", (unsigned long)size);

	return given;
}

void Z_FreeTags(int lowtag, int hightag)
{
	memblock_t *block, *next;

	for (block = head.next; block != &head; block = next)
	{
		next = block->next; // get link before freeing

		if (block->tag >= lowtag && block->tag <= hightag)
			Z_Free((byte *)block->hdr + sizeof *block->hdr);
	}
}

/** Checks the heap, as well as the memhdr_ts, for any corruption or
  * other problems.
  * \param i Identifies from where in the code Z_CheckHeap was called.
  * \author Graue <graue@oceanbase.org>
  */
void Z_CheckHeap(int i)
{
	memblock_t *block;
	unsigned int blocknumon = 0;
	void *given;

	for (block = head.next; block != &head; block = block->next)
	{
		blocknumon++;
		given = (byte *)block->hdr + sizeof *(block->hdr);
		if (block->user != NULL && *(block->user) != given)
		{
			I_Error("Z_CheckHeap %d: block %u doesn't have a "
				"proper user", i, blocknumon);
		}
		if (block->next->prev != block)
		{
			I_Error("Z_CheckHeap %d: block %u lacks proper "
				"backlink", i, blocknumon);
		}
		if (block->prev->next != block)
		{
			I_Error("Z_CheckHeap %d: block %u lacks proper "
				"forward link", i, blocknumon);
		}
		if (block->hdr->block != block)
		{
			I_Error("Z_CheckHeap %d: block %u doesn't have "
				"linkback from allocated memory",
				i, blocknumon);
		}
		if (block->hdr->id != ZONEID)
		{
			I_Error("Z_CheckHeap %d: block %u's memory has "
				"wrong ID", i, blocknumon);
		}
	}
}

#ifdef PARANOIA
void Z_ChangeTag2(void *ptr, int tag, char *file, int line)
#else
void Z_ChangeTag2(void *ptr, int tag)
#endif
{
	memblock_t *block;
	memhdr_t *hdr;

	if (ptr == NULL)
		return;

	hdr = (memhdr_t *)((byte *)ptr - sizeof *hdr);

#ifdef PARANOIA
	if (hdr->id != ZONEID) I_Error("Z_CT at %s:%d: wrong id", file, line);
#endif

	block = hdr->block;

	if (tag >= PU_PURGELEVEL && block->user == NULL)
		I_Error("Internal memory management error: "
			"tried to make block purgable but it has no owner");

	block->tag = tag;
}

/** Calculates memory usage for a given set of tags.
  * \param lowtag The lowest tag to consider.
  * \param hightag The highest tag to consider.
  * \return Number of bytes currently allocated in the heap for the
  *         given tags.
  * \sa Z_TagUsage
  */
size_t Z_TagsUsage(int lowtag, int hightag)
{
	size_t cnt = 0;
	memblock_t *rover;

	for (rover = head.next; rover != &head; rover = rover->next)
	{
		if (rover->tag < lowtag || rover->tag > hightag)
			continue;
		cnt += rover->size + sizeof *rover;
	}

	return cnt;
}

size_t Z_TagUsage(int tagnum)
{
	return Z_TagsUsage(tagnum, tagnum);
}

void Command_Memfree_f(void)
{
	ULONG freebytes, totalbytes;

	Z_CheckHeap(-1);
	CONS_Printf("\2Memory Info\n");
	CONS_Printf("Total heap used   : %7d KB\n", Z_TagsUsage(0, MAXINT)>>10);
	CONS_Printf("Static            : %7d KB\n", Z_TagUsage(PU_STATIC)>>10);
	CONS_Printf("Static (sound)    : %7d KB\n", Z_TagUsage(PU_SOUND)>>10);
	CONS_Printf("Static (music)    : %7d KB\n", Z_TagUsage(PU_MUSIC)>>10);
	CONS_Printf("Level             : %7d KB\n", Z_TagUsage(PU_LEVEL)>>10);
	CONS_Printf("Special thinker   : %7d KB\n", Z_TagUsage(PU_LEVSPEC)>>10);
	CONS_Printf("All purgable      : %7d KB\n",
		Z_TagsUsage(PU_PURGELEVEL, MAXINT)>>10);

#ifdef HWRENDER
	if (rendermode != render_soft && rendermode != render_none)
	{
		CONS_Printf("Patch info headers: %7d KB\n",
			Z_TagUsage(PU_HWRPATCHINFO)>>10);
		CONS_Printf("Mipmap patches    : %7d KB\n",
			Z_TagUsage(PU_HWRPATCHCOLMIPMAP)>>10);
		CONS_Printf("HW Texture cache  : %7d KB\n",
			Z_TagUsage(PU_HWRCACHE)>>10);
		CONS_Printf("Plane polygons    : %7d KB\n",
			Z_TagUsage(PU_HWRPLANE)>>10);
		CONS_Printf("HW Texture used   : %7d KB\n",
			HWR_GetTextureUsed()>>10);
	}
#endif

	CONS_Printf("\2System Memory Info\n");
	freebytes = I_GetFreeMem(&totalbytes);
	CONS_Printf("    Total physical memory: %7d KB\n", totalbytes>>10);
	CONS_Printf("Available physical memory: %7d KB\n", freebytes>>10);
}

// Creates a copy of a string.
char *Z_StrDup(const char *s)
{
	return strcpy(ZZ_Alloc(strlen(s) + 1), s);
}

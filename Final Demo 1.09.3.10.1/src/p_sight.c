// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//-----------------------------------------------------------------------------
/// \file
/// \brief Line of sight/visibility checks, uses REJECT lookup table

#include "doomdef.h"
#include "doomstat.h"
#include "p_local.h"
#include "r_main.h"
#include "r_state.h"

static fixed_t sightzstart; // eye z of looker
fixed_t topslope, bottomslope; // slopes to top and bottom of target

static divline_t strace; // from t1 to t2
static fixed_t t2x, t2y;

static int sightcounts[2];

//
// P_DivlineSide
//
// Returns side 0 (front), 1 (back), or 2 (on).
//
static int P_DivlineSide(fixed_t x, fixed_t y, divline_t* node)
{
	fixed_t dx, dy, left, right;

	if(!node->dx)
	{
		if(x == node->x)
			return 2;

		if(x <= node->x)
			return node->dy > 0;

		return node->dy < 0;
	}

	if(!node->dy)
	{
		if(x == node->y)
			return 2;

		if(y <= node->y)
			return node->dx < 0;

		return node->dx > 0;
	}

	dx = x - node->x;
	dy = y - node->y;

	left = (node->dy>>FRACBITS) * (dx>>FRACBITS);
	right = (dy>>FRACBITS) * (node->dx>>FRACBITS);

	if(right < left)
		return 0; // front side

	if(left == right)
		return 2;

	return 1; // back side
}

//
// P_InterceptVector2
//
// Returns the fractional intercept point along the first divline.
// This is only called by the addthings and addlines traversers.
//
static fixed_t P_InterceptVector2(divline_t* v2, divline_t* v1)
{
	fixed_t frac, num, den;

	den = FixedMul(v1->dy>>8, v2->dx) - FixedMul(v1->dx>>8, v2->dy);

	if(!den)
		return 0;

	num = FixedMul((v1->x - v2->x)>>8, v1->dy) + FixedMul((v2->y - v1->y)>>8, v1->dx);
	frac = FixedDiv(num, den);

	return frac;
}

//
// P_CrossSubsector
//
// Returns true if strace crosses the given subsector successfully.
//
static boolean P_CrossSubsector(int num)
{
	seg_t* seg;
	line_t* line;
	int s1, s2, count;
	subsector_t* sub;
	sector_t* front;
	sector_t* back;
	fixed_t popentop, popenbottom, frac, slope;
	divline_t divl;
	vertex_t* v1;
	vertex_t* v2;

#ifdef RANGECHECK
	if(num >= numsubsectors)
		I_Error("P_CrossSubsector: ss %d with numss = %d", num, numsubsectors);
#endif

	sub = &subsectors[num];

	// check lines
	count = sub->numlines;
	seg = &segs[sub->firstline];

	for(; count; seg++, count--)
	{
		line = seg->linedef;

		// already checked other side?
		if(line->validcount == validcount)
			continue;

		line->validcount = validcount;

		v1 = line->v1;
		v2 = line->v2;
		s1 = P_DivlineSide(v1->x, v1->y, &strace);
		s2 = P_DivlineSide(v2->x, v2->y, &strace);

		// line isn't crossed?
		if(s1 == s2)
			continue;

		divl.x = v1->x;
		divl.y = v1->y;
		divl.dx = v2->x - v1->x;
		divl.dy = v2->y - v1->y;
		s1 = P_DivlineSide(strace.x, strace.y, &divl);
		s2 = P_DivlineSide(t2x, t2y, &divl);

		// line isn't crossed?
		if(s1 == s2)
			continue;

		// stop because it is not two sided anyway
		// might do this after updating validcount?
		if(!(line->flags & ML_TWOSIDED))
			return false;

		// crosses a two sided line
		front = seg->frontsector;
		back = seg->backsector;

		// no wall to block sight with?
		if(front->floorheight == back->floorheight
			&& front->ceilingheight == back->ceilingheight)
		{
			continue;
		}

		// possible occluder because of ceiling height differences
		if(front->ceilingheight < back->ceilingheight)
			popentop = front->ceilingheight;
		else
			popentop = back->ceilingheight;

		// because of ceiling height differences
		if(front->floorheight > back->floorheight)
			popenbottom = front->floorheight;
		else
			popenbottom = back->floorheight;

		// quick test for totally closed doors
		if(popenbottom >= popentop)
			return false; // stop

		frac = P_InterceptVector2(&strace, &divl);

		if(front->floorheight != back->floorheight)
		{
			slope = FixedDiv(popenbottom - sightzstart, frac);
			if(slope > bottomslope)
				bottomslope = slope;
		}

		if(front->ceilingheight != back->ceilingheight)
		{
			slope = FixedDiv(popentop - sightzstart, frac);
			if(slope < topslope)
				topslope = slope;
		}

		if(topslope <= bottomslope)
			return false; // stop
	}
	// passed the subsector ok
	return true;
}

//
// P_CrossBSPNode
//
// Returns true if strace crosses the given node successfully.
//
static boolean P_CrossBSPNode(int bspnum)
{
	node_t* bsp;
	int side;

	if(bspnum & NF_SUBSECTOR)
	{
		if(bspnum == -1)
			return P_CrossSubsector(0);
		else
			return P_CrossSubsector(bspnum & (~NF_SUBSECTOR));
	}

	bsp = &nodes[bspnum];

	// decide which side the start point is on
	side = P_DivlineSide(strace.x, strace.y, (divline_t*)bsp);
	if(side == 2)
		side = 0; // an "on" should cross both sides

	// cross the starting side
	if(!P_CrossBSPNode(bsp->children[side]))
		return false;

	// the partition plane is crossed here
	if(side == P_DivlineSide(t2x, t2y, (divline_t*)bsp))
		return true; // the line doesn't touch the other side

	// cross the ending side
	return P_CrossBSPNode(bsp->children[side^1]);
}

//
// P_CheckSight
//
// Returns true if a straight line between t1 and t2 is unobstructed.
// Uses REJECT.
//
boolean P_CheckSight(mobj_t* t1, mobj_t* t2)
{
	size_t s1, s2, pnum, bytenum, bitnum;

	// First check for trivial rejection.

	if(!t1 || !t2 || !t1->subsector || !t2->subsector
		|| !t1->subsector->sector || !t2->subsector->sector)
	{
		return false;
	}

	// Determine subsector entries in REJECT table.
	s1 = t1->subsector->sector - sectors;
	s2 = t2->subsector->sector - sectors;
	pnum = s1*numsectors + s2;
	bytenum = pnum>>3;
	bitnum = 1 << (pnum&7);

	// Check in REJECT table.
	if(rejectmatrix[bytenum] & bitnum)
	{
		sightcounts[0]++;

		// can't possibly be connected
		return false;
	}

	// An unobstructed LOS is possible.
	// Now look from eyes of t1 to any part of t2.
	sightcounts[1]++;

	validcount++;

	sightzstart = t1->z + t1->height - (t1->height>>2); // the vertical center of t1
	topslope = t2->z + t2->height - sightzstart;
	bottomslope = t2->z - sightzstart;

	// Prevent SOME cases of looking through 3dfloors
	//
	// This WILL NOT work for things like 3d stairs with monsters behind
	// them - they will still see you! TODO: Fix.
	//
	// For future: Have this do some fancy calculation to determine real
	// sight for the Quake3-ish player name display.
	if(t1->subsector->sector == t2->subsector->sector) // Both are in the same sector
	{
		fixed_t sight1, sight2;
		ffloor_t* rover;

		sight1 = t1->z + (t1->height>>2);
		sight2 = t2->z + (t2->height>>2);

		for(rover = t1->subsector->sector->ffloors; rover; rover = rover->next)
		{
			// Allow sight through water, fog, etc.
			/// \todo Improve by checking fog density/translucency
			/// and setting a sight limit.
			if(!(rover->flags & FF_EXISTS)
				|| !(rover->flags & FF_RENDERPLANES) || rover->flags & FF_TRANSLUCENT)
			{
				continue;
			}

			// Check for blocking floors here.
			if((sightzstart < *rover->bottomheight && t2->z >= *rover->topheight)
				|| (sightzstart >= *rover->topheight && t2->z + t2->height < *rover->bottomheight))
			{
				// no way to see through that
				return false;
			}

			if(rover->flags & FF_SOLID)
				continue; // shortcut since neither mobj can be inside the 3dfloor

			if(!(rover->flags & FF_INVERTPLANES))
			{
				if(sightzstart >= *rover->topheight && t2->z + t2->height < *rover->topheight)
					return false; // blocked by upper outside plane

				if(sightzstart < *rover->bottomheight && t2->z >= *rover->bottomheight)
					return false; // blocked by lower outside plane
			}

			if(rover->flags & FF_INVERTPLANES || rover->flags & FF_BOTHPLANES)
			{
				if(sightzstart < *rover->topheight && t2->z >= *rover->topheight)
					return false; // blocked by upper inside plane

				if(sightzstart >= *rover->bottomheight && t2->z + t2->height < *rover->bottomheight)
					return false; // blocked by lower inside plane
			}
		}
	}

	strace.x = t1->x;
	strace.y = t1->y;
	t2x = t2->x;
	t2y = t2->y;
	strace.dx = t2->x - t1->x;
	strace.dy = t2->y - t1->y;

	// the head node is the last node output
	return P_CrossBSPNode(numnodes - 1);
}

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
/// \brief Sound and music info

#ifndef __SOUNDS__
#define __SOUNDS__

// 10 customisable sounds for Skins
typedef enum
{
	SKSSPIN,
	SKSPUTPUT,
	SKSPUDPUD,
	SKSPLPAN1, // Ouchies
	SKSPLPAN2,
	SKSPLPAN3,
	SKSPLPAN4,
	SKSPLDET1, // Deaths
	SKSPLDET2,
	SKSPLDET3,
	SKSPLDET4,
	SKSPLTNT1, // Taunts
	SKSPLTNT2,
	SKSPLTNT3,
	SKSPLTNT4,
	SKSPLVCT1, // Victories
	SKSPLVCT2,
	SKSPLVCT3,
	SKSPLVCT4,
	SKSTHOK,
	SKSSPNDSH,
	SKSZOOM,
	SKSRADIO,
	SKSGASP,
	SKSJUMP,
	NUMSKINSOUNDS
} skinsound_t;

// free sfx for S_AddSoundFx()
#define NUMSFXFREESLOTS 800 // Matches SOC Editor.
#define NUMSKINSFXSLOTS (32*NUMSKINSOUNDS)

//
// SoundFX struct.
//
typedef struct sfxinfo_struct sfxinfo_t;

struct sfxinfo_struct
{
	// up to 6-character name
	const char *name;

	// Sfx singularity (only one at a time)
	int singularity;

	// Sfx priority
	int priority;

	// pitch if a link
	int pitch;

	// volume if a link
	int volume;

	// sound data
	void *data;

	// length of sound data
	int length;

	// sound that can be remapped for a skin, indexes skins[].skinsounds
	// 0 up to (NUMSKINSOUNDS-1), -1 = not skin specifc
	int skinsound;

	// this is checked every second to see if sound
	// can be thrown out (if 0, then decrement, if -1,
	// then throw out, if > 0, then it is in use)
	int usefulness;

	// lump number of sfx
	int lumpnum;

	// Zmemory string
	char *zname;
};

//
// MusicInfo struct.
//
typedef struct
{
	// up to 6-character name
	const char *name;

	// lump number of music
	int lumpnum;

	// music data
	void *data;

	// music handle once registered
	int handle;
} musicinfo_t;

// the complete set of sound effects
extern sfxinfo_t S_sfx[];

// the complete set of music
extern musicinfo_t S_music[];

//
// Identifiers for all music in game.
//

// Music list (don't edit this comment!)
typedef enum
{
	mus_None,
	mus_map01m,
	mus_map02m,
	mus_map03m,
	mus_map04m,
	mus_map05m,
	mus_map06m,
	mus_map07m,
	mus_map08m,
	mus_map09m,
	mus_map10m,
	mus_map11m,
	mus_map12m,
	mus_map13m,
	mus_map14m,
	mus_map15m,
	mus_map16m,
	mus_map17m,
	mus_map18m,
	mus_map19m,
	mus_map20m,
	mus_map21m,
	mus_map22m,
	mus_map23m,
	mus_map24m,
	mus_map25m,
	mus_map26m,
	mus_map27m,
	mus_map28m,
	mus_map29m,
	mus_map30m,
	mus_map31m,
	mus_map32m,
	mus_map33m,
	mus_map34m,
	mus_map35m,
	mus_map36m,
	mus_map37m,
	mus_map38m,
	mus_map39m,
	mus_map40m,
	mus_map41m,
	mus_map42m,
	mus_map43m,
	mus_map44m,
	mus_map45m,
	mus_map46m,
	mus_map47m,
	mus_map48m,
	mus_map49m,
	mus_map50m,
	mus_map51m,
	mus_map52m,
	mus_map53m,
	mus_map54m,
	mus_map55m,
	mus_map56m,
	mus_map57m,
	mus_map58m,
	mus_map59m,
	mus_map60m,
	mus_map61m,
	mus_map62m,
	mus_map63m,
	mus_map64m,
	mus_map65m,
	mus_map66m,
	mus_map67m,
	mus_map68m,
	mus_map69m,
	mus_map70m,
	mus_map71m,
	mus_map72m,
	mus_map73m,
	mus_map74m,
	mus_map75m,
	mus_map76m,
	mus_map77m,
	mus_map78m,
	mus_map79m,
	mus_map80m,
	mus_map81m,
	mus_map82m,
	mus_map83m,
	mus_map84m,
	mus_map85m,
	mus_map86m,
	mus_map87m,
	mus_map88m,
	mus_map89m,
	mus_map90m,
	mus_map91m,
	mus_map92m,
	mus_map93m,
	mus_map94m,
	mus_map95m,
	mus_map96m,
	mus_map97m,
	mus_map98m,
	mus_map99m,
	mus_mapa0m,
	mus_mapa1m,
	mus_mapa2m,
	mus_mapa3m,
	mus_mapa4m,
	mus_mapa5m,
	mus_mapa6m,
	mus_mapa7m,
	mus_mapa8m,
	mus_mapa9m,
	mus_mapaam,
	mus_mapabm,
	mus_mapacm,
	mus_mapadm,
	mus_mapaem,
	mus_mapafm,
	mus_mapagm,
	mus_mapahm,
	mus_mapaim,
	mus_mapajm,
	mus_mapakm,
	mus_mapalm,
	mus_mapamm,
	mus_mapanm,
	mus_mapaom,
	mus_mapapm,
	mus_mapaqm,
	mus_maparm,
	mus_mapasm,
	mus_mapatm,
	mus_mapaum,
	mus_mapavm,
	mus_mapawm,
	mus_mapaxm,
	mus_mapaym,
	mus_mapazm,
	mus_mapb0m,
	mus_mapb1m,
	mus_mapb2m,
	mus_mapb3m,
	mus_mapb4m,
	mus_mapb5m,
	mus_mapb6m,
	mus_mapb7m,
	mus_mapb8m,
	mus_mapb9m,
	mus_mapbam,
	mus_mapbbm,
	mus_mapbcm,
	mus_mapbdm,
	mus_mapbem,
	mus_mapbfm,
	mus_mapbgm,
	mus_mapbhm,
	mus_mapbim,
	mus_mapbjm,
	mus_mapbkm,
	mus_mapblm,
	mus_mapbmm,
	mus_mapbnm,
	mus_mapbom,
	mus_mapbpm,
	mus_mapbqm,
	mus_mapbrm,
	mus_mapbsm,
	mus_mapbtm,
	mus_mapbum,
	mus_mapbvm,
	mus_mapbwm,
	mus_mapbxm,
	mus_mapbym,
	mus_mapbzm,
	mus_mapc0m,
	mus_mapc1m,
	mus_mapc2m,
	mus_mapc3m,
	mus_mapc4m,
	mus_mapc5m,
	mus_mapc6m,
	mus_mapc7m,
	mus_mapc8m,
	mus_mapc9m,
	mus_mapcam,
	mus_mapcbm,
	mus_mapccm,
	mus_mapcdm,
	mus_mapcem,
	mus_mapcfm,
	mus_mapcgm,
	mus_mapchm,
	mus_mapcim,
	mus_mapcjm,
	mus_mapckm,
	mus_mapclm,
	mus_mapcmm,
	mus_mapcnm,
	mus_mapcom,
	mus_mapcpm,
	mus_mapcqm,
	mus_mapcrm,
	mus_mapcsm,
	mus_mapctm,
	mus_mapcum,
	mus_mapcvm,
	mus_mapcwm,
	mus_mapcxm,
	mus_mapcym,
	mus_mapczm,
	mus_mapd0m,
	mus_mapd1m,
	mus_mapd2m,
	mus_mapd3m,
	mus_mapd4m,
	mus_mapd5m,
	mus_mapd6m,
	mus_mapd7m,
	mus_mapd8m,
	mus_mapd9m,
	mus_mapdam,
	mus_mapdbm,
	mus_mapdcm,
	mus_mapddm,
	mus_mapdem,
	mus_mapdfm,
	mus_mapdgm,
	mus_mapdhm,
	mus_mapdim,
	mus_mapdjm,
	mus_mapdkm,
	mus_mapdlm,
	mus_mapdmm,
	mus_mapdnm,
	mus_mapdom,
	mus_mapdpm,
	mus_mapdqm,
	mus_mapdrm,
	mus_mapdsm,
	mus_mapdtm,
	mus_mapdum,
	mus_mapdvm,
	mus_mapdwm,
	mus_mapdxm,
	mus_mapdym,
	mus_mapdzm,
	mus_mape0m,
	mus_mape1m,
	mus_mape2m,
	mus_mape3m,
	mus_mape4m,
	mus_mape5m,
	mus_mape6m,
	mus_mape7m,
	mus_mape8m,
	mus_mape9m,
	mus_mapeam,
	mus_mapebm,
	mus_mapecm,
	mus_mapedm,
	mus_mapeem,
	mus_mapefm,
	mus_mapegm,
	mus_mapehm,
	mus_mapeim,
	mus_mapejm,
	mus_mapekm,
	mus_mapelm,
	mus_mapemm,
	mus_mapenm,
	mus_mapeom,
	mus_mapepm,
	mus_mapeqm,
	mus_maperm,
	mus_mapesm,
	mus_mapetm,
	mus_mapeum,
	mus_mapevm,
	mus_mapewm,
	mus_mapexm,
	mus_mapeym,
	mus_mapezm,
	mus_mapf0m,
	mus_mapf1m,
	mus_mapf2m,
	mus_mapf3m,
	mus_mapf4m,
	mus_mapf5m,
	mus_mapf6m,
	mus_mapf7m,
	mus_mapf8m,
	mus_mapf9m,
	mus_mapfam,
	mus_mapfbm,
	mus_mapfcm,
	mus_mapfdm,
	mus_mapfem,
	mus_mapffm,
	mus_mapfgm,
	mus_mapfhm,
	mus_mapfim,
	mus_mapfjm,
	mus_mapfkm,
	mus_mapflm,
	mus_mapfmm,
	mus_mapfnm,
	mus_mapfom,
	mus_mapfpm,
	mus_mapfqm,
	mus_mapfrm,
	mus_mapfsm,
	mus_mapftm,
	mus_mapfum,
	mus_mapfvm,
	mus_mapfwm,
	mus_mapfxm,
	mus_mapfym,
	mus_mapfzm,
	mus_mapg0m,
	mus_mapg1m,
	mus_mapg2m,
	mus_mapg3m,
	mus_mapg4m,
	mus_mapg5m,
	mus_mapg6m,
	mus_mapg7m,
	mus_mapg8m,
	mus_mapg9m,
	mus_mapgam,
	mus_mapgbm,
	mus_mapgcm,
	mus_mapgdm,
	mus_mapgem,
	mus_mapgfm,
	mus_mapggm,
	mus_mapghm,
	mus_mapgim,
	mus_mapgjm,
	mus_mapgkm,
	mus_mapglm,
	mus_mapgmm,
	mus_mapgnm,
	mus_mapgom,
	mus_mapgpm,
	mus_mapgqm,
	mus_mapgrm,
	mus_mapgsm,
	mus_mapgtm,
	mus_mapgum,
	mus_mapgvm,
	mus_mapgwm,
	mus_mapgxm,
	mus_mapgym,
	mus_mapgzm,
	mus_maph0m,
	mus_maph1m,
	mus_maph2m,
	mus_maph3m,
	mus_maph4m,
	mus_maph5m,
	mus_maph6m,
	mus_maph7m,
	mus_maph8m,
	mus_maph9m,
	mus_mapham,
	mus_maphbm,
	mus_maphcm,
	mus_maphdm,
	mus_maphem,
	mus_maphfm,
	mus_maphgm,
	mus_maphhm,
	mus_maphim,
	mus_maphjm,
	mus_maphkm,
	mus_maphlm,
	mus_maphmm,
	mus_maphnm,
	mus_maphom,
	mus_maphpm,
	mus_maphqm,
	mus_maphrm,
	mus_maphsm,
	mus_maphtm,
	mus_maphum,
	mus_maphvm,
	mus_maphwm,
	mus_maphxm,
	mus_maphym,
	mus_maphzm,
	mus_mapi0m,
	mus_mapi1m,
	mus_mapi2m,
	mus_mapi3m,
	mus_mapi4m,
	mus_mapi5m,
	mus_mapi6m,
	mus_mapi7m,
	mus_mapi8m,
	mus_mapi9m,
	mus_mapiam,
	mus_mapibm,
	mus_mapicm,
	mus_mapidm,
	mus_mapiem,
	mus_mapifm,
	mus_mapigm,
	mus_mapihm,
	mus_mapiim,
	mus_mapijm,
	mus_mapikm,
	mus_mapilm,
	mus_mapimm,
	mus_mapinm,
	mus_mapiom,
	mus_mapipm,
	mus_mapiqm,
	mus_mapirm,
	mus_mapism,
	mus_mapitm,
	mus_mapium,
	mus_mapivm,
	mus_mapiwm,
	mus_mapixm,
	mus_mapiym,
	mus_mapizm,
	mus_mapj0m,
	mus_mapj1m,
	mus_mapj2m,
	mus_mapj3m,
	mus_mapj4m,
	mus_mapj5m,
	mus_mapj6m,
	mus_mapj7m,
	mus_mapj8m,
	mus_mapj9m,
	mus_mapjam,
	mus_mapjbm,
	mus_mapjcm,
	mus_mapjdm,
	mus_mapjem,
	mus_mapjfm,
	mus_mapjgm,
	mus_mapjhm,
	mus_mapjim,
	mus_mapjjm,
	mus_mapjkm,
	mus_mapjlm,
	mus_mapjmm,
	mus_mapjnm,
	mus_mapjom,
	mus_mapjpm,
	mus_mapjqm,
	mus_mapjrm,
	mus_mapjsm,
	mus_mapjtm,
	mus_mapjum,
	mus_mapjvm,
	mus_mapjwm,
	mus_mapjxm,
	mus_mapjym,
	mus_mapjzm,
	mus_mapk0m,
	mus_mapk1m,
	mus_mapk2m,
	mus_mapk3m,
	mus_mapk4m,
	mus_mapk5m,
	mus_mapk6m,
	mus_mapk7m,
	mus_mapk8m,
	mus_mapk9m,
	mus_mapkam,
	mus_mapkbm,
	mus_mapkcm,
	mus_mapkdm,
	mus_mapkem,
	mus_mapkfm,
	mus_mapkgm,
	mus_mapkhm,
	mus_mapkim,
	mus_mapkjm,
	mus_mapkkm,
	mus_mapklm,
	mus_mapkmm,
	mus_mapknm,
	mus_mapkom,
	mus_mapkpm,
	mus_mapkqm,
	mus_mapkrm,
	mus_mapksm,
	mus_mapktm,
	mus_mapkum,
	mus_mapkvm,
	mus_mapkwm,
	mus_mapkxm,
	mus_mapkym,
	mus_mapkzm,
	mus_mapl0m,
	mus_mapl1m,
	mus_mapl2m,
	mus_mapl3m,
	mus_mapl4m,
	mus_mapl5m,
	mus_mapl6m,
	mus_mapl7m,
	mus_mapl8m,
	mus_mapl9m,
	mus_maplam,
	mus_maplbm,
	mus_maplcm,
	mus_mapldm,
	mus_maplem,
	mus_maplfm,
	mus_maplgm,
	mus_maplhm,
	mus_maplim,
	mus_mapljm,
	mus_maplkm,
	mus_mapllm,
	mus_maplmm,
	mus_maplnm,
	mus_maplom,
	mus_maplpm,
	mus_maplqm,
	mus_maplrm,
	mus_maplsm,
	mus_mapltm,
	mus_maplum,
	mus_maplvm,
	mus_maplwm,
	mus_maplxm,
	mus_maplym,
	mus_maplzm,
	mus_mapm0m,
	mus_mapm1m,
	mus_mapm2m,
	mus_mapm3m,
	mus_mapm4m,
	mus_mapm5m,
	mus_mapm6m,
	mus_mapm7m,
	mus_mapm8m,
	mus_mapm9m,
	mus_mapmam,
	mus_mapmbm,
	mus_mapmcm,
	mus_mapmdm,
	mus_mapmem,
	mus_mapmfm,
	mus_mapmgm,
	mus_mapmhm,
	mus_mapmim,
	mus_mapmjm,
	mus_mapmkm,
	mus_mapmlm,
	mus_mapmmm,
	mus_mapmnm,
	mus_mapmom,
	mus_mapmpm,
	mus_mapmqm,
	mus_mapmrm,
	mus_mapmsm,
	mus_mapmtm,
	mus_mapmum,
	mus_mapmvm,
	mus_mapmwm,
	mus_mapmxm,
	mus_mapmym,
	mus_mapmzm,
	mus_mapn0m,
	mus_mapn1m,
	mus_mapn2m,
	mus_mapn3m,
	mus_mapn4m,
	mus_mapn5m,
	mus_mapn6m,
	mus_mapn7m,
	mus_mapn8m,
	mus_mapn9m,
	mus_mapnam,
	mus_mapnbm,
	mus_mapncm,
	mus_mapndm,
	mus_mapnem,
	mus_mapnfm,
	mus_mapngm,
	mus_mapnhm,
	mus_mapnim,
	mus_mapnjm,
	mus_mapnkm,
	mus_mapnlm,
	mus_mapnmm,
	mus_mapnnm,
	mus_mapnom,
	mus_mapnpm,
	mus_mapnqm,
	mus_mapnrm,
	mus_mapnsm,
	mus_mapntm,
	mus_mapnum,
	mus_mapnvm,
	mus_mapnwm,
	mus_mapnxm,
	mus_mapnym,
	mus_mapnzm,
	mus_mapo0m,
	mus_mapo1m,
	mus_mapo2m,
	mus_mapo3m,
	mus_mapo4m,
	mus_mapo5m,
	mus_mapo6m,
	mus_mapo7m,
	mus_mapo8m,
	mus_mapo9m,
	mus_mapoam,
	mus_mapobm,
	mus_mapocm,
	mus_mapodm,
	mus_mapoem,
	mus_mapofm,
	mus_mapogm,
	mus_mapohm,
	mus_mapoim,
	mus_mapojm,
	mus_mapokm,
	mus_mapolm,
	mus_mapomm,
	mus_maponm,
	mus_mapoom,
	mus_mapopm,
	mus_mapoqm,
	mus_maporm,
	mus_maposm,
	mus_mapotm,
	mus_mapoum,
	mus_mapovm,
	mus_mapowm,
	mus_mapoxm,
	mus_mapoym,
	mus_mapozm,
	mus_mapp0m,
	mus_mapp1m,
	mus_mapp2m,
	mus_mapp3m,
	mus_mapp4m,
	mus_mapp5m,
	mus_mapp6m,
	mus_mapp7m,
	mus_mapp8m,
	mus_mapp9m,
	mus_mappam,
	mus_mappbm,
	mus_mappcm,
	mus_mappdm,
	mus_mappem,
	mus_mappfm,
	mus_mappgm,
	mus_mapphm,
	mus_mappim,
	mus_mappjm,
	mus_mappkm,
	mus_mapplm,
	mus_mappmm,
	mus_mappnm,
	mus_mappom,
	mus_mapppm,
	mus_mappqm,
	mus_mapprm,
	mus_mappsm,
	mus_mapptm,
	mus_mappum,
	mus_mappvm,
	mus_mappwm,
	mus_mappxm,
	mus_mappym,
	mus_mappzm,
	mus_mapq0m,
	mus_mapq1m,
	mus_mapq2m,
	mus_mapq3m,
	mus_mapq4m,
	mus_mapq5m,
	mus_mapq6m,
	mus_mapq7m,
	mus_mapq8m,
	mus_mapq9m,
	mus_mapqam,
	mus_mapqbm,
	mus_mapqcm,
	mus_mapqdm,
	mus_mapqem,
	mus_mapqfm,
	mus_mapqgm,
	mus_mapqhm,
	mus_mapqim,
	mus_mapqjm,
	mus_mapqkm,
	mus_mapqlm,
	mus_mapqmm,
	mus_mapqnm,
	mus_mapqom,
	mus_mapqpm,
	mus_mapqqm,
	mus_mapqrm,
	mus_mapqsm,
	mus_mapqtm,
	mus_mapqum,
	mus_mapqvm,
	mus_mapqwm,
	mus_mapqxm,
	mus_mapqym,
	mus_mapqzm,
	mus_mapr0m,
	mus_mapr1m,
	mus_mapr2m,
	mus_mapr3m,
	mus_mapr4m,
	mus_mapr5m,
	mus_mapr6m,
	mus_mapr7m,
	mus_mapr8m,
	mus_mapr9m,
	mus_mapram,
	mus_maprbm,
	mus_maprcm,
	mus_maprdm,
	mus_maprem,
	mus_maprfm,
	mus_maprgm,
	mus_maprhm,
	mus_maprim,
	mus_maprjm,
	mus_maprkm,
	mus_maprlm,
	mus_maprmm,
	mus_maprnm,
	mus_maprom,
	mus_maprpm,
	mus_maprqm,
	mus_maprrm,
	mus_maprsm,
	mus_maprtm,
	mus_maprum,
	mus_maprvm,
	mus_maprwm,
	mus_maprxm,
	mus_maprym,
	mus_maprzm,
	mus_maps0m,
	mus_maps1m,
	mus_maps2m,
	mus_maps3m,
	mus_maps4m,
	mus_maps5m,
	mus_maps6m,
	mus_maps7m,
	mus_maps8m,
	mus_maps9m,
	mus_mapsam,
	mus_mapsbm,
	mus_mapscm,
	mus_mapsdm,
	mus_mapsem,
	mus_mapsfm,
	mus_mapsgm,
	mus_mapshm,
	mus_mapsim,
	mus_mapsjm,
	mus_mapskm,
	mus_mapslm,
	mus_mapsmm,
	mus_mapsnm,
	mus_mapsom,
	mus_mapspm,
	mus_mapsqm,
	mus_mapsrm,
	mus_mapssm,
	mus_mapstm,
	mus_mapsum,
	mus_mapsvm,
	mus_mapswm,
	mus_mapsxm,
	mus_mapsym,
	mus_mapszm,
	mus_mapt0m,
	mus_mapt1m,
	mus_mapt2m,
	mus_mapt3m,
	mus_mapt4m,
	mus_mapt5m,
	mus_mapt6m,
	mus_mapt7m,
	mus_mapt8m,
	mus_mapt9m,
	mus_maptam,
	mus_maptbm,
	mus_maptcm,
	mus_maptdm,
	mus_maptem,
	mus_maptfm,
	mus_maptgm,
	mus_mapthm,
	mus_maptim,
	mus_maptjm,
	mus_maptkm,
	mus_maptlm,
	mus_maptmm,
	mus_maptnm,
	mus_maptom,
	mus_maptpm,
	mus_maptqm,
	mus_maptrm,
	mus_maptsm,
	mus_mapttm,
	mus_maptum,
	mus_maptvm,
	mus_maptwm,
	mus_maptxm,
	mus_maptym,
	mus_maptzm,
	mus_mapu0m,
	mus_mapu1m,
	mus_mapu2m,
	mus_mapu3m,
	mus_mapu4m,
	mus_mapu5m,
	mus_mapu6m,
	mus_mapu7m,
	mus_mapu8m,
	mus_mapu9m,
	mus_mapuam,
	mus_mapubm,
	mus_mapucm,
	mus_mapudm,
	mus_mapuem,
	mus_mapufm,
	mus_mapugm,
	mus_mapuhm,
	mus_mapuim,
	mus_mapujm,
	mus_mapukm,
	mus_mapulm,
	mus_mapumm,
	mus_mapunm,
	mus_mapuom,
	mus_mapupm,
	mus_mapuqm,
	mus_mapurm,
	mus_mapusm,
	mus_maputm,
	mus_mapuum,
	mus_mapuvm,
	mus_mapuwm,
	mus_mapuxm,
	mus_mapuym,
	mus_mapuzm,
	mus_mapv0m,
	mus_mapv1m,
	mus_mapv2m,
	mus_mapv3m,
	mus_mapv4m,
	mus_mapv5m,
	mus_mapv6m,
	mus_mapv7m,
	mus_mapv8m,
	mus_mapv9m,
	mus_mapvam,
	mus_mapvbm,
	mus_mapvcm,
	mus_mapvdm,
	mus_mapvem,
	mus_mapvfm,
	mus_mapvgm,
	mus_mapvhm,
	mus_mapvim,
	mus_mapvjm,
	mus_mapvkm,
	mus_mapvlm,
	mus_mapvmm,
	mus_mapvnm,
	mus_mapvom,
	mus_mapvpm,
	mus_mapvqm,
	mus_mapvrm,
	mus_mapvsm,
	mus_mapvtm,
	mus_mapvum,
	mus_mapvvm,
	mus_mapvwm,
	mus_mapvxm,
	mus_mapvym,
	mus_mapvzm,
	mus_mapw0m,
	mus_mapw1m,
	mus_mapw2m,
	mus_mapw3m,
	mus_mapw4m,
	mus_mapw5m,
	mus_mapw6m,
	mus_mapw7m,
	mus_mapw8m,
	mus_mapw9m,
	mus_mapwam,
	mus_mapwbm,
	mus_mapwcm,
	mus_mapwdm,
	mus_mapwem,
	mus_mapwfm,
	mus_mapwgm,
	mus_mapwhm,
	mus_mapwim,
	mus_mapwjm,
	mus_mapwkm,
	mus_mapwlm,
	mus_mapwmm,
	mus_mapwnm,
	mus_mapwom,
	mus_mapwpm,
	mus_mapwqm,
	mus_mapwrm,
	mus_mapwsm,
	mus_mapwtm,
	mus_mapwum,
	mus_mapwvm,
	mus_mapwwm,
	mus_mapwxm,
	mus_mapwym,
	mus_mapwzm,
	mus_mapx0m,
	mus_mapx1m,
	mus_mapx2m,
	mus_mapx3m,
	mus_mapx4m,
	mus_mapx5m,
	mus_mapx6m,
	mus_mapx7m,
	mus_mapx8m,
	mus_mapx9m,
	mus_mapxam,
	mus_mapxbm,
	mus_mapxcm,
	mus_mapxdm,
	mus_mapxem,
	mus_mapxfm,
	mus_mapxgm,
	mus_mapxhm,
	mus_mapxim,
	mus_mapxjm,
	mus_mapxkm,
	mus_mapxlm,
	mus_mapxmm,
	mus_mapxnm,
	mus_mapxom,
	mus_mapxpm,
	mus_mapxqm,
	mus_mapxrm,
	mus_mapxsm,
	mus_mapxtm,
	mus_mapxum,
	mus_mapxvm,
	mus_mapxwm,
	mus_mapxxm,
	mus_mapxym,
	mus_mapxzm,
	mus_mapy0m,
	mus_mapy1m,
	mus_mapy2m,
	mus_mapy3m,
	mus_mapy4m,
	mus_mapy5m,
	mus_mapy6m,
	mus_mapy7m,
	mus_mapy8m,
	mus_mapy9m,
	mus_mapyam,
	mus_mapybm,
	mus_mapycm,
	mus_mapydm,
	mus_mapyem,
	mus_mapyfm,
	mus_mapygm,
	mus_mapyhm,
	mus_mapyim,
	mus_mapyjm,
	mus_mapykm,
	mus_mapylm,
	mus_mapymm,
	mus_mapynm,
	mus_mapyom,
	mus_mapypm,
	mus_mapyqm,
	mus_mapyrm,
	mus_mapysm,
	mus_mapytm,
	mus_mapyum,
	mus_mapyvm,
	mus_mapywm,
	mus_mapyxm,
	mus_mapyym,
	mus_mapyzm,
	mus_mapz0m,
	mus_mapz1m,
	mus_mapz2m,
	mus_mapz3m,
	mus_mapz4m,
	mus_mapz5m,
	mus_mapz6m,
	mus_mapz7m,
	mus_mapz8m,
	mus_mapz9m,
	mus_mapzam,
	mus_mapzbm,
	mus_mapzcm,
	mus_mapzdm,
	mus_mapzem,
	mus_mapzfm,
	mus_mapzgm,
	mus_mapzhm,
	mus_mapzim,
	mus_mapzjm,
	mus_mapzkm,
	mus_mapzlm,
	mus_mapzmm,
	mus_mapznm,
	mus_mapzom,
	mus_mapzpm,
	mus_mapzqm,
	mus_mapzrm,
	mus_mapzsm,
	mus_mapztm,
	mus_mapzum,
	mus_mapzvm,
	mus_mapzwm,
	mus_mapzxm,
	mus_mapzym,
	mus_mapzzm,

	mus_titles, // title screen
	mus_read_m, // intro
	mus_lclear, // level clear
	mus_invinc, // invincibility
	mus_shoes,  // super sneakers
	mus_minvnc, // Mario invincibility
	mus_drown,  // drowning
	mus_gmover, // game over
	mus_xtlife, // extra life
	mus_contsc, // continue screen
	mus_supers, // Super Sonic
	mus_chrsel, // character select
	mus_credit, // credits
	mus_racent, // Race Results

	NUMMUSIC
} musicenum_t;
// Note: If you make music slots go up to 2048 or higher you'll have to change
// how the mapmusic variable is used.

//
// Identifiers for all sfx in game.
//

// List of sounds (don't modify this comment!)
typedef enum
{
	sfx_None,
	sfx_menu1,
	sfx_shotgn,
	sfx_chchng,
	sfx_plasma,
	sfx_spin,
	sfx_putput,
	sfx_pudpud,
	sfx_wtrdng,
	sfx_strpst,
	sfx_rlaunc,
	sfx_rxplod,
	sfx_dmpain,
	sfx_lvpass,
	sfx_firxpl,
	sfx_pstart,
	sfx_pstop,
	sfx_doropn,
	sfx_dorcls,
	sfx_stnmov,
	sfx_swtchn,
	sfx_swtchx,
	sfx_pop,
	sfx_itemup,
	sfx_wpnup,
	sfx_spring,
	sfx_telept,
	sfx_thok,
	sfx_cybdth,
	sfx_spndsh,
	sfx_zoom,
	sfx_tink,
	sfx_bdopn,
	sfx_bdcls,
	sfx_shield,
	sfx_bkpoof,
	sfx_radio,
	sfx_jump,
	sfx_gasp,
	//test water
	sfx_gloop,
	sfx_splash,
	sfx_floush,
	sfx_amwtr1, // Tails
	sfx_amwtr2, // Tails
	sfx_amwtr3, // Tails
	sfx_amwtr4, // Tails
	sfx_amwtr5, // Tails
	sfx_amwtr6, // Tails
	sfx_amwtr7, // Tails
	sfx_amwtr8, // Tails
	sfx_amwtr9, // Tails
	sfx_splish, // Tails 12-08-2000
	sfx_wslap, // Water Slap Tails 12-13-2000
	sfx_steam1, // Tails 06-19-2001
	sfx_steam2, // Tails 06-19-2001
	sfx_cgot, // Got Emerald! Tails 09-02-2001
	sfx_crumbl, // Platform Crumble Tails 03-16-2001

	// Ambient/Active lightning Tails 08-25-2002
	sfx_litng1,
	sfx_litng2,
	sfx_litng3,
	sfx_litng4,
	sfx_athun1,
	sfx_athun2,
	sfx_rainin,

	// Bubble pops Tails 08-25-2002
	sfx_bubbl1,
	sfx_bubbl2,
	sfx_bubbl3,
	sfx_bubbl4,
	sfx_bubbl5,

	// Teleporter mixup sound Tails 08-28-2002
	sfx_mixup,

	// Demo end talking Tails 09-01-2002
	sfx_annon1,
	sfx_annon2,
	sfx_annon3,
	sfx_annon4,
	sfx_annon5,

	// Some new sounds Tails 09-06-2002
	sfx_supert,
	sfx_lose,
	sfx_drown,
	sfx_spkdth,

	// Player taunts/alternate msgs Tails 09-06-2002
	sfx_taunt1,
	sfx_taunt2,
	sfx_taunt3,
	sfx_taunt4,

	sfx_altow1,
	sfx_altow2,
	sfx_altow3,
	sfx_altow4,

	sfx_victr1,
	sfx_victr2,
	sfx_victr3,
	sfx_victr4,

	sfx_altdi1,
	sfx_altdi2,
	sfx_altdi3,
	sfx_altdi4,

	sfx_shldls, // Lost shield Tails 09-06-2002

	// NiGHTS Sounds Tails
	sfx_drill1,
	sfx_drill2,
	sfx_hoop1,
	sfx_hoop2,
	sfx_hoop3,
	sfx_ncitem,
	sfx_ideya,
	sfx_hidden,
	sfx_nbmper,
	sfx_ngskid,
	sfx_prloop,
	sfx_nghurt,
	sfx_ngdone,

	sfx_pogo,
	sfx_gspray,
	sfx_ghit,

	sfx_alarm,

	sfx_fizzle,
	sfx_turpop,
	sfx_trfire,
	sfx_turhit,
	sfx_trpowr,

	sfx_mario1,
	sfx_mario2,
	sfx_mario3,
	sfx_mario4,
	sfx_mario5,
	sfx_mario6,
	sfx_mario7,
	sfx_mario8,
	sfx_mario9,
	sfx_marioa,
	sfx_thwomp,
	sfx_koopfr,

	sfx_ambint,
	sfx_sahitg,
	sfx_spdpad,

	sfx_ncspec, // Tails 12-15-2003

	sfx_wdjump, // Wind shield jump

	sfx_rumble, // Rumbling
	sfx_ambin2, // Another ambient sound

	sfx_deton, // Deton chase sound

	// free slots for S_AddSoundFx() at run-time --------------------
	sfx_freeslot0,
	//
	// ... 60 free sounds here ...
	//
	sfx_lastfreeslot = sfx_freeslot0 + NUMSFXFREESLOTS-1,
	// end of freeslots ---------------------------------------------

	sfx_skinsoundslot0,
	sfx_lastskinsoundslot = sfx_skinsoundslot0 + NUMSKINSFXSLOTS-1,
	NUMSFX
} sfxenum_t;


void S_InitRuntimeSounds(void);
int S_AddSoundFx(const char *name, int singularity, int pitch, boolean skinsound);
void S_RemoveSoundFx(int id);

#endif

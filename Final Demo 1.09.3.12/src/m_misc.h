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
/// \brief Commonly used routines
//	
///	Default Config File.
///	PCX Screenshots.
///	File i/o

#ifndef __M_MISC__
#define __M_MISC__

#include "doomtype.h"
#include "w_wad.h"

// the file where game vars and settings are saved
#ifdef DC
#define CONFIGFILENAME "srb2dc.cfg"
#else
#define CONFIGFILENAME "config.cfg"
#endif

int M_MapNumber(char first, char second);
boolean FIL_WriteFile(char const* name, void* source, size_t length);
int FIL_ReadFile(char const* name, byte** buffer);
void FIL_DefaultExtension (char *path, const char *extension);

boolean FIL_CheckExtension(char *in);
#ifdef HAVE_PNG
boolean M_SavePNG(const char* filename, void* data, int width, int height, byte* palette);
#endif
void M_ScreenShot(void);

extern char configfile[MAX_WADPATH];

void Command_SaveConfig_f(void);
void Command_LoadConfig_f(void);
void Command_ChangeConfig_f(void);

void M_FirstLoadConfig(void);
// save game config: cvars, aliases..
void M_SaveConfig(char *filename);

// s1=s2+s3+s1 (1024 lenghtmax)
void strcatbf(char *s1, const char *s2, const char *s3);

#endif

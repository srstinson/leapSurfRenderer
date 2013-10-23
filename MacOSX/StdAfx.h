// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#if !defined(_STDAFX_H_)
#define _STDAFX_H_

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////        INCLUDES        //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

/*--------------------- Libraries ---------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

///Mmap library. Permits out of core file maintenance for BinFiles.

#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <ctime>//to seed random num generator
#include <limits.h>
#include <float.h>
#include <fstream.h>

//#ifdef OPENGL_RENDERING
//#include "glui.h"
//#endif

/*------------------- Set Library ---------------------*/
#include "set.h"
#include "prime.h"
//#include "conf.h"
#include "defs.h"
#include "mathlib.h"
//#include "funclib.h"


//#include "_lalgebra.h"

/*--------------- Atom Radius Lookup -------------------*/
//#include "atomRadiusLookup.h"

/*--------------- Structure data Structures-------------------*/
//#include "PdbAtom.h"
//#include "aminoAcid.h"
//#include "atomBag.h"
//#include "AtomList.h"
//#include "caList.h"
//#include "pdbParser.h"


#include "SurfaceObject.h"
#include "GeometryParser.h"
//#include "SurfaceOutput.h"
//#include "PocketAlignment.h"

//#include "outputFile.h"


//#ifdef OPENGL_RENDERING
//#include "Renderer.h"
//#include "ObjRenderer.h"
//#endif




////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////        DEFINITIONS        /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


//basic math stuff
#ifndef CROSS
#define CROSS(dest,v1,v2)                       \
               dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
               dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
               dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#endif

#ifndef DOT
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#endif




/*------------Text Parsing #defs ----------*/

#define NUMCOLUMNS 10000					////parsing param for max # of columns

#define ATOMRADIUS 1.7					////atom radius in angstroms
#define ATOMVERTSUBS 16					////# of vertical subdivisions
#define ATOMHORISUBS 15					////# of horizontal subdivisions

#define HIGHLIGHTEDATOMRADIUS 2.0		////atom radius in angstroms of highlighted Atom
#define HIGHLIGHTEDATOMVERTSUBS 15		////# of vertical subdivisions of highlighted Atom
#define HIGHLIGHTEDATOMHORISUBS 13		////# of horizontal subdivisions of highlighted Atom

#define CLIPPINGVOL 75000.0f			///the depth of the back clipping plane of the view frustrum
#define POINTSIZE 5.0					///size to render points
#define LINEWIDTH 2.0					///size to render lines
#define ZDISPLACEMENT -200.0			///standard Z displacement for easy rendering


#endif



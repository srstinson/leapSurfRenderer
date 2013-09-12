// SurfaceOutput.h : Header file for SurfaceOutput.cpp
//  which generates pdb surface files using the modified 
//  Troll library.
//
#ifndef _SURFACE_OUTPUT_H_
#define _SURFACE_OUTPUT_H_

#include "StdAfx.h"

#ifndef OPENGL_RENDERING

////generateSurface:  This function passes the filename of a PDB file and the probe
////                  radius to the modified troll library, which generates an output
////                  Surface.  This function then prints geometry and topology data
////                  about the surface into the file called "outputFileName"
////                  
////                  =========================================================
////                    OUTPUT FORMAT:
////                       -Anywhere in the file, empty lines and line starting with '#' are
////                       considered comments, and are ignored.
////                       -File has 2 sections: geometry and topology
////                  
////                       The geometry section is always first, and starts with:
////                       GEOMETRY: <int>
////                       where <int> is the number of points to be specified.
////                       then there are <int> lines as follows:
////                       <float> <float> <float> <float> <float> <float>
////                       which stand for x,y,z, and xnormal, ynormal, znormal.
////                  
////                       The topology section is always second, and starts with:
////                       TOPOLOGY: <int>
////                       where <int> specifies the number of triangles on the surface
////                       Then there are <int> lines as follows:
////                       <int> <int> <int>
////                       Each int stands for the 3 corners of the triangle
////                       and is an index into the array of points provided in the
////                       Geometry section.  I.e. the geometry section is indexed
////                       starting at zero, and ending at (size-1).
////                  =========================================================
void generateSurface(char * pdbFileInput, double probeRadius, char * outputFileName);

////generateSurface:  This version of this function takes a PDB file and generates a SurfaceObject
////                  
////                  =========================================================
////                    OUTPUT FORMAT:  A SurfaceObject
////                  =========================================================
SurfaceObject * generateSurface(char * pdbFileInput, double probeRadius);

////generateTmesh:	This function passes the filename of a PDB file and the probe radius
////				to the modified troll library which generates an output surface and
////				an electostatic potential for every position on the surface.
////				This function then prints output in the "tmesh" format.
////
////				=============================================================
////				  OUTPUT FORMAT: A Tmesh File
////				=============================================================
void generateTmesh(char * pdbFileInput, double probeRadius, char * outputFileName, char * INSIGHTgrid);

#endif



////generateSURF:  This function generates a SURF file based on a surfaceObject and a set of
////                  point indices that reference a patch on the surface.  The output is a
////                  SURF file that contains only the points relevant to render the patch.
////                  If the set of points is NULL, the entire surface is returned.
////                  
////                  =========================================================
////                    OUTPUT FORMAT:  A SURF file (See above)
////                  =========================================================
void generateSURF(SurfaceObject * surf, set_t points, char * outputFileName);





#endif





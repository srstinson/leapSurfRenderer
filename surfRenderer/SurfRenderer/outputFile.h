

#ifndef OUTPUT_FILE
#define OUTPUT_FILE


#include "StdAfx.h"


void outputFileAtomList(char * outputFileHead, set_t lists, set_t list_pos, set_t list_rot);
void outputFileSurfObj(char * outputFileHead, set_t surfs, set_t surf_pos, set_t surf_rot);

//void outputFileVolumePrimitives(char * outputFileHead, set_t spheres, set_t radii, double * centroid);
void outputFileVolumePrimitives(char * outputFileHead, set_t spheres, set_t radii, double * centroid, set_t cubes, set_t cubeSize );
#endif




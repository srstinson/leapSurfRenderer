
#ifndef GEOMETRYPARSER_H
#define GEOMETRYPARSER_H

#include "StdAfx.h"

class SurfaceObject;

typedef struct Vertex {
  float x,y,z;             /* the usual 3-space position of a vertex */
} Vertex;

typedef struct Face {
  unsigned char intensity; /* this user attaches intensity to faces */
  unsigned char nverts;    /* number of vertex indices in list */
  int *verts;              /* vertex index list */
} Face;

///Parse the geometry file
SurfaceObject * parseGeometryFile(char * fileName); 

///find out how many points on the surface
int getNumberOfPoints(FILE * surfaceFile);

///get the vectors and surface normals on the surface
double * getSurfaceGeometryAndNormals(FILE * surfaceFile, int numPts);

///get the number of triangles
int getNumberOfTriangles(FILE * surfaceFile);

///get the triangles
int * getTopology(FILE * surfaceFile, int numTris);

///gets the colors
double * getColors(FILE * surfaceFile, int numColors);


#endif




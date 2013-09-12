//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#ifndef SURFACE_RECONSTRUCTION
#define SURFACE_RECONSTRUCTION

#include "StdAfx.h"

	///Uses union find to identify interior cavities (disconnected surfaces)
	///and eliminate them.  Expects that the structure with the most triangles
	///is the exterior surface.  (this is a short cut)
	int * eliminateInteriorCavities(double * pts, int numPts, int * triangles, int numberTriangles, int * numTriangles);


	///this union find groups together all connected patches, and returns them in a set of sets
	set_t findDisparatePatches(double * inputPts, int inputNumPts, int * inputTriangles, int numberTriangles);


	///this function surveys the areas of triangles in the surface, and outputs the results in a histogram.
	void surveyTriangleAreas(SurfaceObject * obj, int numBars);

	///this function surveys the edge Lengths of triangles in the surface, and outputs the results in a histogram. (all edges appear twice)
	void surveyTriangleEdges(SurfaceObject * obj, int numBars);

#endif




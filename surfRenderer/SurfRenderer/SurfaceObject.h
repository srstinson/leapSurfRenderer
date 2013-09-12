// SurfaceObject.h: interface for the SurfaceObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SURFACEOBJECT_H
#define SURFACEOBJECT_H

#include "StdAfx.h"

class SurfaceObject  
{
public:
	bool renderable;
	double * centroid;
	int numPoints;
	double * surfacePoints;
	double * surfaceNormals;		///these averaged normals are used for rendering
	int numTriangles;
	int * triangles;
	double * triangleNormals;	///these normals are used for flat shading and interior checking
	set_t highlights;
	set_t edges; 				///edge highlights

	double * colors;			///optional colors, initialized only through separate request.  One vector for each pt.

	SurfaceObject(int numPts, double * ptsAndNorms, int numTris, int * inputTris, bool elimIntCavities);
	SurfaceObject(int numPts, double * pts, double * norms, int numTris, int * tris, double * triangleNorms);

	virtual ~SurfaceObject();

	///returns the coords of the requested triangle
	///returns null if out of range.
	///notice that the triangle must be formatted in this way in the array (3 then 3 then 3)
	double * getTriangle(int num); 


	///identifies edges which are not surrounded by triangles - locations where the surface
	///is non manifold.
	///This turns the edges variable non-null.
	///
	///THIS FUNCTION IS CURRENTLY BROKEN
	//
	void identifyNonManifoldEdges(void);
	///helper function tells you how int elements are identical between two sets.
	int countNumCommon(set_t set1, set_t set2);

	///This function flips the normals of the surfaceObject backwards 
	///so that we can treat it as a negative volume
	void flipNormals();
	
	///add colors
	void addColors(double * c);

	/////////////////////////////
	//Rendering, only if compiling with OpenGL
	#ifdef OPENGL_RENDERING
	void draw(bool drawPoints, bool drawLines, bool drawTransparent, bool pocketView, double * offset, double * c);
	#endif
	/////////////////////////////


};

#endif 




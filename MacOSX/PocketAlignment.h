// PocketAlignment.h: interface for the PocketAlignment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(POCKET_ALIGNMENT_H)
#define POCKET_ALIGNMENT_H

#include "StdAfx.h"

class Renderer;
class PocketAlignment  
{
	public:

	///variables////////////////////////////////////////
	set_t pockets;			///this holds SurfaceObjects
	set_t aLists;			///this holds atomLists
	set_t alignments;		///this holds double * alignments
	set_t calists;			///this holds caLists
	set_t residues;			///this holds set_t arrays of int residues
	set_t names;			///this holds char * filenames for rendering
	set_t colors;			///this holds a color vector for each pocket.
	set_t rmsds;			///this holds pointers to double arrays of size one, containing RMSD
	int numPockets;			//the number of pocket surfaces to align

	float * centroid;		///this is the center of the first pocket, that everyone else is aligned to.

	///functions////////////////////////////////////////
	PocketAlignment( char * fileName );
	virtual ~PocketAlignment();

	//Rendering, only if compiling with OpenGL
	#ifdef OPENGL_RENDERING
	void draw(int ** renderSwitch, int ** transparencySwitch);
	#endif
	//Rendering, only if compiling with OpenGL

	///converts a list of integers into a set containing those integers
	set_t parseIntegerList(char * string);

	///generates the largest CA mapping of one list of residues onto another, then generates
	///the LRMSD alignment from the second structure onto the first, and outputs the align.
	///the LRMSD is output using the RMSD pointer
	double * generateAlignment(set_t list1, caList * struct1, set_t list2, caList * struct2, double * LRMSD);

	void insertDataIntoRenderer(Renderer * rend);


};


#endif 

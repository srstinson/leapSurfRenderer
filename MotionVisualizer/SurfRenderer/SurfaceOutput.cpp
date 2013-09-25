// SurfaceOutput.cpp : Source file for SurfaceOutput.h
//  which generates pdb surface files using the modified 
//  Troll library.
//

#include "SurfaceOutput.h"

#ifndef OPENGL_RENDERING

using namespace Troll;

////                  
////generateSurface:  This function passes the filename of a PDB file and the probe
////                  radius to the modified troll library, which generates an output
////                  Surface.  This function then prints geometry and topology data
////                  about the surface into the file called "outputFileName"
////                  
////                  Inputs:
////                     char * pdbFileInput           filename of the input PDB file
////                     double probeRadius            decimal radius of the probe
////                     char * outputFileName         filename of the output surface file
////                  
////                  Outputs:
////                     Void - only a file is generated
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
////                  
void generateSurface(char * pdbFileInput, double probeRadius, char * outputFileName)
{
	int i = 0;
	int j = 0;
	
	printf("TROLLBASE INTERFACE MILESTONE 0: Nothing Yet\n");

	PDBFile mypdbFile(pdbFileInput, allatoms);
	Structure mystruct;
	
	printf("TROLLBASE INTERFACE MILESTONE 1: Initialized PDBFile\n");

	///parse PDB file
	mypdbFile >> mystruct;

	printf("TROLLBASE INTERFACE MILESTONE 2: Parsed PDBfile\n");

	///retrieve Probe Radii	
	float surfaceProbeRadius = (float) probeRadius;

	printf("TROLLBASE INTERFACE MILESTONE 3: Retrieved Radii\n");

	///Create Inner Molecular surface
	MolecularSurface * trollSurfInner = new MolecularSurface(&mystruct, allatoms);
	trollSurfInner->pr = surfaceProbeRadius;
	trollSurfInner->Build();

	printf("TROLLBASE INTERFACE MILESTONE 4: Created Inner surface\n");

	///get vertices needed for screen
	int numVerts = trollSurfInner->getNumVerticesOrNormals();
	double * innerVerts = trollSurfInner->getVertices();		///notice that this returns double* arrays with 3 x numVerts entries
	double * innerNorms = trollSurfInner->getNormals();		///notice that this returns double* arrays with 3 x numVerts entries

	printf("TROLLBASE INTERFACE MILESTONE 5: Extracted vertices from inner surface\n");

	///get interconnects for triangls
	int numElements = trollSurfInner->selement.size();
	int numTriangles = 0;								///Note this is not the number of triangles, but 3x the # of triangles
	for(i = 0; i<numElements; i++){
		numTriangles = numTriangles + trollSurfInner->selement[i]->nt;
	}

	printf("TROLLBASE INTERFACE MILESTONE 6: Counted the number of triangles\n");

	///Notice that Trollbase remembers the total number of point entries (nt), not the 
	///the number of triangles.
	int * surfTriangles = new int[numTriangles];
	int counter = 0;
	for(i = 0; i<numElements; i++){
		SurfaceElement * tempSurfElement = trollSurfInner->selement[i];
		for(j = 0; j<tempSurfElement->nt; j++){
			surfTriangles[counter] = tempSurfElement->triangle[j];
			counter++;
			if(counter > numTriangles){
				printf("ERROR: incorrect number of surface element triangles\n");
			}
		}
	}	

	///check for data uniformity
	if( (numTriangles%3) != 0 ){ 
		printf("ERROR: Number of triangle indices is not divisible by 3!\n"); 
		exit(0);
	}

	printf("TROLLBASE INTERFACE MILESTONE 8: Recorded triangles\n");
	printf("Now Generating Output:\n");

	///Compose the file
	char * tempString = new char[300];
	std::ofstream * currentOutputFile = new std::ofstream(outputFileName);

	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "## Surface File Generated by Brian Chen and modified Trolbase Lib    ##\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "\n";

	///output original info
	sprintf(tempString, "#Original PDB file: %s\n", pdbFileInput);
	( *currentOutputFile ) << tempString;

	///generate the Geometry Header
	( *currentOutputFile ) << "########################################\n";
	( *currentOutputFile ) << "###  ##   ##  ## ### #   #   #   ## # ##\n";
	( *currentOutputFile ) << "## #### ### ## #  #  # #### ## ## # # ##\n";
	( *currentOutputFile ) << "## #  #  ## ## # # # #  ### ##   ### ###\n";
	( *currentOutputFile ) << "## ## # ### ## # ### # #### ## # ### ###\n";
	( *currentOutputFile ) << "###  ##   ##  ## ### #   ## ## ## ## ###\n";
	( *currentOutputFile ) << "########################################\n";
	sprintf(tempString, "GEOMETRY: %i\n", numVerts);
	( *currentOutputFile ) << tempString;

	///generate the Geometry
	for(i = 0; i<numVerts; i++){
		sprintf(tempString, "%lf %lf %lf %lf %lf %lf\n", 
			innerVerts[3*i+0], innerVerts[3*i+1], innerVerts[3*i+2], 
			innerNorms[3*i+0], innerNorms[3*i+1], innerNorms[3*i+2] );
		( *currentOutputFile ) << tempString;
	}
	
	///generate the Topology Header
	( *currentOutputFile ) << "########################################\n";
	( *currentOutputFile ) << "##   ##  ##   ###  ## ####  ###  ## # ##\n";
	( *currentOutputFile ) << "### ## ## # ## # ## # ### ## # #### # ##\n";
	( *currentOutputFile ) << "### ## ## #   ## ## # ### ## # #  ## ###\n";
	( *currentOutputFile ) << "### ## ## # #### ## # ### ## # ## ## ###\n";
	( *currentOutputFile ) << "### ###  ## #####  ##   ##  ###  ### ###\n";
	( *currentOutputFile ) << "########################################\n";
	sprintf(tempString, "TOPOLOGY: %i\n", numTriangles/3);
	( *currentOutputFile ) << tempString;
	
	int point1Idx, point2Idx, point3Idx;
	for(i = 0; i<(numTriangles/3); i++){
		point1Idx = surfTriangles[3*i+0];			///get the triangle indices from surfTriangles
		point2Idx = surfTriangles[3*i+1];
		point3Idx = surfTriangles[3*i+2];

		sprintf(tempString, "%i %i %i\n", point1Idx, point2Idx, point3Idx);
		( *currentOutputFile ) << tempString;
	}

	( *currentOutputFile ) << "\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "## Surface File Generated by Brian Chen and modified Trolbase Lib    ##\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";

	///done outputting.  Close file.
	( *currentOutputFile ).close();

}

SurfaceObject * generateSurface(char * pdbFileInput, double probeRadius)
{
	int i = 0;
	int j = 0;
	
	printf("TROLLBASE INTERFACE MILESTONE 0: Nothing Yet\n");
	PDBFile mypdbFile(pdbFileInput, allatoms);
	Structure mystruct;
	
	printf("TROLLBASE INTERFACE MILESTONE 1: Initialized PDBFile\n");
	///parse PDB file
	mypdbFile >> mystruct;

	printf("TROLLBASE INTERFACE MILESTONE 2: Parsed PDBfile\n");
	///retrieve Probe Radii	
	float surfaceProbeRadius = (float) probeRadius;

	printf("TROLLBASE INTERFACE MILESTONE 3: Retrieved Radii\n");
	///Create Inner Molecular surface
	MolecularSurface * trollSurfInner = new MolecularSurface(&mystruct, allatoms);
	trollSurfInner->pr = surfaceProbeRadius;
	trollSurfInner->Build();

	printf("TROLLBASE INTERFACE MILESTONE 4: Created Inner surface\n");
	///get vertices needed for screen
	int numVerts = trollSurfInner->getNumVerticesOrNormals();
	double * innerVerts = trollSurfInner->getVertices();		///notice that this returns double* arrays with 3 x numVerts entries
	double * innerNorms = trollSurfInner->getNormals();		///notice that this returns double* arrays with 3 x numVerts entries

	printf("TROLLBASE INTERFACE MILESTONE 5: Extracted vertices from inner surface\n");
	///get interconnects for triangls
	int numElements = trollSurfInner->selement.size();
	int numTriangles = 0;								///Note this is not the number of triangles, but 3x the # of triangles
	for(i = 0; i<numElements; i++){
		numTriangles = numTriangles + trollSurfInner->selement[i]->nt;
	}

//	printf("TROLLBASE INTERFACE MILESTONE 6: Counted the number of triangles\n");
	///Notice that Trollbase remembers the total number of point entries (nt), not the 
	///the number of triangles.
	int * surfTriangles = new int[numTriangles];
	int counter = 0;
	for(i = 0; i<numElements; i++){
		SurfaceElement * tempSurfElement = trollSurfInner->selement[i];
		for(j = 0; j<tempSurfElement->nt; j++){
			surfTriangles[counter] = tempSurfElement->triangle[j];
			counter++;
			if(counter > numTriangles){
				printf("ERROR: incorrect number of surface element triangles\n");
			}
		}
	}
	///check for data uniformity
	if( (numTriangles%3) != 0 ){ printf("ERROR: Number of triangle indices is not divisible by 3!\n"); exit(0); }

	///calculate triangle normals
	double * p0 = new double[3];
	double * p1 = new double[3];
	double * p2 = new double[3];
	double * v1 = new double[3];
	double * v2 = new double[3];
	double * cross = new double[3];
	double * tempNormal = new double[3];
	double * triangleNorms = new double[numTriangles];
	for(i = 0; i<numTriangles/3; i++){
		p0[0] = innerVerts[3*surfTriangles[3*i+0]+0];
		p0[1] = innerVerts[3*surfTriangles[3*i+0]+1];
		p0[2] = innerVerts[3*surfTriangles[3*i+0]+2];

		p1[0] = innerVerts[3*surfTriangles[3*i+1]+0];
		p1[1] = innerVerts[3*surfTriangles[3*i+1]+1];
		p1[2] = innerVerts[3*surfTriangles[3*i+1]+2];

		p2[0] = innerVerts[3*surfTriangles[3*i+2]+0];
		p2[1] = innerVerts[3*surfTriangles[3*i+2]+1];
		p2[2] = innerVerts[3*surfTriangles[3*i+2]+2];

		v1[0] = p1[0]-p0[0];	v1[1] = p1[1]-p0[1];	v1[2] = p1[2] - p0[2];
		v2[0] = p2[0]-p0[0];	v2[1] = p2[1]-p0[1];	v2[2] = p2[2] - p0[2];
		
		tempNormal[0] = innerNorms[3*surfTriangles[3*i+0]+0];
		tempNormal[1] = innerNorms[3*surfTriangles[3*i+0]+1];
		tempNormal[2] = innerNorms[3*surfTriangles[3*i+0]+2];

		CROSS(cross,v1,v2);
		if( DOT(cross, tempNormal)<0 ){	///if the vectors face opposite way, reverse the x-product
			printf("WARNING: (i = %i) Normals deviate from averaged Normals (%i %i %i)!\n", i, surfTriangles[3*i+0], surfTriangles[3*i+1], surfTriangles[3*i+2]);
			printf("TEMPNORMAL: %lf %lf %lf (point: %i)\n", tempNormal[0], tempNormal[1], tempNormal[2], surfTriangles[3*i+0] );
			printf("CROSS: %lf %lf %lf\n", cross[0], cross[1], cross[2]);

			CROSS(cross,v2,v1);
			printf("CROSS: %lf %lf %lf\n", cross[0], cross[1], cross[2]);
		}
		
		double * tempVec = normalizeVector(cross);
		
		triangleNorms[3*i+0] = tempVec[0];
		triangleNorms[3*i+1] = tempVec[1];
		triangleNorms[3*i+2] = tempVec[2];
		delete[](tempVec);
	}

	////////Create surface object
	////////
//	SurfaceObject * result = new SurfaceObject(numVerts, innerVerts, innerNorms, numTriangles/3, surfTriangles, triangleNorms);

	double * ptsAndNorms = new double[6*numVerts];
	for(i = 0; i<numVerts; i++){
		ptsAndNorms[6*i+0] = innerVerts[3*i+0];
		ptsAndNorms[6*i+1] = innerVerts[3*i+1];
		ptsAndNorms[6*i+2] = innerVerts[3*i+2];
		ptsAndNorms[6*i+3] = innerNorms[3*i+0];
		ptsAndNorms[6*i+4] = innerNorms[3*i+1];
		ptsAndNorms[6*i+5] = innerNorms[3*i+2];
	}
	SurfaceObject * result = new SurfaceObject(numVerts, ptsAndNorms, numTriangles/3, surfTriangles, true);

	delete[](p0);
	delete[](p1);
	delete[](p2);
	delete[](v1);
	delete[](v2);
	delete[](cross);
	delete[](tempNormal);
	delete[](triangleNorms);
	delete[](innerVerts);
	delete[](innerNorms);
	delete[](ptsAndNorms);

	return result;
}


////generateTmesh:	This function passes the filename of a PDB file and the probe radius
////				to the modified troll library which generates an output surface and
////				an electostatic potential for every position on the surface.
////				This function then prints output in the "tmesh" format.
////
////				=============================================================
////				  OUTPUT FORMAT:
////				=============================================================
void generateTmesh(char * pdbFileInput, double probeRadius, char * outputFileName, char * INSIGHTgrid)
{
	int i = 0;
	int j = 0;
	
	printf("TROLLBASE INTERFACE MILESTONE 0: Nothing Yet\n");

	PDBFile mypdbFile(pdbFileInput, allatoms);
	Structure mystruct;
	
	printf("TROLLBASE INTERFACE MILESTONE 1: Initialized PDBFile\n");

	///parse PDB file
	mypdbFile >> mystruct;

	printf("TROLLBASE INTERFACE MILESTONE 2: Parsed PDBfile\n");

	///retrieve Probe Radii	
	float surfaceProbeRadius = (float) probeRadius;

	printf("TROLLBASE INTERFACE MILESTONE 3: Retrieved Radii\n");

	///Create Inner Molecular surface
	MolecularSurface * trollSurfInner = new MolecularSurface(&mystruct, allatoms);
	trollSurfInner->pr = surfaceProbeRadius;
	trollSurfInner->Build();

	printf("TROLLBASE INTERFACE MILESTONE 4: Created Inner surface\n");

	///get vertices needed for screen
	int numVerts = trollSurfInner->getNumVerticesOrNormals();
	double * innerVerts = trollSurfInner->getVertices();		///notice that this returns double* arrays with 3 x numVerts entries
	double * innerNorms = trollSurfInner->getNormals();		///notice that this returns double* arrays with 3 x numVerts entries
	
	printf("TROLLBASE INTERFACE MILESTONE 4A: Generating PHIMAP DATA\n");
	Phimap * pmap = new Phimap(&mystruct, allatoms);
	pmap->LoadInsight(INSIGHTgrid);

	///print extents
	double mx1 = HUGE_VAL;		double mx2 = pmap->origin.x;
	double Mx1 = -HUGE_VAL;		double Mx2 = pmap->extent.x;
	double my1 = HUGE_VAL;		double my2 = pmap->origin.y;
	double My1 = -HUGE_VAL;		double My2 = pmap->extent.y;
	double mz1 = HUGE_VAL;		double mz2 = pmap->origin.z;
	double Mz1 = -HUGE_VAL;		double Mz2 = pmap->extent.z;

	for(i = 0; i<numVerts; i++){
		if(innerVerts[3*i+0] < mx1){ mx1 = innerVerts[3*i+0]; }
		if(innerVerts[3*i+0] > Mx1){ Mx1 = innerVerts[3*i+0]; }
		if(innerVerts[3*i+1] < my1){ my1 = innerVerts[3*i+1]; }
		if(innerVerts[3*i+1] > My1){ My1 = innerVerts[3*i+1]; }
		if(innerVerts[3*i+2] < mz1){ mz1 = innerVerts[3*i+2]; }
		if(innerVerts[3*i+2] > Mz1){ Mz1 = innerVerts[3*i+2]; }
	}

	bool extentTest = false;
	if( ((Mx2-mx2)-(Mx1-mx1)) < 0 ){
		printf("Surface larger than X extents!\n"); 
		printf("PHIMAP EXTENTS X: %lf %lf    SURFACE EXTENTS X: %lf %lf    DIFFERENCE: %lf\n", mx2, Mx2, mx1, Mx1, ((Mx2-mx2)-(Mx1-mx1)));
		extentTest = true;
	}
	if( ((My2-my2)-(My1-my1)) < 0 ){
		printf("Surface larger than Y extents!\n"); 
		printf("PHIMAP EXTENTS Y: %lf %lf    SURFACE EXTENTS Y: %lf %lf    DIFFERENCE: %lf\n", my2, My2, my1, My1, ((My2-my2)-(My1-my1)));
		extentTest = true;
	}
	if( ((Mz2-mz2)-(Mz1-mz1)) < 0 ){
		printf("Surface larger than Z extents!\n"); 
		printf("PHIMAP EXTENTS Z: %lf %lf    SURFACE EXTENTS Z: %lf %lf    DIFFERENCE: %lf\n", mz2, Mz2, mz1, Mz1, ((Mz2-mz2)-(Mz1-mz1)));
		extentTest = true;
	}

	if(extentTest){
//	printf("MIDPOINT: %lf %lf %lf\n", pmap->midpoint.x, pmap->midpoint.y, pmap->midpoint.z);
//	printf("extent: %lf %lf %lf\n", pmap->extent.x, pmap->extent.y, pmap->extent.z);

		double mx3 = HUGE_VAL;
		double Mx3 = -HUGE_VAL;
		double my3 = HUGE_VAL;
		double My3 = -HUGE_VAL;
		double mz3 = HUGE_VAL;
		double Mz3 = -HUGE_VAL;
	
		for(i = 0; i<(&mystruct)->atom.size(); i++){
			if((&mystruct)->atom[i]->pos.x < mx3){ mx3 = (&mystruct)->atom[i]->pos.x; }
			if((&mystruct)->atom[i]->pos.x > Mx3){ Mx3 = (&mystruct)->atom[i]->pos.x; }
			if((&mystruct)->atom[i]->pos.y < my3){ my3 = (&mystruct)->atom[i]->pos.y; }
			if((&mystruct)->atom[i]->pos.y > My3){ My3 = (&mystruct)->atom[i]->pos.y; }
			if((&mystruct)->atom[i]->pos.z < mz3){ mz3 = (&mystruct)->atom[i]->pos.z; }
			if((&mystruct)->atom[i]->pos.z > Mz3){ Mz3 = (&mystruct)->atom[i]->pos.z; }
		}
	
		printf("STRUCTURE EXTENTS X: %lf %lf\n", mx3, Mx3);
		printf("STRUCTURE EXTENTS Y: %lf %lf\n", my3, My3);
		printf("STRUCTURE EXTENTS Z: %lf %lf\n", mz3, Mz3);
	}



	///get centroid; (this doesnt seem necessary anymore) - left it out.
	int na=(&mystruct)->atom.size();
	float n=0.0;
	Vector midpoint=zerovector;
//	for(i=0;i<na;i++){
//		midpoint=midpoint+(&mystruct)->atom[i]->pos;
//		n+=1.0;
//	}
//	midpoint=midpoint/n;
	///compute
	double * potentials = new double[numVerts];	//store potentials here
	
	for(i = 0; i<numVerts; i++){
		potentials[i] = pmap->getPotential(innerVerts[3*i+0]-midpoint.x, innerVerts[3*i+1]-midpoint.y, innerVerts[3*i+2]-midpoint.z);
	}

	printf("TROLLBASE INTERFACE MILESTONE 5: Extracted vertices from inner surface\n");

	///get interconnects for triangls
	int numElements = trollSurfInner->selement.size();
	int numTriangles = 0;								///Note this is not the number of triangles, but 3x the # of triangles
	for(i = 0; i<numElements; i++){
		numTriangles = numTriangles + trollSurfInner->selement[i]->nt;
	}

	printf("TROLLBASE INTERFACE MILESTONE 6: Counted the number of triangles\n");

	///Notice that Trollbase remembers the total number of point entries (nt), not the 
	///the number of triangles.
	int * surfTriangles = new int[numTriangles];
	int counter = 0;
	for(i = 0; i<numElements; i++){
		SurfaceElement * tempSurfElement = trollSurfInner->selement[i];
		for(j = 0; j<tempSurfElement->nt; j++){
			surfTriangles[counter] = tempSurfElement->triangle[j];
			counter++;
			if(counter > numTriangles){
				printf("ERROR: incorrect number of surface element triangles\n");
			}
		}
	}	

	///check for data uniformity
	if( (numTriangles%3) != 0 ){ 
		printf("ERROR: Number of triangle indices is not divisible by 3!\n"); 
		exit(0);
	}

	printf("TROLLBASE INTERFACE MILESTONE 8: Recorded triangles\n");
	printf("Now Generating TMESH Output:\n");

	///Compose the file
	char * tempString = new char[300];
	std::ofstream * currentOutputFile = new std::ofstream(outputFileName);

/////########################################////
/////###  ##   ##  ## ### #   #   #   ## # ##////
/////## #### ### ## #  #  # #### ## ## # # ##////
/////## #  #  ## ## # # # #  ### ##   ### ###////
/////## ## # ### ## # ### # #### ## # ### ###////
/////###  ##   ##  ## ### #   ## ## ## ## ###////
/////########################################////

	///print the number of vertices
	sprintf(tempString, "%i\n", numVerts);
	( *currentOutputFile ) << tempString;

	///generate the Geometry
	///print the vertex coords, vertex norms, and 3 data values (potentials in 2nd data val)
	for(i = 0; i<numVerts; i++){
		sprintf(tempString, "%lf %lf %lf %lf %lf %lf %i %lf %i\n", 
			innerVerts[3*i+0], innerVerts[3*i+1], innerVerts[3*i+2], 
			innerNorms[3*i+0], innerNorms[3*i+1], innerNorms[3*i+2],
			0, potentials[i], 0 );
		( *currentOutputFile ) << tempString;
	}

/////########################################////
/////##   ##  ##   ###  ## ####  ###  ## # ##////
/////### ## ## # ## # ## # ### ## # #### # ##////
/////### ## ## #   ## ## # ### ## # #  ## ###////
/////### ## ## # #### ## # ### ## # ## ## ###////
/////### ###  ## #####  ##   ##  ###  ### ###////
/////########################################////

	///print the number of triangles
	sprintf(tempString, "TOPOLOGY: %i\n", numTriangles/3);
	( *currentOutputFile ) << tempString;

	///generate the triangles
	int point1Idx, point2Idx, point3Idx;
	for(i = 0; i<(numTriangles/3); i++){
		point1Idx = surfTriangles[3*i+0];			///get the triangle indices from surfTriangles
		point2Idx = surfTriangles[3*i+1];
		point3Idx = surfTriangles[3*i+2];

		sprintf(tempString, "3\n%i\n%i\n%i\n", point1Idx, point2Idx, point3Idx);
		( *currentOutputFile ) << tempString;
	}
	
	///done outputting.  Close file.
	( *currentOutputFile ).close();


}


#endif 






////generateSURF:  This function generates a SURF file based on a surfaceObject and a set of
////                  point indices that reference a patch on the surface.  The output is a
////                  SURF file that contains only the points relevant to render the patch.
////                  If the set of points is NULL, the entire surface is returned.
////                  
////                  =========================================================
////                    OUTPUT FORMAT:  A SURF file (See above)
////                  =========================================================
void generateSURF(SurfaceObject * surf, set_t points, char * outputFileName)
{
	int i = 0;
	char * tempString = new char[300];
	std::ofstream * currentOutputFile = new std::ofstream(outputFileName);
	
	int numVerts = surf->numPoints;
	if(points != NULL){
		numVerts = size_set(points);
	}

	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "## Surface File Generated by Brian Chen and modified Trollbase Lib   ##\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "\n";
	///output original info
	sprintf(tempString, "#Original PDB file: none (Surface computations)\n");
	( *currentOutputFile ) << tempString;

	///generate the Geometry Header
	( *currentOutputFile ) << "########################################\n";
	( *currentOutputFile ) << "###  ##   ##  ## ### #   #   #   ## # ##\n";
	( *currentOutputFile ) << "## #### ### ## #  #  # #### ## ## # # ##\n";
	( *currentOutputFile ) << "## #  #  ## ## # # # #  ### ##   ### ###\n";
	( *currentOutputFile ) << "## ## # ### ## # ### # #### ## # ### ###\n";
	( *currentOutputFile ) << "###  ##   ##  ## ### #   ## ## ## ## ###\n";
	( *currentOutputFile ) << "########################################\n";
	sprintf(tempString, "GEOMETRY: %i\n", numVerts);
	( *currentOutputFile ) << tempString;

	///generate the Geometry
	int * map = NULL;
	int * rmap = NULL;
	///if points is null, jsut output the geometry
	if(points==NULL){
		for(i = 0; i<numVerts; i++){
			sprintf(tempString, "%lf %lf %lf %lf %lf %lf\n", 
				surf->surfacePoints[3*i+0], surf->surfacePoints[3*i+1], surf->surfacePoints[3*i+2], 
				surf->surfaceNormals[3*i+0], surf->surfaceNormals[3*i+1], surf->surfaceNormals[3*i+2] );
			( *currentOutputFile ) << tempString;
		}
	}
	//if points is not null, prepare forward and backward maps so that we cna quickly process the triangles.
	//then generate only the points used by this pocket.
	else{
		map = new int[size_set(points)];
		rmap = new int[surf->numPoints];
		for(i = 0; i<surf->numPoints; i++){ rmap[i] = -1; }
		for(i = 0; i<size_set(points); i++){
			map[i] = points[i];
			rmap[points[i]] = i;
		}
		for(i = 0; i<numVerts; i++){
			int tempVal = points[i];
			sprintf(tempString, "%lf %lf %lf %lf %lf %lf\n", 
				surf->surfacePoints[3*tempVal+0], surf->surfacePoints[3*tempVal+1], surf->surfacePoints[3*tempVal+2], 
				surf->surfaceNormals[3*tempVal+0], surf->surfaceNormals[3*tempVal+1], surf->surfaceNormals[3*tempVal+2] );
			( *currentOutputFile ) << tempString;
		}
	}

	///generate the Topology Header
	( *currentOutputFile ) << "########################################\n";
	( *currentOutputFile ) << "##   ##  ##   ###  ## ####  ###  ## # ##\n";
	( *currentOutputFile ) << "### ## ## # ## # ## # ### ## # #### # ##\n";
	( *currentOutputFile ) << "### ## ## #   ## ## # ### ## # #  ## ###\n";
	( *currentOutputFile ) << "### ## ## # #### ## # ### ## # ## ## ###\n";
	( *currentOutputFile ) << "### ###  ## #####  ##   ##  ###  ### ###\n";
	( *currentOutputFile ) << "########################################\n";
	
	///count the number of triangles:
	int numTriangles = 0;
	///If points is null, generate all triangles
	if(points==NULL){
		numTriangles = surf->numTriangles;
	}
	///If points is not null, count the triangles list for the triangles which are
	///entirely contained within points, and only output those.
	else{
		for(i = 0; i<surf->numTriangles; i++){
			bool test1 = contains_set(points, surf->triangles[3*i+0]);
			bool test2 = contains_set(points, surf->triangles[3*i+1]);
			bool test3 = contains_set(points, surf->triangles[3*i+2]);
			if(test1 && test2 && test3){
				numTriangles++;
			}
		}		
	}	
	///output the number of triangles.	
	sprintf(tempString, "TOPOLOGY: %i\n", numTriangles);
	( *currentOutputFile ) << tempString;

	//now actually output the triangles that we need.Use the reverse map.
	int point1Idx, point2Idx, point3Idx;
	///if points is null, just output everything.
	if(points==NULL){
		for(i = 0; i<numTriangles; i++){
			///get the triangle indices from surfTriangles
			point1Idx = surf->triangles[3*i+0];
			point2Idx = surf->triangles[3*i+1];
			point3Idx = surf->triangles[3*i+2];
			sprintf(tempString, "%i %i %i\n", point1Idx, point2Idx, point3Idx);
			( *currentOutputFile ) << tempString;
		}
	}
	//If poitns is non-null, output only the ones we care about.  Use the reverse map.
	else{
		for(i = 0; i<surf->numTriangles; i++){
			bool test1 = contains_set(points, surf->triangles[3*i+0]);
			bool test2 = contains_set(points, surf->triangles[3*i+1]);
			bool test3 = contains_set(points, surf->triangles[3*i+2]);
			if(test1 && test2 && test3){
				sprintf(tempString, "%i %i %i\n", rmap[surf->triangles[3*i+0]], rmap[surf->triangles[3*i+1]], rmap[surf->triangles[3*i+2]]);
				( *currentOutputFile ) << tempString;
			}
		}
	}

	///now output the footer.
	( *currentOutputFile ) << "\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "## Surface File Generated by Brian Chen and modified Trollbase Lib   ##\n";
	( *currentOutputFile ) << "#######################################################################\n";
	( *currentOutputFile ) << "#######################################################################\n";

	///done outputting.  Close file.
	( *currentOutputFile ).close();

	delete[](tempString);
	delete(currentOutputFile);
	if(points != NULL){
		delete[](map);
		delete[](rmap);
	}
}






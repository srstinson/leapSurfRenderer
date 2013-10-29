// SurfaceObject.cpp: implementation of the SurfaceObject class.
//
//  This is an openGL renderable class which represents a connolly surface
//  using vectors, norms, and a triangle topology.
//
//////////////////////////////////////////////////////////////////////

#include "SurfaceObject.h"
//#include <GLUT/glut.h>
//#include "LeapUtilGL.h"
#include "../JuceLibraryCode/JuceHeader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SurfaceObject::SurfaceObject(int numPts, double * ptsAndNorms, int numTris, int * inputTris, bool elimIntCavities)
{
    colorFlag = false;
	renderable = true;
	///get the sizes
	numPoints = numPts;
	numTriangles = numTris;
	highlights = NULL;
	edges = NULL;
	
	int * tris;

	tris = inputTris;


	///allocate the data
	surfacePoints = new double[3*numPoints];
	surfaceNormals = new double[3*numPoints];
	triangles = new int[3*numTriangles];
	centroid = new double[3];  centroid[0] = 0.0;  centroid[1] = 0.0;  centroid[2] = 0.0;
    colors = new double[3*numPoints];
    
	int i = 0;
	///map in the data
	for(i = 0; i<numPoints; i++){
		surfacePoints[3*i+0] = ptsAndNorms[6*i+0];
		surfacePoints[3*i+1] = ptsAndNorms[6*i+1];
		surfacePoints[3*i+2] = ptsAndNorms[6*i+2];
		surfaceNormals[3*i+0] = ptsAndNorms[6*i+3];
		surfaceNormals[3*i+1] = ptsAndNorms[6*i+4];
		surfaceNormals[3*i+2] = ptsAndNorms[6*i+5];
		///compute centroid simultaneously.
		centroid[0] += surfacePoints[3*i+0];
		centroid[1] += surfacePoints[3*i+1];
		centroid[2] += surfacePoints[3*i+2];
	}

	///finish centroid computation
	centroid[0] = centroid[0] / numPoints;
	centroid[1] = centroid[1] / numPoints;
	centroid[2] = centroid[2] / numPoints;

	///map in the triangles
	for(i = 0; i<numTriangles; i++){
		triangles[3*i+0] = tris[3*i+0];
		triangles[3*i+1] = tris[3*i+1];
		triangles[3*i+2] = tris[3*i+2];
	}

	///Compute the triangleNormals
	triangleNormals = new double[3*numTriangles];
	double * cross = new double[3];
	double * p0 = new double[3];
	double * p1 = new double[3];
	double * p2 = new double[3];
	double * v1 = new double[3];
	double * v2 = new double[3];
	double * tempNormal = new double[3];
	for(i = 0; i<numTriangles; i++){
//		printf("TRIANGLE: %i %i %i\n", triangles[3*i+0], triangles[3*i+1], triangles[3*i+2] );
		p0[0] = surfacePoints[3*triangles[3*i+0]+0];
		p0[1] = surfacePoints[3*triangles[3*i+0]+1];
		p0[2] = surfacePoints[3*triangles[3*i+0]+2];

		p1[0] = surfacePoints[3*triangles[3*i+1]+0];
		p1[1] = surfacePoints[3*triangles[3*i+1]+1];
		p1[2] = surfacePoints[3*triangles[3*i+1]+2];

		p2[0] = surfacePoints[3*triangles[3*i+2]+0];
		p2[1] = surfacePoints[3*triangles[3*i+2]+1];
		p2[2] = surfacePoints[3*triangles[3*i+2]+2];
//		printf("p0: %lf %lf %lf (point: %i)  normal: %lf %lf %lf \n", p0[0], p0[1], p0[2], triangles[3*i+0], 
//			surfaceNormals[3*triangles[3*i+0]+0], surfaceNormals[3*triangles[3*i+0]+1], surfaceNormals[3*triangles[3*i+0]+2]);
//		printf("p1: %lf %lf %lf (point: %i)  normal: %lf %lf %lf \n", p1[0], p1[1], p1[2], triangles[3*i+1],
//			surfaceNormals[3*triangles[3*i+1]+0], surfaceNormals[3*triangles[3*i+1]+1], surfaceNormals[3*triangles[3*i+1]+2]);
//		printf("p2: %lf %lf %lf (point: %i)  normal: %lf %lf %lf \n", p2[0], p2[1], p1[2], triangles[3*i+2],
//			surfaceNormals[3*triangles[3*i+2]+0], surfaceNormals[3*triangles[3*i+2]+1], surfaceNormals[3*triangles[3*i+2]+2]);


		v1[0] = p1[0]-p0[0];	v1[1] = p1[1]-p0[1];	v1[2] = p1[2] - p0[2];
		v2[0] = p2[0]-p0[0];	v2[1] = p2[1]-p0[1];	v2[2] = p2[2] - p0[2];
		
		tempNormal[0] = (surfaceNormals[3*triangles[3*i+0]+0] + surfaceNormals[3*triangles[3*i+1]+0] + surfaceNormals[3*triangles[3*i+2]+0])/3;
		tempNormal[1] = (surfaceNormals[3*triangles[3*i+0]+1] + surfaceNormals[3*triangles[3*i+1]+1] + surfaceNormals[3*triangles[3*i+2]+1])/3;
		tempNormal[2] = (surfaceNormals[3*triangles[3*i+0]+2] + surfaceNormals[3*triangles[3*i+1]+2] + surfaceNormals[3*triangles[3*i+2]+2])/3;

		CROSS(cross,v1,v2);
		if( DOT(cross, tempNormal)<0 ){	///if the vectors face opposite way, reverse the x-product
			
		//	printf("WARNING: (Triangle %i) Normals deviate from averaged normals (%i %i %i)!\n", i, triangles[3*i+0], triangles[3*i+1], triangles[3*i+2]);
		//	printf("TEMPNORMAL: %lf %lf %lf (point: %i)\n", tempNormal[0], tempNormal[1], tempNormal[2], triangles[3*i+0] );
		//	printf("CROSS: %lf %lf %lf\n", cross[0], cross[1], cross[2]);
			
			CROSS(cross,v2,v1);
			//printf("CROSS: %lf %lf %lf\n", cross[0], cross[1], cross[2]);
		}
		
		double * tempVec = normalizeVector(cross);
		
		triangleNormals[3*i+0] = tempVec[0];
		triangleNormals[3*i+1] = tempVec[1];
		triangleNormals[3*i+2] = tempVec[2];
		delete[](tempVec);
	}
    delete[](cross); delete[](tempNormal);
	delete[](p0); 	delete[](p1); 	delete[](p2); 
	delete[](v1); 	delete[](v2); 
}


SurfaceObject::SurfaceObject(int numPts, double * pts, double * norms, int numTris, int * tris, double * triangleNorms)
{
	int i = 0;
	numPoints = numPts;
	numTriangles = numTris;
    colorFlag = false;

	/////calculate the centroid	
	centroid = new double[3];	centroid[0] = 0;	centroid[1] = 0;	centroid[2] = 0;	
	for(i = 0; i<numPts; i++){
		centroid[0] += pts[3*i+0];	centroid[1] += pts[3*i+1];	centroid[2] += pts[3*i+2];
	}
	centroid[0] /= numPts;	centroid[1] /= numPts;	centroid[2] /= numPts; 

	/////fill in the pts and averaged normals
	surfacePoints = new double[3*numPts];
	surfaceNormals = new double[3*numPts];
	for(i = 0; i<numPts; i++){
		surfacePoints[3*i+0] = pts[3*i+0];		surfacePoints[3*i+1] = pts[3*i+1];		surfacePoints[3*i+2] = pts[3*i+2];
		surfaceNormals[3*i+0] = norms[3*i+0];	surfaceNormals[3*i+1] = norms[3*i+1];	surfaceNormals[3*i+2] = norms[3*i+2];
	}

	/////fill in the triangles
	triangles = new int[3*numTris];
	triangleNormals = new double[3*numTris];
	for(i = 0; i<numTris; i++){
		triangles[3*i+0] = tris[3*i+0];
		triangles[3*i+1] = tris[3*i+1];
		triangles[3*i+2] = tris[3*i+2];
		triangleNormals[3*i+0] = triangleNormals[3*i+0];
		triangleNormals[3*i+1] = triangleNormals[3*i+1];
		triangleNormals[3*i+2] = triangleNormals[3*i+2];
	}
}

SurfaceObject::~SurfaceObject()
{
    //std::cout<<"DEALLOCATED"<<std::endl;
	delete[](surfacePoints);
	delete[](surfaceNormals);
	delete[](triangles);
	delete[](centroid);
    delete[](colors);
    delete[](triangleNormals);
}


void SurfaceObject::dispose(){
    delete this;
}

///returns the coords of the requested triangle
///returns null if out of range.
///notice that the triangle must be formatted in this way in the array (3 then 3 then 3)
double * SurfaceObject::getTriangle(int num)
{
	if( (num < 0) || (num>=numTriangles) ){
		printf("ERROR: Triangle Not Found!\n");
		return NULL;
	}
	
	double * result = new double[9];
	
	result[0] = surfacePoints[ 3*triangles[3*num+0]+0 ];
	result[1] = surfacePoints[ 3*triangles[3*num+0]+1 ];
	result[2] = surfacePoints[ 3*triangles[3*num+0]+2 ];
	result[3] = surfacePoints[ 3*triangles[3*num+1]+0 ];
	result[4] = surfacePoints[ 3*triangles[3*num+1]+1 ];
	result[5] = surfacePoints[ 3*triangles[3*num+1]+2 ];
	result[6] = surfacePoints[ 3*triangles[3*num+2]+0 ];
	result[7] = surfacePoints[ 3*triangles[3*num+2]+1 ];
	result[8] = surfacePoints[ 3*triangles[3*num+2]+2 ];
	
	return result;
}


///identifies edges which are not surrounded by triangles - locations where the surface
///is non manifold.
///This turns the edges variable non-null.
//
//NOTE: THIS FUNCTION IS CURRENTLY BROKEN
//
//
void SurfaceObject::identifyNonManifoldEdges(void)
{
	int i = 0;
	int j = 0;
	
	///create a set of sets to hold non-manifold edges
	set_t nonManifold = alloc_set(SP_MAP);
		
	///Create a set of sets to remember which triangles associate with which vertex.  Allocate that here.
	set_t verticesMappingToTris = alloc_set(SP_MAP);
	for(i = 0; i<numPoints; i++){
		set_t tris = alloc_set(0);
		verticesMappingToTris = associate_set(verticesMappingToTris, i, tris);
	}

	///associate each vertex with a list of triangles it is part of.
	///we do this by interating through all triangles
	set_t tris;
	for(i = 0; i<numTriangles; i++){
		tris = (set_t) mapsto_set(verticesMappingToTris, triangles[3*i+0]);
		tris = put_set(tris, i);
		verticesMappingToTris = associate_set(verticesMappingToTris, triangles[3*i+0], tris);

		tris = (set_t) mapsto_set(verticesMappingToTris, triangles[3*i+1]);
		tris = put_set(tris, i);
		verticesMappingToTris = associate_set(verticesMappingToTris, triangles[3*i+1], tris);
		
		tris = (set_t) mapsto_set(verticesMappingToTris, triangles[3*i+2]);
		tris = put_set(tris, i);
		verticesMappingToTris = associate_set(verticesMappingToTris, triangles[3*i+2], tris);
	}

	int min = 100000;
	int max = 0;
	int counter = 0;
	for(i = 0; i<size_set(verticesMappingToTris); i++){
		tris = (set_t) mapsto_set(verticesMappingToTris, verticesMappingToTris[i]);
		if(min > size_set(tris)){ 
			min = size_set(tris); 
			if(size_set(tris) == 0){
				counter++;
			}
		}
		if(max < size_set(tris)){ max = size_set(tris); }
	}

	printf("MAXIMUM NUMBER OF TRIANLGES ASSOCIATED WITH A point: %i\n", max);
	printf("MINIMUM NUMBER OF TRIANLGES ASSOCIATED WITH A point: %i  (total 0: %i)\n", min, counter);


	set_t set1;
	set_t set2;
	set_t tempSet;
	int numCommon;
	int * tri = new int[3];
	///iterate through all triangles, 
	for(i = 0; i<numTriangles; i++){
		tri[0] = triangles[3*i+0];
		tri[1] = triangles[3*i+1];
		tri[2] = triangles[3*i+2];

		///for each edge on the triangle, verify that exactly two 
		///distinct triangles are part of that edge.  otherwise it is
		///a non-manifold edge.
		for(j = 0; j<3; j++){
			//set the two vertices of the edge we are working on
			int t1 = tri[(j+0)%3];
			int t2 = tri[(j+1)%3];
			//identify the set of triangles adjacent to each endpoint
			set1 = (set_t) mapsto_set(verticesMappingToTris, t1);
			set2 = (set_t) mapsto_set(verticesMappingToTris, t2);
			///find out how many triangles are common between these endpoints
			numCommon = countNumCommon(set1, set2);

			//if numCommon == 1, then this is an edge of a nonmanifold surface.  Store it.
			if(numCommon == 1){
				if(!contains_set(nonManifold, t1)){ tempSet = alloc_set(0); }
				else{ tempSet = (set_t) mapsto_set(nonManifold, t1); }
				tempSet = put_set(tempSet, t2);
				nonManifold = associate_set(nonManifold, t1, tempSet);

				if(!contains_set(nonManifold, t2)){ tempSet = alloc_set(0); }
				else{ tempSet = (set_t) mapsto_set(nonManifold, t2); }
				tempSet = put_set(tempSet, t1);
				nonManifold = associate_set(nonManifold, t2, tempSet);
//				printf("Edge: %i %i\n", t1, t2);
			}

			//if numCommon is zero, then there is a serious issue with triangle topology.  Report it.
			if(numCommon == 0){
				printf("ERROR: Two vertices of the same triangle (vertex %i and %i in triangle %i) \n", t1, t2, i);
				printf("ERROR: are not members of at least one triangle, according to our data!!\n");
			}

			//if numCommon is greater than two, there is impossible surface occuring.  Report it.
			if(numCommon > 2){
				printf("ERROR: Vertices %i and %i appear to be adjacent to an edge which is part of \n", t1, t2);
				printf("ERROR: more than two triangles, creating a non-manifold surface! error!\n");
			}
			
			///if numCommon is equal to two, that is fine.  Report nothing.
		}

		///The end of this loop creates a list of non-manifold edges at the border of the surface, if it exists.
	}
	
	edges = nonManifold;
	
	delete[](tri);
	//free the data structure
	for(i = 0; i<numPoints; i++){ tris = (set_t) mapsto_set(verticesMappingToTris, i); free_set(tris); }
	free_set(verticesMappingToTris);
	
}

///helper function tells you how int elements are identical between two sets.
///This probably should be in a library... but its too special purpose
int SurfaceObject::countNumCommon(set_t set1, set_t set2)
{
	int i = 0;
	int result = 0;

	int s1 = size_set(set1);		
	int s2 = size_set(set2);
	set_t tempSet1 = set1;		
	set_t tempSet2 = set2;

	if(s2 > s1){ 
		tempSet1 = set2;
		tempSet2 = set1;
		s1 = size_set(set2);
		s2 = size_set(set1);
	}
	
	///now tempSet1 is always at least as large as tempset2.
	for(i = 0; i<size_set(tempSet2); i++){
		if( contains_set(tempSet1, tempSet2[i]) ){
			result++;
		}
	}
	
	return result;
}



///This function flips the normals of the surfaceObject backwards 
///so that we can treat it as a negative volume
void SurfaceObject::flipNormals()
{
	int i = 0;
	for(i = 0; i<3*numPoints; i++){
		surfaceNormals[i] = -surfaceNormals[i];
	}
	for(i = 0; i<3*numTriangles; i++){
		triangleNormals[i] = -triangleNormals[i];
	}
	int temp;
	for(i = 0; i<numTriangles; i++){
		triangles[3*i+0] = triangles[3*i+0];
		temp = triangles[3*i+1];
		triangles[3*i+1] = triangles[3*i+2];
		triangles[3*i+2] = temp;		
	}
}



///adds color data to the object
void SurfaceObject::addColors(double * c)
{
//	printf("OMFGASD: %lf %lf %lf\n", c[0], c[1], c[2] );

	if(c == NULL){return;}
    colorFlag = true;
    int i = 0;
	for(i = 0; i<3*numPoints; i++){
//		printf("c[%i] = %lf\n", i, c[i]);
		colors[i] = c[i];
	}
}













////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#ifdef OPENGL_RENDERING

void SurfaceObject::draw(bool drawPoints, bool drawLines, bool drawTransparent, bool pocketView, double * offset, double * c)
{
	int i = 0;
	int j = 0;
	int pt1, pt2, pt3;

	////Declare Materials
	GLfloat mat_solid[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_zero[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_transparent[] = { 0.2, 0.2, 0.2, 0.2 };
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 0.0 };
	GLfloat low_shininess[] = { .5 };

	float amb[] = {0.20f, 0.50f, 1.0f, 0.1f};
	float diff[] = {0.20f, 0.50f, 1.0f, 0.1f};
	float spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float shine[] = {0.8 * 128.0f}; // The glass is very shiny

	double * cent = new double[3];
	cent[0] = 0; cent[1] = 0; cent[2] = 0;
	if(offset != NULL){
		delete[](cent);
		cent = offset;
	}

	///drawPoints
	if(drawPoints){
		glBegin(GL_POINTS);
		glColor3f(1.00000f, 1.00000f, 1.00000f);
		for(i = 0; i<numTriangles; i++){
			pt1 = triangles[3*i+0];
			pt2 = triangles[3*i+1];
			pt3 = triangles[3*i+2];
			glVertex3f( surfacePoints [3*pt1+0]-cent[0],surfacePoints [3*pt1+1]-cent[1],surfacePoints [3*pt1+2]-cent[2] );
			glVertex3f( surfacePoints [3*pt2+0]-cent[0],surfacePoints [3*pt2+1]-cent[1],surfacePoints [3*pt2+2]-cent[2] );
			glVertex3f( surfacePoints [3*pt3+0]-cent[0],surfacePoints [3*pt3+1]-cent[1],surfacePoints [3*pt3+2]-cent[2] );
		}
		glEnd();
	}
	if(drawLines){
		glBegin(GL_LINES);
		glColor3f(0.00000f, 1.00000f, 0.00000f);
		for(i = 0; i<numTriangles; i++){
			pt1 = triangles[3*i+0];
			pt2 = triangles[3*i+1];
			pt3 = triangles[3*i+2];
			glVertex3f( surfacePoints [3*pt1+0]-cent[0],surfacePoints [3*pt1+1]-cent[1],surfacePoints [3*pt1+2]-cent[2] );
			glVertex3f( surfacePoints [3*pt2+0]-cent[0],surfacePoints [3*pt2+1]-cent[1],surfacePoints [3*pt2+2]-cent[2] );
			glVertex3f( surfacePoints [3*pt2+0]-cent[0],surfacePoints [3*pt2+1]-cent[1],surfacePoints [3*pt2+2]-cent[2] );
			glVertex3f( surfacePoints [3*pt3+0]-cent[0],surfacePoints [3*pt3+1]-cent[1],surfacePoints [3*pt3+2]-cent[2] );
			glVertex3f( surfacePoints [3*pt3+0]-cent[0],surfacePoints [3*pt3+1]-cent[1],surfacePoints [3*pt3+2]-cent[2] );
			glVertex3f( surfacePoints [3*pt1+0]-cent[0],surfacePoints [3*pt1+1]-cent[1],surfacePoints [3*pt1+2]-cent[2] );
		}
		glEnd();
	}
	bool drawNormals = false;
	if(drawNormals){
		glColor3f(1.00000f, 1.00000f, 1.00000f);
		glBegin(GL_LINES);
		for(i = 0; i<numTriangles; i++){
			pt1 = triangles[3*i+0];
			pt2 = triangles[3*i+1];
			pt3 = triangles[3*i+2];
			double * p1 = new double[3];
			p1[0] = surfacePoints [3*pt1+0]-cent[0]; p1[1] = surfacePoints [3*pt1+1]-cent[1]; p1[2] = surfacePoints [3*pt1+2]-cent[2];
			double * p2 = new double[3];
			p2[0] = surfacePoints [3*pt2+0]-cent[0]; p2[1] = surfacePoints [3*pt2+1]-cent[1]; p2[2] = surfacePoints [3*pt2+2]-cent[2];
			double * p3 = new double[3];
			p3[0] = surfacePoints [3*pt3+0]-cent[0]; p3[1] = surfacePoints [3*pt3+1]-cent[1]; p3[2] = surfacePoints [3*pt3+2]-cent[2];
			double * v1 = new double[3];
			v1[0] = p2[0] - p1[0]; v1[1] = p2[1] - p1[1]; v1[2] = p2[2] - p1[2];
			double * v2 = new double[3];
			v2[0] = p3[0] - p1[0]; v2[1] = p3[1] - p1[1]; v2[2] = p3[2] - p1[2];
			double * cross = crossProd(v1, v2);
			double * norm = normalizeVector(cross);
			double * avg = new double[3];
			avg[0] = (p1[0]+p2[0]+p3[0])/3; avg[1] = (p1[1]+p2[1]+p3[1])/3; avg[2] = (p1[2]+p2[2]+p3[2])/3;
			double * newPt = new double[3];
			newPt[0] = avg[0] + norm[0];
			newPt[1] = avg[1] + norm[1];
			newPt[2] = avg[2] + norm[2];
			glVertex3f(   avg[0],   avg[1],   avg[2] );
			glVertex3f( newPt[0], newPt[1], newPt[2] );
			//printf("vectorSize: %lf\n", vectorSize( newPt[0]-avg[0], newPt[1]-avg[1], newPt[2]-avg[2]) ); 
			delete[](p1); delete[](p2); delete[](p3); delete[](v1); delete[](v2); 
			delete[](cross); delete[](norm); delete[](avg); delete[](newPt);
		}
		glEnd();
	}
	
	//set material properties
	if(drawTransparent == true){
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);

		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else{
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	}

	double * color = new double[3];
	if(c != NULL){ color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; }
	else{
		if(drawTransparent){ color[0] = 0.5f; color[1] = 0.5f; color[2] = 0.0f; }
		else{ color[0] = 0.0f; color[1] = 0.5f; color[2] = 0.5f; }
	}

	set_t debug_triangleSet = alloc_set(0);
//	debug_triangleSet = put_set(debug_triangleSet, 37);
//	debug_triangleSet = put_set(debug_triangleSet, 38);
//	debug_triangleSet = put_set(debug_triangleSet, 39);
//	debug_triangleSet = put_set(debug_triangleSet, 213);
//	debug_triangleSet = put_set(debug_triangleSet, 215);

	///render the triangles
	glBegin(GL_TRIANGLES);
	for(i = 0; i<numTriangles; i++){
		pt1 = triangles[3*i+0];	pt2 = triangles[3*i+1];	pt3 = triangles[3*i+2];
		double s = 1.00;	///surface geometry hack - scales up slightly so there isnt so much z-buffer collision.

//		if(i == 215){ glColor4f(1, 0, 0, .5); }

		if(drawTransparent){///surface geometry hack
			glColor4f(color[0], color[1], color[2], .5);
			if( contains_set(debug_triangleSet, i) ){ glColor4f(1, 0, 0, .5); }
			glNormal3f( surfaceNormals[3*pt1+0],		surfaceNormals[3*pt1+1],		surfaceNormals[3*pt1+2] );
			glVertex3f( s*(surfacePoints [3*pt1+0]-cent[0]),s*(surfacePoints [3*pt1+1]-cent[1]),s*(surfacePoints [3*pt1+2]-cent[2]) );
			glNormal3f( surfaceNormals[3*pt2+0],		surfaceNormals[3*pt2+1],		surfaceNormals[3*pt2+2] );
			glVertex3f( s*(surfacePoints [3*pt2+0]-cent[0]),s*(surfacePoints [3*pt2+1]-cent[1]),s*(surfacePoints [3*pt2+2]-cent[2]) );
			glNormal3f( surfaceNormals[3*pt3+0],		surfaceNormals[3*pt3+1],		surfaceNormals[3*pt3+2] );
			glVertex3f( s*(surfacePoints [3*pt3+0]-cent[0]),s*(surfacePoints [3*pt3+1]-cent[1]),s*(surfacePoints [3*pt3+2]-cent[2]) );
		}
		else{
			if(colorFlag == true){
				glColor4f( colors[3*pt1+0],		colors[3*pt1+1],		colors[3*pt1+2], 1.0 );
				glNormal3f( surfaceNormals[3*pt1+0],		surfaceNormals[3*pt1+1],		surfaceNormals[3*pt1+2] );
				glVertex3f( surfacePoints [3*pt1+0]-cent[0],surfacePoints [3*pt1+1]-cent[1],surfacePoints [3*pt1+2]-cent[2] );
				glColor4f( colors[3*pt2+0],		colors[3*pt2+1],		colors[3*pt2+2], 1.0 );
				glNormal3f( surfaceNormals[3*pt2+0],		surfaceNormals[3*pt2+1],		surfaceNormals[3*pt2+2] );
				glVertex3f( surfacePoints [3*pt2+0]-cent[0],surfacePoints [3*pt2+1]-cent[1],surfacePoints [3*pt2+2]-cent[2] );
				glColor4f( colors[3*pt3+0],		colors[3*pt3+1],		colors[3*pt3+2], 1.0 );
				glNormal3f( surfaceNormals[3*pt3+0],		surfaceNormals[3*pt3+1],		surfaceNormals[3*pt3+2] );
				glVertex3f( surfacePoints [3*pt3+0]-cent[0],surfacePoints [3*pt3+1]-cent[1],surfacePoints [3*pt3+2]-cent[2] );
			}
			else{
				glColor4f(color[0], color[1], color[2], 1.0);
				if( contains_set(debug_triangleSet, i) ){ glColor4f(1, 0, 0, 1); }
				glNormal3f( surfaceNormals[3*pt1+0],		surfaceNormals[3*pt1+1],		surfaceNormals[3*pt1+2] );
				glVertex3f( surfacePoints [3*pt1+0]-cent[0],surfacePoints [3*pt1+1]-cent[1],surfacePoints [3*pt1+2]-cent[2] );
				glNormal3f( surfaceNormals[3*pt2+0],		surfaceNormals[3*pt2+1],		surfaceNormals[3*pt2+2] );
				glVertex3f( surfacePoints [3*pt2+0]-cent[0],surfacePoints [3*pt2+1]-cent[1],surfacePoints [3*pt2+2]-cent[2] );
				glNormal3f( surfaceNormals[3*pt3+0],		surfaceNormals[3*pt3+1],		surfaceNormals[3*pt3+2] );
				glVertex3f( surfacePoints [3*pt3+0]-cent[0],surfacePoints [3*pt3+1]-cent[1],surfacePoints [3*pt3+2]-cent[2] );
			}
		}
	}
	for(i = 0; i<numTriangles; i++){
		double s = 1.00;	///surface geometry hack - scales up slightly so there isnt so much z-buffer collision.
		pt1 = triangles[3*i+0];	pt2 = triangles[3*i+1];	pt3 = triangles[3*i+2];
		if(pocketView){/// we render both sides by drawing backwards triangles too.
			//glColor4f(color[0]/2, color[1]/2, color[2]/2, 1.0);
			if(drawTransparent){///surface geometry hack
				glColor4f(color[0], color[1], color[2], .3);
				if( contains_set(debug_triangleSet, i) ){ glColor4f(1, 0, 0, .5); }
				glNormal3f(   -surfaceNormals[3*pt1+0],	          -surfaceNormals[3*pt1+1],           -surfaceNormals[3*pt1+2] );
				glVertex3f( s*(surfacePoints [3*pt1+0]-cent[0]),s*(surfacePoints [3*pt1+1]-cent[1]),s*(surfacePoints [3*pt1+2]-cent[2]) );
				glNormal3f(   -surfaceNormals[3*pt3+0],	          -surfaceNormals[3*pt3+1],           -surfaceNormals[3*pt3+2] );
				glVertex3f( s*(surfacePoints [3*pt3+0]-cent[0]),s*(surfacePoints [3*pt3+1]-cent[1]),s*(surfacePoints [3*pt3+2]-cent[2]) );
				glNormal3f(   -surfaceNormals[3*pt2+0],	          -surfaceNormals[3*pt2+1],	          -surfaceNormals[3*pt2+2] );
				glVertex3f( s*(surfacePoints [3*pt2+0]-cent[0]),s*(surfacePoints [3*pt2+1]-cent[1]),s*(surfacePoints [3*pt2+2]-cent[2]) );
			}
			else{
				glColor4f(color[0]/4, color[1]/4, color[2]/4, 1.0);
				glColor3f(0.00000f, 0.250000f, 0.2500000f);
				if( contains_set(debug_triangleSet, i) ){ glColor4f(1, 0, 0, 1); }
				glNormal3f( surfaceNormals[3*pt1+0],		surfaceNormals[3*pt1+1],		surfaceNormals[3*pt1+2] );
				glVertex3f( surfacePoints [3*pt1+0]-cent[0],surfacePoints [3*pt1+1]-cent[1],surfacePoints [3*pt1+2]-cent[2] );
				glNormal3f( surfaceNormals[3*pt3+0],		surfaceNormals[3*pt3+1],		surfaceNormals[3*pt3+2] );
				glVertex3f( surfacePoints [3*pt3+0]-cent[0],surfacePoints [3*pt3+1]-cent[1],surfacePoints [3*pt3+2]-cent[2] );
				glNormal3f( surfaceNormals[3*pt2+0],		surfaceNormals[3*pt2+1],		surfaceNormals[3*pt2+2] );
				glVertex3f( surfacePoints [3*pt2+0]-cent[0],surfacePoints [3*pt2+1]-cent[1],surfacePoints [3*pt2+2]-cent[2] );
			}
			
		
		}

	}
	glEnd();

	free_set(debug_triangleSet);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if( highlights != NULL ){
		glBegin(GL_POINTS);
		for(i = 0; i<numPoints; i++){
			if(contains_set(highlights, i)){
				//glPushMatrix();
				glVertex3f( surfacePoints[3*i+0]-cent[0], surfacePoints[3*i+1]-cent[1], surfacePoints[3*i+2]-cent[2] );
				//glTranslatef(surfacePoints[3*i+0], surfacePoints[3*i+1], surfacePoints[3*i+2] );
				//glutSolidSphere  ( .3, 4, 4) ;
				//glPopMatrix();
			}
		}
		glEnd();
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if(edges != NULL && drawTransparent == false){
		glBegin(GL_LINES);
		for(i = 0; i<size_set(edges); i++){
			set_t tempSet = (set_t) mapsto_set(edges, edges[i]);
			for(j = 0; j<size_set(tempSet); j++){
				if(tempSet[j] > edges[i]){
					glVertex3f( surfacePoints[3*edges[i]+0]-cent[0], surfacePoints[3*edges[i]+1]-cent[1], surfacePoints[3*edges[i]+2]-cent[2] );
					glVertex3f( surfacePoints[3*tempSet[j]+0]-cent[0], surfacePoints[3*tempSet[j]+1]-cent[1], surfacePoints[3*tempSet[j]+2]-cent[2] );
				}
			}
		}
		glEnd();
	}



	///fix material properties
	if(drawTransparent == true){
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	if(offset == NULL){
		delete[](cent);
	}
	delete[](color);

}

//#endif
/////////////////////////////


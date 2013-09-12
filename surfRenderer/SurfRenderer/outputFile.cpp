


#include "outputFile.h"



void outputFileAtomList(char * outputFileHead, set_t lists, set_t list_pos, set_t list_rot)
{
	int i = 0;
	int j = 0;

	int numProts = size_set(lists);

	char * outputFileName = new char[1000];
	sprintf(outputFileName, "%s.pdb", outputFileHead);

    ofstream * currentOutputFile = new ofstream(outputFileName);

	char * tempLine = new char[1000];
	sprintf(tempLine, "REMARK  ######################################################################\n");
	sprintf(tempLine, "REMARK  #This PDB file created by ProtRenderer, by Brian Chen, Honig Lab 2007#\n");
	sprintf(tempLine, "REMARK  ######################################################################\n");

	for(i = 0; i<numProts; i++){
		AtomList * tempList = (AtomList *) mapsto_set(lists, i);

		float * tmppos = (float *) mapsto_set(list_pos, i);
		float * tmprot = (float *) mapsto_set(list_rot, i);

		double * pos = new double[3];
		pos[0] = (float) tmppos[0];
		pos[1] = (float) tmppos[1];
		pos[2] = (float) tmppos[2];

		double * rot = new double[16];
		rot[0]  = (float) tmprot[0];
		rot[1]  = (float) tmprot[1];
		rot[2]  = (float) tmprot[2];
		rot[3]  = (float) tmprot[3];
		rot[4]  = (float) tmprot[4];
		rot[5]  = (float) tmprot[5];
		rot[6]  = (float) tmprot[6];
		rot[7]  = (float) tmprot[7];
		rot[8]  = (float) tmprot[8];
		rot[9]  = (float) tmprot[9];
		rot[10] = (float) tmprot[10];
		rot[11] = (float) tmprot[11];
		rot[12] = (float) tmprot[12];
		rot[13] = (float) tmprot[13];
		rot[14] = (float) tmprot[14];
		rot[15] = (float) tmprot[15];

		for(j = 0; j<tempList->size; j++){
			PdbAtom * atom = tempList->atomList[j];
			double * pt = atom->coords;

			///perform the transformation
			double * postRot = transformVector3x4(rot, pt);
			postRot[0] += pos[0];
			postRot[1] += pos[1];
			postRot[2] += pos[2];

			atom->coords = postRot;

			tempLine = atom->pdbLine();
		    ( *currentOutputFile ) << tempLine;

			atom->coords = pt;
			delete[](tempLine);
			delete[](postRot);
		}
	}

	( *currentOutputFile ).close();

	printf("Output PDB file [%s] generated successfully!\n", outputFileName);

}




///generates a new surface file for each surface
///using a naming convention
void outputFileSurfObj(char * outputFileHead, set_t surfs, set_t surf_pos, set_t surf_rot)
{
	int i = 0;
	int j = 0;

	for(i = 0; i<size_set(surfs); i++){
		///get the surfaceObject, rot, and trans
		printf("Making new Surf\n");
		SurfaceObject * surf = (SurfaceObject *) mapsto_set(surfs, i);
		float * tmppos = (float *) mapsto_set(surf_pos, i);
		float * tmprot = (float *) mapsto_set(surf_rot, i);

		double * pos = new double[3];
		pos[0] = (float) tmppos[0];		pos[1] = (float) tmppos[1];		pos[2] = (float) tmppos[2];

		double * rot = new double[16];
		rot[0]  = (float) tmprot[0];
		rot[1]  = (float) tmprot[1];
		rot[2]  = (float) tmprot[2];
		rot[3]  = (float) tmprot[3];
		rot[4]  = (float) tmprot[4];
		rot[5]  = (float) tmprot[5];
		rot[6]  = (float) tmprot[6];
		rot[7]  = (float) tmprot[7];
		rot[8]  = (float) tmprot[8];
		rot[9]  = (float) tmprot[9];
		rot[10] = (float) tmprot[10];
		rot[11] = (float) tmprot[11];
		rot[12] = (float) tmprot[12];
		rot[13] = (float) tmprot[13];
		rot[14] = (float) tmprot[14];
		rot[15] = (float) tmprot[15];

		double * newPts = new double[3*surf->numPoints];
		double * newNorms = new double[3*surf->numPoints];
		double * newTrisNorms = new double[3*surf->numTriangles];
		int * newTris = new int[3*surf->numTriangles];
		for(j = 0; j<3*surf->numTriangles; j++){ newTris[j] = surf->triangles[j]; }

		for(j = 0; j<surf->numPoints; j++){
			double * tmp = new double[3];
			tmp[0] = surf->surfacePoints[3*j+0];
			tmp[1] = surf->surfacePoints[3*j+1];
			tmp[2] = surf->surfacePoints[3*j+2];
			double * postRot = transformVector3x4(rot, tmp);
			postRot[0] += pos[0]; postRot[1] += pos[1]; postRot[2] += pos[2];

			newPts[3*j+0] = postRot[0];
			newPts[3*j+1] = postRot[1];
			newPts[3*j+2] = postRot[2];
			delete[](postRot);

			tmp[0] = surf->surfaceNormals[3*j+0];
			tmp[1] = surf->surfaceNormals[3*j+1];
			tmp[2] = surf->surfaceNormals[3*j+2];
			postRot = transformVector3x4(rot, tmp);

			newNorms[3*j+0] = postRot[0];
			newNorms[3*j+1] = postRot[1];
			newNorms[3*j+2] = postRot[2];
			delete[](postRot);
			delete[](tmp);
		}

		for(j = 0; j<surf->numTriangles; j++){
			double * tmp = new double[3];
			tmp[0] = surf->triangleNormals[3*j+0];
			tmp[1] = surf->triangleNormals[3*j+1];
			tmp[2] = surf->triangleNormals[3*j+2];
			double * postRot = transformVector3x4(rot, tmp);
	//		double * postRot2 = normalizeVector(postRot);

			newTrisNorms[3*j+0] = postRot[0];
			newTrisNorms[3*j+1] = postRot[1];
			newTrisNorms[3*j+2] = postRot[2];
			delete[](postRot);
	//		delete[](postRot2);
			delete[](tmp);
		}

		SurfaceObject * newSurf = new SurfaceObject(surf->numPoints, newPts, newNorms, surf->numTriangles, newTris, newTrisNorms);

		///create the file name
		char * outputFileName = new char[1000];
		sprintf(outputFileName, "%s-%i.SURF", outputFileHead, i);

		///output the file
		generateSURF(newSurf, NULL, outputFileName);
		printf("Outputted file: [%s]\n", outputFileName);

		///cleanup
		delete(newSurf);
		delete[](newPts);
		delete[](newNorms);
		delete[](newTrisNorms);
		delete[](newTris);
		delete[](pos);
		delete[](rot);
		delete[](outputFileName);
	}

}







void outputFileVolumePrimitives(char * outputFileHead, set_t spheres, set_t radii, double * centroid, set_t cubes, set_t cubeSize )
{
	///check for logical data
	if( size_set(spheres) != size_set(radii) ){
		printf("Number of spheres not equal to number of radii! exit!\n");
		exit(1);
	}

	//create the file
	char * outputFileName = new char[1000];
	sprintf(outputFileName, "%s.PRIMS", outputFileHead);
    ofstream * currentOutputFile = new ofstream(outputFileName);

	///create the header
	char * tempLine = new char[1000];
	sprintf(tempLine, "######################################################################\n");
	( *currentOutputFile ) << tempLine;
	sprintf(tempLine, "#VOLUMETRIC PRIMATIVES FILE GENERATED BY BRIAN CHEN, HONIG LAB 2008  #\n");
	( *currentOutputFile ) << tempLine;
	sprintf(tempLine, "######################################################################\n");
	( *currentOutputFile ) << tempLine;


	//now create the data
	sprintf(tempLine, "NUM_PRIMATIVES %i\n", size_set(spheres)+size_set(cubes) );
	( *currentOutputFile ) << tempLine;

	///print the spheres
	int i = 0;
	for(i = 0; i<size_set(spheres); i++){
		float * vector = (float *) mapsto_set(spheres, i);
		float * radius = (float *) mapsto_set(radii, i);

		sprintf(tempLine, "SPHERE %lf %lf %lf %lf\n", vector[0]+centroid[0], vector[1]+centroid[1], vector[2]+centroid[2], radius[0] );
		( *currentOutputFile ) << tempLine;
	}

	///print the cubes
	for(i = 0; i<size_set(cubes); i++){
		float * vector = (float *) mapsto_set(cubes, i);
		float * radius = (float *) mapsto_set(cubeSize, i);

		sprintf(tempLine, "CUBE %lf %lf %lf %lf\n", vector[0]+centroid[0], vector[1]+centroid[1], vector[2]+centroid[2], radius[0] );
		( *currentOutputFile ) << tempLine;
	}

	///close the file
	( *currentOutputFile ).close();

	printf("Output VOL file [%s] generated successfully!\n", outputFileName);

	delete[](tempLine);
	delete[](outputFileName);




}

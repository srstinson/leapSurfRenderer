// PocketAlignment.cpp: implementation of the PocketAlignment class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PocketAlignment::PocketAlignment(char * fileName)
{
	int counter = 0;
	char * ptr;
	char * line = new char[10000];

	///allocate the storage
	pockets = alloc_set(SP_MAP);
	aLists = alloc_set(SP_MAP);
	alignments = alloc_set(SP_MAP);
	calists = alloc_set(SP_MAP);
	residues = alloc_set(SP_MAP);
	names = alloc_set(SP_MAP);
	colors = alloc_set(SP_MAP);
	rmsds = alloc_set(SP_MAP);

	///open the file
	FILE * file = fopen(fileName, "r");
	if(file == NULL){ printf("ERROR: Alignment File [%s] does not exist! Exitting!\n", fileName); exit(1); }

	///iterate through the pockets
	while( fgets(line, 10000, file) != NULL){
		if( line[0] == '#' || line[0] == '\n'){ continue; }

		//FIRST: read the pdb name
		ptr = strtok(line, " \n\t\r");
		if( strcmp(ptr, "POCKETPDB") != 0){ printf("ERROR: POCKETPDB definition not in right spot! exitting!\n"); exit(1); }
		else{
			ptr = strtok(NULL, " \n\t\r");
			pdbParser * parse = new pdbParser(ptr);
			AtomList * alist = parse->getAtomList();
			alist->highlightAllAAs();
			caList * clist = new caList(alist);
			aLists = associate_set(aLists, counter, alist);
			alist->highlightNoAAs();
			calists = associate_set(calists, counter, clist);
			char * tempName = new char[100];
			strcpy(tempName, ptr);
			names = associate_set(names, counter, tempName);
			delete(parse);
		}

		//SECOND: read the SURF name
		fgets(line, 10000, file);
		ptr = strtok(line, " \n\t\r");
		if( strcmp(ptr, "POCKETSURF") != 0){ printf("ERROR: POCKETSURF definition not in right spot! exitting!\n"); exit(1); }
		else{
			ptr = strtok(NULL, " \n\t\r");
			SurfaceObject * sobj = parseGeometryFile(ptr);
			pockets = associate_set(pockets, counter, sobj);
			if(sobj != NULL){
				char * tempName = (char *) mapsto_set(names, counter);
				delete[](tempName);
				tempName = new char[100];
				strcpy(tempName, ptr);
				names = associate_set(names, counter, tempName);
			}
		}

		//THIRD: read the residue numbers
		fgets(line, 10000, file);
		ptr = strtok(line, " \n\t\r");
		if( strcmp(ptr, "POCKETAA") != 0){ printf("ERROR: POCKETAA definition not in right spot! exitting!\n"); exit(1); }
		else{
			ptr = strtok(NULL, " \n\t\r");
			set_t iList = parseIntegerList(ptr);
			residues = associate_set(residues, counter, iList);
		}

		///increment the counter
		counter++;
	}
	numPockets = counter;

	///Done parsing.  Now compute the alingmnets
	int i = 0;
	for(i = 0; i<numPockets; i++){
		if(i == 0){
			double * a = new double[16];
			a[0] = 1.0;	a[4] = 0;	a[8] = 0;	a[12] = 0;
			a[1] = 0;	a[5] = 1.0;	a[9] = 0;	a[13] = 0;
			a[2] = 0;	a[6] = 0;	a[10] = 1.0;a[14] = 0;
			a[3] = 0;	a[7] = 0;	a[11] = 0;	a[15] = 1.0;
			double * rms = new double[1];
			rms[0] = 0.0;
			alignments = associate_set(alignments, i, a);
			rmsds = associate_set(rmsds, i, rms);
		}
		else{
			set_t list1 = (set_t) mapsto_set(residues, 0);
			set_t list2 = (set_t) mapsto_set(residues, i);
			caList * struct1 = (caList*) mapsto_set(calists, 0);
			caList * struct2 = (caList*) mapsto_set(calists, i);
			double * rms = new double[1];

			double * tempAlign = generateAlignment(list1, struct1, list2, struct2, rms);
			alignments = associate_set(alignments, i, tempAlign);
			rmsds = associate_set(rmsds, i, rms);

		//	int j = 0;
		//	for(j = 0; j<16; j++){
		//		printf("%f ", tempAlign[j]);
		//		if( j%4 == 3){ printf("\n"); }
		//	}
		//	printf("OMG!\n");
		
		}
		char * tempString = new char[100];
		char * tempName = (char *) mapsto_set(names, i);
		double * rms = (double *) mapsto_set(rmsds, i);
		sprintf(tempString, "%s    RMSD: %lf", tempName, rms[0]);
		delete[](tempName);
		names = associate_set(names, i, tempString);
	}
	
	for(i = 0; i<numPockets; i++){
		double * thisColor = new double[3];
		int marker = i % 12;
		switch(marker){
			case 0:
				thisColor[0] = 1.0; thisColor[1] = 0.0; thisColor[2] = 0.0; break;
			case 1:
				thisColor[0] = 0.0; thisColor[1] = 1.0; thisColor[2] = 0.0; break;
			case 2:
				thisColor[0] = 0.0; thisColor[1] = 0.0; thisColor[2] = 1.0; break;
			case 3:
				thisColor[0] = 1.0; thisColor[1] = 1.0; thisColor[2] = 0.0; break;
			case 4:
				thisColor[0] = 1.0; thisColor[1] = 0.0; thisColor[2] = 1.0; break;
			case 5:
				thisColor[0] = 0.0; thisColor[1] = 1.0; thisColor[2] = 1.0; break;
			case 6:
				thisColor[0] = 1.0; thisColor[1] = 0.5; thisColor[2] = 0.0; break;
			case 7:
				thisColor[0] = 0.5; thisColor[1] = 1.0; thisColor[2] = 0.0; break;
			case 8:
				thisColor[0] = 1.0; thisColor[1] = 0.0; thisColor[2] = 0.5; break;
			case 9:
				thisColor[0] = 0.5; thisColor[1] = 0.0; thisColor[2] = 1.0; break;
			case 10:
				thisColor[0] = 0.0; thisColor[1] = 1.0; thisColor[2] = 0.5; break;
			case 11:
				thisColor[0] = 0.0; thisColor[1] = 0.5; thisColor[2] = 1.0; break;
		}
		colors = associate_set(colors, i, thisColor);
	}

	centroid = new float[3];
	centroid[0] = 0; centroid[1] = 0; centroid[2] = 0;
	set_t firstList = (set_t) mapsto_set(residues, 0);
	caList * firstStruct = (caList*) mapsto_set(calists, 0);
	counter = 0;

	for(i = 0; i<firstStruct->numAcids; i++){
		aminoAcid * thisAcid = firstStruct->acids[i];
		int resNum = thisAcid->residue_number;
		if(contains_set(firstList, resNum)){
			PdbAtom * ca = thisAcid->atoms[0];
			centroid[0] += (float) ca->coords[0];
			centroid[1] += (float) ca->coords[1];
			centroid[2] += (float) ca->coords[2];
			counter++;
		}
	}
	centroid[0] /= (float) counter;
	centroid[1] /= (float) counter;
	centroid[2] /= (float) counter;

}

PocketAlignment::~PocketAlignment()
{

}



set_t PocketAlignment::parseIntegerList(char * string)
{
	set_t result = alloc_set(0);

	char * tempString = new char[10000];
	char * ptr;
	strcpy(tempString, string);

	ptr = strtok(tempString, "{},\r\t\n");
	while(ptr != NULL){
		result = put_set(result, atoi(ptr));
		ptr = strtok(NULL, "{},\r\t\n");
	}

	delete[](tempString);

	return result;
}


double * PocketAlignment::generateAlignment(set_t list1, caList * struct1, set_t list2, caList * struct2, double * LRMSD)
{
	int i = 0;
	int j = 0;
	set_t pairs = alloc_set(0);

	//ensure that l1 is always larger.
	set_t l1 = list1;
	set_t l2 = list2;
	if( size_set(list1) < size_set(list2) ){
		l1 = list2;
		l2 = list1;
	}

	//make pairs the list of all shared amino acids.
	for(i = 0; i<size_set(l2); i++){
		if( contains_set(l1, l2[i]) ){
			pairs = put_set(pairs, l2[i]);
		}
	}

	//create a mapping of indices
	int numShared = size_set(pairs);
	int * index1 = new int[numShared];
	int * index2 = new int[numShared];
	for(i = 0; i<numShared; i++){ index1[i] = -1; index2[i] = -1; }

	for(i = 0; i<struct1->numAcids; i++){
		if( contains_set(pairs, struct1->acids[i]->residue_number) ){
			int localIndex = index_of_set(pairs, struct1->acids[i]->residue_number);
			index1[localIndex] = i;
		}
	}
	for(i = 0; i<struct2->numAcids; i++){
		if( contains_set(pairs, struct2->acids[i]->residue_number) ){
			int localIndex = index_of_set(pairs, struct2->acids[i]->residue_number);
			index2[localIndex] = i;
		}
	}

	///Error check
	for(i = 0; i<numShared; i++){
		if(index1[i] == -1 || index2[i] == -1){
			printf("ERROR: PDB file does not contain the amino acids required for alignment! Exitting!\n");
			exit(1);
		}
	}

	///Assemble the coordinates of the CA atoms, for processing.
	double ** coords1 = new double*[numShared];
	double ** coords2 = new double*[numShared];
	for(i = 0; i<numShared; i++){
		coords1[i] = new double[3];
		coords1[i][0] = struct1->acids[index1[i]]->atoms[0]->coords[0]; ///atoms[0] is always CA.
		coords1[i][1] = struct1->acids[index1[i]]->atoms[0]->coords[1];
		coords1[i][2] = struct1->acids[index1[i]]->atoms[0]->coords[2];
		coords2[i] = new double[3];
		coords2[i][0] = struct2->acids[index2[i]]->atoms[0]->coords[0];
		coords2[i][1] = struct2->acids[index2[i]]->atoms[0]->coords[1];
		coords2[i][2] = struct2->acids[index2[i]]->atoms[0]->coords[2];
	}

	double * transform = new double[16];

	///compute the alignment 
	double * RMSD = min_rmsd(coords1, coords2, numShared, transform);

	///store this value
	LRMSD[0] = RMSD[0];

	///cleanup:
	free_set(pairs);
	delete[](index1);
	delete[](index2);
	for(i = 0; i<numShared; i++){
		delete[](coords1[i]);
		delete[](coords2[i]);
	}
	delete[](coords1);
	delete[](coords2);
	delete[](RMSD);

	return transform;
}























////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef OPENGL_RENDERING


void PocketAlignment::draw(int ** renderSwitch, int ** transparencySwitch)
{

	int i = 0;
	int j = 0;

	GLdouble * m = new GLdouble[16];

	SurfaceObject * firstSurf = (SurfaceObject *) mapsto_set(pockets, 0);

	glTranslatef(-firstSurf->centroid[0], -firstSurf->centroid[1], -firstSurf->centroid[2]);

	for(i = 0; i<numPockets; i++){
		glPushMatrix();
		if(renderSwitch[i][0] == 0){ continue; }
		bool transparent = true;
		if(transparencySwitch[i][0] == 0){ transparent = false; }
		if(transparent == true){ continue; }

		double * thisMatrix = (double *) mapsto_set(alignments, i);
		for(j = 0; j<16; j++){ m[j] = (GLdouble) thisMatrix[j]; }

		glMultMatrixd(m);
		SurfaceObject * s = (SurfaceObject *) mapsto_set(pockets, i);
		double * c = (double *) mapsto_set(colors, i);
		s->draw(false, false, transparent, true, NULL, c);
		glPopMatrix();
	}

	for(i = 0; i<numPockets; i++){
		glPushMatrix();
		if(renderSwitch[i][0] == 0){ continue; }
		bool transparent = true;
		if(transparencySwitch[i][0] == 0){ transparent = false; }
		if(transparent == false){ continue; }

		double * thisMatrix = (double *) mapsto_set(alignments, i);
		for(j = 0; j<16; j++){ m[j] = (GLdouble) thisMatrix[j]; }

		glMultMatrixd(m);
		SurfaceObject * s = (SurfaceObject *) mapsto_set(pockets, i);
		double * c = (double *) mapsto_set(colors, i);
		s->draw(false, false, transparent, true, NULL, c);
		glPopMatrix();
	}

	glPopMatrix();

}



#endif
/////////////////////////////






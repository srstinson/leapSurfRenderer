/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


#include "SurfaceReconstruction.h"






/////////////////////////////////////////////////
////Eliminates interior cavities by analyzing the triangle connectivity.
int * eliminateInteriorCavities(double * pts, int numPts, int * triangles, int numberTriangles, int * numTriangles)
{
	int i = 0;
	int j = 0;

	TargetGrid * tgrid = new TargetGrid(pts, numPts);

	//////////////////////////////////////////////////////////////////////////////////////////////
	///create adjacency info//////////////////////////////////////////////////////////////////////
	set_t top = alloc_set(SP_MAP);
	for(i = 0; i<numPts; i++){
		if(i%10000 == 0){ printf("Adjacency Info processed %i out of %i\n", i, numPts); }
		top = put_set(top, i);
		set_t inSet = alloc_set(0);

		inSet = tgrid->querySphere(pts[3*i+0], pts[3*i+1], pts[3*i+2], .00001, inSet);

		top = associate_set(top, i, inSet);
	}
	///populate adjacency info
	for(i = 0; i<numberTriangles; i++){
		set_t mySet;
		int a = triangles[3*i+0];
		int b = triangles[3*i+1];
		int c = triangles[3*i+2];

		mySet = (set_t) mapsto_set(top, a);
		mySet = put_set(mySet, a); mySet = put_set(mySet, b); mySet = put_set(mySet, c);
		top = associate_set(top, a, mySet);

		mySet = (set_t) mapsto_set(top, b);
		mySet = put_set(mySet, a); mySet = put_set(mySet, b); mySet = put_set(mySet, c);
		top = associate_set(top, b, mySet);

		mySet = (set_t) mapsto_set(top, c);
		mySet = put_set(mySet, a); mySet = put_set(mySet, b); mySet = put_set(mySet, c);
		top = associate_set(top, c, mySet);
	}
	///create adjacency info//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	///Set flags to all points////////////////////////////////////////////////////////////////////
	int * flags = new int[numPts];
	for(i = 0; i<numPts; i++){ 
		set_t tempSet = (set_t) mapsto_set(top, i);
		if( size_set(tempSet) > 1 ){
			flags[i] = i;
		}
		///individual points are automatically cast out.
		if( size_set(tempSet)==1 && contains_set(tempSet, i) ){
			flags[i] = -999999; 
		}
		if( size_set(tempSet) == 0){
			printf("WTF NOTHING SHOULD BE EMPTY! ERROR!\n");
		}
	}
	///Set flags to all points////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	///now perform union find on the flags.///////////////////////////////////////////////////////
	int flagCounter = -1;
	///find the first member which is non-negative
	int nextMember = 0;
	for(i = 0; i<numPts; i++){
		if(flags[nextMember]<0){ nextMember++; }
		else{ break; }
	}
	int paintCounter = 0; ///debug
	bool completion = false;
	while(completion == false){
		printf("Found a new disconnected piece of topology.  Labelled it %i\n", flagCounter);
		set_t wavefront = alloc_set(0);
		set_t nextwave = alloc_set(0);
		wavefront = put_set(wavefront, nextMember);

		while(size_set(wavefront) > 0){
			//printf("inner loop, with %i members in wavefront, painted %i\n", size_set(wavefront), paintCounter );
			///mark the wavefront.
			for(i = 0; i<size_set(wavefront); i++){ flags[wavefront[i]] = flagCounter; paintCounter++;}
			///propagate the nextwave.
			for(i = 0; i<size_set(wavefront); i++){
				set_t mySet = (set_t) mapsto_set(top, wavefront[i]);
				for(j = 0; j<size_set(mySet); j++){
					if( flags[mySet[j]] >= 0 ){ nextwave = put_set(nextwave, mySet[j]); }
				}				
			}

			///swap the nextwave for the wavefront
			free_set(wavefront);
			wavefront = nextwave;
			nextwave = alloc_set(0);
		}

		free_set(wavefront);
		free_set(nextwave);

		///test completion
		completion = true;
		for(i = 0; i<numPts; i++){
			if(flags[i]>=0){ 
				nextMember = i;
				flagCounter--;
				completion = false; 
				break; 
			}
		}
	}
	///now perform union find on the flags.///////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////////
	///free the adjency information
	for(i = 0; i<size_set(top); i++){
		set_t tempSet = (set_t) mapsto_set(top, i);
		free_set(tempSet);
	}
	free_set(top);
	///free the adjency information
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	/////now find the largest flag;  There are exactly -flagCounter different flags
	int * counts = new int[-flagCounter];
	for(i = 0; i<-flagCounter; i++){ counts[i] = 0; }
	for(i = 0; i<numPts; i++){
		if(flags[i] != -999999){
			counts[ (-flags[i])-1 ]++;		//each flag is negative, and greater by one, of its position.
		}
	}

	int largest = 0;
	int max = 0;
	for(i = 0; i<-flagCounter; i++){
		if(max < counts[i]){
			largest = i;
			max = counts[i];
		}
	}
	delete[](counts);
	/////now find the largest flag;  There are exactly -flagCounter different flags
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	////now the largest flag is the one labelled largest, which corresponds to flag (-largest)-1;
	///now count the number of remaining triangles;
	int numFinalTriangles = 0;
	for(i = 0; i<numberTriangles; i++){
		int fa = flags[ triangles[3*i+0] ];
		int fb = flags[ triangles[3*i+1] ];
		int fc = flags[ triangles[3*i+2] ];

		if( (fa!=fb) || (fb!=fc) || (fc!=fa) ){ 
			printf("ERROR!!! UNION FIND FAILED!!!\n"); exit(1); 
		}
		if( fa == (-largest)-1 ){
			numFinalTriangles++;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	///now allocate the result;
	int * result = new int[3*numFinalTriangles];
	numFinalTriangles = 0;
	for(i = 0; i<numberTriangles; i++){
		int fa = flags[ triangles[3*i+0] ];
		int fb = flags[ triangles[3*i+1] ];
		int fc = flags[ triangles[3*i+2] ];

		if( (fa!=fb) || (fb!=fc) || (fc!=fa) ){ printf("ERROR!!! UNION FIND FAILED!!!\n"); exit(1); }
		if( fa == (-largest)-1 ){
			result[ 3*numFinalTriangles+0 ] = triangles[3*i+0];
			result[ 3*numFinalTriangles+1 ] = triangles[3*i+1];
			result[ 3*numFinalTriangles+2 ] = triangles[3*i+2];
			numFinalTriangles++;
		}
	}


	delete[](flags);
	numTriangles[0] = numFinalTriangles;
	return result;
}






















/////////////////////////////////////////////////////////////////////////////////////////////
///this union find groups together all connected patches, and returns them in a set of sets
set_t findDisparatePatches(double * inputPts, int inputNumPts, int * inputTriangles, int numberTriangles)
{
	int i = 0;
	int j = 0;

	printf("identifying used points\n");
	set_t usedPts = alloc_set(0);
	for(i = 0; i<numberTriangles; i++){
		usedPts = put_set(usedPts, inputTriangles[3*i+0]);
		usedPts = put_set(usedPts, inputTriangles[3*i+1]);
		usedPts = put_set(usedPts, inputTriangles[3*i+2]);
	}

	printf("eliminating unused POints\n");
	int * ptMapping = new int[size_set(usedPts)];
	int * RevPtMapping = new int[inputNumPts];
	for(i = 0; i<inputNumPts; i++){ RevPtMapping[i] = -1; }
	double * pts = new double[3*(size_set(usedPts))];
	int counter = 0;
	for(i = 0; i<inputNumPts; i++){
		if( !contains_set(usedPts, i) ){ continue; }
		ptMapping[counter] = i;
		RevPtMapping[i] = counter;
		pts[3*counter+0] = inputPts[3*i+0];
		pts[3*counter+1] = inputPts[3*i+1];
		pts[3*counter+2] = inputPts[3*i+2];
		counter++;
	}
	int numPts = counter;
	free_set(usedPts);

	printf("Old Pts: %i  new Points: %i\n", inputNumPts, counter);

	printf("remap the triangle arrays\n");
	int * triangles = new int[3*numberTriangles];
	for(i = 0; i<numberTriangles; i++){
		triangles[3*i+0] = RevPtMapping[ inputTriangles[3*i+0] ];
		triangles[3*i+1] = RevPtMapping[ inputTriangles[3*i+1] ];
		triangles[3*i+2] = RevPtMapping[ inputTriangles[3*i+2] ];
	}
	delete[](RevPtMapping);
	
	TargetGrid * tgrid = new TargetGrid(pts, numPts);

	//////////////////////////////////////////////////////////////////////////////////////////////
	///create adjacency info//////////////////////////////////////////////////////////////////////
	set_t top = alloc_set(SP_MAP);
	for(i = 0; i<numPts; i++){
		if(i%100000 == 0){ printf("Adjacency Info processed %i out of %i\n", i, numPts); }
		top = put_set(top, i);
		set_t inSet = alloc_set(0);

		inSet = tgrid->querySphere(pts[3*i+0], pts[3*i+1], pts[3*i+2], .00001, inSet);

		top = associate_set(top, i, inSet);
	}
	///populate adjacency info
	for(i = 0; i<numberTriangles; i++){
		set_t mySet;
		int a = triangles[3*i+0];
		int b = triangles[3*i+1];
		int c = triangles[3*i+2];

		mySet = (set_t) mapsto_set(top, a);
		mySet = put_set(mySet, a); mySet = put_set(mySet, b); mySet = put_set(mySet, c);
		top = associate_set(top, a, mySet);

		mySet = (set_t) mapsto_set(top, b);
		mySet = put_set(mySet, a); mySet = put_set(mySet, b); mySet = put_set(mySet, c);
		top = associate_set(top, b, mySet);

		mySet = (set_t) mapsto_set(top, c);
		mySet = put_set(mySet, a); mySet = put_set(mySet, b); mySet = put_set(mySet, c);
		top = associate_set(top, c, mySet);
	}
	///create adjacency info//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	delete(tgrid);

	//////////////////////////////////////////////////////////////////////////////////////////////
	///Set flags to all points////////////////////////////////////////////////////////////////////
	int * flags = new int[numPts];
	for(i = 0; i<numPts; i++){ 
		set_t tempSet = (set_t) mapsto_set(top, i);
		if( size_set(tempSet) > 1 ){
			flags[i] = i;
		}
		///individual points are automatically cast out.
		if( size_set(tempSet)==1 && contains_set(tempSet, i) ){
			flags[i] = -999999; 
		}
		if( size_set(tempSet) == 0){
			printf("WTF NOTHING SHOULD BE EMPTY! ERROR!\n");
		}
	}
	///Set flags to all points////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	///now perform union find on the flags.///////////////////////////////////////////////////////
	int flagCounter = -1;
	///find the first member which is non-negative
	int nextMember = 0;
	for(i = 0; i<numPts; i++){
		if(flags[nextMember]<0){ nextMember++; }
		else{ break; }
	}
	int paintCounter = 0; ///debug
	bool completion = false;
	while(completion == false){
		//printf("Found a new disconnected piece of topology.  Labelled it %i\n", flagCounter);
		set_t wavefront = alloc_set(0);
		set_t nextwave = alloc_set(0);
		wavefront = put_set(wavefront, nextMember);

		while(size_set(wavefront) > 0){
			//printf("inner loop, with %i members in wavefront, painted %i\n", size_set(wavefront), paintCounter );
			///mark the wavefront.
			for(i = 0; i<size_set(wavefront); i++){ flags[wavefront[i]] = flagCounter; paintCounter++;}
			///propagate the nextwave.
			for(i = 0; i<size_set(wavefront); i++){
				set_t mySet = (set_t) mapsto_set(top, wavefront[i]);
				for(j = 0; j<size_set(mySet); j++){
					if( flags[mySet[j]] >= 0 ){ nextwave = put_set(nextwave, mySet[j]); }
				}				
			}

			///swap the nextwave for the wavefront
			free_set(wavefront);
			wavefront = nextwave;
			nextwave = alloc_set(0);
		}

		free_set(wavefront);
		free_set(nextwave);

		///test completion
		completion = true;
		for(i = 0; i<numPts; i++){
			if(flags[i]>=0){ 
				nextMember = i;
				flagCounter--;
				completion = false; 
				break; 
			}
		}
	}
	///now perform union find on the flags.///////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////////
	///free the adjency information
	for(i = 0; i<size_set(top); i++){
		set_t tempSet = (set_t) mapsto_set(top, i);
		free_set(tempSet);
	}
	free_set(top);
	///free the adjency information
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	/////Count the number of points with each flag
	int * counts = new int[-flagCounter];
	for(i = 0; i<-flagCounter; i++){ counts[i] = 0; }
	for(i = 0; i<numPts; i++){
		if(flags[i] != -999999){
			counts[ (-flags[i])-1 ]++;		//each flag is negative, and greater by one, of its position.
		}
	}

	/////now sort the flags by size;  There are exactly -flagCounter different flags
	int * flagSizes = new int[-flagCounter];
	int * ref = new int[-flagCounter];
	for(i = 0; i<-flagCounter; i++){ 
		flagSizes[i] = counts[i];
		ref[i] = i; 
	}
	mergeSort(flagSizes, ref, -flagCounter);

	set_t tempResult = alloc_set(SP_MAP);
	///create the result data structure
	for(i = 0; i<-flagCounter; i++){
		set_t tempSet = alloc_set(0);
		tempResult = associate_set(tempResult, i, tempSet);
	}
	///fill the result data structure
	for(i = 0; i<numPts; i++){
		int tempFlag = (-flags[i])-1;
		set_t tempSet = (set_t) mapsto_set(tempResult, tempFlag);
		tempSet = put_set(tempSet, ptMapping[ i ]);	///notice that we map back to original point numbers
		tempResult = associate_set(tempResult, tempFlag, tempSet);
	}
	///sort the result data structure
	set_t result = alloc_set(SP_MAP);
	for(i = 0; i<-flagCounter; i++){
		set_t tempSet = (set_t) mapsto_set(tempResult, ref[i]);
		result = associate_set(result, -flagCounter-i-1, tempSet);
	}
	free_set(tempResult);

	for(i = 0; i<-flagCounter; i++){ 
		set_t tempSet = (set_t) mapsto_set(result, i);
//		printf("Class %i has %i members.  First five: %i %i %i %i %i\n", i, size_set(tempSet), tempSet[0], tempSet[1], tempSet[2], tempSet[3], tempSet[4]  );
	}


	delete[](ptMapping);
	delete[](pts);
	delete[](triangles);
	delete[](flags);
	delete[](counts);
	delete[](flagSizes);
	delete[](ref);

	return result;

}





///this function surveys the areas of triangles in the surface, and outputs the results in a histogram.
void surveyTriangleAreas(SurfaceObject * obj, int numBars)
{
	int i = 0;
	int j = 0;
	
	//initialize the histogram
	int * hist = new int[numBars];
	for(i = 0; i<numBars; i++){ hist[i] = 0; }
	
//	double * surfacePoints;
//	double * surfaceNormals;		///these averaged normals are used for rendering
//	int numTriangles;
//	int * triangles;

	//get the area min-max;
	double areaMin = HUGE_VAL;
	double areaMax = 0;
	double areaAvg = 0;
	double * t1 = new double[3];
	double * t2 = new double[3];
	double * t3 = new double[3];
	for(i = 0; i<obj->numTriangles; i++){
		t1[0] = obj->surfacePoints[3*(obj->triangles[3*i+0])+0];
		t1[1] = obj->surfacePoints[3*(obj->triangles[3*i+0])+1];
		t1[2] = obj->surfacePoints[3*(obj->triangles[3*i+0])+2];
		
		t2[0] = obj->surfacePoints[3*(obj->triangles[3*i+1])+0];
		t2[1] = obj->surfacePoints[3*(obj->triangles[3*i+1])+1];
		t2[2] = obj->surfacePoints[3*(obj->triangles[3*i+1])+2];
		
		t3[0] = obj->surfacePoints[3*(obj->triangles[3*i+2])+0];
		t3[1] = obj->surfacePoints[3*(obj->triangles[3*i+2])+1];
		t3[2] = obj->surfacePoints[3*(obj->triangles[3*i+2])+2];

		double tempArea = triangleArea(t1, t2, t3);
		if(tempArea > areaMax){ areaMax = tempArea; }
		if(tempArea < areaMin){ areaMin = tempArea; }
		areaAvg += tempArea;
	}

	areaAvg /= obj->numTriangles;

	int tempCounter = 0;

	for(i = 0; i<obj->numTriangles; i++){
		t1[0] = obj->surfacePoints[3*(obj->triangles[3*i+0])+0];
		t1[1] = obj->surfacePoints[3*(obj->triangles[3*i+0])+1];
		t1[2] = obj->surfacePoints[3*(obj->triangles[3*i+0])+2];
		
		t2[0] = obj->surfacePoints[3*(obj->triangles[3*i+1])+0];
		t2[1] = obj->surfacePoints[3*(obj->triangles[3*i+1])+1];
		t2[2] = obj->surfacePoints[3*(obj->triangles[3*i+1])+2];
		
		t3[0] = obj->surfacePoints[3*(obj->triangles[3*i+2])+0];
		t3[1] = obj->surfacePoints[3*(obj->triangles[3*i+2])+1];
		t3[2] = obj->surfacePoints[3*(obj->triangles[3*i+2])+2];

		double tempArea = triangleArea(t1, t2, t3);
		if(tempArea < .0001){tempCounter++;} 
		
		//find the bin
		double normalizedVal = (tempArea-areaMin)/(areaMax-areaMin);
		int bin;
		if((normalizedVal < 1) && (normalizedVal > 0) ){ bin = (int) (normalizedVal*((double)numBars)); }
		else{
			if(normalizedVal == 1){ bin = numBars-1; }
			if(normalizedVal == 0){ bin = 0; }
		}
		
		hist[bin]++;
	}

	///print out the results in stdout.
	printf("SurfaceObject Triangle Area Survey:\n");
	printf("MAX: %lf    MIN: %lf   AVG: %lf   #triangles: %i\n", areaMax, areaMin, areaAvg, obj->numTriangles);
	printf("==========================================================================\n");
	for(i = 0; i<numBars; i++){
		printf("%6.2lf - %6.2lf: ", ((double)i)*( (areaMax-areaMin)/((double)numBars) ), ((double)(i+1))*( (areaMax-areaMin)/((double)numBars) ) );
		int numPounds = ( (int) (( ((double) hist[i]) / ((double) obj->numTriangles) )*100.0) );
		if(hist[i] > 0){ for(j = 0; j<numPounds+1; j++){ printf("#"); } }
		else{ printf(" "); }
		printf(" %i (%lf%%)\n", hist[i], ( ((double) hist[i]) / ((double) obj->numTriangles) )*100.0 );
	}
	printf("==========================================================================\n");

	delete[](hist);	
}






///this function surveys the edge Lengths of triangles in the surface, and outputs the results in a histogram. (all edges appear twice)
void surveyTriangleEdges(SurfaceObject * obj, int numBars)
{
	int i = 0;
	int j = 0;
	
	//initialize the histogram
	double * hist = new double[numBars];
	for(i = 0; i<numBars; i++){ hist[i] = 0; }
	
//	double * surfacePoints;
//	double * surfaceNormals;		///these averaged normals are used for rendering
//	int numTriangles;
//	int * triangles;

	//get the area min-max;
	double lenMin = HUGE_VAL;
	double lenMax = 0;
	double * t1 = new double[3];
	double * t2 = new double[3];
	double * t3 = new double[3];
	for(i = 0; i<obj->numTriangles; i++){
		t1[0] = obj->surfacePoints[3*(obj->triangles[3*i+0])+0];
		t1[1] = obj->surfacePoints[3*(obj->triangles[3*i+0])+1];
		t1[2] = obj->surfacePoints[3*(obj->triangles[3*i+0])+2];
		
		t2[0] = obj->surfacePoints[3*(obj->triangles[3*i+1])+0];
		t2[1] = obj->surfacePoints[3*(obj->triangles[3*i+1])+1];
		t2[2] = obj->surfacePoints[3*(obj->triangles[3*i+1])+2];
		
		t3[0] = obj->surfacePoints[3*(obj->triangles[3*i+2])+0];
		t3[1] = obj->surfacePoints[3*(obj->triangles[3*i+2])+1];
		t3[2] = obj->surfacePoints[3*(obj->triangles[3*i+2])+2];

		double l1 = vectorSize(t2[0]-t1[0], t2[1]-t1[1], t2[2]-t1[2]);
		double l2 = vectorSize(t3[0]-t2[0], t3[1]-t2[1], t3[2]-t2[2]);
		double l3 = vectorSize(t1[0]-t3[0], t1[1]-t3[1], t1[2]-t3[2]);

		if(l1 > 30 || l2 > 30 || l3 > 30){ printf("WTF!: triangle %i has lengths %lf %lf %lf\n", i, l1, l2, l3); exit(1);}

		if(l1 > lenMax){ lenMax = l1; }
		if(l1 < lenMin){ lenMin = l1; }
		if(l2 > lenMax){ lenMax = l2; }
		if(l2 < lenMin){ lenMin = l2; }
		if(l3 > lenMax){ lenMax = l3; }
		if(l3 < lenMin){ lenMin = l3; }
	}

	int tempCounter = 0;

	for(i = 0; i<obj->numTriangles; i++){
		t1[0] = obj->surfacePoints[3*(obj->triangles[3*i+0])+0];
		t1[1] = obj->surfacePoints[3*(obj->triangles[3*i+0])+1];
		t1[2] = obj->surfacePoints[3*(obj->triangles[3*i+0])+2];
		
		t2[0] = obj->surfacePoints[3*(obj->triangles[3*i+1])+0];
		t2[1] = obj->surfacePoints[3*(obj->triangles[3*i+1])+1];
		t2[2] = obj->surfacePoints[3*(obj->triangles[3*i+1])+2];
		
		t3[0] = obj->surfacePoints[3*(obj->triangles[3*i+2])+0];
		t3[1] = obj->surfacePoints[3*(obj->triangles[3*i+2])+1];
		t3[2] = obj->surfacePoints[3*(obj->triangles[3*i+2])+2];

		double l1 = vectorSize(t2[0]-t1[0], t2[1]-t1[1], t2[2]-t1[2]);
		double l2 = vectorSize(t3[0]-t2[0], t3[1]-t2[1], t3[2]-t2[2]);
		double l3 = vectorSize(t1[0]-t3[0], t1[1]-t3[1], t1[2]-t3[2]);

		//find the bin
		int bin;
		double normalizedVal = (l1-lenMin)/(lenMax-lenMin);
		if((normalizedVal < 1) && (normalizedVal > 0) ){ bin = (int) (normalizedVal*((double)numBars)); }
		else{ if(normalizedVal == 1){ bin = numBars-1; } if(normalizedVal == 0){ bin = 0; } }
		hist[bin] += .5;

		normalizedVal = (l2-lenMin)/(lenMax-lenMin);
		if((normalizedVal < 1) && (normalizedVal > 0) ){ bin = (int) (normalizedVal*((double)numBars)); }
		else{ if(normalizedVal == 1){ bin = numBars-1; } if(normalizedVal == 0){ bin = 0; } }
		hist[bin] += .5;

		normalizedVal = (l3-lenMin)/(lenMax-lenMin);
		if((normalizedVal < 1) && (normalizedVal > 0) ){ bin = (int) (normalizedVal*((double)numBars)); }
		else{ if(normalizedVal == 1){ bin = numBars-1; } if(normalizedVal == 0){ bin = 0; } }
		hist[bin] += .5;
	}

	//printf("Number of triangles under area .005: %i\n", tempCounter);

	///print out the results in stdout.
	printf("SurfaceObject Triangle EdgeLength Survey:\n");
	printf("MAX: %lf    MIN: %lf\n", lenMax, lenMin);
	printf("==========================================================================\n");
	for(i = 0; i<numBars; i++){
		printf("%6.2lf - %6.2lf: ", ((double)i)*( (lenMax-lenMin)/((double)numBars) ), ((double)(i+1))*( (lenMax-lenMin)/((double)numBars) ) );
		int numPounds = ( (int) (( ((double) hist[i]) / ((double) obj->numTriangles) )*100.0) );
		if(hist[i] > 0){ for(j = 0; j<numPounds+1; j++){ printf("#"); } }
		else{ printf(" "); }
		printf(" %.0lf (%lf%%)\n", hist[i], ( ((double) hist[i]) / ((double) obj->numTriangles) )*100.0 );
	}
	printf("==========================================================================\n");

	delete[](hist);	
}


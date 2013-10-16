#include "SurfaceSet.h"

SurfaceSet::SurfaceSet() {
		vector = * new std::vector<SurfaceObject>();
		//currentSurface holds the index of the current surface "pointed at".
		//It is -1 when the list is empty, which leads to a number of condidtionals
		//later on.
		currentSurface = -1;
}

SurfaceSet::SurfaceSet() {
	delete &vector;
}

void SurfaceSet::addSurface(SurfaceObject s) {
	vector.push_back(s);

	//If the vector just had its first element added,
	//We can set the first element as the current pointed to element.
	//Otherwise we maintain the current pointer.
	if (vector.size==1) {
		currentSurface=0;
	}
}

void SurfaceSet::deleteCurrentSurface() {
	//If it's empty, call does nothing. Maybe throw some sort of exception/error?
	if (currentSurface!=-1) {
		vector.erase(vector.begin()+currentSurface);
		//Will go to the previous element as the current Surface available to edit.
		//If there's none left it will go to -1, the "empty" state.
		currentSurface--;
	}
}

SurfaceObject *SurfaceSet::getCurrentSurface() {
	//If the list is empty we return a null value, otherwise
	//return a pointer to that element.
	if (currentSurface == -1) {
		return NULL;
	}
	return &vector.at(currentSurface);
}

void incrementSurfacePointer(); {
	//If the list is empty nothing to do!.
	if (currentSurface == -1) {
		return;
	}
	//If the element is at the end "rotate" it around to
	//the beginning, otherwise just increment it.
	if (currentSurface == vector.size()-1) {
		currentSurface = 0;
	}
	else {
		currentSurface++;
	}
}
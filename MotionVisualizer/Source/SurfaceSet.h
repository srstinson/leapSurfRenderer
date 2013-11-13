#include "../SurfRenderer/SurfaceObject.h"
#include <vector>


using std::vector;

/*
* SurfaceSet is a set of surfaces. Because the program is designed to allow editing of
* one surface at a time, this maintains a list of surfaces and allows the user to increment
* the current surface pointed at, and get/delete that specific one. Once gotten, the user can edit
* the surface itself. No random access is allowed as that introduces the possibility for large amounts of complexity
* which a touch interface cannot work with well.
*/ 
class SurfaceSet {
private:
	vector<SurfaceObject> vector;

	int currentSurface;

public:
	SurfaceSet();
	~SurfaceSet();
	void addSurface(SurfaceObject);
	SurfaceObject *getCurrentSurface();
	void incrementSurfacePointer();
	void deleteCurrentSurface();	
};
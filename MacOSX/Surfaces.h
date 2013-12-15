/*
 Surfaces
 Description: Surfaces holds the data structures for storing protein surface sets, is responsible for manipulating the surface sets, and controls which protein surface models are drawn and the transformations applied to these surfaces.
 */

#ifndef __MotionVisualizer__Surfaces__
#define __MotionVisualizer__Surfaces__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include "SurfaceObject.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class Surfaces{
private:
    std::vector<std::string> surfSets; //Vector of surface set filenames
    std::vector<std::vector<std::string> > surfsInSet; //Vector of vectors of surface filenames for each set
    int surfSetIndex = 0; //Surface set pointer
    int surfIndex1 = -1; //Query surface pointer
    int surfIndex2 = -1; //Compared surface pointer
    std::string currentFile; //Query surface filename
    std::string comparedFile; //Compared surface filename
    std::string setName; //Currently displayed set name
    
    SurfaceObject * surf = NULL; //Query Surface
    SurfaceObject * surfCompared = NULL; //Compared Surface
    CriticalSection mutex; //Mutex
public:
    //Constructor
    Surfaces();
    
    //Builds surfSets and surfsInSet
    void initializeSurfaces();
    
    //Finds all files with specific extension
    std::vector<std::string> getAllFilesWithExtension(const std::string & ext);
    
    //Accessors
    std::vector<std::string> getSurfSets();
    std::vector<std::vector<std::string>> getSurfsInSet();
    int getSurfSetIndex();
    int getSurfIndex(int surfaceNum);
    std::string getCurrentFileName();
    std::string getComparedFileName();
    std::string getSetFileName();
    
    //Mutators
    void setSurfSetIndex(int index);
    void setSurfIndex(int surfaceNum, int index);
    void setCurrentFileName(std::string name);
    void setComparedFileName(std::string name);
    void setSetFileName(std::string name);
    
    //Draw query and compared surfaces
    void draw(glm::quat myQuaternion, int keyFlag, bool transparent);
    
    //Parse surface files and prepare for drawing
    void setSurfaces(bool loadSurfaces);
    
    //Surface set pointer right
    void groupPointerRight();
    
    //Surface set pointer left
    void groupPointerLeft();
    
    //Query (0) or compared (1) surface pointer right
    void surfacePointerRight(int surfFoc);
    
    //Query (0) or compared (1) surface pointer left
    void surfacePointerLeft(int surfFoc);
    
    //Move query surface to the set to the right
    void moveSurface();
    
    //Save state of surface sets
    void saveSurfSets();
    
    //Create a new set
    void newSet();
};

#endif

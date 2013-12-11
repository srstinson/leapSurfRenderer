//
//  Surfaces.h
//  MotionVisualizer
//
//  Created by Zach Daniels on 12/10/13.
//
//

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
    std::vector<std::string> surfSets;
    std::vector<std::vector<std::string> > surfsInSet;
    int surfSetIndex = 0;
    int surfIndex1 = -1;
    int surfIndex2 = -1;
    std::string currentFile;
    std::string comparedFile;
    std::string setName;
    
    SurfaceObject * surf = NULL;
    SurfaceObject * surfCompared = NULL;
    CriticalSection mutex;
public:
    Surfaces();
    void initializeSurfaces();
    std::vector<std::string> getAllFilesWithExtension(const std::string & ext);
    std::vector<std::string> getSurfSets();
    std::vector<std::vector<std::string>> getSurfsInSet();
    int getSurfSetIndex();
    void setSurfSetIndex(int index);
    int getSurfIndex(int surfaceNum);
    void setSurfIndex(int surfaceNum, int index);
    std::string getCurrentFileName();
    void setCurrentFileName(std::string name);
    std::string getComparedFileName();
    void setComparedFileName(std::string name);
    std::string getSetFileName();
    void setSetFileName(std::string name);
    void draw(glm::quat myQuaternion, int keyFlag, bool transparent);
    void setSurfaces(bool loadSurfaces);
    void groupPointerRight();
    void groupPointerLeft();
    void surfacePointerRight(int surfFoc);
    void surfacePointerLeft(int surfFoc);
    void moveSurface();
    void saveSurfSets();
    void newSet();
};

#endif /* defined(__MotionVisualizer__Surfaces__) */

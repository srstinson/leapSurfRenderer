/*
 Surfaces
 Description: Surfaces holds the data structures for storing protein surface sets, is responsible for manipulating the surface sets, and controls which protein surface models are drawn and the transformations applied to these surfaces.
 */

#include "Surfaces.h"
//#include <ctime> //For Benchmarking

//int print = 0; //For Benchmarking

Surfaces::Surfaces(){
    currentFile = "";
    comparedFile = "";
    setName = "";
    initializeSurfaces();
}

void Surfaces::initializeSurfaces(){
    surfSets = getAllFilesWithExtension(".SURFSET");
    for(int i =  0; i < surfSets.size(); i++){
        std::vector<std::string> surfaces;
        std::ifstream file;
        file.open(surfSets[i].c_str());
        std::string surfLoc;
        while (file.good())
        {
            getline (file, surfLoc, ',');
            surfLoc = std::string(surfLoc, 0, surfLoc.length());
            std::cout<<surfLoc<<std::endl;
            surfaces.push_back(surfLoc);
        }
        surfsInSet.push_back(surfaces);
    }
}

std::vector<std::string> Surfaces::getAllFilesWithExtension(const std::string & ext)
{
    std::vector<std::string> surfSets2;
    DIR* dirp = opendir(".");
    dirent* dp;
    while ((dp = readdir(dirp)) != NULL){
        std::string filePathString = dp->d_name;
        if(filePathString.find(".SURFSET") != filePathString.npos){
            surfSets2.push_back(filePathString);
            //std::cout<<filePathString<<std::endl;
        }
    }
    (void)closedir(dirp);
    
    return surfSets2;
}

std::vector<std::string> Surfaces::getSurfSets(){
    return surfSets;
}

std::vector<std::vector<std::string>> Surfaces::getSurfsInSet(){
    return surfsInSet;
}

int Surfaces::getSurfSetIndex(){
    return surfSetIndex;
}

int Surfaces::getSurfIndex(int surfaceNum){
    if(surfaceNum == 2){
        return surfIndex2;
    }
    return surfIndex1;
}

void Surfaces::setSurfSetIndex(int index){
    surfSetIndex = index;
}

void Surfaces::setSurfIndex(int surfaceNum, int index){
    if(surfaceNum == 1){
        surfIndex2 = index;
    }
    else{
        surfIndex1 = index;
    }
}

std::string Surfaces::getCurrentFileName(){
    return currentFile;
}

void Surfaces::setCurrentFileName(std::string name){
    currentFile = name;
}

std::string Surfaces::getComparedFileName(){
    return comparedFile;
}

void Surfaces::setComparedFileName(std::string name){
    comparedFile = name;
}

std::string Surfaces::getSetFileName(){
    return setName;
}

void Surfaces::setSetFileName(std::string name){
    setName = name;
}

void Surfaces::draw(glm::quat myQuaternion, int keyFlag, bool transparent){
    
    //clock_t begin = clock(); //For Benchmarking
    
    if (currentFile.compare("") != 0 && keyFlag == 0){
        
        if(surf == NULL){
            printf("File not found! Try again.\n");
        }
        else{
            glm::mat4 rotationMatrix = glm::toMat4(myQuaternion);
            glMultMatrixf(glm::value_ptr(rotationMatrix));
            glPushMatrix();
            
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 1000.0, 0.0, 0.0 );
            glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 1000.0, 0.0 );
            glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 0.0, 1000.0 );
            glEnd();
            glBegin(GL_POINTS);
            glColor3f(1.0f, 1.0f, 1.0f);	glVertex3f( 0.0, 0.0, 0.0 );
            glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f( 1.0, 0.0, 0.0 );  glVertex3f( 2.0, 0.0, 0.0 );
            glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f( 0.0, 1.0, 0.0 );  glVertex3f( 0.0, 2.0, 0.0 );
            glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f( 0.0, 0.0, 1.0 );  glVertex3f( 0.0, 0.0, 2.0 );
            glEnd();
            
            glTranslatef(-surf->centroid[0], -surf->centroid[1], -surf->centroid[2]);
            mutex.enter();
            surf->draw(false, false, transparent, true, NULL, NULL);
            if(comparedFile != ""){
                surfCompared->draw(false, false, true, true, NULL, NULL);
            }
            mutex.exit();
            glPopMatrix();
        }
        //For Benchmarking
        /*clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        
        if (print == 0){
            std::cout<<surf->numTriangles<<"\t"<<elapsed_secs<<std::endl;
            print++;
        }*/

    }
}

void Surfaces::setSurfaces(bool loadSurfaces){
    mutex.enter();
    SurfaceObject * surfTemp = NULL;
    SurfaceObject * surfTemp2 = NULL;
    
    std::cout<<surf<<" "<<surfCompared<<std::endl;
    
    if(surf != NULL){
        surfTemp = surf;
    }
    if(surfCompared != NULL){
        surfTemp2 = surfCompared;
    }
        
    if(surfIndex1 != -1 && surfSetIndex > 0){
        currentFile = surfsInSet[surfSetIndex-1][surfIndex1];
    }
    if(surfIndex2 != -1 && surfSetIndex > 0 && surfsInSet[surfSetIndex-1].size() > 1){
        comparedFile = surfsInSet[surfSetIndex-1][surfIndex2];
    }
    if(currentFile != ""){
        char *cstr = new char[currentFile.length() + 1];
        strcpy(cstr, currentFile.c_str());
        surf = parseGeometryFile(cstr);
        delete [] cstr;
    }
    if(comparedFile != ""){
        char *cstr = new char[comparedFile.length() + 1];
        strcpy(cstr, comparedFile.c_str());
        surfCompared = parseGeometryFile(cstr);
        delete [] cstr;
    }
    
    if(surfTemp != NULL){
        if(surf == surfTemp){
            surf = NULL;
        }
        std::cout<<surf<<" "<<surfTemp<<std::endl;
        surfTemp->dispose();
    }
    if(surfTemp2 != NULL){
        if(surfCompared == surfTemp2){
            surfCompared = NULL;
        }
        std::cout<<surfCompared<<" "<<surfTemp2<<std::endl;
        surfTemp2->dispose();
    }
    //print = 0; //For Benchmarking
    mutex.exit();
}

void Surfaces::groupPointerRight(){
    if(surfSetIndex == surfSets.size()){
        surfSetIndex = 0;
    }
    else{
        surfSetIndex++;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 1){
        surfIndex1 = 0;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 2){
        surfIndex2 = 1;
    }
    if(surfSetIndex == 0){
        currentFile = "";
        comparedFile = "";
        surfIndex1 = -1;
        surfIndex2 = -1;
    }
    setSurfaces(true);
}

void Surfaces::groupPointerLeft(){
    if(surfSetIndex == 0){
        surfSetIndex = surfSets.size();
    }
    else{
        surfSetIndex--;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 1){
        surfIndex1 = 0;
    }
    if(surfsInSet[surfSetIndex-1].size() >= 2){
        surfIndex2 = 1;
    }
    if(surfSetIndex == 0){
        currentFile = "";
        comparedFile = "";
        surfIndex1 = -1;
        surfIndex2 = -1;
    }
    setSurfaces(true);
}

void Surfaces::surfacePointerRight(int surfFoc){
    if (surfFoc == 0){
        if(surfIndex2 != -1){
            if(surfIndex2 == surfsInSet[surfSetIndex-1].size()-1){
                surfIndex2 = 0;
            }
            else{
                surfIndex2++;
            }
        }
    }
    else{
        if(surfIndex1 != -1){
            if(surfIndex1 == surfsInSet[surfSetIndex-1].size()-1){
                surfIndex1 = 0;
            }
            else{
                surfIndex1++;
            }
        }
    }
    setSurfaces(true);
}

void Surfaces::surfacePointerLeft(int surfFoc){
    if (surfFoc == 0){
        if(surfIndex2 != -1){
            if(surfIndex2 == 0){
                surfIndex2 = surfsInSet[surfSetIndex-1].size()-1;
            }
            else{
                surfIndex2--;
            }
        }
    }
    else{
        if(surfIndex1 != -1){
            if(surfIndex1 == 0){
                surfIndex1 = surfsInSet[surfSetIndex-1].size()-1;
            }
            else{
                surfIndex1--;
            }
        }
    }
    setSurfaces(true);
}

void Surfaces::moveSurface(){
    if(surfIndex1 != -1 && surfSets.size() > 1){
        surfsInSet[surfSetIndex - 1].erase(surfsInSet[surfSetIndex - 1].begin() + surfIndex1);
        if(surfSetIndex == surfSets.size()){
            surfSetIndex = 1;
        }
        else{
            surfSetIndex++;
        }
        surfsInSet[surfSetIndex - 1].push_back(currentFile);
        surfIndex1 = surfsInSet[surfSetIndex - 1].size()-1;
        surfIndex2 = 0;
    }
    else if(surfSets.size() > 0 && currentFile != ""){
        surfsInSet[0].push_back(currentFile);
        surfSetIndex = 1;
        surfIndex1 = surfsInSet[0].size()-1;
        surfIndex2 = 0;
    }
    setSurfaces(true);
}

void Surfaces::saveSurfSets(){
    for(int i = 0; i < surfSets.size(); i++){
        std::string setBeingSaved = surfSets[i];
        std::string fileText = "";
        std::ofstream saveFile;
        saveFile.open(setBeingSaved.c_str());
        for(int j = 0; j < surfsInSet[i].size(); j++){
            fileText += surfsInSet[i][j];
            if (j != surfsInSet[i].size() - 1){
                fileText += ",";
            }
        }
        saveFile << fileText;
        saveFile.close();
    }
}

void Surfaces::newSet(){
    mutex.enter();
    surfSets.push_back(setName);
    std::vector<std::string> tempSet;
    if(currentFile != ""){
        tempSet.push_back(currentFile);
    }
    if(comparedFile != ""){
        tempSet.push_back(comparedFile);
    }
    surfsInSet.push_back(tempSet);
    surfSetIndex = surfSets.size();
    surfIndex1 = 0;
    surfIndex2 = 0;
    setName = "";
    mutex.exit();
}

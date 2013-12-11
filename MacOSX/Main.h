//
//  Main.h
//  MotionVisualizer
//
//  Created by Zach Daniels on 12/10/13.
//
//

#ifndef MotionVisualizer_Main_h
#define MotionVisualizer_Main_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "Leap.h"
#include "LeapUtilGL.h"
#include <cctype>
#include "StdAfx.h"
#include <string>
#include <math.h>
#include <iostream>
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <time.h>
#include "GestureRecognitionEngine.h"
#include "Surfaces.h"

#include <iostream>
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"

Surfaces surfaces;

char * outputFileName;
char * inputFileName;

static const float kfNumGrids   = 15.0f;
static const float kfGridScale  = 120.0f;

int main_window;

float aspectRatio;
float * obj_pos;
int * drawAxes;
int * useCentroid;

double * centroid;

int keyFlag;

int background;

int lastSwipe = 0;
int lastCircle = 0;

int mode = 0;

int xyFlag = 0;

float angleX = 0;
float angleY = 0;

glm::quat myQuaternion;

time_t timerStart;

DollarRecognizer::GestureRecognitionEngine* recognitionEngine;

int frameCount = 0;

bool fingerFlag = false;

float previousX = 0;
float previousY = 0;

int pauseCounter = 0;

#endif

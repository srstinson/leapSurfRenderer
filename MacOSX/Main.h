/*
 LeapRenderer
 Description: The main program is responsible for three functions: rendering the application GUI, collecting data from inputs (namely the Leap Motion Controller, keyboard, and mouse), and managing the interactions between the various other components.
 */

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

//Data structure for storing information and algorithms related to surface sets and displayed surfaces
Surfaces surfaces;

//Identifier for main window
int main_window;

//Used to tell when to listen to characters for building file names vs generic keypresses
int keyFlag;

int background;

//ID of last swipe gesture
int lastSwipe = 0;

//ID of last circle gesture
int lastCircle = 0;

//Mode: 0=classification, 1=rotation, 2=scaling
int mode = 0;

//Quaternion representation used to solve Gimbal lock problem for rotation
glm::quat myQuaternion;

//Timer used to ensure partial swipes don't appear as two swipes
time_t timerStart;

//Gesture recognizer: $1 Unistroke Recognizer engine
DollarRecognizer::GestureRecognitionEngine* recognitionEngine;

//Counts frames, used to tell gesture recognizer when to grab new data point
int frameCount = 0;

//Should finger visualizer display?
bool fingerFlag = false;

//Previous x position of tracked finger, used to determine if stroke is complete
float previousX = 0;

//Previous y position of tracked finger, used to determine if stroke is complete
float previousY = 0;

//Counts how many frames finger has remained in roughly the same position; used for recognizing when a stroke is complete
int pauseCounter = 0;

//Used for testing accuracy rates
int confusion[8];

#endif

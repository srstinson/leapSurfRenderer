/*
 GestureRecognitionEngine
 Description: GestureRecognitionEngine acts as an interface between the LeapRenderer main program and the $1 Unistroke Recognizer.
 */

#include "GestureRecognitionEngine.h"

static DollarRecognizer::GestureRecognitionEngine* self;
DollarRecognizer::Path2D recentPath;
static const int GESTURE_SIZE = 128;
DollarRecognizer::GeometricRecognizer recognizer;
std::map<string,DollarRecognizer::Path2D> gestures;

namespace DollarRecognizer {

	GestureRecognitionEngine* GestureRecognitionEngine::Instance() {
		if (self==NULL) {
			self = new GestureRecognitionEngine();
		}
		return self;
	}

	GestureRecognitionEngine::GestureRecognitionEngine() {
		recognizer = *new GeometricRecognizer();
		recentPath = *new Path2D();
		gestures = *new std::map<string,Path2D>();
		recognizer.loadTemplates();

	}

	RecognitionResult GestureRecognitionEngine::recognize() {
		RecognitionResult result = recognizer.recognize(recentPath);
        if (result.name != "Unknown"){
            recentPath.clear();
        }
        
        return result;
	}

	void GestureRecognitionEngine::updateCoord(Leap::Frame frame) {

		if (frame.fingers().count() > 0) {
			float x,y;

            Leap::FingerList fingers = frame.fingers();
            
            x = fingers[0].tipPosition().x;
            y = -fingers[0].tipPosition().y;
            
			if (recentPath.size() == GESTURE_SIZE) {
				recentPath.erase(recentPath.begin());
			}
			recentPath.push_back(*new Point2D(x,y));
		}
	}
    
    void GestureRecognitionEngine::clear(){
        recentPath.clear();
    }

		void GestureRecognitionEngine::addGesture(string name, Path2D pts) {
			recognizer.addTemplate(name, pts);
		}

	}
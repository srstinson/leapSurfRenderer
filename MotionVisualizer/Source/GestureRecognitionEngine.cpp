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
        cout<<"OK!"<<endl;

	}

	RecognitionResult GestureRecognitionEngine::recognize() {
		RecognitionResult result = recognizer.recognize(recentPath);
        if (result.name != "Unknown"){
            recentPath.clear();
        }
        
        return result;
	}

	void GestureRecognitionEngine::updateCoord(Leap::Frame frame) {

		//Leap::Frame frame = controller.frame();
		
		if (frame.fingers().count() > 0) {
			//Leap::Pointable p = frame.pointables()[0];
			//Leap::Screen s = controller.locatedScreens().closestScreenHit(p);
			float x,y;

			//Leap::Vector v = s.intersect(p,true);
			//x = (v.x * s.widthPixels() - x) * 0.25f;
			//y = ((1 - v.y) * s.heightPixels() - y) * 0.25f;

            Leap::FingerList fingers = frame.fingers();
            
            x = fingers[0].tipPosition().x;
            y = -fingers[0].tipPosition().y;
            cout<<x<<" "<<y<<endl;

            //cout<<"HERE!"<<endl;
            
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
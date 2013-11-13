#include "GestureRecognitionEngine.h"

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
		return recognizer.recognize(recentPath);
	}

	void GestureRecognitionEngine::updateCoord(Leap::Controller controller) {

		Leap::Frame frame = controller.frame();
		
		if (frame.pointables().count() > 0) {
			Leap::Pointable p = frame.pointables()[0];
			Leap::Screen s = controller.locatedScreens().closestScreenHit(p);
			float x,y;

			Leap::Vector v = s.intersect(p,true);
			x = (v.x * s.widthPixels() - x) * 0.25f;
			y = ((1 - v.y) * s.heightPixels() - y) * 0.25f;

			if (recentPath.size() == GESTURE_SIZE) {
				recentPath.erase(recentPath.begin());
			}
			recentPath.push_back(*new Point2D(x,y));
		}
	}

		void GestureRecognitionEngine::addGesture(string name, Path2D pts) {
			recognizer.addTemplate(name, pts);
		}

	}
#include "GeometricRecognizer.h"
#include <map>
#include "Leap.h"

/* Wrapper for GestureRecognizer to allow it to work for our purposes */

namespace DollarRecognizer {
class GestureRecognitionEngine {

private:
	static const int GESTURE_SIZE = 128;
	static GestureRecognitionEngine* self;
	GeometricRecognizer recognizer;
	Path2D recentPath;
	std::map<string,Path2D> gestures;

	GestureRecognitionEngine();

public:
	/*Singleton because we don't want multiple instances to have potentially inconsistent cursor data*/
	static GestureRecognitionEngine* Instance();

	/*Returns a RecognitionResult with the most likely gesture. RecognitionResult is a class with the following members:
		string name;
		double score;

		Where the name is the name of the Gesture and the score is a value 0 < p < 1 of the likelyhood of it being that gesture.
	*/
	RecognitionResult recognize();

	/* Add a coordinate to the most recent path. Should be called once a frame.
		TODO: Better way of doing this than calling a method once a frame */
	void updateCoord(Leap::Controller);

	/* Add a gesture to the list. */
	void addGesture(string,Path2D);
};
}
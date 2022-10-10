#pragma once

#include "ofMain.h"
#include "ofxCv.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		/*
		This practice is a face detection example
		You need to add a copy of "haarcascade_frontalface_default.xml" to "OF/addons/ofxCv/example-face/bin/data/".
		"haarcascade_frontalface_default.xml" can be find in "OF/examples/computer_vision/opencvHaarFinderExample/bin/data/"
		*/

		ofVideoGrabber grabber;

		ofxCv::ObjectFinder finder;		
};

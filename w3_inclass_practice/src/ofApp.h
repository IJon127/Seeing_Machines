#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();


		ofVideoGrabber grabber;
		ofImage resultImg;
		ofImage backgroundImg;

		ofParameter<int> thresholeBrightness;
		ofParameter<bool> captureBackground;


		ofxPanel guiPanel;


		
};

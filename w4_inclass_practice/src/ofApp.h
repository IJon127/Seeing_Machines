#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"




class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();



		ofVideoGrabber grabber;
		ofImage backgroundImg;
		ofImage resultImg;

		ofParameter<bool> captureBackground;
		ofParameter<int> briThreshole;

		ofxPanel guiPanel;
		
};

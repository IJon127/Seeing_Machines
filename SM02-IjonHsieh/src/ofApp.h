#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

		ofParameter<int> briThreshole;
		ofParameter<bool> blackAndWhite;
		ofParameter<bool> imgCapture;

		ofxPanel guiPanel;
		bool showGui;
		
		ofVideoGrabber grabber;
		ofImage capturedImg;
		ofImage backgroundImg;
		ofImage resultImg;

		bool fisrtCapture;


		
};

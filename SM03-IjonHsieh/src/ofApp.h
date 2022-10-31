#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofxKinect kinect;
		ofImage bgImg;

		ofPolyline lineHorizontal;
		ofPolyline lineVertical;

		ofParameter<bool> horizontalScan;
		ofParameter<bool> verticalScan;

		ofxPanel guiPanel;

};

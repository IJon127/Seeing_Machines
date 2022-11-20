#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		ofVideoGrabber grabber;

		ofCamera cam;
		ofParameter<bool> useCam;
		ofParameter<glm::vec3> camPosition;
		ofParameter<float> camTruck;
		ofParameter<float> camBoom;
		ofParameter<float> camDolly;
		ofParameter<glm::vec3> camLookAt;
		ofParameter<bool> orientCam;
		ofParameter<float> camPan;
		ofParameter<float> camTilt;
		ofParameter<float> camRoll;

		ofEasyCam easyCam;
		ofParameter<bool> useEasyCam;

		ofxPanel guiPanel;
};

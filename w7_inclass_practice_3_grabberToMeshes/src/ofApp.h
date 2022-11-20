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

	ofMesh quadMesh; //method 1
	ofMesh pointMesh; //method 2

	ofParameter<bool> drawWireFrame;
	ofParameter<bool> usePointMesh;
	ofParameter<int> skipPoints;

	ofxPanel guiPanel;

};

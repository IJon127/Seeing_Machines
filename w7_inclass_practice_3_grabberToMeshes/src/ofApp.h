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

	ofMesh quadMesh;
	ofParameter<bool> drawWireFrame;
	ofxPanel guiPanel;

};

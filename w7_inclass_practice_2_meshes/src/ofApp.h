#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void draw();

	ofMesh quadMesh;
	ofParameter<bool> drawWireFrame;
	ofxPanel guiPanel;

};

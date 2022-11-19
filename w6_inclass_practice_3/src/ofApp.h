#pragma once

#include "ofMain.h"
#include "ofxRealSense2.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		ofxRealSense2::Context rsContext;
		ofxPanel guiPanel;

};

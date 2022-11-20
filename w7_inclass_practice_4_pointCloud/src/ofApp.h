#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxRealSense2.h"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		ofxRealSense2::Context rsContext;
		ofMesh pointMesh;
		ofParameter<int> skipPoints;
		ofParameter<int> depthExtent;

		
		ofEasyCam cam;
		
		ofxPanel guiPanel;
		
};

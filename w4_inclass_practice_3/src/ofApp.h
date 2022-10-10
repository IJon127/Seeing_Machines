#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

//using namespace cv;
//using namespace ofxCv;


class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mousePressed(int x, int y, int button);

		ofVideoGrabber grabber;
		ofImage grabberImg;
	
		ofxCv::ContourFinder contourFinder;

		ofParameter<ofColor> colorTarget;
		ofParameter<int> colorOffset;
		ofColor colorUnderMouse;
		ofParameter<float> minArea;
		ofParameter<float> maxArea;
		ofParameter<int> blurAmount;
		ofParameter<int> erodeAmount;
		ofParameter<int> persistence;
		ofParameter<float> maxDistance; //althought it's pixels based you may need to use math operation /*+-
		ofParameter<bool> showLabels;
		ofParameter<bool> debugMode;

		ofxPanel guiPanel;
		bool drawGui;
		
};

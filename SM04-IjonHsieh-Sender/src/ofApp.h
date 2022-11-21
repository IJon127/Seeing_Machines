#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxRealSense2.h"
#include "ofxOsc.h"
#include "ofxCv.h"
/*
Note:
Haar cascade file (for face detection) does not automatically come with ofxCv.
You need to add it to the /bin/data/ folder.
It canbe found in OF/examples/computer_vision/opencvHaarFinderExample/bin/data/ folder.
*/


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);

		void sendMsg();

		
		ofxRealSense2::Context rsContext;
		ofxCv::ObjectFinder finder;
		ofImage img;

		ofParameter<bool> showDepthTex;
		ofParameter<int> depthExtent;
		ofxPanel guiPanel;

		string sendAddress;
		int sendPort;
		ofxOscSender sender;

		//int x;
		//int y;
};

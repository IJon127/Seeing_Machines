#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofCamera cam;
		//ofEasyCam cam;

		int recvPort;
		ofxOscReceiver receiver;

		vector<int> posX;
		vector<int> posY;
		vector<int> dep;



		ofImage img;

		vector<ofPlanePrimitive> planes;
		
};

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		int recvPort;
		ofxOscReceiver receiver;

		int posX;
		int posY;

		int clrG;
		int clrB;

		char r;

};

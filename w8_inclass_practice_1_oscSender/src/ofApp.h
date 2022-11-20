#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		string sendAddress;
		int sendPort;

		ofxOscSender sender;

		int clrG;
		int clrB;
		char r;

};

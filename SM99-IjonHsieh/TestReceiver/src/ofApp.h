#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();
private:
	const int circleDiameter = 1200;

	int recvPort;
	ofxOscReceiver receiver;

	int posX;
	int posY;

};

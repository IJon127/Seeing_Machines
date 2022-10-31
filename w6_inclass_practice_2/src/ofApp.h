#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void mousePressed(int x, int y, int button);

		//ofImage* imgPtr;
		shared_ptr<ofImage> imgPtr1;
		shared_ptr<ofImage> imgPtr2;


};

#pragma once

#include "ofMain.h"
#include "ofxAzureKinect.h"
#include "ofxGui.h"
#include "ofxOsc.h"


class ofApp : public ofBaseApp
{

public:
	void setup();
	void exit();
	void update();
	void draw();

	//void mouseDragged(int x, int y, int button);

private:
	ofxAzureKinect::Device kinectDevice;

	ofEasyCam camera;

	ofVbo pointsVbo;
	ofShader shader;

	ofVboMesh skeletonMesh;


	ofParameter<int> handThreshole; //distance between the hands and the neck
	ofParameter<int> sensorDist; //distance from the sensor to the edge of the circle
	ofParameter<int> circleRadius;

	ofxPanel guiPanel;

	ofParameter<float> zFront;
	ofParameter<float> zBack;
	ofParameter<float> xLeft;
	ofParameter<float> xRight;

	//osc
	string sendAddress;
	int sendPort;

	ofxOscSender sender;

	

	int r;
	

};

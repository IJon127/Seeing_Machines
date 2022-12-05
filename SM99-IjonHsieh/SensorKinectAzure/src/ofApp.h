#pragma once

#include "ofMain.h"
#include "ofxAzureKinect.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "triggerPoint.h"


class ofApp : public ofBaseApp
{

public:
	void setup();
	void exit();
	void update();
	void draw();

	void addTriggerPoint(int _id, bool _isLeftHand, ofVec2f _pos, float _h);

	//void mouseDragged(int x, int y, int button);

private:
	ofxAzureKinect::Device kinectDevice;

	//ofEasyCam camera;

	//ofVbo pointsVbo;
	//ofShader shader;

	//ofVboMesh skeletonMesh;

	const int circleDiameter = 1200;

	//parameters
	ofParameter<int> raisingHandThreshole; //distance between the hands and the neck
	ofParameter<int> posChangeThreshole;
	ofParameter<int> heightChangeThreshole;

	ofParameter<float> zFront;
	ofParameter<float> zBack;
	ofParameter<float> xLeft;
	ofParameter<float> xRight;

	ofxPanel guiPanel;

	//osc
	string sendAddress;
	int sendPort;

	ofxOscSender sender;


	//trigger point
	vector<triggerPoint> currentPoints;
	vector<triggerPoint> lastPoints;

};

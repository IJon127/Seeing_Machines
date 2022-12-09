#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxCv.h"
#include "ofxGui.h"

#define PROJECTOR_RESOLUTION_X 1920
#define PROJECTOR_RESOLUTION_Y 1080

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();
	void drawProjector(ofEventArgs& args);

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

private:
	const int circleDiameter = PROJECTOR_RESOLUTION_Y;
	const int mappingWidth = 640;
	const int mappingHeight = 360;


	//osc
	int recvPort;
	ofxOscReceiver receiver;

	int posX;
	int posY;

	//projection
	ofFbo renderFbo;
	ofPixels renderPixels;
	ofImage warpedImg;

	std::vector<glm::vec2> srcPoints;
	std::vector<glm::vec2> dstPoints;

	int activePoint;

	cv::Mat homographyMat;
	bool homographyReady;

	ofParameter<bool> adjustMapping;
	ofParameter<bool> projectWarped;

	ofxPanel guiPanel;


};

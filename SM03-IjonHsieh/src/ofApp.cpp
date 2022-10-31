#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	kinect.init();
	kinect.open();
	kinect.setCameraTiltAngle(5);

	ofSetFrameRate(60);
	ofSetWindowShape(kinect.width, kinect.height);

	bgImg.allocate(kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);

	//set parameters
	horizontalScan.set("Horizontal Scan", true);
	verticalScan.set("Vertival Scan", true);

	//set gui panel
	guiPanel.setup();
	guiPanel.add(horizontalScan);
	guiPanel.add(verticalScan);

}

//--------------------------------------------------------------
void ofApp::update()
{
	kinect.update();
	lineHorizontal.clear();
	lineVertical.clear();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (kinect.isFrameNew())
	{
		bgImg.setFromPixels(kinect.getDepthPixels());
		bgImg.draw(0, 0);

		//get distance data from mouse position
		for (int x = 0; x < kinect.width; x++) {
			lineHorizontal.addVertex(x, mouseY+ floor(kinect.getDistanceAt(x, mouseY)/20));
		}
		for (int y = 0; y < kinect.height; y++) {
			lineVertical.addVertex(mouseX + floor(kinect.getDistanceAt(mouseX, y)/20), y);
		}
	}

	bgImg.draw(0, 0); 

	//draw the scan line
	ofPushStyle();
	{
		ofSetColor(255, 0, 0);
		ofNoFill();
		if (horizontalScan)
		{
			lineHorizontal.draw();
		}
		if (verticalScan)
		{
			lineVertical.draw();
		}
	}
	ofPopStyle();

	guiPanel.draw();
}


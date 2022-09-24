#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(0, 0, 255);
	ofDrawCircle(mouseX, mouseY, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'r')
	{
		ofBackground(255, 0, 0);
	}
	else if (key == 'g')
	{
		ofBackground(0, 255, 0);
	}
	else if (key == 'b')
	{
		ofBackground(0, 0, 255);
	}
	else 
	{
		ofBackground(0, 0, 0);
	}

}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 480);

	//make the circle smoother
	ofSetCircleResolution(128);

	//setup osc sender
	sendAddress = "localhost";
	sendPort = 3030;
	sender.setup(sendAddress, sendPort);

	r = 50;
}

//--------------------------------------------------------------
void ofApp::update()
{
	//set random color
	clrG = ofRandom(255);
	clrB = ofRandom(255);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);

	//draw a circle at mouse position
	ofSetColor(0, clrG, clrB);
	if (ofGetMousePressed())
	{
		ofFill();
	}
	else
	{
		ofNoFill();
	}
	ofDrawCircle(mouseX, mouseY, r);

	ofSetColor(255);
	ofNoFill();
	ofDrawCircle(mouseX, mouseY, r);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ')
	{
		r = 100;
		ofxOscMessage msg;
		msg.setAddress("/circle/radius");
		msg.addCharArg(r);

		sender.sendMessage(msg);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == ' ')
	{
		r = 50;
		ofxOscMessage msg;
		msg.setAddress("/circle/radius");
		msg.addCharArg(r);

		sender.sendMessage(msg);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	ofxOscMessage msg;
	msg.setAddress("/circle/position");
	msg.addIntArg(mouseX);
	msg.addIntArg(mouseY);

	sender.sendMessage(msg);
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	ofxOscMessage msg;
	msg.setAddress("/circle/color");
	msg.addIntArg(clrG);
	msg.addIntArg(clrB);

	sender.sendMessage(msg);
}
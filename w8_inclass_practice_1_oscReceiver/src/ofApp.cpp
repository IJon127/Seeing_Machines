#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 480);

	//make the circle smoother
	ofSetCircleResolution(128);

	//setup osc receiver
	recvPort = 3030;
	receiver.setup(recvPort);

	r = 50;
}

//--------------------------------------------------------------
void ofApp::update()
{
	while (receiver.hasWaitingMessages())
	{
		//get the message
		ofxOscMessage msg;
		receiver.getNextMessage(msg);

		if (msg.getAddress() == "/circle/radius")
		{
			r = msg.getArgAsChar(0);
		}
		else if (msg.getAddress() == "/circle/position")
		{
			posX = msg.getArgAsInt(0);
			posY = msg.getArgAsInt(1);
		}
		else if (msg.getAddress() == "/circle/color")
		{
			clrG = msg.getArgAsInt(0);
			clrB = msg.getArgAsInt(1);
		}
		else
		{
			ofLogWarning(__FUNCTION__) << "Unrecognized message" << msg.getAddress();
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(ofColor(0,clrG, clrB));

	//draw a circle at posX poxY
	ofSetColor(0);
	ofFill();
	ofDrawCircle(posX, posY, r);

	ofSetColor(255);
	ofNoFill();
	ofDrawCircle(posX, posY, r);
}


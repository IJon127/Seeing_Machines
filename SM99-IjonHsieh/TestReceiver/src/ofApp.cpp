#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//setup window
	ofSetWindowShape(circleDiameter, circleDiameter);

	//make the circle smoother
	ofSetCircleResolution(128);

	//setup osc receiver
	recvPort = 3030;
	receiver.setup(recvPort);

}

//--------------------------------------------------------------
void ofApp::update()
{
	while (receiver.hasWaitingMessages())
	{
		//get the message
		ofxOscMessage msg;
		receiver.getNextMessage(msg);

		if (msg.getAddress() == "/position")
		{
			posX = msg.getArgAsInt(0);
			posY = msg.getArgAsInt(1);
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
	ofBackground(0);

	//draw circles at posX poxY
	ofSetColor(255);
	ofNoFill();
	ofDrawCircle(circleDiameter / 2, circleDiameter / 2, circleDiameter / 2);
	ofDrawCircle(posX, posY, 80);
}


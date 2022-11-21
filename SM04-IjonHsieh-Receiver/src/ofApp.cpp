#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 360);
	
	//load image
	img.load("tree.png");

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

		if (msg.getAddress() == "/position/xyz")
		{
			posX.push_back(msg.getArgAsInt(0));
			posY.push_back(msg.getArgAsInt(1));
			dep.push_back(msg.getArgAsInt(2));
		}
		else
		{
			ofLogWarning(__FUNCTION__) << "Unrecognized message" << msg.getAddress();
		}

		//add planes (trees) in 3d world
		planes.resize(posX.size());
		for (size_t i = 0; i < planes.size(); i++) {
			planes[i].set(img.getWidth(), img.getHeight(), 2, 2);

			planes[i].mapTexCoordsFromTexture(img.getTexture());
			planes[i].setPosition(posX[i]-img.getWidth()/2, -posY[i], -dep[i]);

		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	cam.begin();

	
	for (int i = 0; i < planes.size(); i++)
	{
		img.bind();
		planes[i].draw();
		img.unbind();
		
	}
	cam.end();
}


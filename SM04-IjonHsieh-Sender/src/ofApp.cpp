#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 360);

	//start realsense
	rsContext.setup(true);

	//setup the parameters
	showDepthTex.set("Show Depth Texture", false);
	depthExtent.set("Depth Extent", 300, 10, 1000);

	//setup the gui
	guiPanel.setup("GUI");
	guiPanel.add(showDepthTex);
	guiPanel.add(depthExtent);

	//setup face detection
	finder.setup("haarcascade_frontalface_default.xml");
	finder.setPreset(ofxCv::ObjectFinder::Fast);

	//setup osc sender
	sendAddress = "localhost";
	sendPort = 3030;
	sender.setup(sendAddress, sendPort);

}

//--------------------------------------------------------------
void ofApp::update()
{
	rsContext.update();

	shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
	if (rsDevice)
	{
		ofPixels pix = rsDevice->getColorPix();
		img.setFromPixels(pix);
		finder.update(img);

	}


}

//--------------------------------------------------------------
void ofApp::draw()
{

	shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
	if (rsDevice)
	{
		//align the color camera to the depth sensor
		rsDevice->alignMode = ofxRealSense2::Device::Align::Color;
		
		if (showDepthTex)
		{
			//draw the depth texture
			rsDevice->getDepthTex().draw(0, 0);

		}
		else
		{
			//draw the color texture
			img.draw(0, 0);
		}

		finder.draw();


		for (int i = 0; i < finder.size(); i++)
		{
			int x = finder.getObject(i).x;
			int y = finder.getObject(i).y;

			ofDrawBitmapStringHighlight("x: " + ofToString(x), x, y - 20);
			ofDrawBitmapStringHighlight("y: " + ofToString(y), x, y);
			//get depth data
			float dist = rsDevice->getDistance(x+20, y+20);
			int distInt = round(dist * depthExtent);
			ofDrawBitmapStringHighlight("depth: " + ofToString(dist, 3), x, y - 40);
			ofDrawBitmapStringHighlight("depth int: " + ofToString(distInt), x, y - 60);

		}
	}

	guiPanel.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ')
	{
		sendMsg();
	}

}



//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	sendMsg();
}

//my function ==================================================
void ofApp::sendMsg()
{
	shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
	if (rsDevice)
	{
		for (int i = 0; i < finder.size(); i++)
		{
			int x = finder.getObject(i).x;
			int y = finder.getObject(i).y;

			//get depth data and convert to int
			float dist = rsDevice->getDistance(x, y);
			int distInt = round(dist * depthExtent);

			ofxOscMessage msg;
			msg.setAddress("/position/xyz");
			msg.addIntArg(x);
			msg.addIntArg(y);
			msg.addIntArg(distInt);

			sender.sendMessage(msg);
		}
		
	}
}



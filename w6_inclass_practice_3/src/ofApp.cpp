#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//default realsense resolution
	ofSetWindowShape(640, 360);

	//realsense setup
	rsContext.setup(true);
	shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);

	//gui setup
	guiPanel.setup("REALSENSE", "settings.json");
	if (rsDevice)
	{
		guiPanel.add(rsDevice->params);
	}

}

//--------------------------------------------------------------
void ofApp::update()
{
	rsContext.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
	if (rsDevice)
	{
		//draw the depth texture
		rsDevice->getDepthTex().draw(0,0);

		//clamp mouseX and mouseY
		int mx = ofClamp(mouseX, 0, rsDevice->getDepthTex().getWidth()-1);
		int my = ofClamp(mouseY, 0, rsDevice->getDepthTex().getHeight()-1);

		//get depth data
		float distAtMouse = rsDevice->getDistance(mx, my);
		ofDrawBitmapStringHighlight(ofToString(distAtMouse, 3), mouseX, mouseY);

		//get depth data from raw pixel data
		ofShortPixels pix = rsDevice->getRawDepthPix();
		int depthVal = pix.getColor(mx, my).r;
		ofDrawBitmapStringHighlight(ofToString(depthVal), mouseX, mouseY-20);
	}

	guiPanel.draw();


}




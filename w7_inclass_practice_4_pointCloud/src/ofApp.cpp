#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 480);

	//start realsense
	rsContext.setup(true);

	//setup the parameters
	skipPoints.set("Skip Points", 1, 1, 8);
	depthExtent.set("Depth Extent", 300, 10, 1000);

	//setup the gui
	guiPanel.setup("Point Cloud");
	guiPanel.add(skipPoints);
	guiPanel.add(depthExtent);
}

//--------------------------------------------------------------
void ofApp::update()
{
	rsContext.update();

	shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);
	if (rsDevice)
	{
		//align the color camera to the depth sensor
		rsDevice->alignMode = ofxRealSense2::Device::Align::Color;

		//ofShortPixels pix = rsDevice->getRawDepthPix();

		//rebuild point mesh
		pointMesh.clear();
		pointMesh.setMode(OF_PRIMITIVE_POINTS);
		for (int y = 0; y < rsDevice->getDepthTex().getHeight();y+=skipPoints)
		{
			for (int x = 0; x < rsDevice->getDepthTex().getWidth(); x += skipPoints)
			{
				int dist = round(rsDevice->getDistance(x,y)*depthExtent);
				pointMesh.addVertex(glm::vec3(x, y, dist));

				//pointMesh.addVertex(rsDevice->getWorldPosition(x,y));
				pointMesh.addTexCoord(glm::vec2(x, y));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	shared_ptr<ofxRealSense2::Device> rsDevice = rsContext.getDevice(0);

	cam.begin();
	ofEnableDepthTest();
	
	if (rsDevice)
	{
		rsDevice->getColorTex().bind();
		ofRotateDeg(180,1,0,0);
		pointMesh.draw();
		rsDevice->getColorTex().unbind();
	}

	ofDisableDepthTest();
	cam.end();

	guiPanel.draw();
}


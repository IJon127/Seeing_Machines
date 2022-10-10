#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//grabber.listDevices(); //use this if there are more than one camera 
	//grabber.setDeviceID(0);

	grabber.setup(1280, 720); //shouold match the camera
	ofSetWindowShape(grabber.getWidth(), grabber.getHeight());

	resultImg.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_GRAYSCALE); //initial setting for an empty image

	//set parameters
	thresholeBrightness.set("Bri Threshole", 127, 0, 255);
	captureBackground.set("Capture", true);

	//set gui panel
	guiPanel.setup("GUI Panel");
	guiPanel.add(thresholeBrightness);
	guiPanel.add(captureBackground);

}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();
	ofPixels& grabPixels = grabber.getPixels();

	if (captureBackground)
	{
		backgroundImg.setFromPixels(grabPixels);
		captureBackground = false;
	}


	
	ofPixels& resultPixels = resultImg.getPixels();
	ofPixels& backgroundPixels = backgroundImg.getPixels();

	for (int y=0; y< grabber.getHeight(); y++)
	{
		for (int x = 0; x < grabber.getWidth(); x++)
		{
			ofColor currCol = grabPixels.getColor(x, y);
			ofColor bgCol = backgroundPixels.getColor(x, y);

			if (abs(currCol.getBrightness() - bgCol.getBrightness()) < thresholeBrightness)
			{
				resultPixels.setColor(x, y, ofColor(0));
			}
			else
			{
				resultPixels.setColor(x, y, ofColor(255));
			}

			/*
			//black and white posterization
			if (currCol.getBrightness() < thresholeBrightness)
			{
				resultPixels.setColor(x, y, ofColor(0));
			}
			else
			{
				resultPixels.setColor(x, y, ofColor(255));
			}
			*/
		}
	}

	resultImg.update(); //use this if using "&" (ofPixels& resultPixels), update GPU
	//resultImg.setFromPixels(resultPixels); //use this if not using "&" (ofPixels resultPixels)

	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	resultImg.draw(0, 0);
	guiPanel.draw();
}



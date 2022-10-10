#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	grabber.setup(1280, 720);
	ofSetWindowShape(grabber.getWidth(), grabber.getHeight());

	//ofParameter setup
	captureBackground.set("Capture BG", true);
	briThreshole.set("Brightness Threshole", 127, 0, 255);

	//Gui setup
	guiPanel.setup();
	guiPanel.add(briThreshole);
	guiPanel.add(captureBackground);

}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();

	if (grabber.isFrameNew()) 
	{
		//convert ofVideoBrabber into ofImage
		ofImage grabberColorImg;
		grabberColorImg.setFromPixels(grabber.getPixels());

		//make a copy of gray image
		ofImage grabberGrayImg;
		ofxCv::copyGray(grabberColorImg, grabberGrayImg);

		if (captureBackground)
		{
			backgroundImg = grabberGrayImg;
			captureBackground = false;
		}

		ofxCv::absdiff(backgroundImg, grabberGrayImg, resultImg);
		ofxCv::threshold(resultImg, briThreshole);

		resultImg.update();
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	resultImg.draw(0, 0);
	guiPanel.draw();
}




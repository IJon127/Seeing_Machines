#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	grabber.setup(1280, 720);
	ofSetWindowShape(grabber.getWidth(), grabber.getHeight());
	
	
	briThreshole.set("Brightness Threshole", 50, 0, 255);
	blackAndWhite.set("Black and White", false);
	imgCapture.set("Image Capture", true);

	guiPanel.setup("Gui Panel", "settings.json");
	guiPanel.add(briThreshole);
	guiPanel.add(blackAndWhite);
	guiPanel.add(imgCapture);

	showGui = true;

	fisrtCapture = true;
}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();

	if (grabber.isFrameNew())
	{
		ofImage grabberColorImg;
		grabberColorImg.setFromPixels(grabber.getPixels());

		ofImage grabberGrayImg;
		ofxCv::copyGray(grabberColorImg, grabberGrayImg);

		if (imgCapture)
		{
			if (fisrtCapture)
			{
				backgroundImg = grabberGrayImg;
				fisrtCapture = false;
			}
			else
			{
				backgroundImg = capturedImg;
			}
			imgCapture = false;

			//pick a random color to tint the image
			ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
		}
		ofxCv::absdiff(backgroundImg, grabberGrayImg, resultImg);
		capturedImg = resultImg;

		if (blackAndWhite)
		{
			ofxCv::threshold(resultImg, briThreshole);
		}

		resultImg.update();
	}

	

}

//--------------------------------------------------------------
void ofApp::draw()
{
	resultImg.draw(0, 0);


	if (showGui)
	{
		guiPanel.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g')
	{
		showGui = !showGui;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


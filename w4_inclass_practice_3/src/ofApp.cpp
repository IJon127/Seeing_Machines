#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	grabber.setup(640, 390);
	ofSetWindowShape(grabber.getWidth(), grabber.getHeight());


	colorTarget.set("Color Target", ofColor(255, 0, 0));
	colorOffset.set("Color Offset", 50, 0, 255);
	minArea.set("Min Area", 0.01f, 0.0f, 0.1f);
	maxArea.set("Max Area", 0.05f, 0.01, 0.3f);
	blurAmount.set("Blur Amount", 0, 0, 100);
	erodeAmount.set("Erode Amount", 0, 0, 10);
	persistence.set("Persistence", 15, 0, 60);
	maxDistance.set("Max Distance", 50, 0, 640);
	showLabels.set("Show Labels", false);
	debugMode.set("Debug Mode", false);

	contourFinder.setUseTargetColor(true);

	drawGui = true;
	guiPanel.setup("GUI press g toggle", "settings.json");
	guiPanel.add(colorTarget);
	guiPanel.add(colorOffset);
	guiPanel.add(minArea);
	guiPanel.add(maxArea);
	guiPanel.add(blurAmount);
	guiPanel.add(erodeAmount);
	guiPanel.add(persistence);
	guiPanel.add(maxDistance);
	guiPanel.add(showLabels);
	guiPanel.add(debugMode);

	guiPanel.loadFromFile("settings.json");

}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();

	if (grabber.isFrameNew())
	{
		grabberImg.setFromPixels(grabber.getPixels()); 

		//update parameters
		contourFinder.setTargetColor(colorTarget, ofxCv::TRACK_COLOR_HSV);
		contourFinder.setThreshold(colorOffset);
		contourFinder.setMinAreaNorm(minArea);
		contourFinder.setMaxAreaNorm(maxArea);

		//erode image (make bright region smaller) the opposite operation is dilate
		if (erodeAmount > 0) 
		{
			ofxCv::erode(grabberImg, erodeAmount.get());
		}

		//blur the Image
		if (blurAmount > 0)
		{
			ofxCv::medianBlur(grabberImg, blurAmount);	
		}


		//update image if you need to render debug image to screen
		if (debugMode)
		{
			grabberImg.update();
		}

		//set tracker
		contourFinder.getTracker().setPersistence(persistence);
		contourFinder.getTracker().setMaximumDistance(maxDistance);

		//find contour on video 
		contourFinder.findContours(grabberImg);


	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (debugMode)
	{
		grabberImg.draw(0, 0);
	}
	else
	{
		grabber.draw(0, 0);
	}
	contourFinder.draw();

	//draw a box to show the color under the cursor
	ofPushStyle();
	{
		ofSetRectMode(OF_RECTMODE_CENTER);
		int boxSize = 30;
		
		ofSetColor(colorUnderMouse);
		ofDrawRectangle(mouseX, mouseY, boxSize, boxSize);

		ofSetColor(colorUnderMouse.getInverted());
		ofNoFill();
		ofDrawRectangle(mouseX, mouseY, boxSize, boxSize);
	}
	ofPopStyle();

	//add tracker label
	if (showLabels)
	{
		ofxCv::RectTracker& tracker = contourFinder.getTracker();
		for (int i = 0; i < contourFinder.size(); i++)
		{
			ofPoint center = ofxCv::toOf(contourFinder.getCenter(i));
			int label = contourFinder.getLabel(i);
			int age = tracker.getAge(label); //index will change overtime
			string msg = ofToString(label) + ":" + ofToString(age);
			ofDrawBitmapString(msg, center);

			//add velocity
			ofVec2f vel = ofxCv::toOf(contourFinder.getVelocity(i));
			ofDrawLine(center, center + vel * 10);
		}
	}

	if (drawGui)
	{
		guiPanel.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g')
	{
		drawGui = !drawGui;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	colorUnderMouse = grabberImg.getColor(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	colorTarget = colorUnderMouse;

}

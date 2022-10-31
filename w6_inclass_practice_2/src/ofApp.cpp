#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//imgPtr = new ofImage("treelamp.jpg");
	//ofSetWindowShape(imgPtr->getWidth(), imgPtr->getHeight());

	imgPtr1 = make_shared<ofImage>("treelamp.jpg");
	ofSetWindowShape(imgPtr1->getWidth(), imgPtr1->getHeight());

	imgPtr2 = imgPtr1;

}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	if(imgPtr2)
	{
		imgPtr2->draw(0, 0);
	}
	
}

//--------------------------------------------------------------
void ofApp::exit()
{
	//delete imgPtr;

	imgPtr1 = nullptr; //method 1
	imgPtr2.reset(); //method 2
}

void ofApp::mousePressed(int x, int y, int button)
{
	if (button == 0)
	{
		imgPtr1.reset();
	}
	else
	{
		imgPtr2.reset();
	}
}

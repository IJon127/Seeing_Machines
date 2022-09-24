#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//fisrtly, declare "ofImage pic" in header file
	pic.load("librarygame.png");

	//pic.resize(pic.getWidth() * 2, pic.getHeight() * 2); 
	ofSetWindowShape(pic.getWidth(), pic.getHeight());

	//set img origin to center
	ofSetRectMode(OF_RECTMODE_CENTER);

}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(255); //reset color to white otherwise the pic will be tinted by mouseColor

	//pic.draw(0,0);
	pic.draw(ofGetWidth() / 2, ofGetHeight() / 2);

	ofPixels picPix = pic.getPixels(); //get pixel information of the picture

	//there are two ways to get color information
	//METHOD 01
	//ofColor mouseColor = picPix.getColor(mouseX, mouseY); 

	//METHOD 02
	int index = (mouseX + mouseY * pic.getWidth()) * picPix.getNumChannels();
	ofColor mouseColor = picPix.getColor(index);


	//draw a circle fill with mouseColor
	ofSetColor(mouseColor);
	ofFill();
	ofDrawCircle(mouseX, mouseY, 20, 20);

	//draw a white frame
	ofSetColor(255);
	ofNoFill();
	ofDrawCircle(mouseX, mouseY, 20, 20);



}


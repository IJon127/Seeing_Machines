#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	grabber.setup(1280, 720);
	ofSetWindowShape(grabber.getWidth(), grabber.getHeight());

	finder.setup("haarcascade_frontalface_default.xml");
	finder.setPreset(ofxCv::ObjectFinder::Fast);


}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();
	if (grabber.isFrameNew())
	{
		finder.update(grabber);
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	grabber.draw(0,0);
	finder.draw();
}


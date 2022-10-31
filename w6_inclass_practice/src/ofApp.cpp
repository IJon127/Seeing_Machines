#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	grabber.setup(640, 480);
	ofSetWindowShape(grabber.getWidth()*2,grabber.getHeight());
	resultImg.allocate(grabber.getWidth(), grabber.getHeight(), OF_IMAGE_GRAYSCALE);
}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();

	int threshold = 127;
	
	unsigned char* grabberPtr = grabber.getPixels().getData();
	unsigned char* resultPtr = resultImg.getPixels().getData();
	
	for (int i = 0; i < grabber.getWidth() * grabber.getHeight(); i++)
	{
		int r = *(grabberPtr++);
		int g = *(grabberPtr++);
		int b = *(grabberPtr++);

		if ((r+g+b)/3 > threshold)
		{
			*resultPtr = 255;
		}
		else
		{
			*resultPtr = 0;
		}
		resultPtr++;
	}
	resultImg.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	grabber.draw(0, 0);
	resultImg.draw(640, 0);
}


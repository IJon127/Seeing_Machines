#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//change openGL version from 2(OF default) to 3
	ofGLFWWindowSettings settings;
	settings.setSize(1024, 768);
	settings.setGLVersion(3, 3);
	settings.windowMode = OF_WINDOW;

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

	/*
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context (OF default)

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	*/

}

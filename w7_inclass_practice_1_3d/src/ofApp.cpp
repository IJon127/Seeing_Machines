#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 480);
	grabber.setup(640, 480);
	
	//setup the parameters
	useCam.set("Use Camera", false);
	useEasyCam.set("Use EasyCam", false);
	camPosition.set("Camera Position", glm::vec3(0, 0, 90), glm::vec3(-100), glm::vec3(100));
	camTruck.set("Truck", 0.0f, -100.0f, 100.0f);
	camBoom.set("Boom", 0.0f, -100.0f, 100.0f);
	camDolly.set("Dolly", 0.0f, -100.0f, 100.0f);
	camLookAt.set("Camera Look At", glm::vec3(0, 0, 0), glm::vec3(-100), glm::vec3(100));
	orientCam.set("Orient Camera", true);
	camPan.set("Pan", 0.0f, -90.0f, 90.0f);
	camTilt.set("Tilt", 0.0f, -90.0f, 90.0f);
	camRoll.set("Roll", 0.0f, -90.0f, 90.0f);



	//setup gui
	guiPanel.setup("3D World");
	guiPanel.add(useCam);
	guiPanel.add(useEasyCam);
	guiPanel.add(camPosition);
	guiPanel.add(camTruck);
	guiPanel.add(camBoom);
	guiPanel.add(camDolly);
	guiPanel.add(camLookAt);
	guiPanel.add(orientCam);
	guiPanel.add(camPan);
	guiPanel.add(camTilt);
	guiPanel.add(camRoll);


}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();

	//reset everything each frame, otherwise the transform will be additive.
	cam.resetTransform();

	cam.setPosition(camPosition);
	cam.truck(camTruck);
	cam.boom(camBoom);
	cam.dolly(camDolly);

	if (orientCam)
	{
		cam.lookAt(camLookAt);
		cam.panDeg(camPan); //or panRad
		cam.tiltDeg(camTilt);
		cam.rollDeg(camRoll);
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (useCam)
	{
		if (useEasyCam)
		{
			easyCam.begin();

			//scale the drawing down into more manageable units
			ofScale(0.1f);
			grabber.draw(-grabber.getWidth() / 2, -grabber.getHeight() / 2);

			easyCam.end();
		}
		else
		{
			cam.begin();

			//scale the drawing down into more manageable units
			ofScale(0.1f);
			grabber.draw(-grabber.getWidth() / 2, -grabber.getHeight() / 2);

			cam.end();
		}
	}
	else
	{
		grabber.draw(0, 0);
	}

	guiPanel.draw();
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//setup the parameters
	raisingHandThreshole.set("Raising Hand Threshole", 200, 100, 500);
	posChangeThreshole.set("Position Change Threshole", 50, 10, 100);
	heightChangeThreshole.set("Height Change Threshole", 50, 10, 100);
	zFront.set("Z front point", 1300, 800, 1800);
	zBack.set("Z back point", 3500, 3000, 4000);
	xLeft.set("X Left point", 1100, 800, 1400);
	xRight.set("X Right point", -1100, -1400, -800);


	//setup the gui
	guiPanel.setup("Gui", "settings.json");
	guiPanel.add(raisingHandThreshole);
	guiPanel.add(posChangeThreshole);
	guiPanel.add(heightChangeThreshole);
	guiPanel.add(zFront);
	guiPanel.add(zBack);
	guiPanel.add(xLeft);
	guiPanel.add(xRight);

	guiPanel.loadFromFile("settings.json");

	//setup window
	ofSetWindowShape(circleDiameter, circleDiameter);

	//setup osc sender
	sendAddress = "localhost";
	sendPort = 3030;
	sender.setup(sendAddress, sendPort);
	
	
	//ofSetLogLevel(OF_LOG_VERBOSE);

	ofLogNotice(__FUNCTION__) << "Found " << ofxAzureKinect::Device::getInstalledCount() << " installed devices.";

	if (this->kinectDevice.open())
	{
		auto deviceSettings = ofxAzureKinect::DeviceSettings();
		deviceSettings.syncImages = false;
		deviceSettings.depthMode = K4A_DEPTH_MODE_NFOV_UNBINNED;
		deviceSettings.updateIr = false;
		deviceSettings.updateColor = false;
		//deviceSettings.colorResolution = K4A_COLOR_RESOLUTION_1080P;
		deviceSettings.updateWorld = true;
		deviceSettings.updateVbo = false;
		this->kinectDevice.startCameras(deviceSettings);

		auto bodyTrackerSettings = ofxAzureKinect::BodyTrackerSettings();
		bodyTrackerSettings.sensorOrientation = K4ABT_SENSOR_ORIENTATION_DEFAULT;
		//bodyTrackerSettings.processingMode = K4ABT_TRACKER_PROCESSING_MODE_CPU;
		this->kinectDevice.startBodyTracker(bodyTrackerSettings);
	}


	//initial triggerPoints
	addTriggerPoint(0, true, ofVec2f(0, 0), 0);
	lastPoints = currentPoints;
}


//--------------------------------------------------------------
void ofApp::exit()
{
	this->kinectDevice.close();
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(0);

	ofSetColor(255);
	ofNoFill();
	ofDrawCircle(circleDiameter/2, circleDiameter/2, circleDiameter/2);

	if (this->kinectDevice.isStreaming())
	{
		this->kinectDevice.getBodyIndexTex().draw(0, 0, 360, 360);
	}


	//ofPushMatrix();
	{


		currentPoints.clear();

		auto& bodySkeletons = this->kinectDevice.getBodySkeletons();
		for (size_t i = 0; i < bodySkeletons.size(); i++)
		{
			int bodyId = this->kinectDevice.getBodyIDs()[i];
			float neckY = bodySkeletons[i].joints[K4ABT_JOINT_NECK].position.v[1];
			float leftHandY = bodySkeletons[i].joints[K4ABT_JOINT_WRIST_LEFT].position.v[1];
			float rightHandY = bodySkeletons[i].joints[K4ABT_JOINT_WRIST_RIGHT].position.v[1];

			float leftHandX = bodySkeletons[i].joints[K4ABT_JOINT_WRIST_LEFT].position.v[0];
			float leftHandZ = bodySkeletons[i].joints[K4ABT_JOINT_WRIST_LEFT].position.v[2];
			float rightHandX = bodySkeletons[i].joints[K4ABT_JOINT_WRIST_RIGHT].position.v[0];
			float rightHandZ = bodySkeletons[i].joints[K4ABT_JOINT_WRIST_RIGHT].position.v[2];


			ofVec2f leftPos = glm::vec2(leftHandX, leftHandZ);
			ofVec2f rightPos = glm::vec2(rightHandX, rightHandZ);

			//check raising hands
			if (neckY - leftHandY > raisingHandThreshole)
			{
				addTriggerPoint(bodyId, true, leftPos, leftHandY);
			}

			if (neckY - rightHandY > raisingHandThreshole)
			{
				addTriggerPoint(bodyId, false, rightPos, rightHandY);
			}
		}

		//debouncing 

		for (auto& currentPoint : currentPoints)
		{
			for (auto& lastPoint : lastPoints)
			{
				if (currentPoint.getId() == lastPoint.getId() && currentPoint.checkIsLeftHand() == lastPoint.checkIsLeftHand())
				{
					float distance = currentPoint.getPosition().distance(lastPoint.getPosition());
					float heightChangeAmount = abs(currentPoint.getHeight() - lastPoint.getHeight());

					if (distance > posChangeThreshole || heightChangeAmount > heightChangeThreshole)
					{
						int x = (int)ofMap(currentPoint.getPosition()[0], xLeft, xRight, 0, circleDiameter);
						int y = (int)ofMap(currentPoint.getPosition()[1], zBack, zFront, 0, circleDiameter);

						ofFill();
						ofDrawCircle(x, y, 50);

						sendMessage(x, y);

					}
				}
			}
		}

		lastPoints.clear();
		lastPoints = currentPoints;

	}
	//ofPopMatrix();



	guiPanel.draw();
}

//--------------------------------------------------------------
void ofApp::addTriggerPoint(int _id, bool _isLeftHand, ofVec2f _pos, float _h)
{
	currentPoints.push_back(triggerPoint());
	currentPoints.back().setup(_id, _isLeftHand, _pos , _h);
}

//--------------------------------------------------------------
void ofApp::sendMessage(int _x, int _y)
{
	ofxOscMessage msg;
	msg.setAddress("/position");
	msg.addIntArg(_x);
	msg.addIntArg(_y);

	sender.sendMessage(msg);
}

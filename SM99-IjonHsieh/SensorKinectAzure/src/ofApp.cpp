#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//setup the parameters
	handThreshole.set("Hand and Neck Distance", 200, 100, 500);
	//sensorDist.set("Sensor and Circle Distance", 1100, 800, 1800);
	//circleRadius.set("Circle Radius", 1100, 900, 1100);
	zFront.set("Z front point", 1300, 800, 1800);
	zBack.set("Z back point", 3500, 3000, 4000);
	xLeft.set("X Left point", 1100, 800, 1400);
	xRight.set("X Right point", -1100, -1400, -800);


	//setup the gui
	guiPanel.setup("Gui");
	guiPanel.add(handThreshole);
	//guiPanel.add(sensorDist);
	//guiPanel.add(circleRadius);
	guiPanel.add(zFront);
	guiPanel.add(zBack);
	guiPanel.add(xLeft);
	guiPanel.add(xRight);

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

	// Load shader.
	auto shaderSettings = ofShaderSettings();
	shaderSettings.shaderFiles[GL_VERTEX_SHADER] = "shaders/render.vert";
	shaderSettings.shaderFiles[GL_FRAGMENT_SHADER] = "shaders/render.frag";
	shaderSettings.intDefines["BODY_INDEX_MAP_BACKGROUND"] = K4ABT_BODY_INDEX_MAP_BACKGROUND;
	shaderSettings.bindDefaults = true;
	if (this->shader.setup(shaderSettings))
	{
		ofLogNotice(__FUNCTION__) << "Success loading shader!";
	}

	// Setup vbo.
	std::vector<glm::vec3> verts(1);
	this->pointsVbo.setVertexData(verts.data(), verts.size(), GL_STATIC_DRAW);

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

	if (this->kinectDevice.isStreaming())
	{
		this->kinectDevice.getBodyIndexTex().draw(0, 0, 360, 360);
	}

	//this->camera.begin();
	{
		//ofPushMatrix();
		{
			//ofRotateXDeg(180);

			/*
			ofEnableDepthTest();
			constexpr int kMaxBodies = 10;
			int bodyIDs[kMaxBodies];
			int i = 0;
			while (i < this->kinectDevice.getNumBodies())
			{
				bodyIDs[i] = this->kinectDevice.getBodyIDs()[i];
				++i;
			}
			while (i < kMaxBodies)
			{
				bodyIDs[i] = 0;
				++i;
			}
			
			this->shader.begin();
			{
				this->shader.setUniformTexture("uDepthTex", this->kinectDevice.getDepthTex(), 1);
				this->shader.setUniformTexture("uBodyIndexTex", this->kinectDevice.getBodyIndexTex(), 2);
				this->shader.setUniformTexture("uWorldTex", this->kinectDevice.getDepthToWorldTex(), 3);
				this->shader.setUniform2i("uFrameSize", this->kinectDevice.getDepthTex().getWidth(), this->kinectDevice.getDepthTex().getHeight());
				this->shader.setUniform1iv("uBodyIDs", bodyIDs, kMaxBodies);

				int numPoints = this->kinectDevice.getDepthTex().getWidth() * this->kinectDevice.getDepthTex().getHeight();
				this->pointsVbo.drawInstanced(GL_POINTS, 0, 1, numPoints);
			}
			this->shader.end();
			ofDisableDepthTest();
			*/


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
				if (neckY - leftHandY > handThreshole)
				{
					addTriggerPoint(bodyId, true, leftPos, leftHandY);
					//cout << "x: " << leftHandX << "\n" << endl;
					//cout << "z: " << leftHandZ << "\n" << endl;
				}

				if (neckY - rightHandY > handThreshole)
				{
					addTriggerPoint(bodyId, false, rightPos, rightHandY);
					//cout << "x: " << rightHandX << "\n" << endl;
					//cout << "z: " << rightHandZ << "\n" << endl;
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
						float heightChangeAmount = abs(currentPoint.getHeight()-lastPoint.getHeight());
						//cout << distance << "\n" << endl;
						//cout << heightChangeAmount << "\n" << endl;
						if (distance > 100 || heightChangeAmount > 100)
						{
							
							//cout << "x: " << currentPoint.getPosition()[0] << "\n" << endl;
							//cout << "z: " << currentPoint.getPosition()[1] << "\n" << endl;
						}
					}
				}
			}

			lastPoints.clear();
			lastPoints = currentPoints;

		}
		//ofPopMatrix();
	}
	//this->camera.end();

	std::ostringstream oss;
	oss << ofToString(ofGetFrameRate(), 2) + " FPS" << std::endl;
	oss << "Joint Smoothing: " << this->kinectDevice.getBodyTracker().jointSmoothing << std::endl;
	ofDrawBitmapStringHighlight(oss.str(), 10, 20);

	guiPanel.draw();
}


void ofApp::addTriggerPoint(int _id, bool _isLeftHand, ofVec2f _pos, float _h)
{
	currentPoints.push_back(triggerPoint());
	currentPoints.back().setup(_id, _isLeftHand, _pos , _h);
}

//--------------------------------------------------------------
/*
void ofApp::mouseDragged(int x, int y, int button)
{
	if (button == 1)
	{
		this->kinectDevice.getBodyTracker().jointSmoothing = ofMap(x, 0, ofGetWidth(), 0.0f, 1.0f, true);
	}
}
*/


/*
ofxOscMessage msg;
msg.setAddress("/circle/position");
msg.addIntArg(mouseX);
msg.addIntArg(mouseY);

sender.sendMessage(msg);
*/
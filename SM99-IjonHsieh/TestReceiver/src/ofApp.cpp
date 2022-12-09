#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
	//setup window
	ofSetWindowShape(mappingWidth*2, mappingHeight);

	//make the circle smoother
	ofSetCircleResolution(128);

	//setup osc receiver
	recvPort = 3030;
	receiver.setup(recvPort);

	//mapping
	ofBackground(0);

	renderFbo.allocate(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);
	warpedImg.allocate(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y, OF_IMAGE_COLOR);

	srcPoints.push_back(glm::vec2(0, 0));
	srcPoints.push_back(glm::vec2(1, 0));
	srcPoints.push_back(glm::vec2(0, 1));
	srcPoints.push_back(glm::vec2(1, 1));

	dstPoints.push_back(glm::vec2(0, 0));
	dstPoints.push_back(glm::vec2(1, 0));
	dstPoints.push_back(glm::vec2(0, 1));
	dstPoints.push_back(glm::vec2(1, 1));

	activePoint = -1;
	homographyReady = false;

	adjustMapping.set("Adjust Mapping", false);
	projectWarped.set("Project Warped", true);

	guiPanel.setup("Homography", "settings.json");
	guiPanel.add(adjustMapping);
	guiPanel.add(projectWarped);

}

//--------------------------------------------------------------
void ofApp::update()
{
	while (receiver.hasWaitingMessages())
	{
		//get the message
		ofxOscMessage msg;
		receiver.getNextMessage(msg);

		if (msg.getAddress() == "/position")
		{
			posX = msg.getArgAsInt(0);
			posY = msg.getArgAsInt(1);
		}
		else
		{
			ofLogWarning(__FUNCTION__) << "Unrecognized message" << msg.getAddress();
		}
	}


	if (adjustMapping)
	{
		// Copy points from glm to cv format.
		std::vector<cv::Point2f> cvSrcPoints;
		std::vector<cv::Point2f> cvDstPoints;
		for (int i = 0; i < srcPoints.size(); i++)
		{
			// Scale points to projector dimensions.
			cvSrcPoints.push_back(cv::Point2f(srcPoints[i].x * PROJECTOR_RESOLUTION_X, srcPoints[i].y * PROJECTOR_RESOLUTION_Y));
			cvDstPoints.push_back(cv::Point2f(dstPoints[i].x * PROJECTOR_RESOLUTION_X, dstPoints[i].y * PROJECTOR_RESOLUTION_Y));
		}

		// Generate a homography from the two sets of points.
		homographyMat = cv::findHomography(cv::Mat(cvSrcPoints), cv::Mat(cvDstPoints));
		homographyReady = true;
	}

	glm::vec2 gravity = glm::vec2(0, 9.8f);
	renderFbo.begin();
	{
		ofBackground(255);
		//draw circles at posX poxY
		ofSetColor(255,0,0);
		ofFill();
		ofDrawCircle(PROJECTOR_RESOLUTION_X / 2, 0, 30, 30);
		ofDrawCircle(PROJECTOR_RESOLUTION_X / 2, PROJECTOR_RESOLUTION_Y, 30, 30);
		ofDrawCircle(PROJECTOR_RESOLUTION_X / 2 - circleDiameter/2, PROJECTOR_RESOLUTION_Y/2, 30, 30);
		ofDrawCircle(PROJECTOR_RESOLUTION_X / 2 + circleDiameter / 2, PROJECTOR_RESOLUTION_Y/2, 30, 30);

		ofSetColor(0, 0, 255);
		ofNoFill();
		ofDrawCircle(PROJECTOR_RESOLUTION_X/2, circleDiameter / 2, circleDiameter / 2);
		ofDrawCircle(posX, posY, 80);
	}
	renderFbo.end();

	if (homographyReady)
	{
		// Read the FBO to pixels.
		renderFbo.readToPixels(renderPixels);

		// Warp the pixels into a new image.
		warpedImg.setFromPixels(renderPixels);
		ofxCv::warpPerspective(renderPixels, warpedImg, homographyMat, CV_INTER_LINEAR);
		warpedImg.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{

	// Draw unwarped image on the left.
	renderFbo.draw(0, 0, mappingWidth, mappingHeight);

	if (homographyReady)
	{
		// Draw warped image on the right.
		warpedImg.draw(mappingWidth, 0, mappingWidth, mappingHeight);
	}

	if (adjustMapping)
	{
		// Draw mapping points.
		for (int i = 0; i < srcPoints.size(); i++)
		{
			ofSetColor(0, 0, 255);
			glm::vec2 srcPt = glm::vec2(ofMap(srcPoints[i].x, 0, 1, 0, 640), ofMap(srcPoints[i].y, 0, 1, 0, 360));
			ofDrawCircle(srcPt, 10);

			ofSetColor(255, 0, 0);
			glm::vec2 dstPt = glm::vec2(ofMap(dstPoints[i].x, 0, 1, 640, 1280), ofMap(dstPoints[i].y, 0, 1, 0, 360));
			ofDrawCircle(dstPt, 10);

			ofSetColor(255, 0, 255);
			ofDrawLine(srcPt, dstPt);

			ofSetColor(255);
		}
	}

	guiPanel.draw();
}

void ofApp::drawProjector(ofEventArgs& args)
{
	ofBackground(0);
	ofSetColor(255);

	if (homographyReady && projectWarped)
	{
		warpedImg.draw(0, 0);
	}
	else
	{
		renderFbo.draw(0, 0);
	}

	if (adjustMapping)
	{
		// Draw mapping dst points.
		for (int i = 0; i < dstPoints.size(); i++)
		{
			ofSetColor(255, 0, 0);
			glm::vec2 dstPt = glm::vec2(dstPoints[i].x * PROJECTOR_RESOLUTION_X, dstPoints[i].y * PROJECTOR_RESOLUTION_Y);
			ofDrawCircle(dstPt, 20);
		}
	}
}



void ofApp::mouseDragged(int x, int y, int button)
{
	if (adjustMapping)
	{
		if (activePoint > -1)
		{
			// Move the active Point under the mouse, but stick to edges.
			glm::vec2 normPt = glm::vec2(ofMap(x, mappingWidth, mappingWidth*2, 0, 1, true), ofMap(y, 0, mappingHeight, 0, 1, true));
			dstPoints[activePoint] = normPt;
		}
	}
}

void ofApp::mousePressed(int x, int y, int button)
{
	if (adjustMapping)
	{
		// Try to snap to a dst point.
		for (int i = 0; i < dstPoints.size(); i++)
		{
			glm::vec2 dstPt = glm::vec2(ofMap(dstPoints[i].x, 0, 1, mappingWidth, mappingWidth*2), ofMap(dstPoints[i].y, 0, 1, 0, mappingHeight));
			glm::vec2 mousePt = glm::vec2(x, y);
			if (glm::distance(dstPt, mousePt) < 20)
			{
				// Close enough, let's grab this one.
				activePoint = i;
				break;
			}
		}
	}
	else
	{
		//add ripple
	}
}

void ofApp::mouseReleased(int x, int y, int button)
{
	if (adjustMapping)
	{
		activePoint = -1;
	}
}
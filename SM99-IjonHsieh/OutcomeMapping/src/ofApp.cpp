#include "ofApp.h"

bool shouldRemove(Circles& c) {
    if (c.radius > 15) return true;
    else return false;
}

//--------------------------------------------------------------
void ofApp::setup()
{

    //setup window
    ofSetWindowShape(mappingWidth * 2, mappingHeight*2);

    //setup osc receiver
    recvPort = 3030;
    receiver.setup(recvPort);

    //CODE FROM TUAN
    {
        //set up video
        /*
        waterMovie.load("cloud-sky.mp4");
        waterMovie.setSpeed(1);
        waterMovie.play();
        */
        ofSetBackgroundColor(0, 0, 255);
        ofSetCircleResolution(128);

    }

    //mapping
    ofBackground(0);

    renderFbo.allocate(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);
    warpedImg.allocate(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y, OF_IMAGE_COLOR);


    // Draw the circular mask
    maskFbo.allocate(PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);
    maskFbo.begin();
    {
        ofClear(0.f, 0.f);
        ofDrawCircle(PROJECTOR_RESOLUTION_X / 2, PROJECTOR_RESOLUTION_Y / 2, circleDiameter / 2);
    }
    maskFbo.end();

    ofTexture& maskTexture = maskFbo.getTexture();
    renderFbo.getTexture().setAlphaMask(maskTexture);


    adjustMapping.set("Adjust Mapping", false);
    projectWarped.set("Project Warped", true);
    
    topLeftX.set("Top Left X", 0, -1,2);
    topLeftY.set("Top Left Y", 0, 0,1);
    topRightX.set("Top Right X", 1, -1, 2);
    topRightY.set("Top Right Y", 0, 0, 1);
    bottomLeftX.set("Bottom Left X", 0, -1, 2);
    bottomLeftY.set("Bottom Left Y", 1, 0, 1);
    bottomRightX.set("Bottom Right X", 1, -1, 2);
    bottomRightY.set("Bottom Right Y", 1, 0, 1);
    
    /*
    cornersGroup.setName("Corners");
    for (int i = 0; i < 4; i++) {
        cornersGroup.add(corners[i]);
    }
    */



    guiPanel.setup("Homography", "settings.json");
    guiPanel.add(adjustMapping);
    guiPanel.add(projectWarped);
    //guiPanel.add(cornersGroup);
    
    guiPanel.add(topLeftX);
    guiPanel.add(topLeftY);
    guiPanel.add(topRightX);
    guiPanel.add(topRightY);
    guiPanel.add(bottomLeftX);
    guiPanel.add(bottomLeftY);
    guiPanel.add(bottomRightX);
    guiPanel.add(bottomRightY);

    guiPanel.loadFromFile("settings.json");
    

    


    srcPoints.push_back(glm::vec2(0, 0));
    srcPoints.push_back(glm::vec2(1, 0));
    srcPoints.push_back(glm::vec2(0, 1));
    srcPoints.push_back(glm::vec2(1, 1));

    /*
    dstPoints.push_back(glm::vec2(0, 0));
    dstPoints.push_back(glm::vec2(1, 0));
    dstPoints.push_back(glm::vec2(0, 1));
    dstPoints.push_back(glm::vec2(1, 1));
    */
    
    dstPoints.push_back(glm::vec2(topLeftX,topLeftY));
    dstPoints.push_back(glm::vec2(topRightX, topRightY));
    dstPoints.push_back(glm::vec2(bottomLeftX, bottomLeftY));
    dstPoints.push_back(glm::vec2(bottomRightX, bottomRightY));

    previewShiftY = 200;
    

    activePoint = -1;
    homographyReady = false;


    //tuan - setup sound
    for (int i = 1; i < 7; i++)
    {
        char soundNumber[1024];
        sprintf(soundNumber, "%d.mp3", i);
        soundArray[i] = new  ofSoundPlayer;
        soundArray[i]->loadSound(soundNumber);
    }
}


//--------------------------------------------------------------
void ofApp::update() {
    waterMovie.update();

    while (receiver.hasWaitingMessages())
    {
        //get the message
        ofxOscMessage msg;
        receiver.getNextMessage(msg);

        if (msg.getAddress() == "/position")
        {
            posX = PROJECTOR_RESOLUTION_X / 2 - circleDiameter / 2 + msg.getArgAsInt(0);
            posY = msg.getArgAsInt(1);

            circleVectors.push_back(Circles(posX, posY));
            //play sound
            int index = floorf(ofRandom(1, 7));
            soundArray[index]->play();
        }
        else
        {
            ofLogWarning(__FUNCTION__) << "Unrecognized message" << msg.getAddress();
        }
    }



    for (int i = 0; i < circleVectors.size(); i++) {
        circleVectors[i].update();
    }

    ofRemove(circleVectors, shouldRemove);


    // MAPPING -----------------------
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
        //CODE FROM TUAN
        {
            //play water
            //ofEnableBlendMode(OF_BLENDMODE_DISABLED);
            //ofEnableBlendMode(OF_BLENDMODE_SCREEN);
            //waterMovie.draw(0, 0, PROJECTOR_RESOLUTION_X, PROJECTOR_RESOLUTION_Y);
            ofBackground(255);

            ofEnableBlendMode(OF_BLENDMODE_SCREEN);
            for (int i = 0; i < circleVectors.size(); i++) {
                circleVectors[i].draw();
            }
        }

        //make a feather mask 
        //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        int featherNum = 50;
        for (int i = 0; i < featherNum; i++) {
            ofEnableAlphaBlending();
            ofSetLineWidth(10);
            ofNoFill();
            ofSetColor(0,0,0, ofMap(circleDiameter-i, circleDiameter, circleDiameter- featherNum, 255,0));
            ofDrawCircle(PROJECTOR_RESOLUTION_X/2, PROJECTOR_RESOLUTION_Y/2, circleDiameter / 2 - i*2);
            ofDisableAlphaBlending();
        }
    }
    renderFbo.end();

    if (homographyReady)
    {
        // Read the FBO to pixels.
        renderFbo.readToPixels(renderPixels);
        maskFbo.readToPixels(maskPixels);

        // Warp the pixels into a new image.
        cv::Mat renderMat = ofxCv::toCv(renderPixels);
        cv::Mat maskMat = ofxCv::toCv(maskPixels);

        cv::Mat warpedMat(renderMat.size(), renderMat.type());
        warpedMat.setTo(0); // Clear data
        renderMat.copyTo(warpedMat, maskMat); // Only values at mask > 0 will be copied.




        // Convert the result CV image back to OF space.
        ofxCv::toOf(warpedMat, warpedImg); 
        ofxCv::warpPerspective(warpedMat, warpedImg, homographyMat, CV_INTER_LINEAR);

        warpedImg.update();


    }


}

//--------------------------------------------------------------
void ofApp::draw() {

    // Draw unwarped image on the left.
    renderFbo.draw(0, previewShiftY, mappingWidth, mappingHeight);

    if (homographyReady)
    {
        // Draw warped image on the right.
        warpedImg.draw(mappingWidth, previewShiftY, mappingWidth, mappingHeight);
    }

    if (adjustMapping)
    {
        // Draw mapping points.
        for (int i = 0; i < srcPoints.size(); i++)
        {
            ofSetColor(0, 0, 255);
            glm::vec2 srcPt = glm::vec2(ofMap(srcPoints[i].x, 0, 1, 0, 640), ofMap(srcPoints[i].y, 0, 1, 0, 360)+ previewShiftY);
            ofDrawCircle(srcPt, 10);

            ofSetColor(255, 0, 0);
            glm::vec2 dstPt = glm::vec2(ofMap(dstPoints[i].x, 0, 1, 640, 1280), ofMap(dstPoints[i].y, 0, 1, 0, 360)+ previewShiftY);
            ofDrawCircle(dstPt, 10);

            ofSetColor(255, 0, 255);
            ofDrawLine(srcPt, dstPt);

            ofSetColor(255);
        }
    }

    guiPanel.draw();

}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (adjustMapping)
    {
        if (activePoint > -1)
        {
            // Move the active Point under the mouse.
            glm::vec2 normPt = glm::vec2(ofMap(x, mappingWidth, mappingWidth * 2, 0, 1, false), ofMap(y, previewShiftY, mappingHeight+ previewShiftY, 0, 1, false));
            dstPoints[activePoint] = normPt;
            //corners[activePoint] = glm::vec2(x, y);

            //pass value to gui
            
            if (activePoint == 0)
            {
                topLeftX = normPt[0];
                topLeftY = normPt[1];
            }
            else if (activePoint == 1)
            {
                topRightX = normPt[0];
                topRightY = normPt[1];
            }
            else if (activePoint == 2)
            {
                bottomLeftX = normPt[0];
                bottomLeftY = normPt[1];
            }
            else
            {
                bottomRightX = normPt[0];
                bottomRightY = normPt[1];
            }
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {



    if (adjustMapping)
    {
        // Try to snap to a dst point.
        for (int i = 0; i < dstPoints.size(); i++)
        {
            glm::vec2 dstPt = glm::vec2(ofMap(dstPoints[i].x, 0, 1, mappingWidth, mappingWidth * 2), ofMap(dstPoints[i].y, 0, 1, previewShiftY, mappingHeight+ previewShiftY));
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

        circleVectors.push_back(Circles(ofGetMouseX(), ofGetMouseY()));
        //play sound
        int index = floorf(ofRandom(1, 7));
        soundArray[index]->play();
    }



}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    if (adjustMapping)
    {
        activePoint = -1;
    }
}


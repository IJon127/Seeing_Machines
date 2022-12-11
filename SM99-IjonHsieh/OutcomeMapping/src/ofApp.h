#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxCv.h"

#define PROJECTOR_RESOLUTION_X 1920
#define PROJECTOR_RESOLUTION_Y 1080


class Circles {
public:
    Circles(int x, int y) {
        pos.set(x, y);
        radius = 1;
    }

    void update() {
        radius += 0.02;
    }

    void draw() {
        for (int i = 0; i < 20; i++) {
            ofEnableAlphaBlending();

            float alpha = ofMap(radius * i, 1, 150, 40, 0);
            float lineWeight = ofMap(radius * i, 1, 100, 1, 12);
            ofSetLineWidth(lineWeight);
            ofNoFill();
            ofSetColor(180,220,255, alpha);
            ofDrawCircle(pos.x, pos.y, radius * i);
            ofDisableAlphaBlending();
        }
    }

    ofVec3f pos;
    float radius;
};

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void drawProjector(ofEventArgs& args);

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);


    //void makeNewCircles(int x, int y);

    int circleAmount = 20;
    vector <ofVec3f> circleData;

    vector<Circles> circleVectors;
    ofVideoPlayer waterMovie;

private:

    //osc
    int recvPort;
    ofxOscReceiver receiver;

    int posX;
    int posY;

    //projection
    const int circleDiameter = PROJECTOR_RESOLUTION_Y;
    const int mappingWidth = 640;
    const int mappingHeight = 360;

    ofFbo renderFbo;
    ofPixels renderPixels;
    
    ofImage warpedImg;

    ofFbo maskFbo;
    ofPixels maskPixels;


    std::vector<glm::vec2> srcPoints;
    std::vector<glm::vec2> dstPoints;

    int activePoint;

    cv::Mat homographyMat;
    bool homographyReady;

    ofParameter<bool> adjustMapping;
    ofParameter<bool> projectWarped;
   
    /* 
    //can't be save in settings.json
    ofParameterGroup cornersGroup;
    ofParameter<glm::vec2> corners[4];
    */

    
    ofParameter<float> topLeftX;
    ofParameter<float> topRightX;
    ofParameter<float> bottomLeftX;
    ofParameter<float> bottomRightX;
    ofParameter<float> topLeftY;
    ofParameter<float> topRightY;
    ofParameter<float> bottomLeftY;
    ofParameter<float> bottomRightY;


    ofxPanel guiPanel;

};

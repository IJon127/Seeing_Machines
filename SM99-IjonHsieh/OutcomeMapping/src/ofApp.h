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
        radius += 0.1;
    }

    void draw() {
        for (int i = 0; i < 20; i++) {
            float alpha = ofMap(radius, 1, 20, 40, 0);
            ofNoFill();
            ofSetColor(255, 255, 255, alpha);
            ofDrawCircle(pos.x, pos.y, radius * i);

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

    std::vector<glm::vec2> srcPoints;
    std::vector<glm::vec2> dstPoints;

    int activePoint;

    cv::Mat homographyMat;
    bool homographyReady;

    ofParameter<bool> adjustMapping;
    ofParameter<bool> projectWarped;

    ofxPanel guiPanel;

};

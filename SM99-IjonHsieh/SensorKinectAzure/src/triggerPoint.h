#pragma once

#include "ofMain.h"

class triggerPoint
{
public:
	void setup(int _id, bool _isLeftHand, ofVec2f _pos, float _h);
	bool checkIsLeftHand();
	int getId();
	ofVec2f getPosition();
	float getHeight();

private:
	int trackerId;
	bool isLeftHand;
	ofVec2f pos;
	float h;
};
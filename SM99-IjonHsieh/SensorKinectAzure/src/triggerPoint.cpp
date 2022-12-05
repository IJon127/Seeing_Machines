#include "triggerPoint.h"


void triggerPoint::setup(int _id, bool _isLeftHand, ofVec2f _pos, float _h)
{
	trackerId = _id;
	isLeftHand = _isLeftHand;
	pos = _pos;
	h = _h;
}

int triggerPoint::getId()
{
	return trackerId;
}

bool triggerPoint::checkIsLeftHand()
{
	return isLeftHand;
}

ofVec2f triggerPoint::getPosition()
{
	return pos;
}

float triggerPoint::getHeight()
{
	return h;
}

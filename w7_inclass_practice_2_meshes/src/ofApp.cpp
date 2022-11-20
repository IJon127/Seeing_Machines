#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//setup the parameters
	drawWireFrame.set("wire Frame", false);

	//setup the gui
	guiPanel.setup("Meshes");
	guiPanel.add(drawWireFrame);



	//build the quad mesh
	quadMesh.setMode(OF_PRIMITIVE_TRIANGLES);

	int w = ofGetWindowWidth();
	int h = ofGetWindowHeight();

	//colors
	ofColor clrTopLeft = ofColor(200, 0, 0);
	ofColor clrTopRight = ofColor(0, 200, 0);
	ofColor clrBottomLeft = ofColor(200, 0, 200);
	ofColor clrBottomRight = ofColor(0, 0, 200);



	//first triangle
	quadMesh.addVertex(glm::vec3(0, 0, 0));
	quadMesh.addVertex(glm::vec3(w, 0, 0));
	quadMesh.addVertex(glm::vec3(w, h, 0));
	//add colors
	quadMesh.addColor(clrTopLeft);
	quadMesh.addColor(clrTopRight);
	quadMesh.addColor(clrBottomRight);


	//second triangle
	quadMesh.addVertex(glm::vec3(0, 0, 0));
	quadMesh.addVertex(glm::vec3(0, h, 0));
	quadMesh.addVertex(glm::vec3(w, h, 0));
	//add colors
	quadMesh.addColor(clrTopLeft);
	quadMesh.addColor(clrBottomLeft);
	quadMesh.addColor(clrBottomRight);
}


//--------------------------------------------------------------
void ofApp::draw()
{
	if (drawWireFrame)
	{
		quadMesh.drawWireframe();
	}
	else
	{
		quadMesh.draw();
	}

	guiPanel.draw();

}

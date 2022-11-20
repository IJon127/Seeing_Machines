#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 480);
	grabber.setup(640, 480);
	
	//setup the parameters
	drawWireFrame.set("wire Frame", false);

	//setup the gui
	guiPanel.setup("Meshes");
	guiPanel.add(drawWireFrame);



	//build the quad mesh
	quadMesh.setMode(OF_PRIMITIVE_TRIANGLES);

	int w = ofGetWindowWidth();
	int h = ofGetWindowHeight();



	//first triangle
	quadMesh.addVertex(glm::vec3(0, 0, 0));
	quadMesh.addVertex(glm::vec3(w, 0, 0));
	quadMesh.addVertex(glm::vec3(w, h, 0));
	//add texture coord
	quadMesh.addTexCoord(glm::vec2(0, 0));
	quadMesh.addTexCoord(glm::vec2(w, 0));
	quadMesh.addTexCoord(glm::vec2(w, h));


	//second triangle
	quadMesh.addVertex(glm::vec3(0, 0, 0));
	quadMesh.addVertex(glm::vec3(0, h, 0));
	quadMesh.addVertex(glm::vec3(w, h, 0));
	//add texture coord
	quadMesh.addTexCoord(glm::vec2(0, 0));
	quadMesh.addTexCoord(glm::vec2(0, h));
	quadMesh.addTexCoord(glm::vec2(w, h));
}

//--------------------------------------------------------------
void ofApp::update()
{
	grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	grabber.bind();
	if (drawWireFrame)
	{
		quadMesh.drawWireframe();
	}
	else
	{
		quadMesh.draw();
	}
	grabber.unbind();

	guiPanel.draw();

}
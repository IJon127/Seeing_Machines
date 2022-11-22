#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowShape(640, 480);
	grabber.setup(640, 480);
	
	//setup the parameters
	drawWireFrame.set("Quad Mesh Wire Frame", false);
	usePointMesh.set("Use Point Mesh", false);
	skipPoints.set("Skip Points", 1, 1, 24);

	//setup the gui
	guiPanel.setup("Meshes");
	guiPanel.add(drawWireFrame);
	guiPanel.add(usePointMesh);
	guiPanel.add(skipPoints);



	
	//METHOD 1: 
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

	//METHOD 2:
	//build the point mesh
	pointMesh.clear(); //rebuild the mesh
	pointMesh.setMode(OF_PRIMITIVE_POINTS);
	for (int y = 0; y < grabber.getHeight(); y += skipPoints)
	{
		for (int x = 0; x < grabber.getWidth(); x += skipPoints)
		{
			pointMesh.addVertex(glm::vec3(x, y, 0));
			pointMesh.addTexCoord(glm::vec2(x, y));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	grabber.bind();

	if (usePointMesh)
	{
		//METHOD 2:
		pointMesh.draw();
	}
	else
	{
		//METHOD 1:
		if (drawWireFrame)
		{
			quadMesh.drawWireframe();
		}
		else
		{
			quadMesh.draw();
		}
	}
	grabber.unbind();

	guiPanel.draw();

}
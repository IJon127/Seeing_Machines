#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{	
	//practice 01 - string functions *****************
	cout << "# Practice 01 ----------\n" << endl;

	string myName = "Ijon";
	if (myName.empty()) 
	{
		cout << "No Name!" << endl;
	}
	else
	{
		cout << "Hello, " << myName << "!" << endl;
	}
	cout << "There are " << myName.size() << " characters.\n" << endl;




	//practice 02 - convert data type *****************
	cout << "# Practice 02 ----------\n" << endl;

	int videoWidth = 1920;
	int videoHeight = 1080;
	string resolution = ofToString(videoWidth) + "x" + ofToString(videoHeight);
	cout << "The resolution of the video is: "<< resolution << endl;

	float videoWidthf = 1920.0;
	float videoHeightf = 1080.0;
	string resolutionf = ofToString(videoWidthf, 2) + "x" + ofToString(videoHeightf, 3);
	cout << "The resolution (float) of the video is: " << resolutionf << "\n\n" << endl;



	//practice 03 - 2D array **************************
	cout << "# Practice 03 ----------\n" << endl;

	int numbers[10][3]; //10 columns by 3 rows
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			numbers[x][y] = x + y * 10;
			//cout << values[x][y] << "\t";
			cout << ofToString(numbers[x][y], 2, '0') << " ";
		}
		cout << endl;
	}
	cout << "\n" << endl;


	//practice 04 - random black and white graphic ******
	cout << "# Practice 04 ----------\n" << endl;

	//bool cells[40][30];  is in header file (ofApp.h) because it is used by draw()
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			cells[x][y] = x + y * 40;
			if (ofRandomuf()< 0.5) // or use ofRandom(0,1)
			{
				cells[x][y] = true;
			}
			else
			{
				cells[x][y] = false;
			}
			cout << cells[x][y];

			//practice 05 - add a black frame ***********
			if (x == 0 || x == 39 || y == 0 || y == 29) {
				cells[x][y] = false;
			}
		}
		cout << endl;
	}
	cout << "\n" << endl;



	//practice 06 - use index **************************
	cout << "# Practice 06 ----------\n" << endl;

	bool idxCells[40*30];
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			int idx = x + y * 40;
			if (ofRandomuf() < 0.5) // or use ofRandom(0,1)
			{
				idxCells[idx] = true;
			}
			else
			{
				idxCells[idx] = false;
			}
			cout << idxCells[idx];
		}
		cout << endl;
	}
	cout << "\n" << endl;
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{

	//practice 04 & 05 - random black and white graphic ******
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			if (cells[x][y]) 
			{
				ofSetColor(255);
			}
			else
			{
				ofSetColor(0);
			}

			ofDrawRectangle(x * 10, y * 10, 10, 10);
		}
	}


}

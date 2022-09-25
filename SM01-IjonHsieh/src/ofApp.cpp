#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    img.allocate(1000, 800, OF_IMAGE_GRAYSCALE);
    ofSetWindowShape(img.getWidth(), img.getHeight());

    imgPix = img.getPixels();
    for (int y = 0; y < ofGetHeight(); y++)
    {
        for (int x = 0; x < ofGetWidth(); x++)
        {
            int index = (x + y * ofGetWidth()) * imgPix.getNumChannels();
            if (ofRandomuf() < 0.2) 
            {
                imgPix.setColor(index, ofColor(255));
            }
            else
            {
                imgPix.setColor(index, ofColor(0));
            }
        }
    }

    img.setFromPixels(imgPix);


}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    img.draw(0, 0);

    ofPixels newImgPix;
    newImgPix = imgPix;

    //for (each cell in image):
    for (int y = 0; y < ofGetHeight(); y++)
    {
        for (int x = 0; x < ofGetWidth(); x++)
        {
            //count live neighbors:
            int sum = 0;
            for (int ny = y - 1; ny <= y + 1; ny++) //count live neighbors:
            {
                for (int nx = x - 1; nx <= x + 1; nx++) 
                {
                    if (imgPix.getColor(nx, ny) == ofColor(255))
                    {
                        sum++;
                    }
                }
            }
            
            //check cell status:
            if (imgPix.getColor(x, y) == ofColor(255)) //if (cell is live)
            {
                if (sum < 3 || sum > 4) //if (num live neighbors < 2) or if (num live neighbors > 3) :
                {
                    newImgPix.setColor(x, y, ofColor(0));
                }

            }
            else //if (cell is dead)
            {
                if (sum == 3) //if (num live neighbors == 3) :
                {
                    newImgPix.setColor(x, y, ofColor(255));
                }
            }
        }
    }
    imgPix = newImgPix; //update pixels
    img.setFromPixels(newImgPix);
}



    



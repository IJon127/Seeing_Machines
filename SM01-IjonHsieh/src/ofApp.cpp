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
    newImgPix = imgPix;

}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    img.draw(0, 0);

    unsigned char* data = img.getPixels().getData();
    //for (each cell in image):
    for (int y = 1; y < ofGetHeight()-1; y++)
    {
        for (int x = 1; x < ofGetWidth()-1; x++)
        {
            //count live neighbors:
            int sum = 0;
            for (int ny = y - 1; ny <= y + 1; ny++)
            {
                for (int nx = x - 1; nx <= x + 1; nx++) 
                {
                    int idx = ny * ofGetWidth() + nx;
                    if (data[idx] == 255)
                    //if (img.getColor(nx, ny) == ofColor(255))
                    {
                        sum++;
                    }
                }
            }
            
            //check cell status:
            int idx = y * ofGetWidth() + x;
            if (data[idx] == 255)
            //if (img.getColor(x, y) == ofColor(255)) //if (cell is live)
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
    img.setFromPixels(newImgPix);
}



    



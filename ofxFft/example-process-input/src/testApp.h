#pragma once

#include "ofMain.h"
#include "ofxProcessFFT.h"
#include "ofxXmlSettings.h"
#include "ofxDelaunay.h"
#include "ofxSvg.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void keyPressed(int key);
	
	ProcessFFT fft;
    
    ofSoundPlayer player;
    vector<ofPoint> lowGraph;
    vector<ofPoint> mediumGraph;
    vector<ofPoint> highGraph;
    
    vector<float> lowGraphpts;
    vector<float> mediumGraphpts;
    vector<float> highGraphpts;
    
    ofxXmlSettings xml;
    ofxDelaunay triLow, triMed, triHigh;
    bool start;
    
    ofxSVG lowPath;
};

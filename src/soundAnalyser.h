//
//  soundAnalyser.h
//  GuitarMap
//
//  Created by Joao Freire on 10/15/15.
//
//

#ifndef soundAnalyser_h
#define soundAnalyser_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxProcessFFT.h"
#include "ofxGui.h"
#include "ofxJSON.h"


class soundAnalyser
{
public:
    void setup();
    void update();
    void draw();
    void getSpectum();
    ofxPanel gui;
    
    vector<float> getBass();

private:
    ProcessFFT fft;
    ofTrueTypeFont verdana;
    
    map <int,ofxFloatSlider> maxVal ;
    map <int,ofxFloatSlider> minVal ;
    ofSoundPlayer sound0, sound1, sound2, sound3, sound4, sound5;
    ofxJSONElement db;
    
    vector<float> bassSpec;
};
#endif /* soundAnalyser_h */

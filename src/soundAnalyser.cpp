//
//  soundAnalyser.cpp
//  GuitarMap
//
//  Created by Joao Freire on 10/15/15.
//
//

#include "soundAnalyser.h"

#include "ofApp.h"

void soundAnalyser::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    fft.setup();

    fft.setHistorySize(300);
    fft.setNormalize(false);
    fft.setVolumeRange(200);
    verdana.loadFont("fonts/Gotham-Black.ttf", 20);

   // getSpectum();
    fft.setNumFFTBins(6);
    sound0.loadSound("bass.mp3");
    sound0.play();
    
   /* sound1.loadSound("drums.mp3");
    sound1.play();
    sound2.loadSound("french-horns.mp3");
    sound2.play();
    sound3.loadSound("guitars.mp3");
    sound3.play();
    sound4.loadSound("saxophone.mp3");
    sound4.play();
    sound5.loadSound("strings.mp3");
    sound5.play();*/
    
}



void soundAnalyser::update() {

    fft.update();
    // float val = fft.getSpectralCentroid();
    //verdana.drawString(ofToString(val), 100, 300);
    vector<float> spec = fft.getSpectrum();
    
    //  fft.getSmoothedUnScaledLoudestValue();
      
}

void soundAnalyser::draw() {
    ofBackground(0);
    fft.drawBars();
    //  fft.drawDebug();
    
    
}



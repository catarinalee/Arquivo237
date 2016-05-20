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

    fft.setup();

    fft.setHistorySize(300);
    fft.setNormalize(false);
    fft.setVolumeRange(400);
    verdana.loadFont("fonts/Gotham-Black.ttf", 20);

   // getSpectum();
    fft.setNumFFTBins(20);
    sound0.loadSound("strings.mp3");
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

vector<float> soundAnalyser::getBass()
{
    return bassSpec;
}

void soundAnalyser::update() {

    fft.update();
    // float val = fft.getSpectralCentroid();
    //verdana.drawString(ofToString(val), 100, 300);
    bassSpec = fft.getSpectrum();
    if(sound0.getIsPlaying())
    {
        float pos = (float)((int)(sound0.getPosition()*10000)/10000.0f);
        cout <<pos<<endl;

        for(int i = 0; i < bassSpec.size(); i++)
        {
            db[ofToString(pos)][i] = bassSpec[i];
        }
       // cout<<"Analysing"<<endl;
        //cout<<db<<endl;

    }
    else
    {
        ofFile newfile(ofToDataPath("json/strings.json"), ofFile::WriteOnly);
        //cout<<db<<endl;
        newfile << db;

        cout<<"Saved"<<endl;
       // exit(1);
    }
    //  fft.getSmoothedUnScaledLoudestValue();
      
}

void soundAnalyser::draw() {
    ofBackground(0);
    fft.drawBars();
    //  fft.drawDebug();
    
    
}



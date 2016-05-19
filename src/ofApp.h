#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "soundAnalyser.h"

struct instrument
{
    ofxPanel panel;
    ofParameter <float> speed;
    ofParameter <float> volume;
    ofParameter <float> pan;
    ofSoundPlayer sound;
    int bin;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofSoundPlayer guitar;
    
    ofxPanel panelGuitar;
    ofParameter <float> speedGuitar;
    ofParameter <float> volumeGuitar;
    ofParameter <float> panGuitar;

    float * fftSmoothedGuitar;
    int nBandsToGetGuitar;
    
    
    ofSoundPlayer drums;
    
    ofxPanel panelDrums;
    ofParameter <float> speedDrums;
    ofParameter <float> volumeDrums;
    
    
    
    ofSoundPlayer strings;
    
    ofxPanel panelStrings;
    ofParameter <float> speedStrings;
    ofParameter <float> volumeStrings;
    ofParameter <float> panStrings;
    
    
    
    ofSoundPlayer bass;
    
    ofxPanel panelBass;
    ofParameter <float> speedBass;
    ofParameter <float> volumeBass;
    
    
    
    ofSoundPlayer sax;
    
    ofxPanel panelSax;
    ofParameter <float> speedSax;
    ofParameter <float> volumeSax;
    
    
    
    ofSoundPlayer horn;
    
    ofxPanel panelHorn;
    ofParameter <float> speedHorn;
    ofParameter <float> volumeHorn;
    
    map<string, instrument> instruments;
    soundAnalyser analyze;
    
		
};

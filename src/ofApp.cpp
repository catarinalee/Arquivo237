#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    
    
 /*   instruments["Guitar"].sound.loadSound("guitar.mp3");
    instruments["drums"].sound.loadSound("guitar.mp3");
    instruments["strings"].sound.loadSound("guitar.mp3");
    instruments["bass"].sound.loadSound("guitar.mp3");
    instruments["sax"].sound.loadSound("guitar.mp3");
    instruments["horn"].sound.loadSound("guitar.mp3");
*/
    
    // load in sounds:
    guitar.loadSound("guitars.mp3");
    guitar.setLoop(true);
    guitar.play();
    //guitar.getPosition();
    
    fftSmoothedGuitar = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothedGuitar[i] = 0;
    }
    nBandsToGetGuitar = 1;

    
    drums.loadSound("drums.mp3");
    drums.setLoop(true);
    //drums.play();
 
    
    strings.loadSound("strings.mp3");
    strings.setLoop(true);
    //strings.play();
    
    bass.loadSound("bass.mp3");
    bass.setLoop(true);
    //bass.play();
    
    sax.loadSound("saxophone.mp3");
    sax.setLoop(true);
    //sax.play();
    
    horn.loadSound("french-horns.mp3");
    horn.setLoop(true);
    //horn.play();
    
    // gui panels:
    panelGuitar.setup("Guitars", "settings.xml", 750, 100);
    panelGuitar.add(speedGuitar.set("Speed", 1.0, 0.25, 2.0));
    panelGuitar.add(volumeGuitar.set("Volume", 0.5, 0.0, 1.0));
    panelGuitar.add(panGuitar.set("Pan", 0.0, -1.0, 1.0));

    panelDrums.setup("Drums", "settings.xml", 750, 200);
    panelDrums.add(speedDrums.set("Speed", 1.0, 0.25, 2.0));
    panelDrums.add(volumeDrums.set("Volume", 0.5, 0.0, 1.0));
    
    panelStrings.setup("Strings", "settings.xml", 750, 300);
    panelStrings.add(speedStrings.set("Speed", 1.0, 0.25, 2.0));
    panelStrings.add(volumeStrings.set("Volume", 0.5, 0.0, 1.0));
    panelStrings.add(panStrings.set("Pan", 0.0, -1.0, 1.0));
    
    panelBass.setup("Bass", "settings.xml", 750, 400);
    panelBass.add(speedBass.set("Speed", 1.0, 0.25, 2.0));
    panelBass.add(volumeBass.set("Volume", 0.5, 0.0, 1.0));
    
    panelSax.setup("Saxophone", "settings.xml", 750, 500);
    panelSax.add(speedSax.set("Speed", 1.0, 0.25, 2.0));
    panelSax.add(volumeSax.set("Volume", 0.5, 0.0, 1.0));
    
    panelHorn.setup("French Horns", "settings.xml", 750, 600);
    panelHorn.add(speedHorn.set("Speed", 1.0, 0.25, 2.0));
    panelHorn.add(volumeHorn.set("Volume", 0.5, 0.0, 1.0));
    
    ofBackground(0);
    analyze.setup();

}

//--------------------------------------------------------------
void ofApp::update(){
    analyze.update();
    guitar.setSpeed(speedGuitar);
    guitar.setVolume(volumeGuitar);
    guitar.setPan(panGuitar);
    
    drums.setSpeed(speedDrums);
    drums.setVolume(volumeDrums);
    
    strings.setSpeed(speedStrings);
    strings.setVolume(volumeStrings);
    strings.setPan(panStrings);
    
    bass.setSpeed(speedBass);
    bass.setVolume(volumeBass);
    
    sax.setSpeed(speedSax);
    sax.setVolume(volumeSax);
    
    horn.setSpeed(speedHorn);
    horn.setVolume(volumeHorn);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofBackground(220,(speedGuitar+speedStrings+speedDrums+speedBass+speedSax+speedHorn)*10,(volumeGuitar+volumeStrings+volumeDrums+volumeBass+volumeSax+volumeHorn)*10);
    
    ofColor colorOne(255, (speedGuitar+speedStrings+speedDrums+speedBass+speedSax+speedHorn)*50, 0);
    ofColor colorTwo(255, (volumeGuitar+volumeStrings+volumeDrums+volumeBass+volumeSax+volumeHorn)*50, 0);
    
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);
        
//    ofSetColor(255,speedGuitar*50,volumeGuitar*100);
//    ofRect(0,0,ofGetWidth()/4,ofGetHeight());
    
    ofColor colorGuitar(255,speedGuitar*150,volumeGuitar*50);
    /*ofMesh guitar;
    guitar.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    guitar.addVertex(ofPoint(ofGetWidth()/6,0));
    guitar.addColor(colorGuitar);
    guitar.addVertex(ofPoint(ofGetWidth()/2-(speedGuitar+volumeGuitar*100),0));
    guitar.addColor(ofColor::orangeRed);
    guitar.addVertex(ofPoint(ofGetWidth()/6,ofGetHeight()));
    guitar.addColor(colorGuitar);
    guitar.addVertex(ofPoint(ofGetWidth()/2-(speedGuitar+volumeGuitar*100),ofGetHeight()));
    guitar.addColor(ofColor::orangeRed);*/
    
    ofMesh guitar;
    guitar.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    int x = ofGetWidth()/6 + panGuitar * 60;
    int y = 0;
    vector <float> aux = analyze.getBass();
    for(int i = 0; i < 20; i++)
    {
        y = ofGetHeight()/20 * i;
        float a = ofMap(aux[i], 50, 200, 0.3, 1);
        float b = ofMap(aux[i], 50, 200, -1, 1);

        guitar.addVertex(ofPoint(x + 100 * a, y));
        guitar.addColor(colorGuitar);
        guitar.addVertex(ofPoint(x - 100 *a, y));
        guitar.addColor(colorGuitar + b*40);
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        guitar.addVertex(ofPoint(x + 100 * a, y));
        guitar.addColor(colorGuitar);
        guitar.addVertex(ofPoint(x - 100 *a, y));
        guitar.addColor(colorGuitar + b*40);

    }
    
    
    
    guitar.draw();
    
   /* ofColor colorSax(255,speedSax*150,volumeSax*50);
    ofMesh sax;
    sax.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    sax.addVertex(ofPoint(ofGetWidth()-(ofGetWidth()/4),0));
    sax.addColor(colorSax);
    sax.addVertex(ofPoint(ofGetWidth()-(speedSax*200),0));
    sax.addColor(ofColor::orangeRed);
    sax.addVertex(ofPoint(ofGetWidth()-(ofGetWidth()/4),ofGetHeight()));
    sax.addColor(colorSax);
    sax.addVertex(ofPoint(ofGetWidth()-(speedSax*200),ofGetHeight()));
    sax.addColor(ofColor::orangeRed);
    sax.draw();
    
    ofColor colorHorn(255,speedHorn*150,volumeHorn*50);
    ofMesh horn;
    horn.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    horn.addVertex(ofPoint(ofGetWidth()/2,0));
    horn.addColor(colorHorn);
    horn.addVertex(ofPoint(200+(speedHorn*volumeHorn*150),0));
    horn.addColor(ofColor::orangeRed);
    horn.addVertex(ofPoint(ofGetWidth()/2,ofGetHeight()));
    horn.addColor(colorHorn);
    horn.addVertex(ofPoint(200+(speedHorn*volumeHorn*150),ofGetHeight()));
    horn.addColor(ofColor::orangeRed);
    horn.draw();
    
    for (int i = 0;i < nBandsToGetGuitar; i++){
        ofSetColor(0);
        ofRect(10,10,20,fftSmoothedGuitar[i]*100);
    }*/
    
    panelGuitar.draw();
    panelDrums.draw();
    panelStrings.draw();
    panelBass.draw();
    panelSax.draw();
    panelHorn.draw();
    
    ofCircle(ofGetMouseX(), ofGetMouseY(),5);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(100);
    
    
 /*   instruments["Guitar"].sound.loadSound("guitar.mp3");
    instruments["drums"].sound.loadSound("guitar.mp3");
    instruments["strings"].sound.loadSound("guitar.mp3");
    instruments["bass"].sound.loadSound("guitar.mp3");
    instruments["sax"].sound.loadSound("guitar.mp3");
    instruments["horn"].sound.loadSound("guitar.mp3");
*/
    
    jsonvalues["saxophone"].open("json/saxophone.json");
    jsonvalues["guitars"].open("json/guitars.json");
    jsonvalues["french-horns"].open("json/french-horns.json");
    jsonvalues["drums"].open("json/drums.json");
    jsonvalues["strings"].open("json/strings.json");
    jsonvalues["bass"].open("json/bass.json");

    

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
    drums.play();
 
    
    strings.loadSound("strings.mp3");
    strings.setLoop(true);
    strings.play();
    
    bass.loadSound("bass.mp3");
    bass.setLoop(true);
    bass.play();
    
    sax.loadSound("saxophone.mp3");
    sax.setLoop(true);
    sax.play();
    
    horn.loadSound("french-horns.mp3");
    horn.setLoop(true);
    horn.play();
    
    // gui panels:
    panelGuitar.setup("Guitars", "settings.xml", 750, 100);
    panelGuitar.add(speedGuitar.set("Speed", 1.0, 0.25, 2.0));
    panelGuitar.add(volumeGuitar.set("Volume", 0.5, 0.0, 1.0));
    panelGuitar.add(panGuitar.set("Pan", 0.0, -1.0, 1.0));

    panelDrums.setup("Drums", "settings.xml", 750, 200);
    panelDrums.add(speedDrums.set("Speed", 1.0, 0.25, 2.0));
    panelDrums.add(volumeDrums.set("Volume", 0.5, 0.0, 1.0));
    panelDrums.add(panDrums.set("Pan", 0.0, -1.0, 1.0));

    panelStrings.setup("Strings", "settings.xml", 750, 300);
    panelStrings.add(speedStrings.set("Speed", 1.0, 0.25, 2.0));
    panelStrings.add(volumeStrings.set("Volume", 0.5, 0.0, 1.0));
    panelStrings.add(panStrings.set("Pan", 0.0, -1.0, 1.0));
    
    panelBass.setup("Bass", "settings.xml", 750, 400);
    panelBass.add(speedBass.set("Speed", 1.0, 0.25, 2.0));
    panelBass.add(volumeBass.set("Volume", 0.5, 0.0, 1.0));
    panelBass.add(panBass.set("Pan", 0.0, -1.0, 1.0));

    panelSax.setup("Saxophone", "settings.xml", 750, 500);
    panelSax.add(speedSax.set("Speed", 1.0, 0.25, 2.0));
    panelSax.add(volumeSax.set("Volume", 0.5, 0.0, 1.0));
    panelSax.add(panSax.set("Pan", 0.0, -1.0, 1.0));

    panelHorn.setup("French Horns", "settings.xml", 750, 600);
    panelHorn.add(speedHorn.set("Speed", 1.0, 0.25, 2.0));
    panelHorn.add(volumeHorn.set("Volume", 0.5, 0.0, 1.0));
    panelHorn.add(panHorn.set("Pan", 0.0, -1.0, 1.0));

    ofBackground(0);
   // analyze.setup();

}

//--------------------------------------------------------------
void ofApp::update(){
   // cout<<ofGetFrameRate()<<endl;
    //analyze.update();
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
    
    ofColor colorGuitar(255,speedGuitar*150,volumeGuitar*50);
    
    ofMesh guitarmesh;
    guitarmesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    int x = ofGetWidth()/7 + panGuitar * 60;
    int y = 0;
    //vector <float> aux = analyze.getBass();
   float pos = (float)((int)(guitar.getPosition()*10000)/10000.0f);
    while(jsonvalues["guitars"][ofToString(pos)] == ofxJSONElement::null)
    {
        pos += 0.0001;
       // cout<<pos<<endl;
       // cout<<jsonvalues["saxophone"][ofToString(pos)]<<endl;
    }

    for(int i = 0; i < 20; i++)
    {
        float val =jsonvalues["guitars"][ofToString(pos)][i].asFloat();
        y = ofGetHeight()/20 * i;
        float a = ofMap(val, 20, 300, 0.3, 3, true);
        float b = ofMap(val, 50, 200, 1, 10, true);

        guitarmesh.addVertex(ofPoint(x + 100 * a, y));
        guitarmesh.addColor(colorGuitar);
        guitarmesh.addVertex(ofPoint(x - 100 *a, y));
        guitarmesh.addColor(ofColor(colorGuitar.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        guitarmesh.addVertex(ofPoint(x + 100 * a, y));
        guitarmesh.addColor(colorGuitar);
        guitarmesh.addVertex(ofPoint(x - 100 *a, y));
        guitarmesh.addColor(ofColor(colorGuitar.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
    }
    guitarmesh.draw();
    
    ofColor colorSax(255,speedSax*150,volumeSax*50);
    ofMesh saxmesh;
    saxmesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    x = ofGetWidth()/7 * 2 + panSax * 60;
    y = 0;
    //vector <float> aux = analyze.getBass();
    pos = (float)((int)(sax.getPosition()*10000)/10000.0f);
    while(jsonvalues["saxophone"][ofToString(pos)] == ofxJSONElement::null)
    {
    pos += 0.0001;
    
    }
    
    for(int i = 0; i < 20; i++)
    {
    float val =jsonvalues["saxophone"][ofToString(pos)][i].asFloat();
    y = ofGetHeight()/20 * i;
        float a = ofMap(val, 20, 300, 0.3, 3, true);
        float b = ofMap(val, 50, 200, 1, 10, true);
    
    saxmesh.addVertex(ofPoint(x + 100 * a, y));
    saxmesh.addColor(colorSax);
    saxmesh.addVertex(ofPoint(x - 100 *a, y));
    saxmesh.addColor(ofColor(colorSax.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
    
    y = ofGetHeight()/20 * i + ofGetHeight()/25;
    
    saxmesh.addVertex(ofPoint(x + 100 * a, y));
    saxmesh.addColor(colorSax);
    saxmesh.addVertex(ofPoint(x - 100 *a, y));
    saxmesh.addColor(ofColor(colorSax.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
    }
    saxmesh.draw();
   
    ofColor colorHorn(255,speedHorn*150,volumeHorn*50);
    
    ofMesh hornmesh;
    hornmesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    x = ofGetWidth()/7 * 3 + panHorn * 60;
    y = 0;
    //vector <float> aux = analyze.getBass();
    pos = (float)((int)(horn.getPosition()*10000)/10000.0f);
    while(jsonvalues["french-horns"][ofToString(pos)] == ofxJSONElement::null)
    {
        pos += 0.0001;
        
    }
    
    for(int i = 0; i < 20; i++)
    {
        float val =jsonvalues["french-horns"][ofToString(pos)][i].asFloat();
        y = ofGetHeight()/20 * i;
        float a = ofMap(val, 20, 300, 0.3, 3, true);
        float b = ofMap(val, 50, 200, 1, 10, true);
        
        hornmesh.addVertex(ofPoint(x + 100 * a, y));
        hornmesh.addColor(colorHorn);
        hornmesh.addVertex(ofPoint(x - 100 *a, y));
        hornmesh.addColor(ofColor(colorHorn.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        hornmesh.addVertex(ofPoint(x + 100 * a, y));
        hornmesh.addColor(colorHorn);
        hornmesh.addVertex(ofPoint(x - 100 *a, y));
        hornmesh.addColor(ofColor(colorHorn.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
    }
    hornmesh.draw();
    
    
    ofColor colorStrings(255,speedStrings*150,volumeStrings*50);
    
    ofMesh stringsmesh;
    stringsmesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    x = ofGetWidth()/7 * 4 + panStrings * 60;
    y = 0;
    //vector <float> aux = analyze.getBass();
    pos = (float)((int)(strings.getPosition()*10000)/10000.0f);
    while(jsonvalues["strings"][ofToString(pos)] == ofxJSONElement::null)
    {
        pos += 0.0001;
        
    }
    
    for(int i = 0; i < 20; i++)
    {
        float val =jsonvalues["strings"][ofToString(pos)][i].asFloat();
        y = ofGetHeight()/20 * i;
        float a = ofMap(val, 20, 300, 0.3, 3, true);
        float b = ofMap(val, 50, 200, 1, 10, true);
        
        stringsmesh.addVertex(ofPoint(x + 100 * a, y));
        stringsmesh.addColor(colorStrings);
        stringsmesh.addVertex(ofPoint(x - 100 *a, y));
        stringsmesh.addColor(ofColor(colorSax.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        stringsmesh.addVertex(ofPoint(x + 100 * a, y));
        stringsmesh.addColor(colorStrings);
        stringsmesh.addVertex(ofPoint(x - 100 *a, y));
        stringsmesh.addColor(ofColor(colorStrings.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
    }
    stringsmesh.draw();
    
    ofColor colorBass(255,speedBass*150,volumeBass*50);
    
    ofMesh bassmesh;
    bassmesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    x = ofGetWidth()/7 * 5 + panBass * 60;
    y = 0;
    //vector <float> aux = analyze.getBass();
    pos = (float)((int)(bass.getPosition()*10000)/10000.0f);
    while(jsonvalues["bass"][ofToString(pos)] == ofxJSONElement::null)
    {
        pos += 0.0001;
        
    }
    
    for(int i = 0; i < 20; i++)
    {
        float val =jsonvalues["bass"][ofToString(pos)][i].asFloat();
        y = ofGetHeight()/20 * i;
        float a = ofMap(val, 20, 300, 0.3, 3, true);
        float b = ofMap(val, 50, 200, 1, 10, true);
        bassmesh.addVertex(ofPoint(x + 100 * a, y));
        bassmesh.addColor(colorBass);
        bassmesh.addVertex(ofPoint(x - 100 *a, y));
        bassmesh.addColor(ofColor(colorBass.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        bassmesh.addVertex(ofPoint(x + 100 * a, y));
        bassmesh.addColor(colorBass);
        bassmesh.addVertex(ofPoint(x - 100 *a, y));
        bassmesh.addColor(ofColor(colorBass.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
    }
    bassmesh.draw();
    
    ofColor colorDrums(255,speedDrums*150,volumeDrums*50);
    
    ofMesh drumsmesh;
    drumsmesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    x = ofGetWidth()/7 * 6 + panDrums * 60;
    y = 0;
    //vector <float> aux = analyze.getBass();
    pos = (float)((int)(drums.getPosition()*10000)/10000.0f);
    while(jsonvalues["drums"][ofToString(pos)] == ofxJSONElement::null)
    {
        pos += 0.0001;
        
    }
    
    for(int i = 0; i < 20; i++)
    {
        float val =jsonvalues["drums"][ofToString(pos)][i].asFloat();
        y = ofGetHeight()/20 * i;
        float a = ofMap(val, 20, 300, 0.3, 3, true);
        float b = ofMap(val, 50, 200, 1, 10, true);
        
        drumsmesh.addVertex(ofPoint(x + 100 * a, y));
        drumsmesh.addColor(colorDrums);
        drumsmesh.addVertex(ofPoint(x - 100 *a, y));
        drumsmesh.addColor(ofColor(colorDrums.r , colorDrums.g-b,colorDrums.g-b));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        drumsmesh.addVertex(ofPoint(x + 100 * a, y));
        drumsmesh.addColor(colorDrums);
        drumsmesh.addVertex(ofPoint(x - 100 *a, y));
        drumsmesh.addColor(ofColor(colorDrums.r , colorDrums.g-b,colorDrums.g-b));//colorGuitar.g, colorGuitar.b));
    }
    drumsmesh.draw();
    /*horn.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
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
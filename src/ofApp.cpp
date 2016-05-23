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
    panelGuitar.add(speedGuitar.set("Speed", 1.0, -1.0, 2.0));
    panelGuitar.add(volumeGuitar.set("Volume", 0.5, 0.0, 1.0));
    panelGuitar.add(panGuitar.set("Pan", 0.0, -1.0, 1.0));
    
    panelSax.setup("Saxophone", "settings.xml", 750, 200);
    panelSax.add(speedSax.set("Speed", 1.0, -1.0, 2.0));
    panelSax.add(volumeSax.set("Volume", 0.5, 0.0, 1.0));
    panelSax.add(panSax.set("Pan", 0.0, -1.0, 1.0));
    
    panelHorn.setup("French Horns", "settings.xml", 750, 300);
    panelHorn.add(speedHorn.set("Speed", 1.0, -1.0, 2.0));
    panelHorn.add(volumeHorn.set("Volume", 0.5, 0.0, 1.0));
    panelHorn.add(panHorn.set("Pan", 0.0, -1.0, 1.0));
    
    panelStrings.setup("Strings", "settings.xml", 750, 400);
    panelStrings.add(speedStrings.set("Speed", 1.0, -1.0, 2.0));
    panelStrings.add(volumeStrings.set("Volume", 0.5, 0.0, 1.0));
    panelStrings.add(panStrings.set("Pan", 0.0, -1.0, 1.0));
    
    panelBass.setup("Bass", "settings.xml", 750, 500);
    panelBass.add(speedBass.set("Speed", 1.0, -1.0, 2.0));
    panelBass.add(volumeBass.set("Volume", 0.5, 0.0, 1.0));
    panelBass.add(panBass.set("Pan", 0.0, -1.0, 1.0));
    
    panelDrums.setup("Drums", "settings.xml", 750, 600);
    panelDrums.add(speedDrums.set("Speed", 1.0, -1.0, 2.0));
    panelDrums.add(volumeDrums.set("Volume", 0.5, 0.0, 1.0));
    panelDrums.add(panDrums.set("Pan", 0.0, -1.0, 1.0));

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
    drums.setPan(panDrums);
    
    strings.setSpeed(speedStrings);
    strings.setVolume(volumeStrings);
    strings.setPan(panStrings);
    
    bass.setSpeed(speedBass);
    bass.setVolume(volumeBass);
    bass.setPan(panBass);
    
    sax.setSpeed(speedSax);
    sax.setVolume(volumeSax);
    sax.setPan(panSax);
    
    horn.setSpeed(speedHorn);
    horn.setVolume(volumeHorn);
    horn.setPan(panHorn);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofBackground(220,(speedGuitar+speedStrings+speedDrums+speedBass+speedSax+speedHorn)*10,(volumeGuitar+volumeStrings+volumeDrums+volumeBass+volumeSax+volumeHorn)*10);
    
    ofColor colorOne(255, ((speedGuitar+1)+(speedStrings+1)+(speedDrums+1)+(speedBass+1)+(speedSax+1)+(speedHorn+1))*18, ((speedGuitar+1)+(speedStrings+1)+(speedDrums+1)+(speedBass+1)+(speedSax+1)+(speedHorn+1))*9);
    ofColor colorTwo(255, ((panGuitar+1)+(panStrings+1)+(panDrums+1)+(panBass+1)+(panSax+1)+(panHorn+1))*100, 0);
    
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);
    
    
    
    //speed -1 2
    //volume 0 1
    //pan -1 1
    
    ofColor colorGuitar(255,(speedGuitar+1)*140,(speedGuitar+1)*45,volumeGuitar*255);
    ofColor colorGuitar2(255,(panGuitar+1)*125,(panGuitar+1)*20,volumeGuitar*255);
    
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
        guitarmesh.addColor(colorGuitar2);//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        guitarmesh.addVertex(ofPoint(x + 100 * a, y));
        guitarmesh.addColor(colorGuitar);
        guitarmesh.addVertex(ofPoint(x - 100 *a, y));
        guitarmesh.addColor(colorGuitar2);//colorGuitar.g, colorGuitar.b));
    }
    guitarmesh.draw();
    
    
    
    ofColor colorSax(255,(speedSax+1)*140,(speedSax+1)*45,volumeSax*255);
    ofColor colorSax2(255,(panSax+1)*125,(panSax+1)*20,volumeSax*255);
    
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
    saxmesh.addColor(colorSax2);
    //saxmesh.addColor(ofColor(colorSax.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
    
    y = ofGetHeight()/20 * i + ofGetHeight()/25;
    
    saxmesh.addVertex(ofPoint(x + 100 * a, y));
    saxmesh.addColor(colorSax);
    saxmesh.addVertex(ofPoint(x - 100 *a, y));
    saxmesh.addColor(colorSax2);
    }
    saxmesh.draw();
   
    
    
    ofColor colorHorn(255,(speedHorn+1)*140,(speedHorn+1)*45,volumeHorn*255);
    ofColor colorHorn2(255,(panHorn+1)*125,(panHorn+1)*20,volumeHorn*255);
    
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
        hornmesh.addColor(colorHorn2);
        //hornmesh.addColor(ofColor(colorHorn.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        hornmesh.addVertex(ofPoint(x + 100 * a, y));
        hornmesh.addColor(colorHorn);
        hornmesh.addVertex(ofPoint(x - 100 *a, y));
        hornmesh.addColor(colorHorn2);
    }
    hornmesh.draw();
    
    
    
    ofColor colorStrings(255,(speedStrings+1)*140,(speedStrings+1)*45,volumeStrings*255);
    ofColor colorStrings2(255,(panStrings+1)*125,(panStrings+1)*20,volumeStrings*255);
    
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
        stringsmesh.addColor(colorStrings2);
        //stringsmesh.addColor(ofColor(colorSax.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        stringsmesh.addVertex(ofPoint(x + 100 * a, y));
        stringsmesh.addColor(colorStrings);
        stringsmesh.addVertex(ofPoint(x - 100 *a, y));
        stringsmesh.addColor(colorStrings2);
    }
    stringsmesh.draw();
    
    
    
    ofColor colorBass(255,(speedBass+1)*140,(speedBass+1)*45,volumeBass*255);
    ofColor colorBass2(255,(panBass+1)*125,(panBass+1)*20,volumeBass*255);
    
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
        bassmesh.addColor(colorBass2);
        //bassmesh.addColor(ofColor(colorBass.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        bassmesh.addVertex(ofPoint(x + 100 * a, y));
        bassmesh.addColor(colorBass);
        bassmesh.addVertex(ofPoint(x - 100 *a, y));
        bassmesh.addColor(colorBass2);
    }
    bassmesh.draw();
    
    
    
    ofColor colorDrums(255,(speedDrums+1)*140,(speedDrums+1)*45,volumeDrums*255);
    ofColor colorDrums2(255,(panDrums+1)*125,(panDrums+1)*20,volumeDrums*255);
    
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
        drumsmesh.addColor(colorDrums2);
        //drumsmesh.addColor(ofColor(colorDrums.r - b, 0,0));//colorGuitar.g, colorGuitar.b));
        
        y = ofGetHeight()/20 * i + ofGetHeight()/25;
        
        drumsmesh.addVertex(ofPoint(x + 100 * a, y));
        drumsmesh.addColor(colorDrums);
        drumsmesh.addVertex(ofPoint(x - 100 *a, y));
        drumsmesh.addColor(colorDrums2);
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
    
   /* panelGuitar.draw();
    panelDrums.draw();
    panelStrings.draw();
    panelBass.draw();
    panelSax.draw();
    panelHorn.draw();*/
    
    ofPushStyle();
    ofSetColor(0,0,0);
    ofDrawBitmapString("Guitar \nvol:" + ofToString(volumeGuitar) + "\nspeed:" + ofToString(speedGuitar)+ "\npan:" + ofToString(panGuitar), ofGetWidth()/7 - 30, ofGetHeight() - 50);
    ofDrawBitmapString("Sax \nvol:" + ofToString(volumeSax) + "\nspeed:" + ofToString(speedSax)+ "\npan:" + ofToString(panSax), ofGetWidth()/7 *2 - 30, ofGetHeight() - 50);
    ofDrawBitmapString("Horns \nvol:" + ofToString(volumeHorn) + "\nspeed:" + ofToString(speedHorn)+ "\npan:" + ofToString(panHorn), ofGetWidth()/7 *3- 30, ofGetHeight() - 50);
    ofDrawBitmapString("Strings \nvol:" + ofToString(volumeStrings) + "\nspeed:" + ofToString(speedStrings)+ "\npan:" + ofToString(panStrings), ofGetWidth()/7 *4- 30, ofGetHeight() - 50);
    ofDrawBitmapString("Bass \nvol:" + ofToString(volumeBass) + "\nspeed:" + ofToString(speedBass)+ "\npan:" + ofToString(panBass), ofGetWidth()/7 *5- 30, ofGetHeight() - 50);
    ofDrawBitmapString("Drums \nvol:" + ofToString(volumeDrums) + "\nspeed:" + ofToString(speedDrums)+ "\npan:" + ofToString(panDrums), ofGetWidth()/7 *6- 30, ofGetHeight() - 50);
    
    ofPopStyle();
    //ofCircle(ofGetMouseX(), ofGetMouseY(),5);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if(key == 'z')
    {
        speedBass = 1;
        speedDrums = 1;
        speedGuitar = 1;
        speedHorn = 1;
        speedSax = 1;
        speedStrings = 1;
        volumeGuitar = 0.5;
        volumeHorn = 0.5;
        volumeSax = 0.5;
        volumeStrings = 0.5;
        volumeBass = 0.5;
        volumeDrums = 0.5;
        panDrums = 0;
        panBass = 0;
        panGuitar = 0;
        panStrings = 0;
        panSax = 0;
        panHorn = 0;
    }
    else if(key == 'q')
    {
        volumeGuitar += 0.1;
        if(volumeGuitar > 1)
            volumeGuitar = 1;
    }
    else if(key == 'a')
    {
        volumeGuitar -= 0.1;
        if(volumeGuitar < 0)
            volumeGuitar = 0;
    }
    else if(key == 's')
    {
        volumeSax -= 0.1;
        if(volumeSax < 0)
            volumeSax = 0;
    }
    else if(key == 'w')
    {
        volumeSax += 0.1;
        if(volumeSax > 1)
            volumeSax = 1;
    }
    else if(key == 'd')
    {
        volumeHorn -= 0.1;
        if(volumeHorn < 0)
            volumeHorn = 0;
    }
    else if(key == 'e')
    {
        volumeHorn += 0.1;
        if(volumeHorn > 1)
            volumeSax = 1;
    }
    else if(key == 'f')
    {
        volumeStrings -= 0.1;
        if(volumeStrings < 0)
            volumeStrings = 0;
    }
    else if(key == 'r')
    {
        volumeStrings += 0.1;
        if(volumeStrings > 1)
            volumeStrings = 1;
    }
    else if(key == 'g')
    {
        volumeBass -= 0.1;
        if(volumeBass < 0)
            volumeBass = 0;
    }
    else if(key == 't')
    {
        volumeBass += 0.1;
        if(volumeBass > 1)
            volumeBass = 1;
    }
    else if(key == 'h')
    {
        volumeDrums -= 0.1;
        if(volumeDrums < 0)
            volumeDrums = 0;
    }
    else if(key == 'y')
    {
        volumeDrums += 0.1;
        if(volumeDrums > 1)
            volumeDrums = 1;
    }
    
    //PAN
    else if(key == '1')
    {
        panGuitar -= 0.1;
        if(panGuitar < -1)
            panGuitar = -1;
    }
    else if(key == '2')
    {
        panGuitar += 0.1;
        if(panGuitar > 1)
            panGuitar = 1;
    }
    else if(key == '3')
    {
        panSax -= 0.1;
        if(panSax < -1)
            panSax = -1;
    }
    else if(key == '4')
    {
        panSax += 0.1;
        if(panSax > 1)
            panSax = 1;
    }
    else if(key == '5')
    {
        panHorn -= 0.1;
        if(panHorn < -1)
            panHorn = -1;
    }
    else if(key == '6')
    {
        panHorn += 0.1;
        if(panHorn > 1)
            panHorn = 1;
    }
    else if(key == '7')
    {
        panStrings -= 0.1;
        if(panStrings < -1)
            panStrings = -1;
    }
    else if(key == '8')
    {
        panStrings += 0.1;
        if(panStrings > 1)
            panStrings = 1;
    }
    else if(key == '9')
    {
        panBass -= 0.1;
        if(panBass < -1)
            panBass = -1;
    }
    else if(key == '0')
    {
        panBass += 0.1;
        if(panBass > 1)
            panBass = 1;
    }
    else if(key == '\'')
    {
        panDrums -= 0.1;
        if(panDrums < -1)
            panDrums = -1;
    }
    else if(key == '+')
    {
        panDrums += 0.1;
        if(panDrums > 1)
            panDrums = 1;
    }
    
    //SPEEDs
    else if(key == 'j')
    {
        speedGuitar -= 0.1;
        if(speedGuitar < -1)
            speedGuitar = -1;
    }
    else if(key == 'u')
    {
        speedGuitar += 0.1;
        if(speedGuitar > 2)
            speedGuitar = 2;
    }
    else if(key == 'k')
    {
        speedSax -= 0.1;
        if(speedSax < -1)
            speedSax = -1;
    }
    else if(key == 'i')
    {
        speedSax += 0.1;
        if(speedSax > 2)
            speedSax = 2;
    }
    else if(key == 'l')
    {
        speedHorn -= 0.1;
        if(speedHorn < -1)
            speedHorn = -1;
    }
    else if(key == 'o')
    {
        speedHorn += 0.1;
        if(speedHorn > 2)
            speedHorn = 2;
    }
    else if(key == 231)//ç
    {
        speedStrings -= 0.1;
        if(speedStrings < -1)
            speedStrings = -1;
    }
    else if(key == 'p')
    {
        speedStrings += 0.1;
        if(speedStrings > 2)
            speedStrings = 2;
    }
    else if(key == '~')
    {
        speedBass -= 0.1;
        if(speedBass < -1)
            speedBass = -1;
    }
    else if(key == 'º')
    {
        speedBass += 0.1;
        if(speedBass > 2)
            speedBass = 2;
    }
    else if(key == '´')
    {
        speedDrums -= 0.1;
        if(speedDrums < -1)
            speedDrums = -1;
    }
    else if(key == '\\')
    {
        speedDrums += 0.1;
        if(speedDrums > 2)
            speedDrums = 2;
    }
    
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
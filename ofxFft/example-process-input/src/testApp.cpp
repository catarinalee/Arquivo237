#include "testApp.h"

void testApp::setup() {
	ofSetVerticalSync(true);	
	ofSetFrameRate(60);
	fft.setup();
    player.loadSound("test.mp3");
    player.play();
    fft.setHistorySize(1);
    start = false;
    
    ofBuffer aux = ofBufferFromFile("low.txt");
    cout<<aux.size()<<endl;
    lowGraph.push_back(ofPoint(50,600));
    lowGraph.push_back(ofPoint(50,600));
    
    mediumGraph.push_back(ofPoint(50,600));
    mediumGraph.push_back(ofPoint(50,600));
    
    highGraph.push_back(ofPoint(50,600));
    highGraph.push_back(ofPoint(50,600));

    for(int i = 0; i < aux.size(); i++)
    {
        if(aux.isLastLine())
        {
            lowGraph.push_back(ofPoint(lowGraph[i-1].x, 600));
            break;
        }
        cout<<ofToFloat(aux.getNextLine())<<endl;
        lowGraph.push_back(ofPoint(50 + i*5, 600 - ofToFloat(aux.getNextLine())*1000));
        
    }
    
    ofBuffer aux2 = ofBufferFromFile("medium.txt");
    cout<<aux2.size()<<endl;
    for(int i = 0; i < aux2.size(); i++)
    {
        if(aux2.isLastLine())
        {
            mediumGraph.push_back(ofPoint(mediumGraph[i-1].x, 600));
            break;
        }
        cout<<ofToFloat(aux2.getNextLine())<<endl;
        mediumGraph.push_back(ofPoint(50 + i*5.2, 600 - ofToFloat(aux2.getNextLine())*1000));
        
    }
    
    ofBuffer aux3 = ofBufferFromFile("high.txt");
    cout<<aux3.size()<<endl;
    for(int i = 0; i < aux3.size(); i++)
    {
        if(aux3.isLastLine())
        {
            highGraph.push_back(ofPoint(highGraph[i-1].x, 600));
            break;
        }
        cout<<ofToFloat(aux3.getNextLine())<<endl;
        highGraph.push_back(ofPoint(50 + i*5.5, 600 - ofToFloat(aux3.getNextLine())*1000));
        
    }
    int a = 0;
    //triLow.addPoints(lowGraph);
   // triLow.addPoints(mediumGraph);
    //triLow.addPoints(highGraph);
    //triLow.triangulate();
}

void testApp::update() {
    
	fft.update();
    /*triLow.reset();
    triMed.reset();
    triHigh.reset();
    for(int i = 0; i < fft.getgraphLow()->size(); i++)
    {
        int y = (*fft.getgraphLow())[i];
        triLow.addPoint(ofPoint(1000 - i*5, y));
    }
    for(int i = 0; i < fft.getgraphMid()->size(); i++)
    {
        int y = (*fft.getgraphMid())[i];
        triMed.addPoint(ofPoint(1000 - i*5, y+250));
    }
    for(int i = 0; i < fft.getgraphHigh()->size(); i++)
    {
        int y = (*fft.getgraphHigh())[i];
        triHigh.addPoint(ofPoint(1000 - i*5, y+500));
    }
    
    triLow.triangulate();
    triMed.triangulate();
    triHigh.triangulate();
*/
   // cout<<fft.getgraphHigh()->size()<<endl;
    if(start)
    {
        lowGraphpts.push_back((*fft.getgraphLow())[199]);
        mediumGraphpts.push_back((*fft.getgraphMid())[199]);
        highGraphpts.push_back((*fft.getgraphHigh())[199]);
    }
    else
    {
        if(lowGraphpts.size() > 0)
        {
        ofFile file("low.txt",ofFile::WriteOnly);
        for(int i = 0; i < lowGraphpts.size(); i++)
        {
            file << lowGraphpts[i]<<endl;
        }
            file.close();
            ofFile file2("medium.txt",ofFile::WriteOnly);
            for(int i = 0; i < mediumGraphpts.size(); i++)
            {
                file2 << mediumGraphpts[i]<<endl;
            }
            file2.close();
            ofFile file3("high.txt",ofFile::WriteOnly);
            for(int i = 0; i < highGraphpts.size(); i++)
            {
                file3 << highGraphpts[i]<<endl;
            }
            file3.close();
        }
    }
}



void testApp::draw() {
   /* fft.drawBars();
    fft.drawDebug();

    ofNoFill();
    ofRect(824, 0, 200, 200);
    ofRect(824, 200, 200, 200);
    ofRect(824, 400, 200, 200);
    ofRect(824, 600, 200, 200);
    
    fft.drawHistoryGraph(ofPoint(824,0), LOW);
    fft.drawHistoryGraph(ofPoint(824,200),MID );
    fft.drawHistoryGraph(ofPoint(824,400),HIGH );
    fft.drawHistoryGraph(ofPoint(824,600),MAXSOUND );
    ofDrawBitmapString("LOW",850,20);
    ofDrawBitmapString("HIGH",850,420);
    ofDrawBitmapString("MID",850,220);
    ofDrawBitmapString("MAX VOLUME",850,620);
    
    ofSetColor(0);
    ofDrawBitmapString("Press 'r' or 'q' to toggle normalization of values", 20,320);*/
    
    triLow.draw();
    triMed.draw();
        triHigh.draw();
    
    ofPolyline path;
    path.addVertices(lowGraph);
    ofPolyline path2;
    path2.addVertices(mediumGraph);
    ofPolyline path3;
    path3.addVertices(highGraph);
    ofSetColor(255,0,0);
    path.draw();
    ofSetColor(0,255,0);
    path2.draw();
    ofSetColor(0,0,255);
    path3.draw();
    
    
  /*  for(int i = 0; i < lowGraph.size(); i++)
    {
        
        ofTriangle(lowGraph[i], mediumGraph[i], highGraph[i]);
        ofCircle(lowGraph[i],2);
        ofCircle(mediumGraph[i],2);
        ofCircle(highGraph[i],2);

    }*/
    
}

void testApp::keyPressed(int key){
    
    //toggle between normalized and not to get a sense of the effects
    //You will need to set a volume range if you're not normalizing everything - but this will depend on your sound source and input type to determine the maximum volume range of your codez
    
    if(key=='q'){
        fft.setVolumeRange(100);
        fft.setNormalize(false);
    }
    if(key=='r'){
        fft.setNormalize(true);
    }
    if(key=='s'){
        start = !start;
    }

}

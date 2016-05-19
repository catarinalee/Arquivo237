#pragma once
#include "ofMain.h"
#include "ofxTween.h"

class Intro
{
public:
	void setup(int app);
	void setupBlob(int i, ofPoint center);
	void update();
	void draw();
	ofImage man;
	map <int,ofPolyline> blob;
	map < int,vector <ofPoint> > vertices;
	map < int,vector   <ofPoint> > currentvertices;
	map < int,vector <ofPoint> > newvertices;
	ofPoint newPoint;
	ofColor patternColor;

	map<int,ofImage> patterns;

	ofImage cover;
	map<int, ofFbo> blobMask;
	ofFbo blobs;
	map<int,ofFbo> patternFbo;
	map<int, ofFbo> blobFbo;
	map<int, ofPoint> centers;

	int updateTime;
	int nBlobs;

};
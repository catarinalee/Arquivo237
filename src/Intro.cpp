#include "Intro.h"

void Intro::setup(int app)
{
	updateTime = 0;
	patterns[0].loadImage("intro/pattern-1A.png");
	patterns[1].loadImage("intro/pattern-1B.png");
	patterns[2].loadImage("intro/pattern-2A.png");
	patterns[3].loadImage("intro/pattern-2B.png");
	patterns[0].setAnchorPercent(0.5, 0.5);
	patterns[1].setAnchorPercent(0.5, 0.5);
	patterns[2].setAnchorPercent(0.5, 0.5);
	patterns[3].setAnchorPercent(0.5, 0.5);

	blobs.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	
	if (app == 1 || app == 2)
	{
		patternColor.set(255, 195, 12);
	}
	else if (app == 3)
	{
		patternColor.set(237, 123, 55);
	}
	setupBlob(0, ofPoint(0, ofGetHeight() / 4));
	setupBlob(1, ofPoint(0, ofGetHeight() * 3 / 5));
	setupBlob(2, ofPoint(ofGetWidth() - 100, ofGetHeight()*3 / 4));
	setupBlob(3, ofPoint(ofGetWidth() - 100, ofGetHeight() / 2));
	nBlobs = 4;
}

void Intro::setupBlob(int j, ofPoint center)
{
	int nPoints1 = 10;// ofRandom(6, 10);
	int angleIncr = 360 / nPoints1;
///	center = ofPoint(0, ofGetHeight() / 2);
	centers[j] = center;
	for (int i = 0; i < nPoints1; i++)
	{
		float radius = ofRandom(300, 400);
		ofPoint vertice;
		vertice.x = center.x + radius*cos(ofDegToRad(i * angleIncr));
		vertice.y = center.y + radius*sin(ofDegToRad(i * angleIncr));
		vertice.z = 0;
		vertices[j].push_back(vertice);
		currentvertices[j].push_back(vertice);
	}
	blobMask[j].allocate(ofGetWidth(), ofGetHeight());
	patternFbo[j].allocate(ofGetWidth(), ofGetHeight());
	blobFbo[j].allocate(ofGetWidth(), ofGetHeight());
}
void Intro::update()
{
	for (int j = 0; j < nBlobs; j++)
	{
		blob[j].clear();
		blob[j].setClosed(true);
		int nPoints1 = 10;// ofRandom(6, 10);
		int angleIncr = 360 / nPoints1;
		for (int i = 0; i < vertices[j].size(); i++)
		{
			//ofPoint vertice = currentvertices[j][i];
			//currentvertices[j][i] = vertice.interpolate(newvertices[j][i], 0.01);
			float complexity = 5;
			float timeSpeed = .01;
			float phase = TWO_PI - j*PI/3 - i*PI/12; // separate u-noise from v-noise
			int step = 10;
			float t = (ofGetFrameNum() + j * 20)  * timeSpeed /2;

			float radius = 300;
			float offradius = 50;
			float u = ofNoise(t + phase, 50 * complexity + phase, 50 * complexity + phase);
			float v = ofNoise(t - phase, 50 * complexity - phase, 50 * complexity + phase);

			ofPoint vertice;
			vertice.x = centers[j].x + (radius + u*offradius)*cos(ofDegToRad(i * angleIncr));
			vertice.y = centers[j].y + (radius + v*offradius)*sin(ofDegToRad(i * angleIncr));
			vertice.z = 0;
			vertices[j][i] = vertice;
			currentvertices[j][i] = vertice;
		}
		
		blob[j].curveTo(currentvertices[j][9]);
		for (int i = 0; i < nPoints1; i++)
		{
			blob[j].curveTo(currentvertices[j][i]);
		}
		blob[j].curveTo(currentvertices[j][0]);
		blob[j].curveTo(currentvertices[j][1]);	//blob1.close();
	}
}


void Intro::draw()
{
	blobs.begin();
	ofClear(255, 255, 255, 255);
	ofSetColor(12, 12, 12, 0);
	ofFill();
	blobs.end();

	for (int i = 0; i < nBlobs; i++)
	{
		patternFbo[i].begin();
		ofEnableAlphaBlending();
		ofSetColor(patternColor);
		patterns[i].draw(centers[i]);
		patternFbo[i].end();
	}
	

	for (int j = 0; j < nBlobs; j++)
	{
		blobMask[j].begin();
		ofClear(255, 255, 255, 255);
		ofSetColor(255, 255, 255, 0);
		ofBeginShape();

		for (int i = 0; i < blob[j].getVertices().size(); i++)
		{
			ofVertex(blob[j].getVertices().at(i).x, blob[j].getVertices().at(i).y);
			//ofSetColor(255, 0, 0);
			//ofCircle(blob[j].getVertices().at(i).x, blob[j].getVertices().at(i).y,5);
		}
		ofEndShape();
		blobMask[j].end();

	}

	//blob1.draw();

	for (int j = 0; j < nBlobs; j++)
	{
		ofDisableAlphaBlending();
		blobFbo[j].begin();
		ofClear(255, 255, 255, 255);
		patternFbo[j].draw(0, 0);
		ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
		blobMask[j].draw(0, 0);
		ofDisableBlendMode();
		blobFbo[j].end();
	}
	
	ofEnableAlphaBlending();
	ofBackground(12, 12, 12);
	for (int j = 0; j < nBlobs; j++)
	{
		blobFbo[j].draw(0, 0);
	}
}

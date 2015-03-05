#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxMtlMapping2D.h"
#include "ofxOsc.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofImage			lenna;
    ofImage			image[7000];
    int imgID, randID_1, randID_2,randID_3,randID_4;
    
	bool			bDrawLenna;
	bool			bShowHelp;

	ofFbo			myFbo;
	ofEasyCam		camera;

	//ofTexture		texture;

	/*Addon instance*/
	ofxPostGlitch	myGlitch;
    
    ofVideoPlayer 		video[3];
    
    int projection[3];

private:
        ofxMtlMapping2D* _mapping;
    ofxOscReceiver	receiver;
    int				current_msg_string;
    string			msg_strings[NUM_MSG_STRINGS];
    float			timers[NUM_MSG_STRINGS];
    string			mouseButtonState;
    
    
};

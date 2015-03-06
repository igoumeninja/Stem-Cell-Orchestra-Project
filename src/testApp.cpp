#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	camera.setDistance(400);
	ofSetCircleResolution(3);

    cout << "listening for osc messages on port " << 12345 << "\n";
    receiver.setup( 12345 );
    current_msg_string = 0;

    
	lenna.loadImage("lenna.png");
	bDrawLenna = false;
	bShowHelp  = true;
	myFbo.allocate(1024,768);

	myGlitch.setup(&myFbo);
    
    _mapping = new ofxMtlMapping2D();
    _mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
    
    
    video[0].loadMovie("video/video01.mp4");
    video[1].loadMovie("video/video02.mov");
    video[2].loadMovie("video/video03.mp4");

    for (int i=0; i<3; i++) {
        video[i].play();
        video[i].setVolume(0);
        projection[i]=i;
        cout << "video[" << i << "] total frames: " << video[i].getTotalNumFrames() << endl;
    }
    ofBackground(0);
}

//--------------------------------------------------------------
void testApp::update(){
    _mapping->update();
    ofBackground(0, 0, 0);
	for ( int i=0; i<NUM_MSG_STRINGS; i++ )
	{
		if ( timers[i] < ofGetElapsedTimef() )
			msg_strings[i] = "";
	}
    
	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		ofxOscMessage m;
		receiver.getNextMessage( &m );
        
		// map implementation

        if ( m.getAddress() == "projection" )	{   projection[m.getArgAsInt32(0)] = m.getArgAsInt32(1);    }
        if ( m.getAddress() == "videoPos" )     {   video[m.getArgAsInt32(0)].setFrame(m.getArgAsInt32(0)); }
        if ( m.getAddress() == "videoSpeed" )     {   video[m.getArgAsInt32(0)].setSpeed(m.getArgAsInt32(0)); }

		if ( m.getAddress() == "filter" )	{
            switch ( m.getArgAsInt32(0) ) {
                case 0:
                    myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
                    myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
                    myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
                    myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
                    myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
                    myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
                    break;

                case 1:
                    myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
                    break;
                case 2:
                    myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
                    break;
                case 3:
                    myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
                    break;
                case 4:
                    myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
                    break;
                case 5:
                    myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
                    break;
                case 6:
                    myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
                    break;
                default:
                    // Code
                    break;
            }        }
        
		if ( m.getAddress() == "img" )	{
			
			//cout << m.getNumArgs() << endl;
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GL_SRC_ALPHA_SATURATE,GL_ONE     GL_SRC_ALPHA, GL_ONE
			switch (m.getNumArgs())	{
				case 1:
					ofFill();
					ofSetColor(0xFFFFFF);
					//image[m.getArgAsInt32(0)].draw(m.getArgAsInt32(1), 0, 0, ofGetWidth(), ofGetHeight());
                    break;
				case 4:
					if (image[m.getArgAsInt32(0)].width/image[m.getArgAsInt32(0)].height > 1.25)	{
						
						//image[id].draw(x,y,width,height);
						
					}	else	{
					}
                    break;
				case 5:
					ofFill();
					ofSetHexColor(0xFFFFFF);
					image[m.getArgAsInt32(0)].draw(m.getArgAsInt32(1), m.getArgAsInt32(2),m.getArgAsInt32(3),m.getArgAsInt32(4));
                    ofSetColor(255, 0, 0);
                    ofRect(100, 200, 300, 340);
                    
                    cout << "ok" << endl;
                    break;
				case 8:
					ofNoFill();
					ofSetColor(0xFFFFFF);
					ofBeginShape();
					ofRotateX(m.getArgAsInt32(5));
					ofRotateY(m.getArgAsInt32(6));
					ofRotateZ(m.getArgAsInt32(7));
					image[m.getArgAsInt32(0)].draw(m.getArgAsInt32(1), m.getArgAsInt32(2),m.getArgAsInt32(3),m.getArgAsInt32(4));
					ofEndShape();
                    break;
				case 11:
					//cout << m.getNumArgs() << endl;
					ofNoFill();
					ofSetColor(0xFFFFFF);
					ofBeginShape();
					ofTranslate(m.getArgAsInt32(5),m.getArgAsInt32(6),m.getArgAsInt32(7));
					ofRotateX(m.getArgAsInt32(8));
					ofRotateY(m.getArgAsInt32(9));
					ofRotateZ(m.getArgAsInt32(10));
					image[m.getArgAsInt32(0)].draw(m.getArgAsInt32(1), m.getArgAsInt32(2),m.getArgAsInt32(3),m.getArgAsInt32(4));
					ofEndShape();
                    break;
				case 14:
					cout << m.getNumArgs() << endl;
					ofNoFill();
					ofSetColor(0xFFFFFF);
					ofBeginShape();
					ofTranslate(m.getArgAsInt32(5),m.getArgAsInt32(6),m.getArgAsInt32(7));
					ofScale(m.getArgAsInt32(8),m.getArgAsInt32(9),m.getArgAsInt32(10));
					ofRotateX(m.getArgAsInt32(11));
					ofRotateY(m.getArgAsInt32(12));
					ofRotateZ(m.getArgAsInt32(13));
					image[m.getArgAsInt32(0)].draw(m.getArgAsInt32(1), m.getArgAsInt32(2),m.getArgAsInt32(3),m.getArgAsInt32(4));
					ofEndShape();
                    break;
                    
			}
		}
		if ( m.getAddress() == "rect")	{
			ofFill();
			ofSetColor(0,0,0);
			ofRect(m.getArgAsInt32(0), m.getArgAsInt32(1), m.getArgAsInt32(2), m.getArgAsInt32(3));
		}
		if ( m.getAddress() == "loadImage" )	{
			image[m.getArgAsInt32(0)].loadImage(m.getArgAsString(1));
			printf("Load Image: %i \n", m.getArgAsInt32(0));
		}		
	}
  
    for (int i=0; i<3; i++) {
        video[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    _mapping->bind();
    myFbo.begin();
    myGlitch.generateFx();
    ofSetHexColor(0xFFFFFF);
    
    // Projection 1
    
    switch (projection[0]) {
        case 0:
            video[0].draw(40,20,200,200);
            break;
        case 1:
            video[1].draw(40,20,200,200);
            break;
        case 2:
            video[2].draw(40,20,200,200);
            break;
            
        default:
            break;
    }
    
    switch (projection[1]) {
        case 0:
            video[0].draw(260,20,200,200);
            break;
        case 1:
            video[1].draw(260,20,200,200);
            break;
        case 2:
            video[2].draw(260,20,200,200);
            break;
            
        default:
            break;
    }
    
    switch (projection[2]) {
        case 0:
            video[0].draw(480,20,200,200);
            break;
        case 1:
            video[1].draw(480,20,200,200);
            break;
        case 2:
            video[2].draw(480,20,200,200);
            break;
            
        default:
            break;
    }
    myFbo.end();

    myFbo.draw(0, 0);
    _mapping->unbind();
    _mapping->draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);

	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);

	if (key == 'l') bDrawLenna ^= true;
	if (key == 'h') bShowHelp ^= true;
    
	if(key == 'f' or key == 'F'){
		int previousWindowX, previousWindowY;
		
		if(ofGetWindowMode() == 0){
            
			ofSetFullscreen(true);
			ofBackground(0, 0, 0);
		}else{
			ofSetFullscreen(false);
			ofBackground(0, 0, 0);
		}  
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);

	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
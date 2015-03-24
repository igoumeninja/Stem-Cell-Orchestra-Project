/*
  Start edit with Emacs
  the project is hosted at https://github.com/igoumeninja/Stem-Cell-Orchestra-Project
  Aris Bezas
*/

#include <string>
//using namespace std;
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  //ofSetVerticalSync(true);
  ofSetFrameRate(30);
  camera.setDistance(400);
  ofSetCircleResolution(3);
  
  cout << "listening for osc messages on port " << 12345 << "\n";
  receiver.setup( 12345 );
  current_msg_string = 0;
  
  lenna.loadImage("lenna.png");
  bDrawLenna = false;
  bShowHelp  = true;
  myFbo.allocate(1440,900);
  
  myGlitch.setup(&myFbo);
  
  _mapping = new ofxMtlMapping2D();
  _mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
  string path = "video/video_GREYForPerformance/";
  ofDirectory dir(path);
  //only show png files
  dir.allowExt("mp4");
  //populate the directory object
  dir.listDir();
  //go through and print out all the paths
  for(int i = 0; i < dir.numFiles(); i++){
    ofLogNotice(dir.getPath(i));
    video[i].loadMovie(dir.getPath(i));
    video[i].setVolume(0);
    videoPlay[i] = false;
  }
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
        if ( m.getAddress() == "/test" ) cout << "Connection is working" << endl;
        if ( m.getAddress() == "/projection" )	{
          
        //if (m.getArgAsInt32(5) != 666) video[m.getArgAsInt32(5)].setLoopState(OF_LOOP_NONE);
        video[m.getArgAsInt32(5)].setLoopState(OF_LOOP_NONE);
        
        if(mainVideo != m.getArgAsInt32(5)) {
          mainVideoChanged = true;
          video[mainVideo].setLoopState(OF_LOOP_NORMAL);
          video[mainVideo].setPosition(0);
          mainVideo = m.getArgAsInt32(5);        
        }
        
        for (int i = 0; i < NUM_PROJECTION; i++) {
          videoProjection[i] = false;
          videoPrevious[i] = videoPlaying[i];
        }
        for (int i = 0; i < NUM_VIDEOS; i++) {
          videoPlay[i] = false;
        }
        
        for (int i = 0; i < NUM_PROJECTION; i++) {
          if(m.getArgAsInt32(i) != 666) {
            videoID[i] = m.getArgAsInt32(i);
            videoProjection[i] = true;
            //if (video[mainVideo].getIsMovieDone()) {videoProjection[5] = false; video[mainVideo].stop();}
            videoPlay[m.getArgAsInt32(i)] = true;
            
            //if((i != 5) & (m.getArgAsInt32(i) != mainVideo)) {
            if(m.getArgAsInt32(i) != mainVideo) {
              video[m.getArgAsInt32(i)].setPosition(0);
            }
            videoPlaying[i] = m.getArgAsInt32(i);
          }
        }
        
        for (int i = 0; i < NUM_PROJECTION; i++) {
          if(m.getArgAsInt32(i) != 666) {
            if(videoPrevious[i] != videoPlaying[i]) {
              video[videoPrevious[i]].stop();
            }
          }
        }
        // PRINT THE MESSAGE
          
        cout << "/projection" << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << " " << m.getArgAsInt32(2) << " " << m.getArgAsInt32(3) << " " << m.getArgAsInt32(4) << " " << m.getArgAsInt32(5) << " " << m.getArgAsInt32(6) << " " << m.getArgAsInt32(7) << " " << m.getArgAsInt32(8) << " " << m.getArgAsInt32(9) << " " << m.getArgAsInt32(10) << ")" << endl;
          
      } 
      
      
      if ( m.getAddress() == "state" )	{
        if(m.getArgAsString(0) == "main") {
          _mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
        } else {
          string tempVideoDir = "mapping/xml/state_" + m.getArgAsString(0) + ".xml";
          _mapping->init(ofGetWidth(), ofGetHeight(), tempVideoDir, "mapping/controls/mapping.xml");
        }
      }
      if ( m.getAddress() == "videoPos" )   {   video[m.getArgAsInt32(0)].setFrame(m.getArgAsInt32(0)); }
      if ( m.getAddress() == "/videoSec" )   { video[m.getArgAsInt32(0)].setFrame(m.getArgAsInt32(1)*24);}
      if ( m.getAddress() == "/videoSpeed" ) {   video[m.getArgAsInt32(0)].setSpeed(m.getArgAsInt32(1)); }
      // Send /filter, filterID, milliseconds
      
      if ( m.getAddress() == "/filter" )	    {
        endFilterTime = ofGetElapsedTimeMillis() + m.getArgAsInt32(1);
        //cout << ofGetElapsedTimeMillis() << endl;
        switch ( m.getArgAsInt32(0) ) {
        case 1: myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE,    true);break;
        case 2: myGlitch.setFx(OFXPOSTGLITCH_SHAKER,         true);break;
        case 3: myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER,         true);break;          
        case 4: myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST,true);break;
        case 5: myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE,   true);break;
        case 6: myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE,    true);break;
        default: break;
        }
      }
    }
  
  if(endFilterTime < ofGetElapsedTimeMillis()) {
    myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	 , false);
    myGlitch.setFx(OFXPOSTGLITCH_SHAKER		     , false);
    myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER	     , false);
    myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST , false);
    myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	 , false);
    myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	 , false);
  }
  
  for (int i = 0; i < NUM_VIDEOS; i++) {
    if (i != mainVideo) {
      if(videoPlay[i]) {
        video[i].update(); video[i].play();
      }
    } else {
      if (!video[mainVideo].getIsMovieDone()) {
        video[i].update(); video[i].play();
      }
    }
  }
  //if (mainVideo != 666)
  if (video[mainVideo].getIsMovieDone()) videoProjection[5] = false;
  
}

//--------------------------------------------------------------
void testApp::draw(){
  
  _mapping->bind();
  myFbo.begin();
  myGlitch.generateFx();
  ofBackground(0,0,0);
  ofSetHexColor(0xFFFFFF);
  
  if(videoProjection[0])  video[videoID[0]].draw(   50,   10, 640, 480);    
  if(videoProjection[1])  video[videoID[1]].draw(   50,  500, 256, 144);
  if(videoProjection[2])  video[videoID[2]].draw(   50,  650, 256, 144);
  if(videoProjection[3])  video[videoID[3]].draw(   310, 500, 256, 144);
  if(videoProjection[4])  video[videoID[4]].draw(   310, 650, 256, 144);
  if(videoProjection[5])  video[videoID[5]].draw(   580, 500, 256, 144);
  if(videoProjection[6])  video[videoID[6]].draw(   580, 650, 256, 144);
  if(videoProjection[7])  video[videoID[7]].draw(   850,  50, 256, 144);
  if(videoProjection[8])  video[videoID[8]].draw(   850, 200, 256, 144);
  if(videoProjection[9])  video[videoID[9]].draw(   850, 350, 256, 144);
  if(videoProjection[10]) video[videoID[10]].draw(  850, 500, 256, 144);
  myFbo.end();
  
  myFbo.draw(0, 0);
  _mapping->unbind();
  _mapping->draw();
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
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

void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y ){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){ }

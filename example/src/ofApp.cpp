#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Usage 1
    // No parametors, if you wanna default settings
    
    ofxFpsAutoReducer::setup();
    
    // Usage 2
    // Setup with parametors
    /*
    bool withDefaultSettings = false;
    ofxFpsAutoReducer::setup(withDefaultSettings);
    ofxFpsAutoReducer::setNormalFps(30);
    
     // power saving (wait -> low fps) setting
     // SleepSetting(<time>, <frameRate>)
     ofxFpsAutoReducer::addSleepSetting(ofxFpsAutoReducer::SleepSetting(1., 10));
     ofxFpsAutoReducer::addSleepSetting(ofxFpsAutoReducer::SleepSetting(5., 5));
     ofxFpsAutoReducer::addSleepSetting(ofxFpsAutoReducer::SleepSetting(60., 2));
    */
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Show current fps
    ofDrawBitmapString("FPS: " + ofToString(ofGetTargetFrameRate()), 50, 50);
    
    // Circle follows your cursor.
    // It move smooth, because FPS get highest when mouse moving.
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 100);
}

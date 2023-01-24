#pragma once

#include "ofMain.h"
#include "ofxFpsAutoReducer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    float fps, pastUpdate;
};

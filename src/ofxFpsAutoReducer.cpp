#include "ofxFpsAutoReducer.h"

ofxFpsAutoReducer *ofxFpsAutoReducer::singleton = nullptr;

ofxFpsAutoReducer::ofxFpsAutoReducer() {
    
}

void ofxFpsAutoReducer::setup(bool withDefaultSettings) {
    if (singleton == nullptr) {
        singleton = new ofxFpsAutoReducer();
    }
    
    // resistor event
    ofAddListener(ofEvents().update, singleton, &ofxFpsAutoReducer::m_update, OF_EVENT_ORDER_AFTER_APP);
    ofAddListener(ofEvents().keyPressed, singleton, &ofxFpsAutoReducer::m_keyEvent);
    ofAddListener(ofEvents().keyReleased, singleton, &ofxFpsAutoReducer::m_keyEvent);
    ofAddListener(ofEvents().mouseMoved, singleton, &ofxFpsAutoReducer::m_mouseEvent);
    ofAddListener(ofEvents().mousePressed, singleton, &ofxFpsAutoReducer::m_mouseEvent);
    ofAddListener(ofEvents().mouseDragged, singleton, &ofxFpsAutoReducer::m_mouseEvent);
    ofAddListener(ofEvents().mouseReleased, singleton, &ofxFpsAutoReducer::m_mouseEvent);
    ofAddListener(ofEvents().mouseScrolled, singleton, &ofxFpsAutoReducer::m_mouseEvent);

    if (withDefaultSettings) {
        setNormalFps(60);
        
        // power saving (wait -> low fps) setting
        addSleepSetting(SleepSetting(1., 30));
        addSleepSetting(SleepSetting(5., 10));
        addSleepSetting(SleepSetting(60., 5));
        addSleepSetting(SleepSetting(300., 2));
        wakeup();
    }
}

void ofxFpsAutoReducer::m_update(ofEventArgs &args) {
    if (sleepSettings.empty()) return;
    
    float elapsed = ofGetElapsedTimef() - lastCursorMoveTime;

    auto s = sleepSettings.end() - 1;
    while(true) {
        if (s->time < elapsed) {
            if (ofGetFrameRate() > s->fps) {
                ofSetFrameRate(s->fps);
            }
            break;
        }
        if (s == sleepSettings.begin()) break;
        else s--;
    }
}

void ofxFpsAutoReducer::m_keyEvent(ofKeyEventArgs &key) {
    wakeup();
}

void ofxFpsAutoReducer::m_mouseEvent(ofMouseEventArgs &mouse) {
    wakeup();
}

void ofxFpsAutoReducer::setNormalFps(int fps) {
    if (!singleton) setup();
    singleton->normalFps = fps;
}

int ofxFpsAutoReducer::getNormalFps() {
    if (!singleton) setup();
    return singleton->normalFps;
}

void ofxFpsAutoReducer::addSleepSetting(const float time, const float fps) {
    SleepSetting(time, fps);
}

void ofxFpsAutoReducer::addSleepSetting(const SleepSetting &s) {
    if (!singleton) setup(false);
    
    singleton->sleepSettings.push_back(s);

    // sort
    sort(singleton->sleepSettings.begin(), singleton->sleepSettings.end());
}

void ofxFpsAutoReducer::clearSleepSettings() {
    if (singleton) {
        singleton->sleepSettings.clear();
    }
}

vector<ofxFpsAutoReducer::SleepSetting> ofxFpsAutoReducer::getSleepSettings() {
    if (!singleton) setup(false);
    return singleton->sleepSettings;
}

void ofxFpsAutoReducer::wakeup() {
    if (!singleton) setup();
    singleton->lastCursorMoveTime = ofGetElapsedTimef();
    ofSetFrameRate(singleton->normalFps);
}

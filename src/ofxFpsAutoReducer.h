#include "ofMain.h"

class ofxFpsAutoReducer {
public:
    // power saving
    struct SleepSetting {
        SleepSetting(float time, int fps):time(time),fps(fps){}
        float time;
        int fps;
        
        bool operator<( const SleepSetting& right ) const {
            return time < right.time;
        }
    };
    
private:
    ofxFpsAutoReducer();
    
    // update on ofEvent update;
    void m_setup();
    void m_update(ofEventArgs &args);
    void m_keyEvent(ofKeyEventArgs &key);
    void m_mouseEvent(ofMouseEventArgs &mouse);

    vector<SleepSetting> sleepSettings;
    float lastCursorMoveTime;
    int normalFps;
    static ofxFpsAutoReducer *singleton;
    
public:
    static void setup(bool withDefaultSettings = true);
    static void setNormalFps(int fps);
    static int getNormalFps();
    static void addSleepSetting(const SleepSetting &s);
    static void clearSleepSettings();
    static vector<SleepSetting> getSleepSettings();
    static void wakeup();
};

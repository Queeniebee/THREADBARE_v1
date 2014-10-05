#pragma once

#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL

#define NUM_CLIPS 12

#include "ofMain.h"
#include <GLFW/glfw3.h>
#include "GLFW/glfw3native.h"
#include "ofQTKitPlayer.h"
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"
#include "threadSerial.h"

//#include "ofxSyphon.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void conversionToInt(char* fromSerial);
    int sensors(int *reads);
    
    int sensorReadings[NUM_BYTES];

    ofSoundPlayer videoSound;
    string paths[NUM_CLIPS];

    ofQTKitPlayer *clipsPointer;
    ofQTKitDecodeMode decodeMode;
    ofQTKitPlayer videos[NUM_CLIPS];
    
    ofFbo fbo, maskFbo;
    threadSerial mSerial;
    
    int firstSensor, secondSensor;

    bool getSerialMessage;
    int countCycles;
    int selectVideo(int sensorValue);
    int prevSensorReading = 0;
    
//    ofxSyphonServer mainOutputSyphonServer;
//	ofxSyphonServer individualTextureSyphonServer;


};
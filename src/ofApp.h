#pragma once

#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL

#define NUM_AVG 5

#include "ofMain.h"
#include <GLFW/glfw3.h>
#include "GLFW/glfw3native.h"

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
    
    float averageSensors(int sensorValue1, int sensorValue2);
    float triggerFunction(int sensorValue1, int sensorValue2);
    
    ofShader shader;
    ofVideoPlayer video;
    ofFbo fbo, maskFbo;
    
    ofSerial serial;
    int firstSensor[NUM_AVG], secondSensor[NUM_AVG];
};
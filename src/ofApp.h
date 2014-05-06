#pragma once

#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL

#define NUM_AVG 5

#include "ofMain.h"
#include <GLFW/glfw3.h>
#include "GLFW/glfw3native.h"
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"

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
    
    //Splitting up the averageSensor function into 2 because not enough
    // time to configure a struct or return a pair
    int averageSensor1(int sensorValue[]);
    int averageSensor2(int sensorValue2[]);
    void onNewMessage(string & message);
    float triggerFunction(int sensorValue1, int sensorValue2);
    
    ofShader shader;
    ofVideoPlayer video[NUM_AVG];
    ofSoundPlayer videoSound;
    string paths[NUM_AVG];

    ofFbo fbo, maskFbo;
    
    ofSerial serial;
    string message;
    
    int stringToInt(const string &Text);
    int firstSensor, secondSensor;
    int somevalue, somevalue2;
    float shaderValue;


};
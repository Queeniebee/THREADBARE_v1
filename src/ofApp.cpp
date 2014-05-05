#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
		shader.load("shader.vert", "shader.frag");
    
        serial.enumerateDevices();
        serial.setup(0,9600);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int bytesRequired = 5;
    unsigned char bytesReturned[bytesRequired];
    int bytesRemaining = bytesRequired;
    int Result = 0;
    
//    if(serial.available() > 0){
//        serial.readBytes(&bytesReturned[bytesPreventOverwrite], bytesRemaining);            
//        if(bytesReturned[0] == '1'){
//            firstSensor = bytesReturned[1];
//            cout<<"FirstSensor: "<<firstSensor<<endl;
//        }
//        if(bytesReturned[2] == '2'){
//            secondSensor = bytesReturned[3];
//            cout<<"SecondSensor: "<<secondSensor<<endl;
//            }
//        serial.flush();
//        serial.writeByte('A');
//        
//    }
    while(bytesRemaining > 0){
        if(serial.available() > 0){
            int bytesPreventOverwrite = bytesRequired - bytesRemaining;
            Result = serial.readBytes(&bytesReturned[bytesPreventOverwrite], bytesRemaining);
            
            if(bytesReturned[Result] == '1'){
            firstSensor = bytesReturned[Result-1];
            cout<<"FirstSensor: "<<firstSensor<<endl;
        }
        if(bytesReturned[Result] == '2'){
            secondSensor = bytesReturned[Result-1];
            cout<<"SecondSensor: "<<secondSensor<<endl;
        }
        bytesRemaining -= Result;
        serial.flush();
        serial.writeByte('A');
        }
    }
}
//--------------------------------------------------------------
void ofApp::draw(){

    float time = 0.0;
    if(ofGetElapsedTimef() >= 30.0){
        
        time = fmod(ofGetElapsedTimef(), 30)*0.079;
//        cout<<"TIME2:  "<<time<<endl;
        
    } else{
    
    time = ofGetElapsedTimef()*0.079;
    
    }
    float change = 0.076+10.0;
    float percent = fmod(time,change);
    ofSetColor(255);
    
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform1f("percent", percent);

    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'D'){
        
        ofToggleFullscreen();
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
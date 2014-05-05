#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    shader.load("shader.vert", "shader.frag");
    video.loadMovie("test_video/Resources/test_video.mov");
    video.play();
    
//    int width = video.getWidth();
//    int height = video.getHeight();
    
    maskFbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    
    maskFbo.begin();
    ofClear(0,0,0,255);
    maskFbo.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

    serial.enumerateDevices();
    serial.setup(0,9600);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int bytesRequired = 5;
    unsigned char bytesReturned[bytesRequired];
    int bytesRemaining = bytesRequired;
    int Result = 0;
    
    // This is a good serial read formula
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
    
    video.update();
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    
//    ofSetColor(255);
    
    float secondSensor2;
    float time = 0.0;
    
    if(ofGetElapsedTimef() >= 30.0){
        
        time = fmod(ofGetElapsedTimef(), 30)*0.079;
//        cout<<"TIME2:  "<<time<<endl;
        
    } else{
    
    time = ofGetElapsedTimef()*0.079;
    
    }
    float change = 0.076+10.0;
    float percent = fmod(time,change);
    

    //This fbo is in draw because the "mask" is the shader of lerped colors
    //It is in this fbo where we will use the values from ofSerial
    if(((secondSensor >= 0) && (secondSensor < 100)) || ((firstSensor >= 0) && (firstSensor < 10))){
        secondSensor2 = 0.5;
    } else{
    
        secondSensor2 = 0.3;
    
    }
    maskFbo.begin();
    shader.begin();
    shader.setUniform1f("percent", percent);
    shader.setUniform1f("alpha", secondSensor2);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    shader.end();
    maskFbo.end();
    
    fbo.begin();
//    ofClear(0, 0, 0, 0);
//    shader.begin();
//    shader.setUniformTexture("maskTex", maskFbo.getTextureReference(), 1 );
//    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    video.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
//    shader.end();
    fbo.end();
    
    fbo.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    maskFbo.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());

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
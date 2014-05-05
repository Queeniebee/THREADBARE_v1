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
    cout<<"firstSensor before: "<<firstSensor[0]<<endl;
    for(int i = 0; i < NUM_AVG; i++){
    firstSensor[i] = 0;
    secondSensor[i] = 0;
    }
    // This is a good serial read formula
    while(bytesRemaining > 0){
        if(serial.available() > 0){
            int bytesPreventOverwrite = bytesRequired - bytesRemaining;
            Result = serial.readBytes(&bytesReturned[bytesPreventOverwrite], bytesRemaining);
                if(bytesReturned[Result] == '1'){
                    firstSensor[0] = bytesReturned[Result-1];
                    firstSensor[1] = bytesReturned[Result-1];
                    firstSensor[2] = bytesReturned[Result-1];
                    firstSensor[3] = bytesReturned[Result-1];
                    firstSensor[4] = bytesReturned[Result-1];

                    cout<<"firstSensor after1: "<<firstSensor[0]<<endl;
                
                }
                if(bytesReturned[Result] == '2'){
                    secondSensor[0] = bytesReturned[Result-1];
                    secondSensor[1] = bytesReturned[Result-1];
                    secondSensor[2] = bytesReturned[Result-1];
                    secondSensor[3] = bytesReturned[Result-1];
                    secondSensor[4] = bytesReturned[Result-1];

                    cout<<"secondSensor after1: "<<secondSensor[0]<<endl;

            }
            bytesRemaining -= Result;
            serial.flush();
            serial.writeByte('A');
    
        }
        }

    video.update();
    //    int somevalue, somevalue2;
    somevalue = averageSensor1(firstSensor);
    cout<<"firstSensor after2: "<<somevalue<<endl;
    
    somevalue2 = averageSensor2(secondSensor);
    cout<<"SecondSensor after2: "<<somevalue2<<endl;
    
    
}
//--------------------------------------------------------------
void ofApp::draw(){
/*    float time = 0.0;
    if(ofGetElapsedTimef() >= 30.0){
        
        time = fmod(ofGetElapsedTimef(), 30)*0.079;
        cout<<"TIME2:  "<<time<<endl;
        
    } else{
    
    time = ofGetElapsedTimef()*0.079;
    
    }
    float change = 0.076+10.0;
    float percent = fmod(time,change); */


//    firstSensor = averageSensor1(firstSensor);
//    secondSensor = averageSensor2(secondSensor);
    

    float shaderValue;
    shaderValue = triggerFunction(somevalue, somevalue2);
    cout<<"sensorValue: "<<shaderValue<<endl;


    //This fbo is in draw because the "mask" is the shader of lerped colors
    //It is in this fbo where we will use the values from ofSerial

    maskFbo.begin();
    shader.begin();
//    shader.setUniform1f("percent", percent);
    shader.setUniform1f("alpha", shaderValue);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    shader.end();
    maskFbo.end();
    
    fbo.begin();
    ofClear(0, 0, 0, 0);
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
int ofApp::averageSensor1(int sensorValue1[]){
    int returnValue = 0;
    for(int i = 0; i < NUM_AVG; i++){
        returnValue += sensorValue1[i];
    }
    return returnValue / NUM_AVG;
}
//--------------------------------------------------------------
int ofApp::averageSensor2(int sensorValue2[]){
    int returnValue = 0;
    for(int i = 0; i < NUM_AVG; i++){
        returnValue += sensorValue2[i];
    } 
        return returnValue / NUM_AVG;
}
//--------------------------------------------------------------
float ofApp::triggerFunction(int sensorValue, int sensorValue2){

    float alphaValue = 0.0;
    
    if(((sensorValue >= 0) && (sensorValue < 10)) || ((sensorValue2 >= 0) && (sensorValue2 < 10))){
        //The closer the person is, the clearer the picture
        alphaValue = 0.0;
        return alphaValue;

        
        //Will add change between video clips
    } else if (((sensorValue >= 10) && (sensorValue < 64)) || ((sensorValue2 >= 10) && (sensorValue2 < 25))){
        
        sensorValue2 = 0.1;
        return alphaValue;


    } else if (((sensorValue >= 64) && (sensorValue < 128)) || ((sensorValue2 >= 64) && (sensorValue2 < 128))){
        alphaValue = 0.25;
        return alphaValue;


    
    } else if (((sensorValue >= 128) && (sensorValue < 192)) || ((sensorValue2 >= 128) && (sensorValue2 < 192))){
        alphaValue = 0.3;
        return alphaValue;


        
    } else if (((sensorValue >= 192) && (sensorValue < 256)) || ((sensorValue2 >= 192) && (sensorValue2 < 256))){
        alphaValue = 0.4;
        return alphaValue;

    } else{
        
        alphaValue = 0.9;
        return alphaValue;

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
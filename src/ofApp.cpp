#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    shader.load("shader.vert", "shader.frag");
//    video.loadMovie("test_video/Resources/test_video.mov");
//    video.play();
    
    paths[0] = "THREABARE_v2/Resources/THREABARE_v2.mov";
    paths[1] = "THREADBARE_v3/Resources/THREADBARE_v3.mov";
    paths[2] = "THREADBARE_v42/Resources/THREADBARE_v42.mov";
    paths[3] = "THREADBARE_v52/Resources/THREADBARE_v52.mov";
    paths[4] = "THREADBARE_v6/Resources/THREADBARE_v6.mov";
    
    for(int i = 0; i < NUM_AVG; i++){
        video[i].loadMovie(paths[i]);
        video[i].play();
    }
  /*
    video[0].loadMovie(paths[0]);
    video[1].loadMovie(paths[1]);
    video[2].loadMovie(paths[2]);
    video[3].loadMovie(paths[3]);
    video[4].loadMovie(paths[4]);
    
    video[0].play();
    video[1].play();
    video[2].play();
    video[3].play();
    video[4].play();
*/
    
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
//    serial.setup("/dev/tty.usbmodemfa131",9600);
//    serial.startContinuousRead(true);

}

//--------------------------------------------------------------
void ofApp::update(){
   /* {
    ofAddListener(serial.NEW_MESSAGE,this,&ofApp::onNewMessage);
	message = "";    
    cout << "sendRequest\n";
    serial.sendRequest();}*/
    shaderValue = 0;

    int bytesRequired = 5;
    unsigned char bytesReturned[bytesRequired];
    int bytesRemaining = bytesRequired;
    int bytesPreventOverwrite = bytesRequired - bytesRemaining;
    int Result = 0;
    cout<<"firstSensor before: "<<firstSensor<<endl;

        if(serial.available() > 0){
            serial.readBytes(&bytesReturned[bytesPreventOverwrite], bytesRemaining);
            if(bytesReturned[4] == 'z'){
                if(bytesReturned[0] == '1'){
                    firstSensor = bytesReturned[1];
                    cout<<"firstSensor after1: "<<firstSensor<<endl;
                
                }
                if(bytesReturned[2] == '2'){
                    secondSensor = bytesReturned[3];
                    cout<<"secondSensor after1: "<<secondSensor<<endl;

            }
            }
            
//            bytesRemaining -= Result;
            serial.flush();
            serial.writeByte('A');
        }

    for (int i = 0; i < NUM_AVG; i++) {
		video[i].update();
	}
    cout<<"FirstSensor: "<<firstSensor<<endl;
    cout<<"SecondSensor: "<<secondSensor<<endl;
    shaderValue = triggerFunction(firstSensor, secondSensor);
    cout<<"shaderValue: "<<shaderValue<<endl;
    
//    maskFbo.begin();
//    shader.begin();
//    //    shader.setUniform1f("percent", percent);
//    shader.setUniform1f("alpha", shaderValue);
//    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//    
//    shader.end();
//    maskFbo.end();

}
//--------------------------------------------------------------
void ofApp::onNewMessage(string &message){
    
//    vector<string> input = ofSplitString(message, ",");
//    string firstOne, secondOne;
//	if(input.size() >= 3)
//	{
//        firstOne = input.at(0).c_str();
//        secondOne = input.at(2).c_str();
//	}
//    
//    firstSensor = stringToInt(firstOne);
//    secondSensor = stringToInt(secondOne);

    
}
//--------------------------------------------------------------
int ofApp::stringToInt(const string &Text){
    
    stringstream convert(Text);
    int result;
    return convert >> result ? result : 0;

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
    
//    cout<<"FirstSensor: "<<firstSensor<<endl;
//    cout<<"SecondSensor: "<<secondSensor<<endl;
//    float shaderValue;
//    shaderValue = triggerFunction(firstSensor, secondSensor);
//    cout<<"sensorValue: "<<shaderValue<<endl;


    //This fbo is in draw because the "mask" is the shader of lerped colors
    //It is in this fbo where we will use the values from ofSerial
    maskFbo.begin();
    ofClear(0, 0, 0, 0);
    shader.begin();
//    shader.setUniform1f("percent", percent);
    shader.setUniform1f("alpha", shaderValue);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    shader.end();
    maskFbo.end();

//    fbo.begin();
//    ofClear(0, 0, 0, 0);
    int oldShaderValue = 0;
    int cue = 0;
  /*  if (shaderValue == 0.35) {
        cue = 0;
        fbo.begin();
        ofClear(0, 0, 0, 0);
        video[0].draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
        fbo.end();
        cout<<"cue: "<<cue<<endl;
    } else if (shaderValue == 0.7){
        cue = 1;
        fbo.begin();
        ofClear(0, 0, 0, 0);
        video[1].draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
        fbo.end();
        cout<<"cue: "<<cue<<endl;

    } else if (shaderValue == 0.85){
        cue = 2;
        fbo.begin();
        ofClear(0, 0, 0, 0);
        video[2].draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
        fbo.end();
        cout<<"cue: "<<cue<<endl;

    } else if (shaderValue == 1.0){
        cue = 3;
        fbo.begin();
        ofClear(0, 0, 0, 0);
        video[3].draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
        fbo.end();
        cout<<"cue: "<<cue<<endl;

    } else {
        cue = 4;
        fbo.begin();
        ofClear(0, 0, 0, 0);
        video[4].draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
        fbo.end();
        cout<<"cue: "<<cue<<endl;

        
    } */
    if(oldShaderValue != shaderValue){
        oldShaderValue = shaderValue;

    if (oldShaderValue == 0.35) {
     cue = 0;
     cout<<"cue: "<<cue<<endl;
     } else if (oldShaderValue == 0.7){
     cue = 1;
     cout<<"cue: "<<cue<<endl;
     
     } else if (oldShaderValue == 0.85){
     cue = 2;
     cout<<"cue: "<<cue<<endl;
     
     } else if (oldShaderValue == 1.0){
     cue = 3;
     cout<<"cue: "<<cue<<endl;
     
     } else {
     cue = 4;
     cout<<"cue: "<<cue<<endl;
     }
    }
    fbo.begin();
    ofClear(0, 0, 0, 0);
    video[cue].draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    fbo.end();
    
//    video[cue].draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
//    fbo.end();
//    cout<<"cue: "<<cue<<endl;
    
    fbo.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    maskFbo.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());

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

    float alphaValue = 1.0;

    if(((sensorValue >= 1) && (sensorValue < 10)) || ((sensorValue2 >= 0) && (sensorValue2 < 10))){
        //The closer the person is, the clearer the picture
        alphaValue = 0.0;
        return alphaValue;

        
        //Will add change between video clips
    } else if (((sensorValue >= 10) && (sensorValue < 64)) || ((sensorValue2 >= 10) && (sensorValue2 < 25))){
        
        alphaValue = 0.35;
        return alphaValue;


    } else if (((sensorValue >= 64) && (sensorValue < 128)) || ((sensorValue2 >= 64) && (sensorValue2 < 128))){
        alphaValue = 0.70;
        return alphaValue;


    
    } else if (((sensorValue >= 128) && (sensorValue < 192)) || ((sensorValue2 >= 128) && (sensorValue2 < 192))){
        alphaValue = 0.85;
        return alphaValue;


        
    } else if (((sensorValue >= 192) && (sensorValue < 256)) || ((sensorValue2 >= 192) && (sensorValue2 < 256))){
        alphaValue = 1.0;
        return alphaValue;

    } else{
        
//        alphaValue = 1.0;
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
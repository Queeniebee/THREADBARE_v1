#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    paths[0] = "THREADBARE_hair/Resources/THREADBARE_hair.mov";
    paths[1] = "THREADBARE_shoes4/Resources/THREADBARE_shoes4.mov";
    paths[2] = "THREADBARE_replacev52/Resources/THREADBARE_replacev52.mov";
    paths[3] = "THREADBARE_shoes3/Resources/THREADBARE_shoes3.mov";
    paths[4] = "THREADBARE_v9_c/Resources/THREADBARE_v9_c.mov"; 
    paths[5] = "THREADBARE_shoes1/Resources/THREADBARE_shoes1.mov";
    paths[6] = "THREADBARE_v6/Resources/THREADBARE_v6.mov";
    paths[7] = "THREADBARE_v7/Resources/THREADBARE_v7.mov"; 
    paths[8] = "THREADBARE_v6/Resources/THREADBARE_v6.mov"; 
    paths[9] = "THREADBARE_v42/Resources/THREADBARE_v42.mov"; 
    paths[10] = "THREABARE_v2/Resources/THREABARE_v2.mov";
    paths[11] = "THREADBARE_curtain/Resources/THREADBARE_curtain.mov";
    

    clipsPointer =  &videos[0];
    clipsPointer->setPixelFormat(OF_PIXELS_RGBA);
    
    decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
    for(int i = 0; i< sizeof(videos)/sizeof(ofQTKitPlayer); i++){
        videos[i].loadMovie(paths[i], decodeMode);
    }
    clipsPointer->setVolume(0.0);
    clipsPointer->play();

//    videoSound.loadSound("Threadbare_voiceover.mp3");
//    videoSound.setVolume(0.8f);
//    videoSound.play();
    
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

    serial.enumerateDevices();
    serial.setup(0,9600);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i = 0; i<sizeof(videos)/sizeof(ofQTKitPlayer); i++){
        videos[i].update();
    }
    clipsPointer->update();


    int bytesRequired = 5;
    unsigned char bytesReturned[bytesRequired];
    int bytesRemaining = bytesRequired;
    int bytesPreventOverwrite = bytesRequired - bytesRemaining;
    int Result = 0;

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
            serial.flush();
            serial.writeByte('A');
        }
    if(fmodf(ofGetElapsedTimef(), 60.0) >= 0 && fmodf(ofGetElapsedTimef(), 60.0) <= 1){

        shaderValue = triggerFunction(firstSensor, secondSensor);
    }


}
//--------------------------------------------------------------
void ofApp::onNewMessage(string &message){

    
}
//--------------------------------------------------------------
int ofApp::stringToInt(const string &Text){

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
    
//    cout<<"FirstSensor: "<<firstSensor<<endl;
//    cout<<"SecondSensor: "<<secondSensor<<endl;
//    float shaderValue;
//    shaderValue = triggerFunction(firstSensor, secondSensor);
//    cout<<"sensorValue: "<<shaderValue<<endl;


    //This fbo is in draw because the "mask" is the shader of lerped colors
    //It is in this fbo where we will use the values from ofSerial
//    maskFbo.begin();
//    ofClear(0, 0, 0, 0);
//    shader.begin();
////    shader2.setUniform1f("percent", percent);
//    shader.setUniform1f("alpha", shaderValue);
//    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
//
//    shader.end();
//    maskFbo.end();

    
    if(oldShaderValue != shaderValue){
        cout<<"This Check Happened: "<<shaderValue<<endl;
        cout<<"oldShaderValue before set: "<<oldShaderValue<<endl;
        oldShaderValue = shaderValue;
        cout<<"oldShaderValue after set: "<<oldShaderValue<<endl;
        if (oldShaderValue == 0.08){
            cue = 1;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[1];
            //            clipsPointer->loadMovie(paths[1], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.16){
            cue = 2;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[2];
            //            clipsPointer->loadMovie(paths[2], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.24){
            cue = 3;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[3];
            //            clipsPointer->loadMovie(paths[3], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.32){
            cue = 4;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[4];
            //            clipsPointer->loadMovie(paths[4], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.40){
            cue = 5;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[5];
            //            clipsPointer->loadMovie(paths[5], decodeMode);
            cout<<"oldShaderValue: "<<oldShaderValue<<endl;
            
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if(oldShaderValue == 0.48){
            cue = 6;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[6];
            //            clipsPointer->loadMovie(paths[6], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.56){
            cue = 7;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[7];
            //            clipsPointer->loadMovie(paths[7], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.64){
            cue = 8;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[8];
            //            clipsPointer->loadMovie(paths[8], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.72){
            cue = 9;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[9];
            //            clipsPointer->loadMovie(paths[9], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 0.8){
            cue = 10;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[10];
            //            clipsPointer->loadMovie(paths[10], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
        } else if (oldShaderValue == 1.0){
            cue = 11;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[11];
            //            clipsPointer->loadMovie(paths[11], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
            cout<<"cue: "<<cue<<endl;
        } else if (oldShaderValue == 0.0){
            cue = 0;
            clipsPointer->stop();
//            clipsPointer->close();
            clipsPointer = &videos[cue];
            //            clipsPointer->loadMovie(paths[0], decodeMode);
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
        }else{
            cout<<"shadervalue is the same: "<<oldShaderValue<<endl;
        }
    }
    
    fbo.begin();
    ofClear(0, 0, 0, 0);
    clipsPointer->draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    fbo.end();
    
    fbo.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
//    maskFbo.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'D'){
        
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
int ofApp::averageSensor1(int sensorValue1[]){

}
//--------------------------------------------------------------
int ofApp::averageSensor2(int sensorValue2[]){
}
//--------------------------------------------------------------
float ofApp::triggerFunction(int sensorValue, int sensorValue2){
// WILL REPLACE THESE IF STATEMENTS WITH MODULO
    
    float alphaValue = 1.0;

    if(((sensorValue >= 1) && (sensorValue < 20)) || ((sensorValue2 >= 1) && (sensorValue2 < 20))){
        alphaValue = 0.0;
        return alphaValue;

    } else if (((sensorValue >= 20) && (sensorValue < 36)) || ((sensorValue2 >= 20) && (sensorValue2 < 36))){
        alphaValue = 0.08;
        return alphaValue;

    } else if (((sensorValue >= 36) && (sensorValue < 52)) || ((sensorValue2 >= 36) && (sensorValue2 < 52))){
        alphaValue = 0.16;
        return alphaValue;

    } else if (((sensorValue >= 52) && (sensorValue < 68)) || ((sensorValue2 >= 52) && (sensorValue2 < 68))){
        alphaValue = 0.24;
        return alphaValue;
        
    } else if (((sensorValue >= 68) && (sensorValue < 84)) || ((sensorValue2 >= 68) && (sensorValue2 < 84))){
        alphaValue = 0.32;
        return alphaValue;
        
    } else if (((sensorValue >= 84) && (sensorValue < 100)) || ((sensorValue2 >= 84) && (sensorValue2 < 100))){
        alphaValue = 0.4;
        return alphaValue;
        
    } else if (((sensorValue >= 100) && (sensorValue < 116)) || ((sensorValue2 >= 100) && (sensorValue2 < 116))){
        alphaValue = 0.48;
        return alphaValue;
        
    } else if (((sensorValue >= 116) && (sensorValue < 142)) || ((sensorValue2 >= 116) && (sensorValue2 < 142))){
        alphaValue = 0.56;
        return alphaValue;
        
    } else if (((sensorValue >= 142) && (sensorValue < 168)) || ((sensorValue2 >= 142) && (sensorValue2 < 168))){
        alphaValue = 0.64;
        return alphaValue;
        
    } else if (((sensorValue >= 168) && (sensorValue < 182)) || ((sensorValue2 >= 168) && (sensorValue2 < 182))){
        alphaValue = 0.72;
        return alphaValue;
        
    } else if (((sensorValue >= 182) && (sensorValue < 228)) || ((sensorValue2 >= 182) && (sensorValue2 < 228))){
        alphaValue = 0.8;
        return alphaValue;
        
    } else if (((sensorValue >= 228) && (sensorValue < 246)) || ((sensorValue2 >= 228) && (sensorValue2 < 246))){
        alphaValue = 1.0;
        return alphaValue;
    } else{
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
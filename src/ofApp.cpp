#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    getSerialMessage = false;

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

    clipsPointer = &videos[0];
    clipsPointer->setPixelFormat(OF_PIXELS_RGBA);

    decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
 /*   for(int i = 0; i< NUM_CLIPS; i++){
        videos[i].setPixelFormat(OF_PIXELS_RGBA);
        videos[i].loadMovie(paths[i], decodeMode);
        videos[i].setVolume(0.0f);
        videos[i].play();
    } */
    
    for(int i = 0; i< sizeof(videos)/sizeof(ofQTKitPlayer); i++){
        videos[i].loadMovie(paths[i], decodeMode);
    }
    clipsPointer->setVolume(0.0f);
    clipsPointer->play();
    
    videoSound.loadSound("Threadbare_voiceover.mp3");
    videoSound.setVolume(1.0f);
    videoSound.setLoop(true);
    videoSound.play();
    
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

    serial.enumerateDevices();
    serial.setup(0,9600);

    mainOutputSyphonServer.setName("Screen Output");

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
 /*   int bytesRequired = 5;
    uint8_t bytesReturned[bytesRequired];
    int bytesRemaining = bytesRequired;
    int bytesPreventOverwrite = bytesRequired - bytesRemaining;
    int Result = 0;
    
    memset(bytesReturned, 0, bytesRequired * sizeof(uint8_t));
    
        if(serial.available() > 0){
            
            serial.readBytes( bytesReturned, bytesRemaining );
            if(bytesReturned[4] == 'z'){
                if(bytesReturned[0] == '1'){
                    firstSensor = bytesReturned[1];
                    cout<<"firstSensor after1: "<< firstSensor <<endl;
                
                }
                if(bytesReturned[2] == '2'){
                    secondSensor = bytesReturned[3];
                    cout<<"secondSensor after1: "<<secondSensor<<endl;

            }
            }
            serial.flush();
            serial.writeByte('A');
        }*/

    
    int bytesRequired = 5;
    uint8_t bytesReturned[bytesRequired];
    int bytesRemaining = bytesRequired;
    int bytesPreventOverwrite = bytesRequired - bytesRemaining;
//    countCycles = 0;
    
//    int averageFirstSensor;
//    int averageSecondSensor;
//    int index = 0;
    
    memset(bytesReturned, 0, bytesRequired * sizeof(uint8_t));
//    memset(averageFirstSensor, 0, bytesRequired * sizeof(uint8_t));
//    memset(averageSecondSensor, 0, bytesRequired * sizeof(uint8_t));

    if(serial.available() > 0){
        serial.writeByte('A');

    if(getSerialMessage){

//        cout << "I'm here" << endl;
        serial.readBytes( bytesReturned, bytesRemaining );
//        index++;
        
        if(bytesReturned[4] == 'z'){
            if(bytesReturned[0] == '1'){
                firstSensor = bytesReturned[1];
//                averageFirstSensor += firstSensor;

//                cout<<"firstSensor after1: "<< firstSensor <<endl;
//                cout<<"averageFirstSensor after1: "<< averageFirstSensor <<endl;

            }
            if(bytesReturned[2] == '2'){
                secondSensor = bytesReturned[3];
//                averageSecondSensor += secondSensor;

//                cout<<"secondSensor after1: "<<secondSensor<<endl;
//                cout<<"averageSecondSensor after1: "<< averageSecondSensor <<endl;

            }
            }
 
//        index++;
//        averageFirstSensor += firstSensor;
//        averageSecondSensor += secondSensor;
//        if(index == 10){
//            firstSensor = averageFirstSensor / 10;
//            secondSensor = averageSecondSensor / 10;
//            index = 0;
//        }
     
        serial.flush();

    }
//        if (index == 5) {
//            firstSensor = averageFirstSensor / index;
//            secondSensor = averageSecondSensor / index;
//            cout<<"averageSecondSensor after1: "<< averageSecondSensor <<endl;
//            
//            index = 0;
//        }
        getSerialMessage = false;


    }
//    cout<<"Get Serial?: "<<getSerialMessage<<endl;
    countCycles++;
//    cout<<"countCyles: "<<countCycles<<endl;
    if(countCycles == 5){
        getSerialMessage = true;
        countCycles = 0;
    }

    int selectedSensor = MIN(firstSensor, secondSensor);
    if(selectedSensor != prevSensorReading){
        //do stuff here
        //else ignore it
        int currentVideoIndex = selectVideo(selectedSensor);
        clipsPointer->stop();
        clipsPointer = &videos[currentVideoIndex];
        clipsPointer->setVolume(0.0f);
        clipsPointer->play();
        
    }
    prevSensorReading = selectedSensor;

    //    int videoIndex =
    shaderValue = triggerFunction(firstSensor, secondSensor);
//    cout<<"shaderValue after triggerFunction: "<<shaderValue<<endl;

    
    
//    oldShaderValue = 0;
    int intShaderValue = shaderValue * 100;
    int cue = 0;
    
    if(oldShaderValue != intShaderValue){

        oldShaderValue = intShaderValue;
        
        if(oldShaderValue == 0){
            cue = 0;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
        } else if(oldShaderValue == 8){
            cue = 1;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
            
//            cout<<"cue: "<<cue<<endl;
        } else if (oldShaderValue == 16){
            cue = 2;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 24){
            cue = 3;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 32){
            cue = 4;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 40){
            cue = 5;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if(oldShaderValue == 48){
            cue = 6;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 56){
            cue = 7;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 64){
            cue = 8;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 72){
            cue = 9;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
            
        } else if (oldShaderValue == 80){
            cue = 10;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
        } else {
            //olderShaderValue == 100;
            cue = 11;
            clipsPointer->stop();
            //            clipsPointer->close();
            clipsPointer = &videos[cue];
            clipsPointer->setVolume(0.0f);
            clipsPointer->play();
//            cout<<"cue: "<<cue<<endl;
        }
//        cout<<"Why is nothing happening???"<<endl;
    }
    
//    cout<<"cue after: "<<cue<<endl;
    clipsPointer->update();

}
//--------------------------------------------------------------
void ofApp::draw(){


    fbo.begin();
    ofClear(0, 0, 0, 0);
    clipsPointer->draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    fbo.end();
    
    fbo.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    mainOutputSyphonServer.publishScreen();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'D'){
        
        ofToggleFullscreen();
    }
}

int ofApp::selectVideo(int sensorValue){
    int sensorMin = 0;
    int sensorMax = 300;
    int videoIndexMin = 0;
    int videoIndexMax = 11;
    int currentVideoIndex  = ofMap(sensorValue, sensorMin, sensorMax, videoIndexMin, videoIndexMax,true);
    cout<<" Current Sensor Value "<<sensorValue<<" Current Video Index "<<currentVideoIndex<<endl;

    return currentVideoIndex;
}

//--------------------------------------------------------------
float ofApp::triggerFunction(int sensorValue, int sensorValue2){
// WILL REPLACE THESE IF STATEMENTS WITH MODULO
    
    bool first = ((sensorValue >= 1) && (sensorValue < 20));
    bool firstFromSecond = ((sensorValue2 >= 1) && (sensorValue2 < 20));
    
    bool second = ((sensorValue >= 20) && (sensorValue < 36));
    bool secondFromSecond = ((sensorValue2 >= 20) && (sensorValue2 < 36));
    
    bool third = ((sensorValue >= 36) && (sensorValue < 52));
    bool thirdFromSecond = ((sensorValue2 >= 36) && (sensorValue2 < 52));
                  
    bool fourth = ((sensorValue >= 52) && (sensorValue < 68));
    bool fourthFromSecond = ((sensorValue2 >= 52) && (sensorValue2 < 68));
                  
    bool fifth = ((sensorValue >= 68) && (sensorValue < 84));
    bool fifthFromSecond = ((sensorValue2 >= 68) && (sensorValue2 < 84));
                  
    bool sixth = ((sensorValue >= 84) && (sensorValue < 100));
    bool sixthFromSecond = ((sensorValue2 >= 84) && (sensorValue2 < 100));
                  
    bool seventh = ((sensorValue >= 100) && (sensorValue < 116));
    bool seventhFromSecond = ((sensorValue2 >= 100) && (sensorValue2 < 116));
                  
    bool eighth = ((sensorValue >= 116) && (sensorValue < 142));
    bool eighthFromSecond = ((sensorValue2 >= 116) && (sensorValue2 < 142));
                  
    bool ninth = ((sensorValue >= 142) && (sensorValue < 168));
    bool ninthFromSecond = ((sensorValue2 >= 142) && (sensorValue2 < 168));
                  
    bool tenth = ((sensorValue >= 168) && (sensorValue < 182));
    bool tenthFromSecond = ((sensorValue2 >= 168) && (sensorValue2 < 182));
                  
    bool eleventh = ((sensorValue >= 182) && (sensorValue < 232));
    bool eleventhFromSecond = ((sensorValue2 >= 182) && (sensorValue2 < 232));
    
    float alphaValue = 1.0;

    if((first && firstFromSecond) || first || firstFromSecond){
        alphaValue = 0.0;
        return alphaValue;
        
    } else if ((second && secondFromSecond) || (second && !firstFromSecond)|| (secondFromSecond && !first)){
        alphaValue = 0.08;
        return alphaValue;
        
    } else if ((third && thirdFromSecond) || (third && !secondFromSecond) ||  (thirdFromSecond && !second) || (third && !firstFromSecond) || (thirdFromSecond && !first)){
        alphaValue = 0.16;
        return alphaValue;
        
    } else if ((fourth && fourthFromSecond) || (fourth) || (fourthFromSecond)){
        alphaValue = 0.24;
        return alphaValue;
        
    } else if ((fifth && fifthFromSecond) || fifth || fifthFromSecond){
        alphaValue = 0.32;
        return alphaValue;
        
    } else if ((sixth && sixthFromSecond) || sixth || sixthFromSecond){
        alphaValue = 0.4;
        return alphaValue;
        
    } else if ((seventh && seventhFromSecond) || seventh|| seventhFromSecond){
        alphaValue = 0.48;
        return alphaValue;
        
    } else if ((eighth && eighthFromSecond) || eighth || eighthFromSecond){
        alphaValue = 0.56;
        return alphaValue;
        
    } else if ((ninth && ninthFromSecond) || ninth || ninthFromSecond){
        alphaValue = 0.64;
        return alphaValue;
        
    } else if ((tenth && tenthFromSecond) || tenth || tenthFromSecond){
        alphaValue = 0.72;
        return alphaValue;
        
    } else if ((eleventh && eleventhFromSecond) || eleventh|| eleventhFromSecond){
        alphaValue = 0.8;
        return alphaValue;
        
    } else if (((sensorValue >= 232) &&  (sensorValue2 >= 232))){
        alphaValue = 1.0;
        return alphaValue;
    } else if((sensorValue >= 232 && firstFromSecond) || (sensorValue2 >= 228 && first)) {
        alphaValue = 0.0;
        return alphaValue;
    } else if ((sensorValue >= 232 && secondFromSecond) || (sensorValue2 >= 228 && second)){
        alphaValue = 0.08;
        return alphaValue;
    }else if ((sensorValue >= 232 && thirdFromSecond)|| (sensorValue2 >= 232 && third)){
        alphaValue = 0.16;
        return alphaValue;
    } else if((sensorValue >= 232 && fourthFromSecond) || (sensorValue2 >= 232 && fourth)){
        alphaValue = 0.24;
        return alphaValue;
    } else if((sensorValue >= 232 && fifthFromSecond) || (sensorValue2 >= 232 && fifth)){
        alphaValue = 0.32;
        return alphaValue;
    } else if ((sensorValue >= 232 && sixthFromSecond) || (sensorValue2 >= 232 && sixth)){
        alphaValue = 0.40;
        return alphaValue;
    } else if((sensorValue >= 232 && seventhFromSecond) || (sensorValue2 >= 232 && seventh)){
        alphaValue = 0.48;
        return alphaValue;
    } else if((sensorValue >= 232 && eighthFromSecond) || (sensorValue2 >= 232 && eighth)){
        alphaValue = 0.56;
        return alphaValue;
    } else if ((sensorValue >= 232 && ninthFromSecond) || (sensorValue2 >= 232 && ninth)){
        alphaValue = 0.64;
        return alphaValue;
    } else if ((sensorValue >= 232 && tenthFromSecond) || (sensorValue2 >= 232 && tenth)){
        alphaValue = 0.72;
        return alphaValue;
    } else if ((sensorValue >= 232 && eleventhFromSecond) || (sensorValue2 >= 232 && eleventh)){
        alphaValue = 0.80;
        return alphaValue;
    } else{
        return alphaValue;
    }
    
//    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == '1'){
        selectVideo(20);
    }
    else if(key =='2'){
        selectVideo(280);
    }
        
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
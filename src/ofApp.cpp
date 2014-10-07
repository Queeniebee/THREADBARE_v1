#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    getSerialMessage = false;

//    paths[0] = "THREADBARE_hair/Resources/THREADBARE_hair.mov";
//    paths[1] = "THREADBARE_shoes4/Resources/THREADBARE_shoes4.mov";
//    paths[2] = "THREADBARE_replacev52/Resources/THREADBARE_replacev52.mov";
//    paths[3] = "THREADBARE_shoes3/Resources/THREADBARE_shoes3.mov";
//    paths[4] = "THREADBARE_v9_c/Resources/THREADBARE_v9_c.mov"; 
//    paths[5] = "THREADBARE_shoes1/Resources/THREADBARE_shoes1.mov";
//    paths[6] = "THREADBARE_v6/Resources/THREADBARE_v6.mov";
//    paths[7] = "THREADBARE_v7/Resources/THREADBARE_v7.mov"; 
//    paths[8] = "THREADBARE_v6/Resources/THREADBARE_v6.mov"; 
//    paths[9] = "THREADBARE_v42/Resources/THREADBARE_v42.mov"; 
//    paths[10] = "THREABARE_v2/Resources/THREABARE_v2.mov";
//    paths[11] = "THREADBARE_curtain/Resources/THREADBARE_curtain.mov";
    
    paths[0] = "for_SHOW/THREADBARE_hair.mov";
    paths[1] = "for_SHOW/THREADBARE_shoes4.mov";
    paths[2] = "for_SHOW/THREADBARE_replacev52.mov";
    paths[3] = "for_SHOW/THREADBARE_shoes3.mov";
    paths[4] = "for_SHOW/THREADBARE_v9_c.mov";
    paths[5] = "for_SHOW/THREADBARE_shoes1.mov";
    paths[6] = "for_SHOW/THREADBARE_v6.mov";
    paths[7] = "for_SHOW/THREADBARE_v7.mov";
    paths[8] = "for_SHOW/THREADBARE_v6.mov";
    paths[9] = "for_SHOW/THREADBARE_v42.mov";
    paths[10] = "for_SHOW/THREABARE_v2.mov";
    paths[11] = "for_SHOW/THREADBARE_curtain.mov";

    clipsPointer = &videos[0];
    clipsPointer->setPixelFormat(OF_PIXELS_RGBA);

    decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    
    for(int i = 0; i< sizeof(videos)/sizeof(ofQTKitPlayer); i++){
        videos[i].loadMovie(paths[i], decodeMode);
    }
    clipsPointer->setVolume(1.0f);
    clipsPointer->play();
    
    videoSound.loadSound("Threadbare_voiceover.mp3");
    videoSound.setVolume(0.0f);
    videoSound.setLoop(true);
    videoSound.play();
    
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

    mSerial.openSerialPort();
    mSerial.startContinuousRead(true);

    ofAddListener(mSerial.readFromSerial, this, &ofApp::conversionToInt);


    //    mainOutputSyphonServer.setName("Screen Output");

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();

//    int selectedSensor = MIN(firstSensor, secondSensor);
//    ofAddListener(mSerial.readFromSerial, this, &ofApp::conversionToInt);

    mSerial.sendRequest();

    int currentSensorReading = sensors(sensorReadings);
    if(currentSensorReading != prevSensorReading){
        //do stuff here
        //else ignore it
        int currentVideoIndex = selectVideo(currentSensorReading);
        clipsPointer->stop();
        clipsPointer = &videos[currentVideoIndex];
        clipsPointer->setVolume(0.0f);
        clipsPointer->play();
        
    }
/*    if (bytesRemaining == 0) {
        serial.writeByte('A');
    } */
    prevSensorReading = currentSensorReading;
    clipsPointer->update();

}
//--------------------------------------------------------------
void ofApp::draw(){


    fbo.begin();
    ofClear(0, 0, 0, 0);
    clipsPointer->draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    fbo.end();
    
    fbo.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
//    mainOutputSyphonServer.publishScreen();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'D'){
        
        ofToggleFullscreen();
    }
}
//---------------------------------------------------------
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
void ofApp::conversionToInt(string &fromSerial){
//    int sensorReadings[NUM_BYTES];
    vector<string>convertedReadings = ofSplitString(fromSerial, ",");
    //    int sensorReadings[BYTES_REQUIRED];
    for(int i = 0; i < convertedReadings.size(); i++){
        sensorReadings[i] = ofToInt(convertedReadings[i]);
    }
//    ofNotifyEvent(sensorReading, *sensorReadings, this);
//    return *sensorReadings;
}
//--------------------------------------------------------------

int ofApp::sensors(int *reads){
    //cast from string to int
    int firstSensor;
    int secondSensor;
    int selectedSensor;
    
    if(reads[0] == 1){
            firstSensor = reads[1];
        }
        if(reads[2] == 2){
            secondSensor = reads[3];
            
        }
    selectedSensor = MIN(firstSensor, secondSensor);
    return (selectedSensor);
}
//--------------------------------------------------------------

void ofApp::keyReleased(int key){    
     switch (key){
     
     case '1':
             firstSensor = 45;
             secondSensor = 54;

     break;
     
     case '2':
             firstSensor = 54;
             secondSensor = 45;
             
     break;
     
     case '3':
             firstSensor = 60;
             secondSensor = 70;
     break;
     
     case '4':
             firstSensor = 80;
             secondSensor = 70;
     break;
     
     case '5':
             firstSensor = 120;
             secondSensor = 130;
     break;
     
     case '6':
             firstSensor = 130;
             secondSensor = 145;
     break;
     
     case '7':
             firstSensor = 160;
             secondSensor = 145;
     break;
     
     case '8':
             firstSensor = 185;
             secondSensor = 150;
     break;
     
     case '9':
             firstSensor = 200;
             secondSensor = 210;
     break;
     
     case '0':
             firstSensor = 255;
             secondSensor = 230;;
     break;
     
     case 'p':
             firstSensor = 230;
             secondSensor = 280;
     break;
     
     case 'o':
             firstSensor = 300;
             secondSensor = 300;
     break;
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
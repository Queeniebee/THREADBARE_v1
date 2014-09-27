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
    serial.setup(0,115200);

    mainOutputSyphonServer.setName("Screen Output");

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate();
 /*

  WORKING SERIAL VERSION 
  =======================
  */

    int bytesRequired = 5;
    uint8_t bytesReturned[bytesRequired];
    int bytesRemaining = bytesRequired;
    memset(bytesReturned, 0, bytesRequired * sizeof(uint8_t));
    
    int bytesPreventOverwrite = bytesRequired - bytesRemaining;
    int result = serial.readBytes( &bytesReturned[bytesPreventOverwrite], bytesRemaining );
    
    while ( bytesRemaining > 0 ){
        if(serial.available() > 0){
            serial.writeByte('A');
        
            if ( result == OF_SERIAL_ERROR )
            {
                // something bad happened
                ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                // bail out
                break;
            }
            else if ( result == OF_SERIAL_NO_DATA )
            {
                // nothing was read, try again
            }
            else
            {
                // we read some data!
                bytesRemaining -= result;
            }
            
            if(bytesReturned[4] == 'z'){
                if(bytesReturned[0] == '1'){
                    firstSensor = bytesReturned[1];
                }
                if(bytesReturned[2] == '2'){
                    secondSensor = bytesReturned[3];
                    
                }
            }
            serial.flush();
            cout<<"result: "<<result<<endl;

        }        
    }
    if (bytesRemaining == 0) {
        serial.writeByte('A');
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
void ofApp::keyReleased(int key){
//    if(key == '1'){
//        selectVideo(20);
//    }
//    else if(key =='2'){
//        selectVideo(280);
//    } else if (key == '3'){
//        selectVideo(280);
//    
//    }
    
     switch (key){
     
     case '1':
             selectVideo(45);

     break;
     
     case '2':
             selectVideo(45);
     break;
     
     case '3':
             selectVideo(60);
     break;
     
     case '4':
             selectVideo(80);
     break;
     
     case '5':
             selectVideo(120);
     break;
     
     case '6':
             selectVideo(130);
     break;
     
     case '7':
             selectVideo(160);
     break;
     
     case '8':
             selectVideo(185);
     break;
     
     case '9':
             selectVideo(210);
     break;
     
     case '0':
             selectVideo(255);
     break;
     
     case 'p':
             selectVideo(280);
     break;
     
     case 'o':
             (300);
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
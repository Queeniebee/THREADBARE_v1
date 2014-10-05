//
//  threadSerial.cpp
//  THREADBARE_v1
//
//  Created by Joelle on 10/4/14.
//
//

#include "threadSerial.h"

threadSerial::threadSerial(){
    serialMessage = "";
    messageBuffer = "";
}
//-----------------------------------------------
threadSerial::~threadSerial(){

}
//-----------------------------------------------
void threadSerial::openSerialPort(){

    serial.enumerateDevices();
    serial.setup(0,115200);

}
//-----------------------------------------------

void threadSerial::startContinuousRead(bool writeByte) {
    continuousRead = true;
    bwriteByte = writeByte;
    sendRequest();
}
//-----------------------------------------------
void threadSerial::stopContinuousRead() {
    continuousRead = false;
    ofRemoveListener(ofEvents().update, this, &threadSerial::update);
}

//-----------------------------------------------

void threadSerial::sendRequest(){
    if ((bwriteByte) && (serial.available() == 'B')){
        serial.writeByte('A');
    }
//    ofNotifyEvent(ofEvents().update, this, &threadSerial::update);
    ofAddListener(ofEvents().update, this, &threadSerial::update);

}
//-----------------------------------------------

void threadSerial::update(ofEventArgs & args){
    readFromSerialPort();
    if (continuousRead){
        sendRequest();
    }

}

//-----------------------------------------------
void threadSerial::readFromSerialPort(){

//    while((serial.available() > 0) && (serial.available() != 'B')) {
    while(serial.available() != 'B') {

            serial.readBytes(bytesRead, BYTES_REQUIRED);
        
            if (*bytesRead == '\n'){
				serialMessage = messageBuffer;
				messageBuffer = "";
				ofRemoveListener(ofEvents().update, this, &threadSerial::update);
				ofNotifyEvent(readFromSerial, serialMessage, this);
				break;
            } else {
				if (*bytesRead != '\r')
                    messageBuffer += *bytesRead;
                    }
            }

            // clear the message buffer
            memset(bytesRead, 0, BYTES_REQUIRED);
            //memset(bytesRead, 0, bytesRequired * sizeof(uint8_t));


}
//-----------------------------------------------
bool threadSerial::stopReadFromSerialPort(){
//where elasped time goes
    //and the ofRemoveEventListener() goes

}
//-----------------------------------------------


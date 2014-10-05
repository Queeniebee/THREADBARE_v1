//
//  threadSerial.h
//  THREADBARE_v1
//
//  Created by Joelle on 10/4/14.
//
//

#ifndef THREADBARE_v1__threadSerial
#define THREADBARE_v1__threadSerial

#include "ofSerial.h"
#include "ofEvents.h"
#include "ofMain.h"

#define BYTES_REQUIRED 5

class threadSerial {

public:
    threadSerial();
    ~threadSerial();
    
    
    ofSerial serial;
//    ofEvent<int> sensorReading;
    ofEvent<string> readFromSerial;
    
    void openSerialPort();
    void readFromSerialPort();
    void startContinuousRead(bool writeByte);
    void stopContinuousRead();
    void sendRequest();
    void update(ofEventArgs & args);

    bool stopReadFromSerialPort();
    
    int bytesRequired = BYTES_REQUIRED;
    int bytesRemaining;
    uint8_t bytesRead[BYTES_REQUIRED];
    string serialMessage;
    string messageBuffer;
    bool bwriteByte;
    bool continuousRead;
    
    int sensorReadings[BYTES_REQUIRED];

    

};
#endif 
/* defined(THREADBARE_v1__threadSerial) */

#include <NewPing.h>

#define NUM_SENSORS    2 // Number or sensors.
#define MAX_DISTANCE 300 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).


#define TRIGGER_PIN_1 13
#define ECHO_PIN_1    12
#define TRIGGER_PIN_2 11
#define ECHO_PIN_2    10

unsigned long pingTimer[NUM_SENSORS]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[NUM_SENSORS];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[NUM_SENSORS] = {     // Sensor object array.
  NewPing(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE),
};

void setup() {
  Serial.begin(9600);
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < NUM_SENSORS; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  for (uint8_t i = 0; i < NUM_SENSORS; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * NUM_SENSORS;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == 1){ // Sensor ping cycle complete, do something with the results.
        oneSensorCycle(); 
      } 
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  // The rest of your code would go here.
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
//    cm[currentSensor] = sonar[currentSensor].convert_cm();
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
}


/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-rain-sensor-servo-motor
 */

#include <Servo.h>

#define RAIN_SENSOR_PIN A0 // Arduino pin connected to rain sensor's pin
#define SERVO_PIN       9  // Arduino pin connected to servo motor's pin

Servo servo; // create servo object to control a servo

// variables will change:
int angle = 0;          // the current angle of servo motor
int prev_rain_state;    // the previous state of rain sensor
int rain_state; // the current state of rain sensor

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(RAIN_SENSOR_PIN, INPUT); // set arduino pin to input mode
  servo.attach(SERVO_PIN);           // attaches the servo on pin 9 to the servo object

  servo.write(angle);
  rain_state = digitalRead(RAIN_SENSOR_PIN);
}

void loop() {
  prev_rain_state = rain_state;             // save the last state
  rain_state = digitalRead(RAIN_SENSOR_PIN); // read new state

  Serial.println( rain_state );

  // 2025-11-17 jj5 - turns out my servo works different to the servo used in the demo
  // 2025-11-17 jj5 - this code just runs the servo through 180 "degrees" (not actually degreees)
  int angle;
  for ( angle = 0; angle <= 180; angle++ ) {
    Serial.println( angle );
    servo.write( angle );
    delay( 100 );
  }

  if (rain_state == LOW && prev_rain_state == HIGH) { // pin state change: LOW -> HIGH
    Serial.println("Rain detected!");
    //servo.write(90);
  }
  else
  if (rain_state == HIGH && prev_rain_state == LOW) { // pin state change: HIGH -> LOW
    Serial.println("Rain stopped!");
    //servo.write(0);
  }
}

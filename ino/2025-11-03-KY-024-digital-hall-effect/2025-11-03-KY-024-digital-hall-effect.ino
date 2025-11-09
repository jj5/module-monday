
// 2025-11-10 jj5 - SEE: https://arduinomodules.info/ky-024-linear-magnetic-hall-module/

const int LED_PIN = 13;
const int SENSOR_PIN = 3;
int reading = 0;

void setup() {
  pinMode( LED_PIN, OUTPUT );
  pinMode( SENSOR_PIN, INPUT );
  Serial.begin( 9600 );
  Serial.println( "Running..." );
}

void loop() {
  reading = digitalRead( SENSOR_PIN );
  Serial.println( reading );
  delay( 1000 );
}

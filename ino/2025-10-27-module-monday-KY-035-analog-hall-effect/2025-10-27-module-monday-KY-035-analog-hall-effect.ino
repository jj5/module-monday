
// 2025-10-27 jj5 - our analog input is on pin A5...
const int SENSOR_PIN = A5;

// 2025-10-27 jj5 - the onboard LED is pin 13, we use this as an output...
const int LED_PIN = 13;

// 2025-10-27 jj5 - we read our analog input into this variable...
int sensor_value = 0;

void setup () {
  pinMode( LED_PIN, OUTPUT );
  Serial.begin ( 9600 );
  Serial.println( "Running..." );
}

void loop () {
  // 2025-10-27 jj5 - read an analog value from our sensor pin...
  sensor_value = analogRead( SENSOR_PIN );
  // 2025-10-27 jj5 - print the current sensor value...
  Serial.println( sensor_value );
  // 2025-10-27 jj5 - this will flash fast in presense of magnetism and flash slow otherwise...
  digitalWrite( LED_PIN, HIGH );
  delay( sensor_value );
  digitalWrite( LED_PIN, LOW );
  delay( sensor_value );
}

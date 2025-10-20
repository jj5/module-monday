#include <Arduino.h>

// 2025-10-20 jj5 - the Arduino output LED is on pin 13 (but we're not using it at the moment in this sketch).
//
const int LED = 13;

// 2025-10-20 jj5 - the input pin from our KY-031 knock sensor is nominated here:
//
const int PIN = 3;

// 2025-10-20 jj5 - we read our digital input from PIN into this variable:
//
int val = 0;

// 2025-10-20 jj5 - we count how many loops we do per interval (5 seconds)
//
unsigned long count = 0;

// 2025-10-20 jj5 - we count low values (index 0) and high values (index 1)
//
unsigned long counters[2] = { 0, 0 };

// 2025-10-20 jj5 - this is book keeping for figuring out when five seconds has elapsed
//
unsigned long previous_millis = 0;
const unsigned long interval = 5000; // 5 seconds in milliseconds

// 2025-10-20 jj5 - this assertion courtesy ChatGPT, if there's a problem we print then hang
//
#define ASSERT(condition, message)            \
  if (!(condition)) {                         \
    Serial.print("Assertion failed: ");       \
    Serial.println(message);                  \
    Serial.print("At: ");                     \
    Serial.print(__FILE__);                   \
    Serial.print(":");                        \
    Serial.println(__LINE__);                 \
    while (true) { delay(100); }              \
  }

// 2025-10-20 jj5 - this function is for printf integration
//
int serial_putchar( char c, FILE * ) {
  Serial.write( c );
  return 0;
}

// 2025-10-20 jj5 - the setup routine runs once at the beginning of the program
//
void setup() { 

  // 2025-10-20 jj5 - our LED output, presently unused
  //
  pinMode( LED, OUTPUT);

  // 2025-10-20 jj5 - out PIN input, from the KY-031 knock sensor
  //
  pinMode( PIN, INPUT);

  // 2025-10-20 jj5 - connect the serial line
  //
  Serial.begin(115200);

  // 2025-10-20 jj5 - wait for serial initialization
  //
  while ( ! Serial );

  // 2025-10-20 jj5 - integrate printf with Serial.print
  //
  static FILE uartout;
  fdev_setup_stream(&uartout, serial_putchar, nullptr, _FDEV_SETUP_WRITE);
  stdout = &uartout;

  // 2025-10-20 jj5 - tell the user we're ready
  //
  printf( "Console ready.\n" );

} 

// 2025-10-20 jj5 - this function from ChatGPT, it's supposed to print thousands with comma separators
//
void print_with_commas( unsigned long n ) {
  char buf[32];
  char out[32];
  int i = 0, j = 0, len;
  sprintf(buf, "%lu", n);
  len = strlen(buf);
  // Copy digits from right to left, inserting commas
  for (i = len - 1, j = 0; i >= 0; i--) {
      out[j++] = buf[i];
      if (((len - i) % 3 == 0) && i != 0)
          out[j++] = ',';
  }
  out[j] = '\0';
  // Reverse to restore correct order
  for (i = 0; i < j / 2; i++) {
      char c = out[i];
      out[i] = out[j - 1 - i];
      out[j - 1 - i] = c;
  }
  printf("%s", out);
}

void loop () {

  // 2025-10-20 jj5 - read the digital value (0 or 1) from the input PIN
  //
  val = digitalRead( PIN );

  // 2025-10-20 jj5 - ensure the input is valid
  //
  ASSERT( val == 0 || val == 1, "invalid value." );

  // 2025-10-20 jj5 - increment our counters
  //
  count++;
  counters[ val ]++;

  // 2025-10-20 jj5 - read the current time
  //
  unsigned long current_millis = millis();

  // 2025-10-20 jj5 - if the timer hasn't expired stop processing
  //
  if ( current_millis - previous_millis < interval ) { return; }

  // 2025-10-20 jj5 - reset the timer
  //
  previous_millis = current_millis;

  // 2025-10-20 jj5 - print the total count
  //
  printf( "5 seconds passed! " );
  print_with_commas( count );
  printf( " values read.\n" );

  // 2025-10-20 jj5 - ensure the counters balance
  //
  unsigned long total = counters[ 0 ] + counters[ 1 ];
  if ( count != total ) {
    // 2025-10-20 jj5 - this shouldn't happen
    printf( "count != total\n" );
  }

  // 2025-10-20 jj5 - print the low count and the high count
  //
  print_with_commas( counters[ 0 ] );
  printf( " / " );
  print_with_commas( counters[ 1 ] );
  printf( "\n" );

  // 2025-10-20 jj5 - reset the counters
  //
  count = 0;
  counters[ 0 ] = 0;
  counters[ 1 ] = 0;

}

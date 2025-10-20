#include <Arduino.h>

const int LED = 13;
const int PIN = 3;

int val = 0;

unsigned long count = 0;
unsigned long counters[2] = { 0, 0 };

unsigned long previous_millis = 0;
const unsigned long interval = 5000; // 5 seconds in milliseconds

// 2025-10-20 jj5 - this assertion courtesy ChatGPT
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

int serial_putchar( char c, FILE * ) {
  Serial.write( c );
  return 0;
}

void setup() { 

  pinMode( LED, OUTPUT);
  pinMode( PIN, INPUT);

  Serial.begin(115200);
  while ( ! Serial );

  static FILE uartout;
  fdev_setup_stream(&uartout, serial_putchar, nullptr, _FDEV_SETUP_WRITE);
  stdout = &uartout;

  printf( "Console ready.\n" );

} 

// 2025-10-20 jj5 - this function from ChatGPT
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

  val = digitalRead( PIN );

  ASSERT( val == 0 || val == 1, "invalid value." );

  count++;
  counters[ val ]++;

  unsigned long current_millis = millis();

  if ( current_millis - previous_millis >= interval ) {

    // 2025-10-20 jj5 - reset the timer
    previous_millis = current_millis;

    printf( "5 seconds passed! " );
    print_with_commas( count );
    printf( " values read.\n" );

    unsigned long total = counters[ 0 ] + counters[ 1 ];

    if ( count != total ) {

      printf( "count != total\n" );

    }

    print_with_commas( counters[ 0 ] );
    printf( " / " );
    print_with_commas( counters[ 1 ] );
    printf( "\n" );

    count = 0;
    counters[ 0 ] = 0;
    counters[ 1 ] = 0;

  }
}

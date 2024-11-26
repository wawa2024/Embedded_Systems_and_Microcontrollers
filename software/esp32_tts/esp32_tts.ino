#include <Arduino.h>
#include <ESP8266SAM.h>
#include <AudioOutputI2SNoDAC.h>
#define BAUD_RATE 115200
#define GPIO_DAC 27
#define BUFFER_SIZE 80
#define TX 17
#define RX 16

AudioOutputI2SNoDAC *out = NULL;
ESP8266SAM *sam = NULL;

void samSay(char* line) {
  ESP8266SAM *sam = new ESP8266SAM;
  sam -> Say(out,line);
  delete sam;
}

char buf[BUFFER_SIZE];
constexpr int BUFFER_LIMIT = ( BUFFER_SIZE - 2 );

bool pushBuf(unsigned int i, char c) {

  if ( i > BUFFER_LIMIT ) {

    samSay("error");
    samSay("buffer overflow");

    return true;

  } else {

    buf[i] = c;
    return false;

  }
}

void speakSerial(void) {

  static unsigned int i = 0;

  if (Serial2.available() > 0) {

    char c = (char)Serial2.read();

    if (c == '\n') {
      pushBuf(i++,0);
      samSay(buf);
      i = 0;
    }

    else
      pushBuf(i++,c);
  }
}

void setup()
{
  Serial.begin(BAUD_RATE);
  Serial.print("ESP32 SERIAL_ONLINE, BAUD_RATE=");
  Serial.println(BAUD_RATE);

  Serial2.begin(BAUD_RATE,SERIAL_8N1,RX,TX);

  out = new AudioOutputI2SNoDAC();
  // out -> SetPinout(/*bclkPin*/26,/*wclkPin*/25,/*doutPin*/22);
  out -> begin();
}

void loop(void) {
  speakSerial();
}

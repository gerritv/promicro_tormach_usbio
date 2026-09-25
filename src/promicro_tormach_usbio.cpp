#include <arduino.h>

#define INPUT0 A0
#define INPUT1 A1
#define INPUT2 A2
#define INPUT3 A3

#define OUTPUT0 2
#define OUTPUT1 3
#define OUTPUT2 4
#define OUTPUT3 5

#define MSG_PIN 13



#define VERSION_STR "Tormach I/O ID=0\n"
#define DEBOUNCE_MS 10

//  what to actually set the outputs to
bool outputs[4];
//  what to actually send as inputs
bool inputs[4];

//  de-bounce input
bool tInputs[4];
//  time to use for de-bounce
uint32_t tmInputs[4];



void setup() {

  Serial.begin(38400);

  // put your setup code here, to run once:
  pinMode(OUTPUT0, OUTPUT);
  digitalWrite(OUTPUT0,HIGH);
  pinMode(OUTPUT1, OUTPUT);
  digitalWrite(OUTPUT1, HIGH);
  pinMode(OUTPUT2, OUTPUT);
  digitalWrite(OUTPUT2, HIGH);
  pinMode(OUTPUT3, OUTPUT);
  digitalWrite(OUTPUT3, HIGH);
  pinMode(MSG_PIN, OUTPUT);
  digitalWrite(MSG_PIN, LOW);

  pinMode(INPUT0, INPUT_PULLUP);
  pinMode(INPUT1, INPUT_PULLUP);
  pinMode(INPUT2, INPUT_PULLUP);
  pinMode(INPUT3, INPUT_PULLUP);
}

char inbuf[256];
uint8_t iptr;
bool led;

void toggleLed() {
  led = !led;
  digitalWrite(MSG_PIN, led ? HIGH : LOW);
}

void loop() {
  uint32_t now = millis();

  int n = Serial.available();
  //  Parse whatever we have -- which may be partial lines, so keep buffer
  while (n > 0) {
    --n;
    int ch = Serial.read();
    if (ch == '\r' || ch == '\n') {
      if (iptr > 0) {
        if (inbuf[0] == 'V' && inbuf[1] == 'E') {
          Serial.write(VERSION_STR);
          toggleLed();
        } else if (inbuf[0] == 'S' && inbuf[1] == 'R' && inbuf[2] == ' ') {
          if (iptr < 7) {
            //  bad CMD!
          } else {
            outputs[0] = (inbuf[3] == '1');
            outputs[1] = (inbuf[4] == '1');
            outputs[2] = (inbuf[5] == '1');
            outputs[3] = (inbuf[6] == '1');
            char msg[5] = {
              inputs[0] ? '0' : '1',
              inputs[1] ? '0' : '1',
              inputs[2] ? '0' : '1',
              inputs[3] ? '0' : '1',
              '\n'
            };
            Serial.write(msg, 5);
            toggleLed();
          }
        } else if (inbuf[0] == '?') {
          inbuf[iptr] = 0;
          char buf[120];

          sprintf(buf, "* %d%d%d%d %d%d%d%d\n",
            outputs[0], outputs[1], outputs[2], outputs[3],
            !inputs[0], !inputs[1], !inputs[2], !inputs[3]);

          Serial.write(buf);
        } else {
          //  bad CMD!!
        }
      }
      memset(inbuf, 0, iptr);
      iptr = 0;
    } else  {
      if (iptr == sizeof(inbuf)-1) {
        //  OVERFLOW!
        iptr = 0;
      } else {
        inbuf[iptr++] = ch;
      }
    }
  }


  tInputs[0] = digitalRead(INPUT0);
  tInputs[1] = digitalRead(INPUT1);
  tInputs[2] = digitalRead(INPUT2);
  tInputs[3] = digitalRead(INPUT3);


  //  debounce input pins
  for (int i = 0; i != 4; ++i) {
    if (tInputs[i] == inputs[i]) {
      tmInputs[i] = now;
    }
    if (now - tmInputs[i] > DEBOUNCE_MS) {
      inputs[i] = tInputs[i];
    }
  }
  
  //  output relay status
  digitalWrite(OUTPUT0, !outputs[0]);
  digitalWrite(OUTPUT1, !outputs[1]);
  digitalWrite(OUTPUT2, !outputs[2]);
  digitalWrite(OUTPUT3, !outputs[3]);


}


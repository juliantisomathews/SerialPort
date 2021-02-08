#include <Arduino_JSON.h>

const int buttonPin = 2;
const int buttonPin2 = 3;

int lastButtonState = HIGH;
int lastButtonState2 = HIGH;

int lastKnobState = 0;
int lastKnobState2 = 0; 

int threshold = 3;
int threshold2 = 3;

bool inputsChanged = false;
bool inputsChanged2 = false;


JSONVar outgoing;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  outgoing["knob"] = 0;
  outgoing["knob2"] = 0;
  outgoing["button"] = 0;
  outgoing["button2"] = 0;

}

void loop() {
  // put your main code here, to run repeatedly:

  int knobState = analogRead(A0);
  knobState = map(knobState, 0, 1023, 0, 100);
  int knobState2 = analogRead(A1);
  knobState2 = map(knobState2, 0, 1023, 0, 100);

  int buttonState = digitalRead(buttonPin);
  int buttonState2 = digitalRead(buttonPin2);

  if (abs(knobState - lastKnobState) > threshold) { // could use some explaining on this - why set the threshold to 3 too?
    outgoing["knob"] = knobState;

    lastKnobState = knobState;

    inputsChanged = true;
  }

    // if the button has changed:
  if (buttonState != lastButtonState) {
    outgoing["button"] = buttonState;
    // save button state for comparison next time:
    lastButtonState = buttonState;
    // set change flag so serial will send:
    inputsChanged = true;
  }
  
  if (inputsChanged) {
    Serial.println(outgoing);
    inputsChanged = false;
  }

  if (abs(knobState2 - lastKnobState2) > threshold2) { // could use some explaining on this - why set the threshold to 3 too?
    outgoing["knob2"] = knobState2;

    lastKnobState2 = knobState2;

    inputsChanged2 = true;
  }

    // if the button has changed:
  if (buttonState2 != lastButtonState2) {
    outgoing["button2"] = buttonState2;
    // save button state for comparison next time:
    lastButtonState2 = buttonState2;
    // set change flag so serial will send:
    inputsChanged2 = true;
  }


  if (inputsChanged2) {
    Serial.println(outgoing);
    inputsChanged2 = false;
  }

}

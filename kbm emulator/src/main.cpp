#include <Arduino.h>
#include <BleKeyboard.h>
#include <BleMouse.h>

BleKeyboard Keyboard;
BleMouse Mouse;

//variable declaration 
const int kbON = 33;
const int mON = 32;
const int LC = 26;
const int RC = 25;
// put function declarations here:
int readAxis(int thisAxis);
void osKB();
void mouseOn();


void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}

// put function definitions here:

void mouseOn(){
  Serial.println("MC CLICKED");
  if(mON){
    Serial.println("Mouse off");
    mON = false;
      
  } else {
    mON = true;
      Serial.println("mouse on");
      
  }
  delay(500);
}
void osKB(){
  Serial.println("OKB TRIG");
  Keyboard.begin();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_GUI);   // Windows key
  Keyboard.press('o');            // 'O' key (use lowercase)
  delay(200); // Small delay to ensure the OS registers it

  // Release all keys
  Keyboard.releaseAll();
}
int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;
  if (abs(distance) < threshold) {

    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}
#include <Arduino.h>
#include <BleKeyboard.h>
#include <BleMouse.h>

BleKeyboard Keyboard;
BleMouse Mouse;

//variable declaration
bool mSwitch = false;
int lastMouseState = LOW;
const int range = 127;
//digital pins  
const int testpin = 2;
const int kb = 25;
const int mouse = 32;
const int LC = 33;
const int RC = 26;
//analog pins, using ADC 1 
const int LJx = 36;
const int LJy = 39; 
const int RJx = 34;
const int RJy = 35;

// put function declarations here:
int readAxis(int thisAxis);
void osKB();
void mouseOn(int pin);


void setup() {
  // put your setup code here, to run once:
  pinMode(testpin, OUTPUT);
  pinMode(LC, INPUT);
  pinMode(RC, INPUT);
  pinMode(kb, INPUT);
  pinMode(mouse, INPUT);
  Mouse.begin();
  mSwitch = false;
}
// put your main code here, to run repeatedly:
void loop() {
  //this enables and disables mouse input 
  mouseOn(mouse);


  if(mSwitch){
    //mouse left click 
    if(digitalRead(LC) == HIGH){
      if(!Mouse.isPressed()){
        Mouse.press();
      }
    } else {
      Mouse.release();
    }
    //mouse right click
    if(digitalRead(RC) == HIGH){
      if(!Mouse.isPressed(MOUSE_RIGHT)){
        Mouse.press(MOUSE_RIGHT);
      }
    } else {
      Mouse.release(MOUSE_RIGHT);
    }
    
    

    
    //mouseX = readAxis(RJx);
    //mouseY = readAxis(RJy);
  }  


  if(digitalRead(kb) == HIGH){
    osKB();
  }
}

// put function definitions here:

void mouseOn(int pin){
  int mouseState = digitalRead(pin);
  if (mouseState != lastMouseState) {
    if (mouseState == HIGH) {
      mSwitch = !mSwitch;
      // turn on LED to indicate mouse state:
      digitalWrite(testpin, mSwitch);
    }
  }
  lastMouseState = mouseState;
}

//macro that enables and disables on screen keyboard 
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
/*
//reads joystick analog into mouse movement distance
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
  */
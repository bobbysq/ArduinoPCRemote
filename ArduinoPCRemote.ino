#include <HID.h>
#include <Keyboard.h>
#include <Mouse.h>
//#include <HID-Project.h>
//#include <HID-Settings.h>
#include <SoftwareSerial.h>

int TX_PIN=3;
int RX_PIN=2;
int KEYBOARD_LED=6;
int MOUSE_LED=7;

SoftwareSerial BT(TX_PIN,RX_PIN); //HC-06


void setup() {
  // put your setup code here, to run once:
  pinMode(KEYBOARD_LED,OUTPUT);
  pinMode(MOUSE_LED,OUTPUT);
  BT.begin(9600);
  while (!BT) {
    ;
  }
//  Mouse.begin();
//  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  byte startByte;
  if (BT.available()) {
    startByte = byte(BT.read());
    if (startByte==206){
      String message = String(BT.readStringUntil(char(255)));
      digitalWrite(KEYBOARD_LED,HIGH);
//      Keyboard.print(message); not working right now
      digitalWrite(KEYBOARD_LED,LOW);
    }
    else if (startByte==208){
      byte mouse[4];
      BT.readBytes(mouse,4);
//      Mouse.move(mouse[0],mouse[1],mouse[2]);
      digitalWrite(MOUSE_LED,HIGH);
      int buttons = mouse[3];
      if (buttons==1){
//        Mouse.click();
      }
      else if (buttons==2){
//        Mouse.click(MOUSE_MIDDLE);
      }
      else if (buttons==3){
//        Mouse.click(MOUSE_RIGHT);
      }
      else if (buttons==4){
//        Mouse.click();
//        Mouse.click();
      }
      digitalWrite(MOUSE_LED,LOW);
    }
  }
}

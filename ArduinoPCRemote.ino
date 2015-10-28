#include <HID.h>
#include <Keyboard.h>
#include <Mouse.h>
//#include <HID-Project.h>
//#include <HID-Settings.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(2,3); //HC-06

void setup() {
  // put your setup code here, to run once:
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
//      Keyboard.print(message); not working right now
    }
    else if (startByte==208){
      byte mouse[4];
      BT.readBytes(mouse,4);
//      Mouse.move(mouse[0],mouse[1],mouse[2]);
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
    }
  }
}

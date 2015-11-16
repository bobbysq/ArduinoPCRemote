//#include <HID.h>
//#include <Keyboard.h>
//#include <Mouse.h>
#include <HID-Project.h>
#include <HID-Settings.h>
#include <SoftwareSerial.h>

const int TX_PIN=1;
const int RX_PIN=3;
const int KEYBOARD_LED=17;
const int MOUSE_LED=18;

SoftwareSerial BT(RX_PIN,TX_PIN); //HC-06


void setup() {
  // put your setup code here, to run once:
  pinMode(KEYBOARD_LED,OUTPUT);
  pinMode(MOUSE_LED,OUTPUT);
  BT.begin(9600);
  while (!BT) {
    ;
  }
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  byte startByte;
  if (BT.available()) {
    delay(1);
    startByte = byte(BT.read());
    if (startByte==0xCE){
      digitalWrite(KEYBOARD_LED,LOW);
//      String message = String(BT.readStringUntil(char(255)));
      while(BT.available()){
        delay(100);//yay it works for no reason
        Keyboard.write(char(BT.read()));
      }
//      Keyboard.print(BT.readString());
      digitalWrite(KEYBOARD_LED,HIGH);
      BT.flush();
    }
    else if (startByte==0xD0){
      byte mouse[4];
      BT.readBytes(mouse,4);
      Mouse.move(mouse[0],mouse[1],mouse[2]);
      digitalWrite(MOUSE_LED,LOW);
      int buttons = mouse[3]; //1=L,2=M,3=R,4=Doubleclick
      if (buttons==1){
        Mouse.click();
      }
      else if (buttons==2){
        Mouse.click(MOUSE_MIDDLE);
      }
      else if (buttons==3){
        Mouse.click(MOUSE_RIGHT);
      }
      else if (buttons==4){
        Mouse.click();
        Mouse.click();
      }
      digitalWrite(MOUSE_LED,HIGH);
    }
    else if (startByte==0xCF){
      combo();
    }
  }
}

void combo() {
  byte key = byte(BT.read());
  BT.flush();//it'll probably end with an FF
  if (key==1){
    Keyboard.write(KEY_LEFT_CTRL);
  }
  else if (key==2){
    Keyboard.write(KEY_LEFT_GUI);
  }
  else if (key==3){
    Keyboard.write(KEY_LEFT_ALT);
  }
  else if (key==4){
    Keyboard.write(KEY_TAB);
  }
  else if (key==5){
    Keyboard.write(KEY_DELETE);
  }
  else if (key==6){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_DELETE);
    delay(50);
    Keyboard.releaseAll();
  }
  else if (key==7){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('c');
    delay(50);
    Keyboard.releaseAll();
  }
  else if (key==8){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('v');
    delay(50);
    Keyboard.releaseAll();
  }
  else if (key==9){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('f');
    delay(50);
    Keyboard.releaseAll();
  }
}


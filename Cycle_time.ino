#include <Arduino.h>
#include <BUTTON.h>
#include <PINOUT.h>
#include <TM1637Display.h>

#define CLK 11
#define DIO 12

TM1637Display display(CLK, DIO);

#define bt_start 9
#define bt_stop 10

BUTTON btn_start(bt_start);
BUTTON btn_stop(bt_stop);

#define bt_set A4
#define bt_down A5
#define bt_up A6
#define bt_esc A7

BUTTON btn_set(bt_set);
BUTTON btn_down(bt_down);
BUTTON btn_up(bt_up);
BUTTON btn_esc(bt_esc);

// Variables
long unsigned int time = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin();


}

void loop() {
  // put your main code here, to run repeatedly:

}

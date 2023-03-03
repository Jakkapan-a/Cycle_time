#include <Arduino.h>
#include <BUTTON.h>
#include <PINOUT.h>
#include <TM1637Display.h>
#include <EEPROM.h>

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
int cycle_time = 0;
bool is_start = false;
bool is_stop = false;
bool is_recording = false;

// Variables for Timer 0.5 second
unsigned long period_ms = 500;   // 0.5 second
unsigned long last_time_ms = 0;  // last time the LED was updated

// Variables for Timer 1 second
unsigned long period = 1000;  // 1 second
unsigned long last_time = 0;  // last time the LED was updated

// Function Timer 0.5 second
void timer_ms() {
  if (millis() - last_time_ms >= period_ms) {



    last_time_ms = millis();
  } else if (millis() <= 1000) {
    last_time_ms = millis();
  }
}

// Function Timer 1 second
void timer() {
  if (millis() - last_time >= period) {

    if(is_recording){
        cycle_time++;
        display.showNumberDec(cycle_time);
        Serial.println(cycle_time);
      }

    if(is_stop){
      // Save cycle time to sd card to csv file
      

      // Reset cycle time
      cycle_time = 0;
      is_recording = false;
      is_stop = false;
    }
    last_time = millis();
  } else if (millis() <= 1000) {
    last_time = millis();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.setBrightness(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer_ms();
  timer();

  if (btn_start.isPressed() && !is_recording) {
    Serial.println("Start");
    is_recording = true;
    delay(10);
  }

  if(btn_stop.isPressed() && is_recording){
    Serial.println("Stop");
    is_stop = true;
    delay(10);
  }
}

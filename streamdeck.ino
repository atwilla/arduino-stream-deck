#include "Keyboard.h"
#include "Keystroke.h"

const int num_switches = 2, num_btns = 10;

const int switches[] = {PD1, PD0};
bool switch_states[] = {false, false};

const int btns[] = {PD4, PC6, PD7, PE6, PB4, PB5, PB6, PB7, PD6, PC7};
Keystroke *switch_strokes[num_switches], *btn_strokes[num_btns];

// Doing it this way may seem repetitive but allows for more complex keystrokes.
int ss1_arr[] = {KEY_LEFT_ALT, '1'}, ss2_arr[] = {KEY_LEFT_ALT, '2'};
int bs1_arr[] = {KEY_LEFT_ALT, 'm'}, bs2_arr[] = {KEY_LEFT_ALT, 'c'};
int bs3_arr[] = {KEY_F1}, bs4_arr[] = {KEY_F2}, bs5 = {KEY_F4};
int bs6_arr[] = {KEY_LEFT_ALT, '3'}, bs7_arr[] = {KEY_LEFT_ALT, '4'};
int bs8_arr[] = {KEY_LEFT_ALT, '5'}, bs9_arr[] = {KEY_LEFT_ALT, '6'};
int bs10_arr[] = {KEY_LEFT_ALT, '7'};

void toggle_input(const int input_array[], int array_size) {

  for (int i = 0; i < array_size; i++) {
    Keyboard.press(input_array[i]);
  }

  for (int i = 0; i < array_size; i++) {
    Keyboard.release(input_array[i]);
  }
}

void setup() {
  Keyboard.begin();
      
  switch_strokes[0] = new Keystroke(ss1_arr, 2);
  switch_strokes[1] = new Keystroke(ss2_arr, 2);

  btn_strokes[0] = new Keystroke(bs1_arr, 2);

  for (int i = 0; i < num_switches; i++) {
    pinMode(switches[i], INPUT_PULLUP);
  }

  for (int i = 0; i < num_btns; i++) {
    pinMode(btns[i], INPUT_PULLUP);
  }
}

void loop() {

  for (int i = 0; i < num_switches; i++) {

    if ((!digitalRead(switches[i]) && !switch_states[i]) || (digitalRead(switches[i]) && switch_states[i])) {
      switch_states[i] = !switch_states[i];
      toggle_input(switch_strokes[i]->keys_array, switch_strokes[i]->num_keys);
    } /*else {

      if (switch_states[i]) {
        switch_states[i] = false;
      }
    }*/
  }

  // for loop for button inputs here

  for (int i = 0; i < num_btns; i++) {

    if (!digitalRead(btns[i])) {

      for (int j = 0; j < btn_strokes[i]->num_keys; j++) {
        Keyboard.press(btn_strokes[i]->keys_array[j]);
      }
      
    } else {

      for (int j = 0; j < btn_strokes[i]->num_keys; j++) {
        Keyboard.release(btn_strokes[i]->keys_array[j]);
      }
    }
  }

  //delay(10);
}

#include "Keyboard.h"
#include "Keystroke.h"

const int num_switches = 2, num_btns = 10;

const int switches[] = {PD1, PD0};
bool switch_states[] = {true, true};

const int btns[] = {PD4, PC6, PD7, PE6, PB4, PB5, PB6, PB7, PD6, PC7};
Keystroke *switch_strokes[num_switches], *btn_strokes[num_btns];

int ss1_arr[] = {KEY_LEFT_ALT, 'm'}, ss2_arr[] = {KEY_LEFT_ALT, 'c'};
int bs1_arr[] = {KEY_F1}, bs2_arr[] = {KEY_F2}, bs3_arr[] = {KEY_F4};

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

  for (int i = 0; i < num_switches; i++) {
    pinMode(switches[i], INPUT_PULLUP);
  }

  for (int i = 0; i < num_btns; i++) {
    pinMode(btns[i], INPUT_PULLUP);
  }
}

void loop() {

  for (int i = 0; i < num_switches; i++) {

    if (digitalRead(switches[i]) == LOW) {

      if (!switch_states[i]) {
        switch_states[i] = true;
      }
      
    } else {

      if (switch_states[i]) {
        switch_states[i] = false;
      }
    }
  }
  
  /*if (digitalRead(mic_switch) == LOW) {

    // mic_state checks ensure keystroke only sent on change of states.
    if (!mic_state) {
      mic_state = true;
      //toggle_input(keystrokes[0], 2);
    }
    
  } else {

    if (mic_state) {
      mic_state = false;
      //toggle_input(keystrokes[0], 2);
    }
  }

  if (digitalRead(cam_switch) == LOW) {

    if (!cam_state) {
      cam_state = true;
      //toggle_input(keystrokes[1], 2);
    }
    
  } else {

    if (cam_state) {
      cam_state = false;
      //toggle_input(keystrokes[1], 2);
    }
  }*/

  // for loop for button inputs here

  //delay(10);
}

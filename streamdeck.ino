#include "Keyboard.h"
#include "Keystroke.h"

const int num_switches = 2, num_btns = 10;

const int switches[] = {2, 3};
bool switch_states[] = {HIGH, HIGH};
bool btn_states[num_btns] = {HIGH};
int btn_result;

const int btns[] = {4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
Keystroke *switch_strokes[num_switches], *btn_strokes[num_btns];

// Doing it this way may seem repetitive but allows for more complex keystrokes.
int ss1_arr[] = {KEY_LEFT_ALT, '1'}, ss2_arr[] = {KEY_LEFT_ALT, '2'};
int bs1_arr[] = {KEY_LEFT_ALT, 'm'}, bs2_arr[] = {KEY_LEFT_ALT, 'c'};
int bs3_arr[] = {KEY_F1}, bs4_arr[] = {KEY_F2}, bs5_arr[] = {KEY_F4};
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
  btn_strokes[1] = new Keystroke(bs2_arr, 2);
  btn_strokes[2] = new Keystroke(bs3_arr, 1);
  btn_strokes[3] = new Keystroke(bs4_arr, 1);
  btn_strokes[4] = new Keystroke(bs5_arr, 1);
  btn_strokes[5] = new Keystroke(bs6_arr, 2);
  btn_strokes[6] = new Keystroke(bs7_arr, 2);
  btn_strokes[7] = new Keystroke(bs8_arr, 2);
  btn_strokes[8] = new Keystroke(bs9_arr, 2);
  btn_strokes[9] = new Keystroke(bs10_arr, 2);

  for (int i = 0; i < num_switches; i++) {
    pinMode(switches[i], INPUT_PULLUP);
  }

  for (int i = 0; i < num_btns; i++) {
    pinMode(btns[i], INPUT_PULLUP);
  }
}

void loop() {

  // Check switches.
  for (int i = 0; i < num_switches; i++) {

    if ((digitalRead(switches[i]) == LOW && switch_states[i] == HIGH) || (digitalRead(switches[i]) == HIGH && switch_states[i] == LOW)) {
      switch_states[i] = !switch_states[i];
      toggle_input(switch_strokes[i]->keys_array, switch_strokes[i]->num_keys);
      delay(170);
    }
  }

  // Check btns.
  for (int i = 0; i < num_btns; i++) {
    btn_result = digitalRead(btns[i]);

    if (btn_result != btn_states[i]) {

      if (btn_result == LOW) {

        for (int j = 0; j < btn_strokes[i]->num_keys; j++) {
          Keyboard.press(btn_strokes[i]->keys_array[j]);
        }
        delay(10);
        
      } else {

        for (int j = 0; j < btn_strokes[i]->num_keys; j++) {
          Keyboard.release(btn_strokes[i]->keys_array[j]);
        }

      }

      btn_states[i] = !btn_states[i];
    }
  }

}

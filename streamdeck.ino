#include "Keyboard.h"

bool mic_state = true, cam_state = true;
const int mic_switch = PD1, cam_switch = PD0;
const int pins[] = {PD4, PC6, PD7, PE6, PB4, PB5, PB6, PB7, PD6, PC7};
const int keystrokes[3][2] = {{KEY_F1, 'm'}, {KEY_F1, 'c'}, {KEY_F2, 'V'}};

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
  pinMode(mic_switch, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(mic_switch) == LOW) {

    // mic_state checks ensure keystroke only sent on change of states.
    if (!mic_state) {
      mic_state = true;
      toggle_input(keystrokes[0], 2);
      /*Keyboard.press(KEY_F1);
      Keyboard.press('m');
      Keyboard.release(KEY_F1);
      Keyboard.release('m');*/
    }
    
  } else {

    if (mic_state) {
      mic_state = false;
      Keyboard.press(KEY_F1);
      Keyboard.press('m');
      Keyboard.release(KEY_F1);
      Keyboard.release('m');
    }
  }

  if (digitalRead(cam_switch) == LOW) {

    if (!cam_state) {
      cam_state = true;
      Keyboard.press(KEY_F1);
      Keyboard.press('c');
      Keyboard.release(KEY_F1);
      Keyboard.release('c');
    }
    
  } else {

    if (cam_state) {
      cam_state = false;
      Keyboard.press(KEY_F1);
      Keyboard.press('c');
      Keyboard.release(KEY_F1);
      Keyboard.release('c');
    }
  }

  //delay(10);
}

#include "Keyboard.h"

bool mic_state = true, cam_state = true;
const int mic_switch = PD1, cam_switch = PD0;
const int num_buttons = 10;
const int pins[] = {PD4, PC6, PD7, PE6, PB4, PB5, PB6, PB7, PD6, PC7};
const int keystrokes[3][2] = {{KEY_LEFT_ALT, 'm'}, {KEY_LEFT_ALT, 'c'}, {KEY_F2, 'V'}};

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
    }
    
  } else {

    if (mic_state) {
      mic_state = false;
      toggle_input(keystrokes[0], 2);
    }
  }

  if (digitalRead(cam_switch) == LOW) {

    if (!cam_state) {
      cam_state = true;
      toggle_input(keystrokes[1], 2);
    }
    
  } else {

    if (cam_state) {
      cam_state = false;
      toggle_input(keystrokes[1], 2);
    }
  }

  for(int i = 2; i < num_buttons; i++) {

    if (digitalRead(pins[i]) == LOW) {

      for (int j = 0; j < 2; j++) {
        Keyboard.press(keystrokes[i][j]);
      }
        
    } else {

      for (int j = 0; j < 2; j++) {
        Keyboard.release(keystrokes[i][j]);
      }
    } 
  }

  //delay(10);
}

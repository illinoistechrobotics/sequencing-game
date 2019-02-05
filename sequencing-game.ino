// MRDC Sequencing Game
// 5 February 2019
// Developed by Taylor Berg for Illinois Tech Robotics and the MRDC community
// 
// Caveats:
// - We're unsure of whether or not the button order is generated randomly. We assume here that it is.
// - We are also unsure of whether or not a button can be repeated in the sequence. We assume here that they can be repeated.
//
// Wiring/Setup:
// 1. Define the number of rounds and buttons below
// 2. For each button, define a light pin and a button pin in the provided arrays. Make sure the light and button pin are at the same index in both arrays.
// 3. Wire light pins to LEDs to ground via a 1 kOhm resistor.
// 4. Wire button pins to ground via a 1 kOhm resistor.

/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define ROUNDS 4
#define BUTTONS 4
const int light_pins[] = {2, 3, 4, 5};
const int button_pins[] = {8, 9, 10, 11};

void setup() {
  for (int i = 0; i < BUTTONS; i++) {
    pinMode(light_pins[i], OUTPUT);
    pinMode(button_pins[i], INPUT_PULLUP);
    digitalWrite(light_pins[i], LOW);
  }
  // it's kind of random, right?
  randomSeed(analogRead(0));
}

void loop() {
  for (int i = 0; i < ROUNDS; i++) {
    int target = random(BUTTONS);
    digitalWrite(light_pins[target], HIGH);
    bool won = false;
    delay(500);
    while (!won) {
      for (int b = 0; b < BUTTONS; b++) {
        bool state = digitalRead(button_pins[b]);
        if (state == LOW) {
          if (b != target) {
            digitalWrite(light_pins[b], LOW);
            digitalWrite(light_pins[target], LOW);
            delay(5000);
            while (!digitalRead(button_pins[b]));
            return;
          } else {
            won = true;
            digitalWrite(light_pins[target], LOW);
            break;
          }
        }
      }
      while (!digitalRead(button_pins[target])) ;
    }
    digitalWrite(light_pins[target], LOW);
  }

  for (int l = 0; l < 5; l++) {
    for (int i = 0; i < BUTTONS; i++) {
      digitalWrite(light_pins[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < BUTTONS; i++) {
      digitalWrite(light_pins[i], LOW);
    }
    delay(500);
  }
}

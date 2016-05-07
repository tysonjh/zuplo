/*
 * @author ("Tyson Hamilton" <tyson@planetzuplo.com")
 * This program demonstrates a very simple single dimension theremin.
 * It uses a single Ultrasonic Ranging Module (HC-SR04) for measuring
 * the distance of the hand and a piezoelectric buzzer for audio output.
 * This program is targeted at a Arduino Metro Mini but should work with
 * any of the Arduino Uno derivatives.
 *
 * Copyright (C) 2016 Tyson Hamilton
 *
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

// A compiler macro for instrumenting the application with debug
// output to the Serial port.
//#define _DEBUG

#include <NewPing.h>
#include <NewTone.h>

#define PIN_SPEAKER 3 // PWM pin
#define PIN_PING_TRIG 10
#define PIN_PING_ECHO 11
#define MAX_DISTANCE 30
#define NOTE_DURATION_MS 50
#define MAX_FREQUENCY 1000
#define MIN_FREQUENCY 100

unsigned long previousMillis = 0;
NewPing sonar(PIN_PING_TRIG, PIN_PING_ECHO, MAX_DISTANCE);

// Measures the distance (cm) of the hand and plays a tone if
// within range. If the distance is not in range the tone is stopped.
void playTone() {
  int cm = sonar.ping_cm();

  #ifdef _DEBUG
  Serial.print("Distance of hand: ");
  Serial.println(cm);
  #endif

  if(cm < MAX_DISTANCE && cm > 0) {
    NewTone(PIN_SPEAKER, frequency(cm));
  } else {
    #ifdef _DEBUG
    Serial.println("Not playing tone.");
    #endif
    
    noNewTone();
  }
}

// Calculate the frequency of the tone to play as a function of distance.
int frequency(int cm) {
  int f = MAX_FREQUENCY * ((float(1) - float(cm) / MAX_DISTANCE));

  #ifdef _DEBUG
  Serial.print("Frequency to play: ");
  Serial.println(f);
  #endif

  return f;
}

// This method is called once during startup. It contains all pin
// initializations, including the Serial output for debugging if defined.
void setup() {
  #ifdef _DEBUG
  Serial.begin(115200);
  Serial.println("Begin setup");
  #endif

  pinMode(PIN_PING_TRIG, OUTPUT);
  pinMode(PIN_PING_ECHO, INPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
}

// The main loop of the program.
void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= NOTE_DURATION_MS) {
    previousMillis = currentMillis;
    playTone(); 
  }
}

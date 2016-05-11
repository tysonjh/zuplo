# Theremin

A basic theremin that uses an ultrasonic ranging module to control frequency. 

## Components

* Arduino Metro Mini (or Uno)
* 4 male-male jumpers
* piezoelectric buzzer
* ultrasonic ranging module (HC-SR04)
* breadboard

## Software

* theremin.c (in this repository)
* [NewPing library](http://playground.arduino.cc/Code/NewPing)
* [NewTone library](https://bitbucket.org/teckel12/arduino-new-tone/wiki/Home)

## Setup

1. prepare circuit as shown in schematic.jpg (optionally add a resistor for the buzzer)
2. upload the code to the metro mini (NewPing, NewTone libraries required)
3. wave your hand within 20cm of the ultrasonic ranging module
4. go on tour with your new instrument
/*
 * main.cpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: Mauricio
 */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Print.h>
#include <WString.h>

const byte TYPE_INPUT_OUTPUT = 0;
const byte TYPE_LEG_RGB = 1;

byte incomingByte[6] = {0,0,0,0,0,0};
byte curByte = 0;
int index = 0;
const byte INITIAL_MESSAGE = 99;

const char* MSG_INIT = "{";
const char* MSG_END = "}";
const char* MSG_SEPARATOR = ",";


int led = 13;

int redPin = 9;
int greenPin = 10;
int bluePin = 11;


// the setup routine runs once when you press reset:
void setup() {
    Serial.begin(9600);
  // initialize the digital pin as an output.
    pinMode(led, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  //digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  //byte currentRead = digitalRead(led);
  //printSerial(led, currentRead);
  //delay(1000);               // wait for a second
  //digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  //currentRead = digitalRead(led);
  //printSerial(led, currentRead);
  delay(100);               // wait for a second

  int serial = 0;

   //Serial.println("[DEBUG] 1");
   // upstream
   while (Serial.available() > 0) {
	   serial = 1;
	   //Serial.println(" [DEBUG] 2 - while");
      curByte = Serial.read();
      String myString = String(curByte);
      //Serial.println(" [DEBUG] 3 - curByte " + myString);
      if (curByte==INITIAL_MESSAGE) {
    	  //Serial.println(" [DEBUG] 4 curByte==INITIAL_MESSAGE");
        for (int i=0;i<6;i++) {
        	//Serial.println(" [DEBUG] 5 for " + i);
            incomingByte[i]=0;
        }
        //Serial.println(" [DEBUG] 6 ");
        index=0;
      }
      else {
    	  //Serial.println(" [DEBUG] 7 ");
        incomingByte[index] = curByte;
        index++;
      }
   }

   if (serial==1) {
	   String myString2 = String(incomingByte[0]);
	   myString2 += "," + String(incomingByte[1]);
	   myString2 += "," + String(incomingByte[2]);
	   myString2 += "," + String(incomingByte[3]);
	   myString2 += "," + String(incomingByte[4]);
	   Serial.println("Recebido " + myString2);
	   if (index == 5) {
		  if (incomingByte[1]==TYPE_INPUT_OUTPUT) {
			pinMode(incomingByte[0], OUTPUT);
			digitalWrite(incomingByte[0], incomingByte[4]);
			//printSerial(incomingByte[0], digitalRead(incomingByte[0]));
			Serial.print(MSG_INIT);
			Serial.print(incomingByte[0], DEC);
			Serial.print(MSG_SEPARATOR);
			Serial.print(digitalRead(incomingByte[0]), DEC);
			Serial.print(MSG_END);

		  }
		  else if (incomingByte[1]==TYPE_LEG_RGB) {
			   analogWrite(redPin, incomingByte[2]);
			   analogWrite(greenPin, incomingByte[3]);
			   analogWrite(bluePin, incomingByte[4]);
		  }
	   }
   }
}

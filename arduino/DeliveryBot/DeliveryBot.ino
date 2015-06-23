#include <QueueList.h>
#include "CONSTANTS.h"
#include "States.h"
#include "Queue.h"
#include "Drive.h"
#include <ros.h>
#include <std_msgs/Int16.h> // Incoming type
#include <std_msgs/String.h> // Outgoing type

void setup()
{
  //loadCommandQ();
  
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(PWML, OUTPUT);
  pinMode(PWMLR, OUTPUT);
  pinMode(PWMR, OUTPUT);
  pinMode(PWMRR, OUTPUT);
  digitalWrite(PWML,LOW);
  digitalWrite(PWMLR,LOW);
  digitalWrite(PWMR,LOW);
  digitalWrite(PWMRR,LOW);
  attachInterrupt(0, pulseL, RISING);//interrupt on pin2
  attachInterrupt(1, pulseR, RISING); //interrupt on pin3
  nh.initNode();
  nh.subscribe(instructionListener);
  nh.advertise(arduinoListener);
}

//Main Loop
void loop()
{
   //checking for messages 
   if(finished) {
    str_msg.data = doneMsg;
    arduinoListener.publish( &str_msg );
    finished = false;
  }
  
  nh.spinOnce();
  
  //delay(250);
  if(interruptL == true && interruptR == true){
    Serial.print("Left diff : ");
    Serial.println(diffL,5);
    Serial.print("Right diff: ");
    Serial.println(diffR,5);
    adjustOffsets();
    Serial.print("offsetL: ");
    Serial.println(offsetL,5);
    Serial.print("offsetR: ");
    Serial.println(offsetR,5);
  }
  stateControl();
}














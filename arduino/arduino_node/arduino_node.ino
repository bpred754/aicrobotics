/*
 * Arduino Node
 */

#include <ros.h>
#include <std_msgs/Int16.h> // Incoming type
#include <std_msgs/String.h> // Outgoing type

ros::NodeHandle nh;

std_msgs::String str_msg;
char doneMsg[5] = "DONE";
boolean finished = false;

void messageCb( const std_msgs::Int16& toggle_msg){
  int instruction = (int)toggle_msg.data;
  
  switch(instruction){
    case -1:
      turnLeft();
     case -2:
       turnRight();
     case -3:
       reverse();
      case -100:
        stopExecution();
     default:
       goStraight(instruction);
  }
}

ros::Subscriber<std_msgs::Int16> instructionListener("instruction_listener", &messageCb );
ros::Publisher arduinoListener("arduino_response", &str_msg);

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(instructionListener);
  nh.advertise(arduinoListener);
}

void loop()
{
  if(finished) {
    str_msg.data = doneMsg;
    arduinoListener.publish( &str_msg );
    finished = false;
  }
  
  nh.spinOnce();
  delay(1);
}

void goStraight(int amount) {
  // Straight logic
  for(int i = 0; i < amount; i++) {
   digitalWrite(13, HIGH-digitalRead(13));  // blink the led 
   delay(500);
  }
  
  finished = true;
}

void turnLeft() {
  // Turn left logic
  for(int i = 0; i < 20; i++) {
    digitalWrite(13, HIGH-digitalRead(13));  // blink the led 
    delay(100);
  }
  
  finished = true;
}

void turnRight() {
  // Turn right logic
  for(int i = 0; i < 20; i++) {
    digitalWrite(13, HIGH-digitalRead(13));  // blink the led 
    delay(100);
  }
  
  finished = true;
}

void reverse() {
  // Reverse logic
  finished = true;
}

void stopExecution() {
  
}

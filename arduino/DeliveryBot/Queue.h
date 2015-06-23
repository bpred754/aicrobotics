  
  #ifndef __QUEUE_H_INCLUDED__
  #define __QUEUE_H_INCLUDED__
  #include "CONSTANTS.h"
  #include <ros.h>
  #include <std_msgs/Int16.h> // Incoming type
  #include <std_msgs/String.h> // Outgoing type
  
  ros::NodeHandle nh;
  std_msgs::String str_msg;
  char doneMsg[5] = "DONE";
  boolean finished = false;
  
  void messageCb( const std_msgs::Int16& toggle_msg);
  
  ros::Subscriber<std_msgs::Int16> instructionListener("instruction_listener", &messageCb );
  ros::Publisher arduinoListener("arduino_response", &str_msg);
  
  //int commands[] = {14, rightCom, 8,rightCom,14,rightCom,8,rightCom};//temporary array to fill queue
  int commands[] = {-1, 4, -2, 10, 5,};//temporary array to fill queue
  QueueList <int> commandQ;
  void loadCommandQ();//temporary method to fill temp array into queue

  //implementation
  void messageCb( const std_msgs::Int16& toggle_msg){
    int instruction = (int)toggle_msg.data;
    
    switch(instruction){
      case -1:
        commandQ.push(leftCom);
        //turnLeft();
       case -2:
         commandQ.push(rightCom);
         //turnRight();
       case -3:
         commandQ.push(leftCom);
         commandQ.push(leftCom);
         //reverse();
       case -100:
         commandQ.push(eStop);
          //stopExecution();
       default:
         commandQ.push(instruction);
         //goStraight(instruction);
    }
  }
  
  void loadCommandQ(){
    
    int command;
    for (int x; x<  (sizeof(commands) / sizeof(commands[0])); x++){
      command = commands[x]; 
      commandQ.push(command);
    }
  }
  #endif

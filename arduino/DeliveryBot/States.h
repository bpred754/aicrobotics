  
  #ifndef __STATES_H_INCLUDED__
  #define __STATES_H_INCLUDED__
  #include "CONSTANTS.h"
  #include "Drive.h"
  #include "Queue.h"
  
  extern states state = next;
  states getNextState();//get state from the queued commands
  void stateControl();// run correct state and move to the next
  
  //implementation
  void stateControl(){
    
    switch (state){
      case eStop  :
        //come to gradual stop at the one foot mark? finish the turn?
        break;
      case forward:
        Serial.println("running forward state");
        if(forwardControl()){
          state = next;
        }
        break;
      case left   :
        Serial.println("running left state");
        if(steerControl()){
          state = next;
        }
        break;
      case right  :
        Serial.println("running right state");
        if(steerControl()){
          state = next;
        }
        break;
      default     :
        if(!commandQ.isEmpty()){
          state = getNextState();
          Serial.print("State is ");
          Serial.println(state);
        }
        break;
    }   
  }
  
  states getNextState(){
    int command;
    flag1 = initialize;
    resetOffsets();
    command = commandQ.pop();
    delay(500);
    switch(command){
      case stopCom  :
        return eStop;
      case leftCom  :
        distance = PI * wheelBaseDiameter/4;//quarter turn
        return left;
      case rightCom :
        distance = PI * wheelBaseDiameter/4;
        return right;
      default  :
        if(command > 0){
          distance = command*12;//set distance in inches
          return forward;
        }else{
          return next;
        }
    }
  }

  #endif

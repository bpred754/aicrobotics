  
  #ifndef __DRIVE_H_INCLUDED__
  #define __DRIVE_H_INCLUDED__
  #include "CONSTANTS.h"
  #include "States.h"
  
  volatile long diffL;
  volatile long diffR;
  volatile long timeL = 0;
  volatile long timeR = 0;
  volatile long tempL;
  volatile long tempR;
  volatile boolean interruptL = false;
  volatile boolean interruptR = false;
  enum innerStates {initialize, start, run, slowDown};
  int countL;
  int countR;
  int distance = 0;//measured in inches
  int duration = 0;
  innerStates flag1 = initialize;//is reset to init inside getNextState(), used inside each state to control inner states
  float offsetL = 1.0;
  float offsetR = 1.0;
  
  void resetCounters();//counters track distance traveled
  int getDistance();//returns distance travelled in inches since last resetCounters()
  boolean forwardControl();//controls speed up, distance and slow down, returns true when state is done
  boolean steerControl();//controls speed up and slow down, returns true when state is done
  void pulseL();//interrupt routine for encoder
  void pulseR();//interrupt routine for encoder
  void resetInterrupts();//called after encoder information is used to make sure that both values are new next time
  void adjustOffsets();//evaluate if motors need speeded up or down//balance them based on time
  void forwardDrive();//sets motors to drive straight
  void steerDrive();//calls right or leftDrive based on state that it is in
  void leftDrive();//sets motors to turn left
  void rightDrive();
  void drive(int durationL, int durationR,int durationLR, int durationRR);//sets the motor drive duration, called by right, left, and forwardDrive
  void shutOffDrive();//sets all pins on the h bridges to low
  void resetOffsets();//sets the offset values back to 1.0, each command starts back at 1.0 
  
  //implementation
  boolean steerControl(){
    switch(flag1){
      case initialize:
        resetCounters();
        duration = minTurnDuration;
        steerDrive();
        flag1 = start;
        return false;
      case start:
        if((duration += durationIncrease) > maxTurnDuration){//set duration to next duration and test
           duration = maxTurnDuration;//adding duration made it larger than max so make it max
           flag1 = run; //switch to state 2
        }
        steerDrive(); 
        return false;
      case run:
        steerDrive();
        if(distance - getDistance() < FOOT/2)//keep running until last 6 inches   
          flag1 = slowDown;//switch to state 3
      return false;    
      case slowDown:
        if((duration -= durationIncrease) > minTurnDuration){
          steerDrive();
          return false;
        }else{
          duration = minTurnDuration;
          if(distance-getDistance()<=0){
            shutOffDrive();
            return true;  
          }else{
            steerDrive();
            return false;
          } 
        }
    } 
  }
  
  boolean forwardControl(){
    switch(flag1){
      case initialize:
        resetCounters();//sets distance traveled to 0
        duration = minDuration;//get initial duration
        forwardDrive();//set motors to duration
        flag1 = start;//switch to state 1
        return false;
      case start://probably need to pull micros and only perform at intervals or based on count
        if((duration += durationIncrease) > maxDuration){//set duration to next duration and test
           duration = maxDuration;//adding duration made it larger than max so make it max
           flag1 = run; //switch to state 2
        }
        forwardDrive();
        return false;
      case run:
        forwardDrive();
      
        if(distance - getDistance() < FOOT)//keep running until last foot   
          flag1 = slowDown;//switch to state 3
      return false;    
      case slowDown:
        if((duration -= durationIncrease) > minDuration){
          forwardDrive();
          return false;
        }else{
          duration = minDuration;
          if(distance-getDistance()<=0){
            shutOffDrive();  
            return true;
          }else{
            forwardDrive();
            return false;
          }
        }
    } 
  }
  
  //Set all the pwm values to 0
  void shutOffDrive(){
    analogWrite(PWMR,0);
    analogWrite(PWML,0);
    analogWrite(PWMRR,0);
    analogWrite(PWMLR,0);
  }
  void resetCounters(){
   countL = 0;
   countR = 0; 
  }
  
  int getDistance(){
    int distance = countL/countPerInch;
    return distance;  
  }
  
  //sets the pwm values
  void drive(int durationL, int durationR, int durationLR, int durationRR){
    analogWrite(PWMR,durationR*offsetR);
    analogWrite(PWML,durationL*offsetL);
    analogWrite(PWMRR,durationRR*offsetR);
    analogWrite(PWMLR,durationLR*offsetL);
  }
  
  void steerDrive(){
    extern states state;
     if(state == left){
      leftDrive();
     }else{
      rightDrive();
     } 
  }
  
  void rightDrive(){
    drive(duration, 0, 0, duration); 
  }
  
  void leftDrive(){
    drive(0, duration, duration, 0); 
  }
  void forwardDrive(){
    drive(duration,duration, 0, 0); 
  }
  
  void pulseL()
  {  
    tempL= micros();
    diffL = tempL-timeL;
    timeL = tempL;
    interruptL = true;
    countL++;
  }
  void pulseR()
  {
    tempR = micros();
    diffR = tempR-timeR;
    timeR = tempR;
    interruptR = true;
    countR++;
  }
  void resetInterrupts(){
     interruptL = false;
     interruptR = false; 
  
  }
  
  void resetOffsets(){
    offsetL = 1.0;
    offsetR = 1.0;  
  }
  
  void adjustOffsets(){
    if(distance>=1){
      if(diffL > diffR + difference){
        
        if(offsetL < 1.0){
          offsetL = ((float)diffL/diffR) * offsetL;
          if(offsetL > 1.0)offsetL = 1.0;
        } 
        else{
          offsetR= ((float)diffR/diffL) * offsetR;
        }
      }
      if(diffR > diffL + difference){
        if(offsetR < 1.0){
          offsetR = ((float)diffR/diffL) * offsetR;
          if(offsetR > 1.0) offsetR = 1.0;
        } 
        else{
          offsetL = ((float)diffL/diffR) * offsetL;  
        }
      }
    }
    resetInterrupts();
  }
  
  #endif

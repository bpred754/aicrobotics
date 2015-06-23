#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

enum states {eStop, forward, left, right, next};
const int PWML = 10;
const int PWMR = 9;
const int PWMRR= 11;//right reverse
const int PWMLR= 6;//left reverse
const int durationIncrease = 20;
const int increase = 1;
const int minDuration = 100;
const int minTurnDuration = 175;
const int maxTurnDuration= 240;
const int maxDuration = 255;
const int offDuration = 0;
const int pulsePerRevolution = 464;
const int inchPerRevolution = 11;
const int countPerInch = pulsePerRevolution/inchPerRevolution;
const int wheelBaseDiameter = 14;//inches
const int led = 13;//board led
const int FOOT = 12;
const int difference = 20;//how many microseconds difference to ignore.
//commands from ROS, forward will be a > 0 int that will specifiy the distance 
const int leftCom = -1;
const int rightCom = -2;
const int stopCom = 0;

#endif

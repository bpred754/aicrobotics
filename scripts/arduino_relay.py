#!/usr/bin/env python

import rospy # ROS-Python library
from std_msgs.msg import String # Message type
from std_msgs.msg import Int16 # Message type
import Queue

# Global variables
publisher = None
sentMessage = None
instructions = None

def init():
    global publisher 
    global sentMessage
    global instructions 

    sentMessage = False
    instructions = Queue.Queue()

    # This node will publish to 'instruction_listener' topic using Int16 type.
    # Queue size limits the amount of messages sent to the topic if they are not being read
    publisher = rospy.Publisher("instruction_listener", Int16, queue_size=10)

    # This node will subscribe to the instructions_list topic and send the String messages to the parseInstructions function
    rospy.Subscriber("instructions_list", String, parseInstructions)

    # This node will subscribe to the arduino_response topic and send the String messages to the parseArduinoResponse function
    rospy.Subscriber("arduino_response", String, parseArduinoResponse) 

    # Initialize node
    rospy.init_node('relay', anonymous=True)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

def parseInstructions(data):
    rospy.loginfo("Parsing instructions: %s", data.data)

    global instructions
    instructionString = data.data

    if(instructionString != "stop"):
        # Parse instructions string and add each instruction to the instruction queue
        instructionsArray = instructionString.split(",")
        for i in range(len(instructionsArray)):
            instructions.put(instructionsArray[i])
    else:
        with instructions.mutex:
            instructions.queue.clear()
            instructions.put(-100)

    # Send first instruction
    sendInstruction()

def parseArduinoResponse(data):
    rospy.loginfo("Parsing arduino response: %s", data.data)

    # Send next instruction once confirmation is received from aruduino
    sendInstruction()

def sendInstruction():
    global instructions
    instruction = instructions.get()
    
    rospy.loginfo("Publishing %s to instruction_lister", instruction)
    if(not rospy.is_shutdown()):
        publisher.publish(int(instruction))

if __name__ == '__main__':
    init()
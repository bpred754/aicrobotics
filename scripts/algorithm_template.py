#!/usr/bin/env python

import rospy # ROS-Python library
from std_msgs.msg import String # Message type

# Global vars
publisher = None
sentMessage = None

def init():
    rospy.loginfo('Initializing YOUR_NODE_NAME_HERE)')

    # This node will publish to 'YOUR_TOPIC_NAME_HERE' topic using String type.
    # Queue size limits the amount of messages sent to the topic if they are not being read
    global publisher 
    publisher = rospy.Publisher("YOUR_TOPIC_NAME_HERE", String, queue_size=10) 

    # Initialize node with name 'YOUR_NODE_NAME_HERE'
    rospy.init_node('YOUR_NODE_NAME_HERE', anonymous=True)

    global sentMessage 
    sentMessage = False

def runAlgorithm():
    # Place algorithm here
    instructions = "10,-1,20,-2" # go straight 10, turn left, go straight 20, go right
    relay(instructions)

def relay(instructions):
    global sentMessage
    r = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        if sentMessage == False:
            rospy.loginfo('Publishing to YOUR_TOPIC_NAME_HERE')
            publisher.publish(instructions)
            sentMessage = True
        r.sleep()

if __name__ == '__main__':
    try:
        init()
        runAlgorithm()
        
    # Thrown by rospy.sleep() and rospy.Rate.sleep() methods when Ctrl-C is pressed or your Node is otherwise shutdown. 
    # The reason this exception is raised is so that you don't accidentally continue executing code after the sleep(). 
    except rospy.ROSInterruptException: pass

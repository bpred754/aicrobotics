#!/usr/bin/env python

import rospy # ROS-Python library
from std_msgs.msg import String # Message type

# Global vars
publisher = None
sentMessage = None

def init():
    rospy.loginfo('Initializing stop_node)')

    global publisher
    global sentMessage 

    # This node will publish to 'instructions_list' topic using String type.
    # Queue size limits the amount of messages sent to the topic if they are not being read
    publisher = rospy.Publisher("instructions_list", String, queue_size=10) 

    # Initialize node with name 'instruction_algorithm'
    rospy.init_node('stop_node', anonymous=True)

    sentMessage = False

def relay():
    global sentMessage
    r = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        if sentMessage == False:
            rospy.loginfo('Publishing stop command to instructions_list topic')
            publisher.publish('stop')
            sentMessage = True
        r.sleep()

if __name__ == '__main__':
    try:
        init()
        relay()
        
    # Thrown by rospy.sleep() and rospy.Rate.sleep() methods when Ctrl-C is pressed or your Node is otherwise shutdown. 
    # The reason this exception is raised is so that you don't accidentally continue executing code after the sleep(). 
    except rospy.ROSInterruptException: pass

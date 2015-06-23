#!/usr/bin/env python

import rospy # ROS-Python library
from std_msgs.msg import String # Message type

# Global vars
publisher = None
sentMessage = None

def init():
    rospy.loginfo('Initializing user_control node')

    # This node will publish to instructions_list topic using String type.
    # Queue size limits the amount of messages sent to the topic if they are not being read
    global publisher 
    publisher = rospy.Publisher("instructions_list", String, queue_size=10)

    # Initialize node with name user_control
    rospy.init_node("user_control", anonymous=True)

    global sentMessage 
    sentMessage = False

def relay(instructions):
    rospy.loginfo('Publishing to instructions_list ' + instructions)
    publisher.publish(instructions)


if __name__ == '__main__':
    try:
        init()

        while not rospy.is_shutdown():
            rospy.loginfo("Enter Command")
            command = raw_input()
            rospy.loginfo("INPUT: " + command)
            relay(command)
        
    # Thrown by rospy.sleep() and rospy.Rate.sleep() methods when Ctrl-C is pressed or your Node is otherwise shutdown. 
    # The reason this exception is raised is so that you don't accidentally continue executing code after the sleep(). 
    except rospy.ROSInterruptException: pass

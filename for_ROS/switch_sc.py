#! /usr/bin/env python

from subprocess import call
import rospy
from std_msgs.msg import String

initial_state = 1

def timer_cb(timer):
    # global data, data_hist
    global initial_state
    
    if not initial_state:
        print("STARTING SERVER FROM ROS")
        initial_state+=1
        rc = call("/home/tyjo/projects/sop/ns3/NS3/NS3/build/bin/server")    
        print("COMPLETED SERVER ACTION FROM ROS")

    else:
        rospy.sleep(3)
        print("STARTING CLIENT FROM ROS")
        initial_state-=1
        rc = call("/home/tyjo/projects/sop/ns3/NS3/NS3/build/bin/client")
        print("COMPLETED CLIENT ACTION FROM ROS")
def set_data(msg):
    pass

if __name__ == "__main__":
    sub = rospy.Subscriber("/mydata" , String, set_data)
    rospy.init_node("NS3_integration")
    rospy.Timer(rospy.Duration(10), timer_cb)
    rospy.spin()




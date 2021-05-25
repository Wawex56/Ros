#!/usr/bin/env python3 
#-*- coding: utf-8 -*-

import rospy 
from sensor_msgs.msg import LaserScan

def func(data):
    print(data) 

def stopit():
    rospy.loginfo('Stopped!')


if __name__ == "__main__":
    rospy.init_node('lidar_data',anonymous=True)
    rospy.loginfo('CTRL+C for shutting down')
    rospy.on_shutdown(stopit)

    rospy.Subscriber('/mybot/laser/scan', LaserScan, func)
    rospy.spin() 

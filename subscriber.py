#!/usr/bin/env python3 
# -*- coding: UTF-8 -*-

import rospy 
from ilk_paket.msg import drone 
import yaml

def func(data):
    rospy.loginfo('alinan veriler: (%d,%s,%d,%2f,%2f)',data.id,data.name,data.speed,data. temperature,data.battery)
    
rospy.init_node('subscriber',anonymous=True)
rospy.Subscriber('drone_topic',drone,func)
rospy.spin()

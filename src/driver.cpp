#ifndef DRIVER_NODE
#define DRIVER_NODE

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "ros/ros.h"

#include "message.cpp"

int main(int argc, char **argv)
{
    ms:: message("Driver node created.", 0);
    ros::init(argc, argv, "driver");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    ros::Rate loop_rate(10);
    while(1) {

    }
}

#endif

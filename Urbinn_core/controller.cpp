#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "ros/ros.h"

void *controller_node()
{
    cout << "Main: program exiting." << endl;
    ros::init(argc, argv, "driver");
    ros::NodeHandle n;
    //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);
    while(1)
    {

    }
    pthread_exit(NULL);
}

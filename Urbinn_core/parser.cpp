#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "ros/ros.h"

void *parser_node()
{
    cout << "Thread parser creaded." << endl;
    ros::init(argc, argv, "parser");
    ros::NodeHandle n;
    //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);
    while(1)
    {

    }
    pthread_exit(NULL);
}

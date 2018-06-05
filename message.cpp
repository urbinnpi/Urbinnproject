#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ostream>
#include <iterator>

namespace ms
{
using namespace std;

void message(std::string string)
{
        stringstream ss;
		std_msgs::String msg;
		
        for(std::string::size_type i = 0; i < string.size(); ++i)
        {
        ss << string[i];
        }
		
		msg.data = ss.str();

        ROS_INFO("%s", ss.str());
		ROS_INFO("%s", msg.data.c_str());
};

void message(const communication::msgStruct msg, std::string topic)
{
	stringstream ss;
	
        for(std::string::size_type i = 0; i < topic.size(); ++i)
        {
        ss << topic[i];
        }
	ss << " : ";
	
        for(uint8_t i = 0; msg.dl > i; i++)
        {
        ss << msg.data[i];
        }
	
        ROS_INFO("%s", ss.str());
};

}

#endif

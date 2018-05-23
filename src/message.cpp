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

void message(string sin, int iin)
{
    std_msgs::String msg;
    //string num =  std::to_string(iin);;
    string num = "0";
    stringstream ss;
    for(std::string::size_type i = 0; i < sin.size(); ++i) {
        ss << sin[i];
    }
    if (iin !=0)
    {
        for(std::string::size_type i = 0; i < num.size(); ++i) {
            ss << num[i];
        }
    }
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());
};

}

#endif

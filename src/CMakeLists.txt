cmake_minimum_required(VERSION 2.8.3)
project(urbinn)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
#generate_messages(DEPENDENCIES)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

#add_executable(talker publisher.cpp)
#target_link_libraries(talker ${catkin_LIBRARIES})
#add_dependencies(talker beginner_tutorials_generate_messages_cpp)


add_executable(driver driver.cpp)
target_link_libraries(driver ${catkin_LIBRARIES})

add_executable(controller controller.cpp)
target_link_libraries(controller ${catkin_LIBRARIES})

add_executable(parser parser.cpp)
target_link_libraries(parser ${catkin_LIBRARIES})


#add_executable(listener subscriber.cpp)
#target_link_libraries(listener ${catkin_LIBRARIES})
#add_dependencies(listener beginner_tutorials_generate_messages_cpp)

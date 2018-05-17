#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
	void receiveInfo(); // Callback van topic ParserController1
private:
	// Returntype bij gebruik ROS is void!
	int transmitMsg(/* messageStruct */); // Publish op topic ControllerDriver1
	// void steer, enz.
};

#endif // CONTROLLER_H
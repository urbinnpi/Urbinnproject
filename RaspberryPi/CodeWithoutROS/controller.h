#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
	void receiveInfo(); // Callback van topic ParserController1
	// Returntype bij gebruik ROS is void! Functie is ook private
	int transmitMsg(/* messageStruct */); // Publish op topic ControllerDriver1
private:
	// void steer, enz.
};

#endif // CONTROLLER_H
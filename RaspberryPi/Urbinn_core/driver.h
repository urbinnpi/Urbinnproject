#ifndef DRIVER_H
#define DRIVER_H


class Driver{
public:
    Driver(){}
    ~Driver(){}
        virtual void readinput() =0;
        virtual void receivemsg()=0;
        virtual void transmitMsg()=0;
  private:

}
#endif // DRIVER_H

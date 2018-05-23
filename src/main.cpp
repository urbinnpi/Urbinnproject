#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

#include "controller.cpp"
#include "driver.cpp"
#include "parser.cpp"
#include "message.cpp"

using namespace std;
using namespace ms;

int main (int argc, char **argv) {
    int error;
    int i;
    pthread_t threadCon, threadDriv, threadPar;
    pthread_attr_t attr;
    void *status;

    // Initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Creating threads
    ms::message("creating thread controller", 0);
    error = pthread_create(&threadCon, NULL, controller_node, NULL);
    if (error)
    {
        ms::message("Error:unable to create thread controller: ", error);
        exit(-1);
    }

    ms::message("creating thread driver", 0);
    error = pthread_create(&threadDriv, NULL, driver_node, NULL);
    if (error)
    {
        ms::message("Error:unable to create thread driver: " , error);
        exit(-1);
    }

    ms::message("creating thread parser", 0);
    error = pthread_create(&threadPar, NULL, parser_node, NULL);
    if (error)
    {
        ms::message("Error:unable to create thread parser: " , error);
        exit(-1);
    }

    // free attribute and wait for the other threads
    pthread_attr_destroy(&attr);

    // joining threads
    error = pthread_join(threadCon, &status);
    if (error) {
        ms::message("Error:unable to join controller: ", error);
        exit(-1);
    }

    error = pthread_join(threadDriv, &status);
    if (error) {
        ms::message("Error:unable to join driver: ", error);
        exit(-1);
    }

    error = pthread_join(threadPar, &status);
    if (error) {
        ms::message("Error:unable to join parser: ", error);
        exit(-1);
    }

    //message("  exiting with status :", status);
    ms::message("program exiting.", 0);
    pthread_exit(NULL);
}

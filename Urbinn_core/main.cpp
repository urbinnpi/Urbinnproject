#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

#include "controller.cpp"
#include "driver.cpp"
#include "parser.cpp"

using namespace std;

int main () {
    int error;
    int i;
    pthread_t threadCon, threadDriv, threadPar;
    pthread_attr_t attr;
    void *status;

    // Initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Creating threads
    cout << "creating thread controller, " << endl;
    error = pthread_create(threadCon, NULL, controller_node, NULL);
    if (error)
    {
        cout << "Error:unable to create thread controller: ," << error << endl;
        exit(-1);
    }

    cout << "creating thread driver, " << endl;
    error = pthread_create(threadDriv, NULL, driver_node, NULL);
    if (error)
    {
        cout << "Error:unable to create thread driver: ," << error << endl;
        exit(-1);
    }

    cout << "creating thread parser, " << endl;
    error = pthread_create(threadPar, NULL, parser_node, NULL);
    if (error)
    {
        cout << "Error:unable to create thread parser: ," << error << endl;
        exit(-1);
    }

    // free attribute and wait for the other threads
    pthread_attr_destroy(&attr);

    // joining threads
    error = pthread_join(threadCon, &status);
    if (error) {
        cout << "Error:unable to join controller: ," << error << endl;
        exit(-1);
    }

    error = pthread_join(threadDriv, &status);
    if (error) {
        cout << "Error:unable to join driver: ," << error << endl;
        exit(-1);
    }

    error = pthread_join(threadPar, &status);
    if (error) {
        cout << "Error:unable to join parser: ," << error << endl;
        exit(-1);
    }

    cout << "  exiting with status :" << status << endl;
    cout << "program exiting." << endl;
    pthread_exit(NULL);
}

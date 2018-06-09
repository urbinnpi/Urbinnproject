/*
 * stateMachine.h
 *
 * Created: 17-5-2018 15:51:15
 *  Author: lucan
 */


#ifndef stateMachine_H_
#define stateMachine_H_

#define STATE_QUEUE_SIZE 10 // size of the state queue

typedef enum {
	ST_IDLE, // need to be first, 0 == nothing to do
	ST_READ_UART,
	ST_READ_CAN,
	ST_ADC_DONE,
	ST_POLL_SENSOR
} state_t;


extern volatile state_t state_queue[STATE_QUEUE_SIZE];

void done();
void addState(state_t s);
void init_system();




#endif /* stateMachine_H_ */
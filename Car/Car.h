/*
 * Car.h
 *
 *  Created on: Jun 3, 2013
 *      Author: chris
 */

#ifndef CAR_H_
#define CAR_H_


#define MSG_SIZE 20


class Car {
private:

	char* direction;
	bool inTunnel;
	int timer;
	int loops;



public:
	static const long int TO_NORTH = 1;
	static const long int TO_SOUTH = 2;
	int messageQueueID ;

	void static sighandler(int signal);
	void waitForSignal();
	bool sendMessage(char* type);
	void startMovement();
	Car(char* direction, int messageQueueID);
	virtual ~Car();




};



#endif /* CAR_H_ */

/*
 * Car.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: chris
 */

#include "Car.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <signal.h>


Car::Car(char* direction, int messageQueueID) {
	this->messageQueueID = messageQueueID;
	this->direction = direction;
	this->inTunnel = false;
	this->timer = (rand() % 5) + 3;

	this->startMovement();
	this->loops = 1;

}

Car::~Car() {

}

void Car::startMovement() {
	printf("\n [Auto %d]  - Starte Fahrt! Nummer: %d", getpid(), loops);
	printf(" Richtung:  %s", this->direction);
	sleep(timer);

	printf("\n [Auto %d]  - TunnelEingang erreicht! Warten auf Freigabe", getpid());
	if (!sendMessage("ARRIVE"))
		printf("\n [Auto %d] - Fehler beim Senden der Message", getpid());



	waitForSignal();

	printf("\n [Auto %d]  - Signal erhalten Fahre weiter", getpid());

	sleep(timer);

	printf("\n [Auto %d]  - Verlasse Tunnel", getpid());
	if (!sendMessage("LEAVE"))
		printf("\n [Auto %d] - Fehler beim Senden der Message", getpid());

	printf("\n [Auto %d] - Restart", getpid());
	loops++;


	this->startMovement();

}

bool Car::sendMessage(char* type) {
	struct myMsg {
		long type;
		char text[MSG_SIZE];
	} dataMsg;

	char buffer[MSG_SIZE] ;
	sprintf(buffer,"%d_%s_%d",getpid(), type, loops);
	int messageQueue	 = msgget(messageQueueID, 0666);



	if (strcmp(direction, "TO_NORTH") == 0) {
		dataMsg.type = TO_NORTH;
	} else
		dataMsg.type = TO_SOUTH;

	strcpy(dataMsg.text, buffer);



std::cout <<" [MessageQuee: " << messageQueueID << "]" ;

	if (-1 == msgsnd((key_t)messageQueue, &dataMsg,MSG_SIZE , 0)) {
		perror("msgsnd failed:");
		return false;
	} else {
		std::cout << "Message sent: " << dataMsg.text;
	}

	return true;
}

void Car::waitForSignal() {
	pause();
}

void static sighandler(int signal){


	std::cout << "\n[Signalhandler] Signal SIGCONT abgefangen! " << signal;

}

int main(int argc, char **argv) {

	signal(SIGCONT, sighandler);

	const char* messageQueueIDArray = argv[1];
	char* direction = argv[2];
	Car* car = new Car(direction, atoi(messageQueueIDArray));

	car->startMovement();

}




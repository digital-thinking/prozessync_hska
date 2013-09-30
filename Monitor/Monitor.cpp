/*
 * Monitor.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: chris
 */

#include "Monitor.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

Monitor* Monitor::instance;

Monitor::Monitor() {
	sharedMemoryID = shmget(2404, SHARED_MEM_SIZE, IPC_CREAT | 0666);

}

Monitor::~Monitor() {

}

Monitor* Monitor::getInstance() {
	if (instance == 0) {
		instance = new Monitor();
	}
	return instance;

}

void Monitor::show() {
	struct State {
		long numCars;
		int direction;

	};

	void* myPtr;
	if (sharedMemoryID >= 0) {
		/* get*/
		myPtr = shmat(sharedMemoryID, 0, 0);
		if (myPtr == (char *) -1) {
			perror("shmat");
		} else {
			/* Speicher lesen */
			char* directionString;
			State* statePtr = (State*) myPtr;
			if (statePtr->direction != lastDirection) {
				lastDirection = statePtr->direction;
				if (lastDirection == TO_NORTH) {
					directionString = "Norden";
				} else if (lastDirection == TO_SOUTH) {
					directionString = "Süden";
				} else {
					directionString = "Tunnel leer";
				}
				printf("\n[Monitor]Autos fahren in Richtung: %s", directionString);
			}
			if (lastNumOfCars != statePtr->numCars) {
				lastNumOfCars = statePtr->numCars;
				printf("\n[Monitor]Derzeit im Tunnel: %d", lastNumOfCars);
			}
			shmdt(myPtr);

		}
	}

}

int main(int argc, char **argv) {
	while (1)
	Monitor::getInstance()->show();
	sleep(1);

}


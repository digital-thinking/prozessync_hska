/*
 * CarFactory.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: chris
 */

#include "Runner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <signal.h>
#include "Car/Car.h"
#include "TunnelManager/TunnelManager.h"
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

Runner::Runner(int msgQueue) {




	pid = 0;
	key_t  messageQueueID = (key_t) msgQueue;
	refMsgQueue = msgget(messageQueueID, 0666 |IPC_CREAT);
	sprintf(buffer,"%d",refMsgQueue);





}

Runner::~Runner() {

	// TODO Auto-generated destructor stub
}

bool Runner::createCar(char* direction){


	pid = fork();
	if (pid == 0) {
			/* Kindprozess
			 * wenn fork eine 0 zurückgibt, befinden wir uns im Kindprozess
			 */

			std::cout << "Kindprozess:  (PID: %d)\n" << getpid();

			const char* path = "/home/chris/workspace/Prozesssync/Car/Car";

			char* arg[] = {"Car", buffer , direction};


			execv(path, arg);




		} else if (pid > 0) {
			/* Elternprozess
			 * Gibt fork einen Wert größer 0 zurück, so ist dies die PID des Kindprozesses
			 */

			//printf("Elternprozess:  (PID: %d)\n", getpid());


		} else {
			/* Wird ein negativer Wert zurückgegeben, ist ein Fehler aufgetreten */
			std::cout << stderr << "Error Fork";
			exit(1);
		}

	return true;
}
bool Runner::createTunnelManager(){
	int pid = fork();
			if (pid == 0) {
					const char* path = "/home/chris/workspace/Prozesssync/TunnelManager/TunnelManager";
					char* arg[] = {"TunnelManager", buffer};

					execv(path, arg);
			}
return true;
}

int main(int argc, char **argv) {



	Runner *cF =  new Runner(1338);
	cF->createTunnelManager();
	cF->createCar("TO_SOUTH");
	cF->createCar("TO_NORTH");
	sleep(100);




}


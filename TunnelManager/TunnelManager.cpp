/*
 * TunnelManager.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: chris
 */

#include "TunnelManager.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

TunnelManager::TunnelManager(int messageQueueID) {
	msgctl(msgget(messageQueueID, 0666), IPC_RMID, NULL);
	this->messageQueueID = messageQueueID;
	msgget(messageQueueID, 0666 | IPC_CREAT);

	std::cout << "\n[Tunnelmanager " << getpid() << "] MessageQueueID: " << this->messageQueueID;
	currentDirection = 0;
	inTunnel = 0;

}

TunnelManager::~TunnelManager() {

}

void TunnelManager::run() {

	struct myMsg {
		long type;
		char text[MSG_SIZE];
	} receiveMsg;
	int messageQueue = msgget(messageQueueID, 0666);
	if (messageQueue >= 0) {
		if (currentDirection == 0) {
			if (-1 == msgrcv(messageQueue, &receiveMsg, MSG_SIZE, TO_NORTH, IPC_NOWAIT)) {
				//perror("msgrcv failed:");

			} else {
				std::cout << "\n[Einfahrt nach Norden]  Südeingang - Autos im Tunnel: " << ++inTunnel;
				//std::cout << "\n Nachricht: ";
				//std::cout << receiveMsg.text;
				currentDirection = TO_NORTH;

				int pid = atoi(receiveMsg.text);
				sendSignal(pid);
				return;

			}

			if (-1 == msgrcv(messageQueue, &receiveMsg, MSG_SIZE, TO_SOUTH, IPC_NOWAIT)) {
				//perror("msgrcv failed:");

			} else {
				std::cout << "\n[Einfahrt nach Süden]  Nordeingang - Autos im Tunnel: " << ++inTunnel;
				//std::cout << "\n Nachricht: ";
				//std::cout << receiveMsg.text;
				currentDirection = TO_SOUTH;
				int pid = atoi(receiveMsg.text);
				sendSignal(pid);
				return;

			}
		} else if (currentDirection == TO_NORTH) {
			if (-1 == msgrcv(messageQueue, &receiveMsg, MSG_SIZE, TO_NORTH, IPC_NOWAIT)) {
				//perror("msgrcv failed:");

			} else {
				//Altes fährt raus
				if (strstr(receiveMsg.text, "LEAVE")) {
					std::cout << "\n[Ausfahrt nach Norden]  Nordeingang - Autos im Tunnel: " << --inTunnel;
					//std::cout << "\n Nachricht: ";
					//std::cout << receiveMsg.text;
				}

				// Neues Auto
				else if (strstr(receiveMsg.text, "ARRIVE")) {
					std::cout << "\n[Einfahrt nach Norden]  Südeingang - Autos im Tunnel: " << ++inTunnel;
					//std::cout << "\n Nachricht: ";
					//std::cout << receiveMsg.text;
					int pid = atoi(receiveMsg.text);
					sendSignal(pid);
				}

				if (inTunnel == 0) {
					std::cout << "\n[FREI] Kein Auto mehr im Tunnel, gebe Tunnel frei";
					currentDirection = 0;
				}
			}

		} else if (currentDirection == TO_SOUTH) {
			if (-1 == msgrcv(messageQueue, &receiveMsg, MSG_SIZE, TO_SOUTH, IPC_NOWAIT)) {
				//perror("msgrcv failed:");

			} else {
				//Altes fährt raus
				if (strstr(receiveMsg.text, "LEAVE")) {
					std::cout << "\n[Ausfahrt nach Süden]  Südeingang - Autos im Tunnel: " << --inTunnel;
					//std::cout << "\n Nachricht: ";
					//std::cout << receiveMsg.text;

				}

				// Neues Auto
				else if (strstr(receiveMsg.text, "ARRIVE")) {
					std::cout << "\n[Einfahrt nach Süden]  Nordeingang - Autos im Tunnel: " << ++inTunnel;
					//std::cout << "\n Nachricht: ";
					//std::cout << receiveMsg.text;
					int pid = atoi(receiveMsg.text);
					sendSignal(pid);
				}

			}
			if (inTunnel == 0) {
				std::cout << "\n[FREI] Kein Auto mehr im Tunnel, gebe Tunnel frei";
				currentDirection = 0;
			}
		}

		sleep(1);
	}
}

void TunnelManager::sendSignal(int pid) {
	char command[30];
	sprintf(command, "kill -s CONT %d", pid);
	int err = 0;
	 err = system(command);
	if(err != 0){
		std::cout << "\n[KRITISCH] Auto ist im Tunnel verschwunden! Melde Fahrzeug als vermisst!";
		inTunnel--;
	}

}

int main(int argc, char **argv) {

	const char* messageQueueIDArray = argv[2];

	TunnelManager * tm = new TunnelManager(atoi(messageQueueIDArray));

	while (1)
		tm->run();

}

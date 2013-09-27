/*
 * CarFactory.h
 *
 *  Created on: Sep 26, 2013
 *      Author: chris
 */

#ifndef CARFACTORY_H_
#define CARFACTORY_H_

class Runner {
public:


	bool createTunnelManager();
	bool createCar(char* direction);
	Runner(int msgQueue);
	virtual ~Runner();

private:
	int refMsgQueue;
	int pid;
	int msgQueue;
	char buffer[4];
};




#endif /* CARFACTORY_H_ */

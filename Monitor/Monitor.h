/*
 * Monitor.h
 *
 *  Created on: Sep 29, 2013
 *      Author: chris
 */

#ifndef MONITOR_H_
#define MONITOR_H_
#define SHARED_MEM_SIZE 16



class Monitor {
public:
	static const long int TO_NORTH = 1;
	static const long int TO_SOUTH = 2;
	static Monitor* getInstance();
	void show();
private:
	int sharedMemoryID;
	static Monitor* instance;

	long lastNumOfCars;
	int lastDirection;

	Monitor();
	virtual ~Monitor();




};


#endif /* MONITOR_H_ */

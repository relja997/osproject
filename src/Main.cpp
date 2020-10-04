/*
 * Main.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: OS1
 */
#include <iostream.h>
#include "Thread.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include "Other.h"

#include "Semaphor.h"
#include "KernSem.h"
#include "Event.h"
#include <stdlib.h>



extern int userMain(int argc, char* argv[]);

void main(int argc, char** argv){

	Other::inicinterrupt();
	userMain(argc, argv);
	Other::restoreinterrupt();

}


/*
 * BlockQueue.h
 *
 *  Created on: Jul 27, 2019
 *      Author: OS1
 */

#ifndef BLKQUEUE_H_
#define BLKQUEUE_H_
#include "PCB.h"

class BlkQueue {
public:
	struct Elem{
		PCB* pcb;
		Elem* next;
		Time ttw;
		Elem(PCB* pcb_, Time ttw_):pcb(pcb_),ttw(ttw_), next(0){}
		~Elem(){
			pcb = 0;
			next = 0;
		}
	};

	Elem *headblk, *tailblk;
	int threadnum;

	BlkQueue();

	void put(PCB* pcb, Time ttw_);
	PCB* get();
	void listDel();
	void ttwDecrement();

	virtual ~BlkQueue();
};

#endif /* BLKQUEUE_H_ */

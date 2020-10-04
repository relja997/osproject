/*
 * SemList.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: OS1
 */

#include "SemList.h"
#include "Other.h"
extern int syncPrintf(const char *format, ...);

SemList::SemList():headsem(0), tailsem(0), semnum(0) {}

void SemList::remove(KernelSem* semaphore_){
	SemList::Elem *p1 = headsem, *p2 = 0;
	while(p1 && p1->semaphore != semaphore_){
		p2 = p1;
		p1 = p1->next;
	}
	if(p1 == 0) return;

	if(p1 == headsem)
		headsem = headsem->next;

	else if(p1 == tailsem)
		tailsem = p2;

	else
		p2->next = p1->next;

	if(p1->semaphore->queue->threadnum){
			while(p1->semaphore->queue->threadnum){
				p1->semaphore->unblock();
				p1->semaphore->value++;
			}
		}
		p1->semaphore->queue->headblk = p1->semaphore->queue->tailblk = 0;

		Other::semaphores_list->semnum--;
		delete p1;
}

void SemList::put(KernelSem* semaphore_){
	Other::lock();
	SemList::Elem* e = new SemList::Elem(semaphore_);
	if(headsem==0)
			headsem = tailsem = e;
		else{
			tailsem->next = e;
			tailsem = e;
		}
		semnum++;
}

void SemList::semListDel(){
	Elem* curr = 0;

			while(headsem!=0){
				curr = headsem;
				headsem = headsem->next;
				delete curr;
			}
			headsem = tailsem = 0;
}

void SemList::semListDecrement(){
	SemList::Elem* p1 = Other::semaphores_list->headsem;
	if(!p1)
		return;
	while(p1){
		if(p1->semaphore->queue->threadnum)
			p1->semaphore->queue->ttwDecrement();
		p1 = p1->next;
	}

}

SemList::~SemList() {
	semListDel();
}



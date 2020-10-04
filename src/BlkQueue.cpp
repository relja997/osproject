/*
 * BlkQueue.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: OS1
 */

#include "BlkQueue.h"
#include "Other.h"
#include "Schedule.h"

BlkQueue::BlkQueue() :
		headblk(0), tailblk(0), threadnum(0) {
}

void BlkQueue::put(PCB* pcb_, Time ttw_) {
	pcb_->blkFlag = 1;
	Elem* e = new Elem(pcb_, ttw_);
	if (headblk == 0)
		headblk = tailblk = e;
	else {
		tailblk->next = e;
		tailblk = e;
	}
	threadnum++;
}



PCB* BlkQueue::get() {
	if (!headblk)
		return 0;
	PCB* p = headblk->pcb;
	p->blkFlag = 1;
	Elem* d = headblk;
	headblk = headblk->next;
	d->pcb = 0;
	d->next = 0;
	delete d;
	threadnum--;
	return p;
}

void BlkQueue::listDel() {
	Elem* t = 0;

	while (headblk != 0) {
		t = headblk;
		headblk = headblk->next;
		t->pcb = 0;
		delete t;
	}
	headblk = tailblk = 0;
}

BlkQueue::~BlkQueue() {
	listDel();
}

void BlkQueue::ttwDecrement() {
	Other::lock();
	BlkQueue::Elem *p1 = headblk, *p2 = 0;
	while (p1) {
		if (p1->ttw > 0) {
			p1->ttw--;
			if (!p1->ttw) {
				if (p1 == headblk) {
					p1->pcb->blkFlag = 0;
					p1->pcb->state = PCB::READY;
					Scheduler::put(p1->pcb);
					if (headblk == tailblk)
						headblk = tailblk = 0;
					else
						headblk = headblk->next;
					delete p1;
					p1 = headblk;
				} else {
					p1->pcb->blkFlag = 0;
					p1->pcb->state = PCB::READY;
					Scheduler::put(p1->pcb);
					p2->next = p1->next;
					p1->next = 0;
					if (p1 == tailblk)
						tailblk = p2;
					delete p1;
					p1 = p2->next;
				}
				threadnum--;
			} else {
				p2 = p1;
				p1 = p1->next;
			}
		}
		else{
			p2 = p1;
			p1 = p1->next;
		}
	}
	Other::unlock();
}


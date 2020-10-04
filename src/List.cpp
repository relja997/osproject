/*
 * List.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#include "List.h"

List::List():head(0), tail(0) {}

void List::listDel(){
	Elem* t = 0;

	while(head!=0){
		t = head;
		head = head->next;
		t->pcb = 0;
		delete t;
	}
	head = tail = 0;
}

void List::put(PCB* pcb_){
	Elem* e = new Elem(pcb_);
	if(head==0)
		head = tail = e;
	else{
		tail->next = e;
		tail = e;
	}
}

PCB* List::get(){
	Elem* t;
	PCB* p;
	if(!head) return 0;
	t = head;
	p = t->pcb;
	head = head->next;
	if(head == 0)
		head = tail = 0;
	delete t;
	return p;
}


List::~List() {
	List::listDel();
}


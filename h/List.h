/*
 * List.h
 *
 *  Created on: Jul 16, 2019
 *      Author: OS1
 */

#ifndef OS1VJEZB_LIST_H_
#define OS1VJEZB_LIST_H_

class PCB;

class List {
public:
	friend class PCB;
	struct Elem {
		PCB* pcb;
		Elem* next;
		Elem(PCB* pcb_) :
				pcb(pcb_), next(0) {
		}
		;
	};

	Elem *head, *tail;

	List();

	void put(PCB* pcb_);
	PCB* get();
	void listDel();

	~List();

};

#endif /* OS1VJEZB_LIST_H_ */

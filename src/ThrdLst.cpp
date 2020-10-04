/*
 * ThrdLst.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: OS1
 */

#include "ThrdLst.h"

ThrdLst::ThrdLst():headthr(0), tailthr(0) {}

void ThrdLst::listDel(){
	Elem* t = 0;

		while(headthr!=0){
			t = headthr;
			headthr = headthr->next;
			t->thr = 0;
			delete t;
		}
		headthr = tailthr = 0;
}


ThrdLst::~ThrdLst() {
	ThrdLst::listDel();
}

void ThrdLst::put(Thread* thr_){
	Elem* e = new Elem(thr_);
		if(headthr == 0)
			headthr = tailthr = e;
		else{
			tailthr->next = e;
			tailthr = e;
		}
}



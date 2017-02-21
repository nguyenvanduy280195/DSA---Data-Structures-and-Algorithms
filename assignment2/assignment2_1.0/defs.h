/*
 * =========================================================================================
 * Name        : defs.h
 * Author      : Nguyen Hoang Minh
 * Email       : nghoangminh1505@gmail.com
 * Copyright   : Faculty of Computer Science and Engineering - HCMC University of Technology
 * Description : Initial code for Assignment 2 - Data structures and Algorithms - March 2016
 * =========================================================================================
 */

#ifndef DEFS_H_
#define DEFS_H_

#define INPUT_FILE	"input.txt"

using namespace std;

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

struct nodeTree {
	int attribute;
	int exp;
	int number;
	bool hoopa; // TRUE if this pokemon belongs to Hoopa team
					// and FALSE if it belongs to Hoopa_Unbound team
	int balance;	//will be used in AVL only, and be ignored in other cases.
	nodeTree* pLeft;
	nodeTree* pRight;
};

struct legendTree {
	nodeTree* root;
};

struct eventList {
	int nEventCode; 
	eventList* next;
};

void battle(eventList* pEvent, legendTree*& aTree);

#endif /* DEFS_H_ */
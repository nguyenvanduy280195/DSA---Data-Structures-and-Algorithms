/*
 * =========================================================================================
 * Name        : defs.h
 * Author      : Nguyen Hoang Minh
 * Email       : nghoangminh1505@gmail.com
 * Copyright   : Faculty of Computer Science and Engineering - HCMC University of Technology
 * Description : Initial code for Assignment 1 - Data structures and Algorithms - March 2016
 * =========================================================================================
 */

#ifndef DEFS_H_
#define DEFS_H_

#define INPUT_FILE	"input.txt"
#define MIN_CHAR_REQUIRE	3

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

struct piece {
	int attribute;
	piece *next;
};

struct arceus {
	int hp;
	int skill;
	piece *piece_of_life;	
};

struct pokemon {
	int attribute;
	int exp;
	pokemon *next;
};

struct eventList {
	int nEventCode; 
	eventList* next;
};

void combat(eventList* pEvent, arceus *& pArceus, pokemon *& pPokemon);

#endif /* DEFS_H_ */
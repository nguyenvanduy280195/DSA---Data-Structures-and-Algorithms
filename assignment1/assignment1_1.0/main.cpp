/*
 * =========================================================================================
 * Name        : main.cpp
 * Author      : Nguyen Hoang Minh
 * Email       : nghoangminh1505@gmail.com
 * Copyright   : Faculty of Computer Science and Engineering - HCMC University of Technology
 * Description : Initial code for Assignment 1 - Data structures and Algorithms - March 2016
 * =========================================================================================
 */

#ifndef _DEFS_H_
#include "defs.h"
#define _DEFS_H_
#endif

using namespace std;

/*
 * Function parsePieceInfo
 * Create the piece_of_life
 */
piece* parsePieceInfo(string info)
{
	piece* pHead = NULL;
	piece* pTail = NULL;

	string word;
	stringstream stream(info);	

	int count = 1;
	int value;

	while (getline(stream, word, '_')){
		
		stringstream convert(word);
		convert >> value;	

		if (pHead == NULL){
			pHead = new piece;
			pHead->attribute = value;
			pHead->next = NULL;
			pTail = pHead;
		}

		else{
			piece *pTemp = new piece;
			pTemp->attribute = value;
			pTemp->next = NULL;
			pTail->next = pTemp;
			pTail = pTemp;
		}		
	}

	return pHead;
}

/*
 * Function separateArceus
 * Create Arceus
 */
void separateArceus(arceus* &pArceus, string line)
{
	pArceus = new arceus;
	pArceus->skill = -1;
	int count = 1;

	istringstream iss(line);
	while (iss)
	{
		string sub;
		iss >> sub;	
		if(sub.length() >= MIN_CHAR_REQUIRE)
		{
			if (count == 1){
				stringstream convert(sub);
				convert >> pArceus->hp;
			}
			else{
				pArceus->piece_of_life = parsePieceInfo(sub);
			}

			count++;
		}		
	}
}

/*
 * Function separateEvent
 * Create event list
 */
void separateEvent(eventList* &pHead, string line)
{
	eventList* pTail = NULL;
	int value;
	
	istringstream iss(line);

	while (iss)
	{
		string sub;
		iss >> sub;

		if (sub != ";" && sub != ""){

			stringstream convert(sub);
			convert >> value;
	
			eventList* pTemp = new eventList;
			pTemp->nEventCode = value;
			pTemp->next = NULL;

			if (pHead == NULL)
			{
				pHead = pTemp;			
			}			
			else 
			{
				pTail->next = pTemp;			
			}
			pTail = pTemp;
		}			
	}
}

/*
 * Function readFile
 * Read data from input file to corresponding variables
 */
void readFile(eventList* &pEvent, arceus* &pArceus)
{
	int linecount = 1;
	string line;
	ifstream infile(INPUT_FILE);
	if (infile) {
		while (getline( infile , line) ) {		
			switch (linecount){			
				case 1:
					separateArceus(pArceus, line);
					break;
				case 2:
					separateEvent(pEvent,line);
					break;
			}
			linecount++;
		}
	}
	infile.close();
}

/*
 * Function display
 * Display the data of argument passed in
 * No exception handled
 */
void display(pokemon* pPokemon){

	cout.flush();
	while(pPokemon != NULL){
		printf("%02d_%d", pPokemon->attribute, pPokemon->exp);
		if (pPokemon->next != NULL) cout << " ";
		pPokemon = pPokemon->next;
	}

	if (pPokemon == NULL) cout << "NULL";
}

/*
 * Function main
 */
int main(void)
{
   eventList* pEvent = NULL;
   arceus* pArceus = NULL;
   pokemon* pPokemon = NULL;
   
   readFile(pEvent, pArceus);
   
   combat(pEvent, pArceus, pPokemon);
   
   if (pArceus != NULL) cout << pArceus->hp << endl;
   display(pPokemon);
   
   // delete garbage
   piece* r = pArceus->piece_of_life;
   if (pArceus != NULL){
	   while (pArceus->piece_of_life != NULL){
		   r = pArceus->piece_of_life; //cout << r->attribute << "_";
		   pArceus->piece_of_life = pArceus->piece_of_life->next;
		   delete r;
	   }
   }
   delete pArceus;

   pokemon* q;
   while (pPokemon != NULL){
	   q = pPokemon;
	   pPokemon = pPokemon->next;
	   delete q;
   }

   eventList* p;
   while (pEvent != NULL){
	   p = pEvent; //cout << p->nEventCode << " ";
	   pEvent = pEvent->next;
	   delete p; 
   }
   
   return 0;
}

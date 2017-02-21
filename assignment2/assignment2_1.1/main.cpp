/*
 * =========================================================================================
 * Name        : main.cpp
 * Author      : Nguyen Hoang Minh
 * Email       : nghoangminh1505@gmail.com
 * Copyright   : Faculty of Computer Science and Engineering - HCMC University of Technology
 * Description : Initial code for Assignment 2 - Data structures and Algorithms - March 2016
 * =========================================================================================
 */

#ifndef _DEFS_H_
#include "defs.h"
#define _DEFS_H_
#endif

/*
 * Function readFile
 * Read data from input file to corresponding variables
 */
void readFile(eventList* &pEvent)
{
	ifstream infile(INPUT_FILE);	

	if (infile) {

		string line;
		int value;
		eventList* pTail = NULL;

		while ( getline(infile , line) ) {
				
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

					if (pEvent == NULL)
					{
						pEvent = pTemp;			
					}			
					else 
					{
						pTail->next = pTemp;			
					}
					pTail = pTemp;
				}			
			}
		}
	}
	
	else
		cout << "The file is not found!";
	infile.close();
}

/*
 * Function deleteTree
 * Free all of nodes in the tree
 */
void deleteTree (nodeTree *root){
	if (!root) return;
	nodeTree *pDel = root;
	deleteTree(root->pLeft);
	deleteTree(root->pRight);
	delete pDel; pDel = NULL;
}

/*
 * Function display 1
 * Display the tree
 */
void displayTree(nodeTree *root)
{
	if(root == NULL) return;

	cout.flush();
	if (root != NULL)
	{
		cout << setw(3) << setfill('0') << root->number;

		if (root->pLeft == NULL && root->pRight == NULL) return;
		
		else if (root->pLeft != NULL && root->pRight == NULL) {
			cout << " (";
			displayTree(root->pLeft);
			cout << " N)";
			return;
		}
		
		else if (root->pLeft == NULL && root->pRight != NULL) {
			cout << " (N ";
			displayTree(root->pRight);
			cout << ")";
			return;
		}

		else {
			cout << " (";
			displayTree(root->pLeft);
			cout << " ";
			displayTree(root->pRight);
			cout << ")";
			return;
		}
	}	
}

/*
 * Function display 2
 * Display LNR style of tree
 */
void displayTree_LNR(nodeTree *root){
	
	if (root == NULL) return;

	cout.flush();
	if (root != NULL){
		displayTree_LNR(root->pLeft);
		cout << setw(3) << setfill('0') << root->number;
		cout << "_";
		cout << setw(2) << setfill('0') << root->attribute;
		cout << "_" << root->exp << "_";
		if (root->hoopa) cout << "1  ";
		else cout << "0  ";
		displayTree_LNR(root->pRight);
	}
}


/*
 * Function main
 */
int main(void)
{
	eventList* pEvent = NULL;
	legendTree* aTree = new legendTree;
	aTree->root = NULL;
	
	readFile(pEvent);
	
	battle(pEvent, aTree);

	// display result
	if (aTree == NULL || aTree->root == NULL)
		cout << "NULL";
	else{
		displayTree(aTree->root);
		cout << endl;
		displayTree_LNR(aTree->root);
	}

	// delete garbage
	eventList* p;
	while (pEvent != NULL){
		p = pEvent;//cout << p->nEventCode << " ";
		pEvent = pEvent->next;
		delete p; 
	} 

	if (aTree) deleteTree(aTree->root);

	system("pause");
	return 0;
}


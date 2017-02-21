/*
* =========================================================================================
* Name        : pokemon_legend.cpp
* Author      : Nguyen Hoang Minh
* Email       : nghoangminh1505@gmail.com
* Copyright   : Faculty of Computer Science and Engineering - HCMC University of Technology
* Description : Initial code for Assignment 2 - Data structures and Algorithms - March 2016
* =========================================================================================
*/

//REMEMBER: Do not include any other library. Otherwise you will get 0 mark. :P

#ifndef _DEFS_H_
#include "defs.h"
#define _DEFS_H_
#endif

//number

#define Groudon		111
#define Kyogre		222
#define Rayquaza	333
#define Virizion	200
#define Keldeo		400
#define Cobalion	600
#define Terrakion	800
#define Articuno	444
#define Moltres		555
#define Zapdos		666
#define Lugia		456
#define Entei		100
#define Suicune		300
#define Raikou		500
#define HoOh		700
#define Zekrom		777
#define Reshiram	888
#define Kyurem		999
//attribute

#define Undefined	0
#define Bug			1
#define Dark		2
#define Dragon		3
#define Electric	4
#define Fighting	5
#define Fire		6
#define Flying		7
#define Ghost		8
#define Grass		9
#define	Ground		10
#define Ice			11
#define Poison		12
#define Psychic		13
#define Rock		14
#define Steel		15
#define Water		16
//type of tree

#define BST			1
#define AVL			2
#define MinHeap		3
#define MaxHeap		4
//-----------------------------support-----------------------------

template <class T>
/*
* define abs of a type T
*/
T abs(T a){
	return a > 0 ? a : -a;
}
/*
* swap data of two tree
* @param a:	first tree
* @param b:	second tree
*/
void swap(nodeTree *&a, nodeTree *&b){
	int attribute = a->attribute;
	int exp = a->exp;
	bool hoopa = a->hoopa;
	int number = a->number;

	a->attribute = b->attribute;
	a->exp = b->exp;
	a->hoopa = b->hoopa;
	a->number = b->number;

	b->attribute = attribute;
	b->exp = exp;
	b->hoopa = hoopa;
	b->number = number;
}
/*
* create a node of tree
*/
nodeTree* createNode(int attribute, int balance, int exp, bool hoopa, int number){
	nodeTree *p = new nodeTree;

	p->attribute = attribute;
	p->balance = balance;
	p->exp = exp;
	p->hoopa = hoopa;
	p->number = number;
	p->pLeft = NULL;
	p->pRight = NULL;

	return p;
}
/*
* copy a node of tree
*/
nodeTree* copyNode(nodeTree *origin){
	nodeTree *p = new nodeTree;

	p->attribute = origin->attribute;
	p->balance = origin->balance;
	p->exp = origin->exp;
	p->hoopa = origin->hoopa;
	p->number = origin->number;
	p->pLeft = NULL;
	p->pRight = NULL;

	return p;
}
//-----------------------------queue-----------------------------

//data of queue
struct linkedlist{
	nodeTree *node;
	linkedlist *next;
};
//the structural of a queue
struct queue{
	linkedlist *front;
	linkedlist *rear;
};
//create a queue
queue* createQueue(){
	queue *q = new queue;
	q->front = 0;
	q->rear = 0;

	return q;
}

//check queue
bool EmptyQueue(queue *q){
	return q->front == 0;
}
void EnQueue(queue *&q, nodeTree *data){
	//create node
	linkedlist *p = new linkedlist;
	p->node = data;
	p->next = 0;
	//enqueue
	if (q->front == 0){
		q->front = p;
		q->rear = p;
		return;
	}
	q->rear->next = p;
	q->rear = q->rear->next;
}
void DeQueue(queue *q, nodeTree *&data){
	if (EmptyQueue(q)){
		q = 0;
		data = NULL;
		return;
	}

	linkedlist *temp = q->front;
	data = q->front->node;
	q->front = q->front->next;
	delete temp;
}
void clearQueue(queue *q){
	if (EmptyQueue(q)) return;
	delete q;
}

namespace bst{
	nodeTree* searchNode(nodeTree *root, int number){
		if (root == 0) return NULL;
		nodeTree *run = root;
		while (run){
			if (run->number == number)
				return run;

			if (number < run->number){
				run = run->pLeft;
			} else if (number > run->number){
				run = run->pRight;
			} else return NULL;
		}

		return NULL;
	}
	nodeTree* searchPar(nodeTree *root, nodeTree *idx){
		if (root == NULL) return NULL;
		if (idx == NULL) return NULL;
		nodeTree *run = root;
		while (run){
			if (run->pLeft == idx || run->pRight == idx)
				return run;

			if (idx->number < run->number){
				run = run->pLeft;
			} else if (idx->number > run->number){
				run = run->pRight;
			} else return NULL;
		}

		return NULL;
	}
	void insert(nodeTree *&root, nodeTree *p){
		if (root == 0){
			//if (p->number > 999 || (isSpecialValue(p->number) && !isTrue)) return;
			root = p;
			return;
		}
		if (p->number < root->number){
			insert(root->pLeft, p);
		} else if (p->number > root->number){
			insert(root->pRight, p);
		} else{
			p->number++;

			insert(root, p);
		}

	}
	void remove(nodeTree *root, nodeTree *&idx){
		nodeTree *par = searchPar(root, idx);
		if (idx == NULL) return;
		if (idx->pLeft == NULL){
			if (par == NULL){
				nodeTree *temp = idx;
				idx = idx->pRight;
				delete temp;
			} else{
				if (par->pLeft == idx){
					par->pLeft = idx->pRight;
				} else{
					par->pRight = idx->pRight;
				}
				delete idx;
				idx = NULL;
			}
			return;
		}

		nodeTree *parMaxLeft = idx->pLeft;
		nodeTree *maxLeft = idx->pLeft;
		for (; maxLeft->pRight != 0; maxLeft = maxLeft->pRight) parMaxLeft = maxLeft;
		swap(maxLeft, idx);
		//delete maxleft
		if (parMaxLeft != maxLeft) parMaxLeft->pRight = maxLeft->pLeft;
		else idx->pLeft = maxLeft->pLeft;

		delete maxLeft;
	}
}
namespace avl{
	struct leaf{
		int data;

		leaf* next = 0;
	};
	void addList(leaf *&head, int data){
		leaf *p = new leaf;
		p->data = data;
		if (head == 0){
			head = p;
			return;
		}
		leaf *tail = head;
		for (leaf *i = head; i != 0; i = i->next) tail = i;
		tail->next = p;
	}

	void leafOfTree(leaf *&head, nodeTree *root){
		if (root == 0) return;
		if (root->pLeft == NULL && root->pRight == NULL) addList(head, root->number);
		leafOfTree(head, root->pLeft);
		leafOfTree(head, root->pRight);
	}
	void countNode(nodeTree *root, int data, int &count){
		if (root == 0) return;
		if (data < root->number){
			count++;
			countNode(root->pLeft, data, count);
		} else if (data > root->number){
			count++;
			countNode(root->pRight, data, count);
		} else count++;
	}
	int height(nodeTree *root){
		int h = 0;
		leaf *head = NULL;
		leafOfTree(head, root);
		int count = 0;
		int max = 0;

		for (leaf *i = head; i != 0; i = i->next){
			countNode(root, i->data, count);
			if (count > max) max = count;
			count = 0;
		}

		return max;
	}
	int balanceFactor(nodeTree *root){
		int l = height(root->pLeft);
		int r = height(root->pRight);
		return l - r;
	}

	void rotateLeft(nodeTree *&subRoot){
		nodeTree* temp = subRoot->pRight;
		subRoot->pRight = temp->pLeft;
		temp->pLeft = subRoot;
		subRoot = temp;
	}
	void rotateRight(nodeTree *&subRoot){
		nodeTree* temp = subRoot->pLeft;
		subRoot->pLeft = temp->pRight;
		temp->pRight = subRoot;
		subRoot = temp;
	}
	void rotateRightLeft(nodeTree *&root){
		rotateRight(root->pRight);
		rotateLeft(root);
	}
	void rotateLeftRight(nodeTree *&root){
		rotateLeft(root->pLeft);
		rotateRight(root);
	}

	/*
	 * - check balance and rotate when not balance
	 * - check balance of idx, loop check balance of par until par == root
	 * @param root	: is root of tree, when search par
	 * @param idx	: check balance of idx
	 *-2 -1 left
	 * 2 -1 left right
	 * 2  1 right
	 *-2  1 right left
	 */
	void balanceTree(nodeTree *&idx){
		int bIdx = balanceFactor(idx);

		if (bIdx == 2){
			int bLeft = balanceFactor(idx->pLeft);
			if (bLeft == -1){
				rotateLeftRight(idx);
			} else/* if (bLeft == 1)*/{
				rotateRight(idx);
			}

		} else if (bIdx == -2){
			int bRight = balanceFactor(idx->pRight);
			if (bRight == 1){
				rotateRightLeft(idx);
			} else/* if (bRight == -1)*/{
				rotateLeft(idx);
			}
		}
	}

	void insert(nodeTree *&root, nodeTree *p){
		if (root == 0){
			root = p;
			return;
		}
		if (p->number < root->number){
			insert(root->pLeft, p);
			if (root->pLeft != NULL)
				balanceTree(root);
		} else if (p->number > root->number){
			insert(root->pRight, p);
			if (root->pRight != NULL)
				balanceTree(root);
		} else{
			p->number++;
			insert(root, p);
		}
	}
	void balanceForRemove(nodeTree *root, nodeTree *&idx){
		nodeTree *par = bst::searchPar(root, idx);
		if (par == NULL) {//root
			balanceTree(idx);
			//root = idx;
			return;
		}
		balanceTree(idx);
		balanceForRemove(root, par);
	}
	
	void remove(nodeTree *&root, nodeTree *&idx){
		if (idx == NULL) return;

		if (idx->pLeft == NULL){
			nodeTree *par = bst::searchPar(root, idx);
			if (par->pLeft == idx)
			par->pLeft = idx->pLeft;
			else
			par->pRight = idx->pLeft;
			delete idx;
			balanceForRemove(root, par);
			return;
		}

		nodeTree *maxLeft = idx->pLeft;
		for (; maxLeft->pRight != NULL; maxLeft = maxLeft->pRight);
		nodeTree *parMaxLeft = bst::searchPar(root, maxLeft);
		swap(idx, maxLeft);
		if (parMaxLeft->pLeft == maxLeft)
			parMaxLeft->pLeft = maxLeft->pLeft;
		else
			parMaxLeft->pRight = maxLeft->pLeft;
		if (parMaxLeft == maxLeft){
			delete maxLeft;
			balanceForRemove(root, parMaxLeft);
			root = parMaxLeft;
		} else{
			delete maxLeft;
			balanceForRemove(root, parMaxLeft);
		}
		

	}
}
namespace heap{
	//duplicate trong heap
	nodeTree* searchNode(nodeTree *root, int number){
		queue *q = createQueue();
		nodeTree *run = root;
		while (run){
			if (run->number == number)
				return run;

			if (run->pLeft) EnQueue(q, run->pLeft);
			if (run->pRight) EnQueue(q, run->pRight);
			DeQueue(q, run);
		}
		return NULL;
	}
	void searchPar(nodeTree *&par, nodeTree *root, int idxOfPar){
		if (!root) return;
		if (root->balance == idxOfPar){
			par = root;
			return;
		}
		searchPar(par, root->pLeft, idxOfPar);
		searchPar(par, root->pRight, idxOfPar);
	}
	nodeTree* nodeEnd(nodeTree *root){
		queue *q = createQueue();
		nodeTree *run = root;
		nodeTree *end = 0;

		while (run){
			end = run;
			if (run->pLeft) EnQueue(q, run->pLeft);
			if (run->pRight) EnQueue(q, run->pRight);
			DeQueue(q, run);
		}

		return end;
	}
	void reHeapUp(nodeTree* root, nodeTree *node, int typeTree){
		if (!node) return;

		int idxOfPar = (node->balance - !(node->balance % 2) - 1) / 2;
		nodeTree *par = 0;
		searchPar(par, root, idxOfPar);

		if (par == 0) return;
		if (par == node) return;
		if ((typeTree == 4) ? (par->number < node->number) : (par->number > node->number)){
			swap(par, node);
			reHeapUp(root, par, typeTree);
		}
	}
	void reHeapDown(nodeTree* root, nodeTree *node, int typeTree){
		if (!node) return;
		nodeTree *left = node->pLeft;
		nodeTree *right = node->pRight;
		nodeTree *idx = 0;
		bool righLeft = typeTree == 1 ? right->number < left->number : right->number > left->number;
		bool leftNode = typeTree == 1 ? left->number > node->number : left->number > node->number;
		bool rightNode = typeTree == 1 ? right->number > node->number : right->number > node->number;

		if (left && right){
			if (righLeft){
				if (leftNode) idx = left;
			} else{
				if (rightNode) idx = right;
			}
		} else if (left){
			if (leftNode) idx = left;
		} else if (rightNode){
			if (node->number < right->number) idx = right;
		}
		swap(node, idx);
		reHeapDown(root, idx, typeTree);
	}
	void insert(nodeTree *&root, nodeTree *p, int typeTree){
		queue *q = createQueue();
		nodeTree *run = root;
		while (run){
			if (!run->pLeft){
				run->pLeft = p;
				run = run->pLeft;
				reHeapUp(root, run, typeTree);
				break;
			} else if (!run->pRight){
				run->pRight = p;
				run = run->pRight;
				reHeapUp(root, run, typeTree);
				break;
			}

			if (run->pLeft) EnQueue(q, run->pLeft);
			if (run->pRight) EnQueue(q, run->pRight);
			DeQueue(q, run);
		}
		clearQueue(q);
	}
	void remove(nodeTree *&root, nodeTree *p, int typeTree){
		nodeTree *end = nodeEnd(root);
		int idxOfPar = (end->balance - !(end->balance % 2) - 1) / 2;
		nodeTree *parOfNodeEnd = 0; searchPar(parOfNodeEnd, root, idxOfPar);
		swap(end, p);
		delete end;
		reHeapDown(root, p, typeTree);
	}
}

int typeTree = 0;
//s2

bool treeHasGroudon = false;
bool treeHasKyogre = false;
bool treeHasRayquaza = false;
//s4

bool treeHasArticuno = false;
bool treeHasMoltres = false;
bool treeHasZapdos = false;
bool treeHasLugia = false;
//s5
bool treeHasRaikou = false;	nodeTree *RaikousInformation = NULL;	bool rWasRecovered = false;	bool rWasRevived = false;
bool treeHasSuicune = false; nodeTree *SuicunesInformation = NULL;	bool sWasRecovered = false;	bool sWasRevived = false;
bool treeHasEntei = false;	nodeTree *EnteisInformation = NULL;		bool eWasRecovered = false;	bool eWasRevived = false;
bool treeHasHoOh = false;
//s6

bool treeHasReshiram = false;
bool treeHasZekrom = false;
bool treeHasKyurem = false;

namespace s1{
	bool isPerfectSquare(int number){
		for (int i = 10; i <= 31; i++)
			if (i*i == number) return true;
		return false;
	}
	bool isAverage(int number){
		int x = number / 100;
		int y = number / 10 % 10;
		int z = number % 10;

		return (x + z) / 2 == y;
	}
	int index = 1;
	void s1(nodeTree *&root, nodeTree *p){
		if (root == NULL){
			root = p;
			typeTree = BST;
			if (isPerfectSquare(root->number)) typeTree = AVL;
			if (isAverage(root->number)) typeTree = MaxHeap;
			return;
		}
		switch (typeTree){
			case AVL:
				avl::insert(root, p);
				break;
			case BST:
				bst::insert(root, p);
				break;
			case MaxHeap:
			case MinHeap:
				p->balance = index;
				if (p->balance == 1){
					if (p->number > root->number) typeTree = MinHeap;
					root->balance = 0;
				}
				heap::insert(root, p, typeTree);
				index++;
				break;
		}

	}
}
namespace s2{
	//increase when Groudon or Kyogre or Rayquaza appear
	void incExp(nodeTree *&root, int attr1, int attr2, int attr3, bool isHoopa){
		if (root == NULL) return;

		if (root->number != Groudon && root->number != Kyogre && root->number != Rayquaza)
			if ((root->attribute == attr1 || root->attribute == attr2 || root->attribute == attr3) && root->hoopa == isHoopa)
				root->exp += 200;
		if (root->exp >= 999)
			root->exp = 999;

		incExp(root->pLeft, attr1, attr2, attr3, isHoopa);
		incExp(root->pRight, attr1, attr2, attr3, isHoopa);
	}
	//increase when has Groudon or Kyogre or Rayquaza
	void incExist(nodeTree *&p){
		if (p == NULL)return;
		if ((treeHasGroudon && (p->attribute == Fire || p->attribute == Ground)
			|| (treeHasKyogre && (p->attribute == Grass || p->attribute == Water))
			|| (treeHasRayquaza && (p->attribute == Dragon || p->attribute == Electric || p->attribute == Flying))) && p->number>0)
			p->exp += 200;
		if (p->exp >= 999)p->exp = 999;
	}
	/*
	* Groudon	(number = 111)(attribute = 06) ton tai (kiem tra thuoc tinh cua groudon)
	*	- attribute cua pokemon cung phe = fire(6) or ground(10) duoc tang them 200 exp
	* Kyogre	(number = 222)(attribute = 16) ton tai (kiem tra thuoc tinh cua kyogre)
	*	- attribute cua pokemon cung phe = grass(9) or water(16) duoc tang tham 200 exp
	* Rayquaza (number = 333)(attribute = 04) ton tai (kiem tra thuoc tinh cua rayquaza)
	*	- attribue cua pokemon cung phe = dragon(03) or electric(04) or flying(07) duoc tang tham 200 exp
	*/
	bool s2(nodeTree *&root, nodeTree *p){
		int number = p->number;
		int attribute = p->attribute;
		bool isHoopa = p->hoopa;

		if (attribute == Fire && number == Groudon && !treeHasGroudon){
			incExp(root, Fire, Ground, Undefined, isHoopa);
			treeHasGroudon = true;
		} else if (attribute == Water && number == Kyogre && !treeHasKyogre){
			incExp(root, Grass, Water, Undefined, isHoopa);
			treeHasKyogre = true;
		} else if (attribute == Electric && number == Rayquaza && !treeHasRayquaza){
			incExp(root, Dragon, Electric, Flying, isHoopa);
			treeHasRayquaza = true;
		} else return false;
		return true;
	}
}
namespace s3{
	/*
	* hieu number cua tsos voi cac node la nho nhat
	* The sarecd of swordsman == tsos
	*/
	nodeTree* tsosChooseNode(nodeTree *root, int tsosNumber, bool isHoopa){
		if (!root) return NULL;
		queue *q = createQueue();
		nodeTree *run = root;
		nodeTree *nodeMin = 0;
		nodeTree *parMin = 0;
		int min = 1000;

		while (run){

			int sub = abs(run->number - tsosNumber);
			if (sub < min && run->hoopa != isHoopa){
				nodeMin = run;
				min = sub;
			} else if (sub == min){
				if (run->number < tsosNumber){
					nodeMin = run;
					min = sub;
				}
			}

			if (run->pLeft) EnQueue(q, run->pLeft);
			if (run->pRight) EnQueue(q, run->pRight);
			DeQueue(q, run);
		}

		return nodeMin;
	}
	//xoa bst avl heap
	void s3(nodeTree *&root, bool isHoopa, int xyz){
		int tsosNumber = xyz;
		nodeTree *nodeIsSelected = tsosChooseNode(root, tsosNumber, isHoopa);
		
		if (nodeIsSelected == NULL) return;

		if (nodeIsSelected->number == Groudon) treeHasGroudon = false;
		if (nodeIsSelected->number == Kyogre) treeHasKyogre = false;
		if (nodeIsSelected->number == Rayquaza) treeHasRayquaza = false;

		if (nodeIsSelected->number == Articuno) treeHasArticuno = false;
		if (nodeIsSelected->number == Moltres) treeHasMoltres = false;
		if (nodeIsSelected->number == Zapdos) treeHasZapdos = false;
		if (nodeIsSelected->number == Lugia) treeHasLugia = false;

		if (nodeIsSelected->number == Raikou) treeHasRaikou = false;
		if (nodeIsSelected->number == Suicune) treeHasSuicune = false;
		if (nodeIsSelected->number == Entei) treeHasEntei = false;
		if (nodeIsSelected->number == HoOh) treeHasHoOh = false;

		if (nodeIsSelected->number == Reshiram) treeHasReshiram = false;
		if (nodeIsSelected->number == Kyurem) treeHasKyurem = false;
		if (nodeIsSelected->number == Zekrom) treeHasZekrom = false;
		
		switch (typeTree){
			case 2:
				avl::remove(root, nodeIsSelected);
				break;
			case 3:
			case 4:
				heap::remove(root, nodeIsSelected, typeTree);
				break;
			case 1:
				bst::remove(root, nodeIsSelected);
				break;
			default:
				break;

		}
	}
}
namespace s4{
	//exp giam xuong 0 thi bi xoa
	/*
	* su xuat hien cua bo 3 linh dieu hay co them lugia
	* neu co 3 con linh dieu + thuoc tinh phu hop + khac phe -> exp = exp - 10 - 100;
	*/

	//3 linh dieu dang danh nhau (cung ton tai trong 1 cay)
	bool fighting(){
		if (treeHasArticuno && treeHasMoltres && treeHasZapdos && !treeHasLugia)
			return true;
		return false;
	}
	//delete exp == 0
	void delExp0(nodeTree *root, nodeTree *idx){
		if (idx->number == Groudon) treeHasGroudon = false;
		if (idx->number == Kyogre) treeHasKyogre = false;
		if (idx->number == Rayquaza) treeHasRayquaza = false;

		if (idx->number == Articuno) treeHasArticuno = false;
		if (idx->number == Moltres) treeHasMoltres = false;
		if (idx->number == Zapdos) treeHasZapdos = false;
		if (idx->number == Lugia) treeHasLugia = false;

		if (idx->number == Raikou) treeHasRaikou = false;
		if (idx->number == Suicune) treeHasSuicune = false;
		if (idx->number == Entei) treeHasEntei = false;
		if (idx->number == HoOh) treeHasHoOh = false;
		
		if (idx->number == Reshiram) treeHasReshiram = false;
		if (idx->number == Kyurem) treeHasKyurem = false;
		if (idx->number == Zekrom) treeHasZekrom = false;

		switch (typeTree){
			case 2:
				avl::remove(root, idx);
				break;
			case 3:
			case 4:
				heap::remove(root, idx, typeTree);
				break;
			case 1:
				bst::remove(root, idx);
				break;
			default:
				break;

		}
	}

	
	//Affer appearance of event s4
	void decExist(nodeTree *root, nodeTree *p){
		nodeTree *raikou = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Raikou) : heap::searchNode(root, Raikou);
		nodeTree *suicune = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Suicune) : heap::searchNode(root, Suicune);
		nodeTree *entei = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Entei) : heap::searchNode(root, Entei);

		if (treeHasArticuno && (p->attribute == Bug || p->attribute == Grass || p->attribute == Water)
			|| (treeHasMoltres && (p->attribute == Bug || p->attribute == Dark || p->attribute == Grass || p->attribute == Ice || p->attribute == Steel))
			|| (treeHasZapdos && (p->attribute == Bug || p->attribute == Steel || p->attribute == Water))){
			if (raikou != NULL){
				raikou->exp -= 100;
				if (raikou->exp <= 0){
					delExp0(root, raikou);
				}
			} else if (suicune != NULL){
				suicune->exp -= 100;
				if (suicune->exp <= 0){
					delExp0(root, suicune);
				}
			} else if (entei != NULL){
				entei->exp -= 100;
				if (entei->exp <= 0){
					delExp0(root, entei);
				}
			} else{
				p->exp -= 100;
			}
		}

		if (fighting()) p->exp -= 10;
	}

	void allIsSubbed10(nodeTree *root, nodeTree *&idx){
		if (idx == NULL) return;

		if (idx->number > 0){
			nodeTree *raikou = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Raikou) : heap::searchNode(root, Raikou);
			nodeTree *suicune = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Suicune) : heap::searchNode(root, Suicune);
			nodeTree *entei = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Entei) : heap::searchNode(root, Entei);
			if (raikou != NULL){
				raikou->exp -= 10;
				if (raikou->exp <= 0){
					delExp0(root, raikou);
				}
			} else if (suicune != NULL){
				suicune->exp -= 10;
				if (suicune->exp <= 0){
					delExp0(root, suicune);
				}
			} else if (entei != NULL){
				entei->exp -= 10;
				if (entei->exp <= 0){
					delExp0(root, entei);
				}
			} else{
				idx->exp -= 10;
				if (idx->exp <= 0){
					delExp0(root, idx);
				}
			}
		}

		allIsSubbed10(root, idx->pLeft);
		allIsSubbed10(root, idx->pRight);
	}
	
	void decExp(nodeTree *root, nodeTree *&idx, int attr1, int attr2, int attr3, int attr4, int attr5, bool isHoopa){
		if (!idx) return;

		if (idx->attribute != Articuno && idx->attribute != Moltres, idx->attribute != Zapdos)
			if ((idx->attribute == attr1 || idx->attribute == attr2 || idx->attribute == attr3 || idx->attribute == attr4 || idx->attribute == attr5) && (isHoopa != idx->hoopa) && idx->number > 0){
				
				nodeTree *raikou = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Raikou) : heap::searchNode(root, Raikou);
				nodeTree *suicune = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Suicune) : heap::searchNode(root, Suicune);
				nodeTree *entei = (typeTree == AVL || typeTree == BST) ? bst::searchNode(root, Entei) : heap::searchNode(root, Entei);
				
				if (raikou != NULL && raikou->hoopa != isHoopa){
					raikou->exp -= 100;
					if (raikou->exp <= 0){
						delExp0(root, raikou);
					}
				} else if (suicune != NULL && suicune->hoopa != isHoopa){
					suicune->exp -= 100;
					if (suicune->exp <= 0){
						delExp0(root, suicune);
					}
				} else if (entei != NULL && entei->hoopa != isHoopa){
					entei->exp -= 100;
					if (entei->exp <= 0){
						delExp0(root, entei);
					}
				} else{
					idx->exp -= 100;
					if (idx->exp <= 0){
						delExp0(root, idx);
					}
				}
			}
		decExp(root, idx->pLeft, attr1, attr2, attr3, attr4, attr5, isHoopa);
		decExp(root, idx->pRight, attr1, attr2, attr3, attr4, attr5, isHoopa);
	}
	/* -100
	* Articuno(11)	: Bug, Grass, Water
	* Moltres(6)	: Bug, Dark, Grass, Ice, Steel
	* Zapdo(4)		: Bug, Steel, Water
	* Lugia(3)		:
	*/
	bool s4(nodeTree *&root, nodeTree *p){
		int number = p->number;
		int attribute = p->attribute;
		bool isHoopa = p->hoopa;
		//displayTree_LNR(root); cout << endl;

		if (number == Articuno && attribute == Ice && !treeHasArticuno){
			decExp(root, root, Bug, Grass, Water, Undefined, Undefined, isHoopa);
			treeHasArticuno = true;
		} else if (number == Moltres && attribute == Fire && !treeHasMoltres){
			decExp(root, root, Bug, Dark, Grass, Ice, Steel, isHoopa);
			treeHasMoltres = true;
		} else if (number == Zapdos && attribute == Electric && !treeHasZapdos){
			decExp(root, root, Bug, Steel, Water, Undefined, Undefined, isHoopa);
			treeHasZapdos = true;
		} else if (number == Lugia && attribute == Dragon && !treeHasLugia){
			treeHasLugia = true;
		} else return false;


		return true;
	}
}
namespace s5{
	void hoOhRecover3Animal(nodeTree *root){
		if (root == NULL)return;
		if (treeHasHoOh == NULL)return;

		if (root->number == Raikou && !rWasRecovered){
			root->exp = 500;
			rWasRecovered = true;
		}
		if (root->number == Suicune && !sWasRecovered){
			root->exp = 300;
			sWasRecovered = true;
		}
		if (root->number == Entei && !eWasRecovered){
			root->exp = 100;
			eWasRecovered = true;
		}

		hoOhRecover3Animal(root->pLeft);
		hoOhRecover3Animal(root->pRight);
	}
	void hoOhRevive3Animal(nodeTree *root){
		if (root == NULL)return;
		if (treeHasHoOh == NULL)return;

		if (RaikousInformation != NULL && !treeHasRaikou && !rWasRevived){
			s1::s1(root, RaikousInformation);
			treeHasRaikou = true;
			rWasRevived = true;
		}
		if (SuicunesInformation != NULL && !treeHasSuicune && !sWasRevived){
			s1::s1(root, SuicunesInformation);
			treeHasSuicune = true;
			sWasRevived = true;
		}
		if (EnteisInformation != NULL && !treeHasEntei && !eWasRevived){
			s1::s1(root, EnteisInformation);
			treeHasEntei = true;
			eWasRevived = true;
		}

	}

	bool s5(nodeTree *root, nodeTree *p){
		int number = p->number;
		int attribute = p->attribute;

		if (number == Raikou && attribute == Electric && !treeHasRaikou){
			treeHasRaikou = true;
			RaikousInformation = copyNode(p);
		} else if (number == Suicune && attribute == Water && !treeHasSuicune){
			treeHasSuicune = true;
			SuicunesInformation = copyNode(p);
		} else if (number == Entei && attribute == Fire && !treeHasEntei){
			treeHasEntei = true;
			EnteisInformation = copyNode(p);
		} else if (number == HoOh && attribute == Fire && !treeHasHoOh){
			treeHasHoOh = true;
		} else return false;
		return true;
	}
}
namespace s6{
	void yin(nodeTree *root, nodeTree *&nroot){//am - hoopa == false
		if (root == NULL) return;
		yin(root->pLeft, nroot);

		if (root->hoopa == false){
			nodeTree *p = copyNode(root);
			s1::s1(nroot, p);
		}

		yin(root->pRight, nroot);
	}
	void yang(nodeTree *root, nodeTree *&nroot){//duong - hoopa == true
		if (root == NULL) return;
		yang(root->pLeft, nroot);

		if (root->hoopa == true){
			nodeTree *p = copyNode(root);
			s1::s1(nroot, p);
		}

		yang(root->pRight, nroot);
	}
	void deleteTree(nodeTree *root){
		if (!root) return;
		nodeTree *pDel = root;
		deleteTree(root->pLeft);
		deleteTree(root->pRight);
		delete pDel; pDel = NULL;
	}

	bool s6(nodeTree *root, nodeTree *p){
		int number = p->number;
		int attribute = p->attribute;
		bool isHoopa = p->hoopa;

		if (number == Reshiram && attribute == Dragon && isHoopa && !treeHasReshiram){
			treeHasReshiram = true;
		} else if (number == Zekrom && attribute == Dragon && !isHoopa && !treeHasZekrom){
			treeHasZekrom = true;
		} else if (number == Kyurem && attribute == Dragon && !treeHasKyurem){
			treeHasKyurem = true;
		} else return false;
		return true;
	}
}


//value's number is event's number -> true || false
bool isSpecialValue(int number){
	switch (number){
		case Groudon: case Kyogre: case Rayquaza:
		case Virizion: case Keldeo: case Cobalion: case Terrakion:
		case Articuno: case Moltres: case Zapdos: case Lugia:
		case Raikou: case Suicune: case Entei: case HoOh:
		case Zekrom: case Reshiram: case Kyurem:
			return true;
	}
	return false;
}
//check duplicate
void duplicateNumber(nodeTree *root, int number, bool &duplicated){
	if (root == 0) return;

	if (root->number == number){
		duplicated = true;
		return;
	}

	duplicateNumber(root->pLeft, number, duplicated);
	duplicateNumber(root->pRight, number, duplicated);
}

//check init
bool initIsSuccess(nodeTree *root, nodeTree *&p, int code, bool isS1){
	//input from event
	int attribute = abs(code % 100);
	int balance = 1;
	int exp = abs(code / 10000) * 100;
	bool hoopa = (code > 0) ? true : false;
	int number = abs(code / 100);
	//check attribute
	if (!(1 <= attribute && attribute <= 16)) return false;//attribute (- [1, 16]
	//check number
	if (!(100 <= number && number <= 999)) return false;//number (- [100, 999]
	//check duplicate of number
	bool duplicated = false;
	while (isS1){
		duplicateNumber(root, number, duplicated);
		if (duplicated) number++;
		else break;
		duplicated = false;
	}
	if (isSpecialValue(number) && isS1) return false;
	p = createNode(attribute, balance, exp, hoopa, number);
	return true;
}

void init(){
	s1::index = 1;
	typeTree = 0;
	//s2

	treeHasGroudon = false;
	treeHasKyogre = false;
	treeHasRayquaza = false;
	//s4

	treeHasArticuno = false;
	treeHasMoltres = false;
	treeHasZapdos = false;
	treeHasLugia = false;
	//s5

	treeHasRaikou = false; RaikousInformation = NULL; rWasRecovered = false; rWasRevived = false;
	treeHasSuicune = false; SuicunesInformation = NULL; sWasRecovered = false; sWasRevived = false;
	treeHasEntei = false; EnteisInformation = NULL; eWasRecovered = false; eWasRevived = false;
	treeHasHoOh = false;
	//s6

	treeHasReshiram = false;
	treeHasZekrom = false;
	treeHasKyurem = false;

}

void battle(eventList* pEvent, legendTree*& aTree){
	// TO DO
	init();
	for (eventList *i = pEvent; i != NULL; i = i->next){
		int code = i->nEventCode;
		int number = abs(code / 100);
		bool isS1 = !isSpecialValue(number);
		bool success = false;

		nodeTree *p = NULL;

		//check input
		if (!initIsSuccess(aTree->root, p, code, isS1))
			continue;

		s4::decExist(aTree->root, p);	
		if (s4::fighting()) s4::allIsSubbed10(aTree->root, aTree->root);

		//choose
		switch (number){
			case Groudon: case Kyogre: case Rayquaza:
				success = s2::s2(aTree->root, p);
				if (success) s1::s1(aTree->root, p);
				else { delete p; p = NULL; }
				break;
			case Virizion: case Keldeo: case Cobalion: case Terrakion:
				//displayTree(aTree->root); cout << endl; displayTree_LNR(aTree->root); cout << endl; cout << endl;
				s3::s3(aTree->root, p->hoopa, number);
				delete p;
				p = NULL;
				break;
			case Articuno: case Moltres: case Zapdos: case Lugia:
				displayTree(aTree->root); cout << endl; displayTree_LNR(aTree->root); cout << endl; cout << endl;
				success = s4::s4(aTree->root, p);
				displayTree(aTree->root); cout << endl; displayTree_LNR(aTree->root); cout << endl; cout << endl;
				if (success) s1::s1(aTree->root, p);
				else { delete p; p = NULL; }
				displayTree(aTree->root); cout << endl; displayTree_LNR(aTree->root); cout << endl; cout << endl;
				break;
			case Raikou: case Entei: case Suicune: case HoOh:
				
				success = s5::s5(aTree->root, p);
				if (success) s1::s1(aTree->root, p);
				else { delete p; p = NULL; }
				break;
			case Zekrom: case Reshiram: case Kyurem:
				success = s6::s6(aTree->root, p);
				if (success) s1::s1(aTree->root, p);
				else { delete p; p = NULL; }
				break;
			default:
				s1::s1(aTree->root, p);
				break;

		}
		if (p != NULL)
		if (p->exp <= 0){
			s4::delExp0(aTree->root, p);
			//delete p;
			//continue;
		}
		s2::incExist(p);

		s5::hoOhRecover3Animal(aTree->root);
		s5::hoOhRevive3Animal(aTree->root);
		if (treeHasReshiram && treeHasKyurem && !treeHasZekrom){
			nodeTree *temp = NULL;
			init();
			s6::yang(aTree->root, temp);
			s6::deleteTree(aTree->root);
			aTree->root = temp;

		} else if (!treeHasReshiram && treeHasKyurem && treeHasZekrom){
			nodeTree *temp = NULL;
			init();
			s6::yin(aTree->root, temp);
			s6::deleteTree(aTree->root);
			aTree->root = temp;
		}
		
	}
}
/*
* =========================================================================================
* Name        : pokemon.cpp
* Author      : Nguyen Hoang Minh
* Email       : nghoangminh1505@gmail.com
* Copyright   : Faculty of Computer Science and Engineering - HCMC University of Technology
* Description : Initial code for Assignment 1 - Data structures and Algorithms - March 2016
* =========================================================================================
*/

//REMEMBER: Do not include any other library. Otherwise you will get 0 mark. :P

#ifndef _DEFS_H_
#include "defs.h"
#define _DEFS_H_
#endif

struct node{
	int data;
	node *next;
};

struct queue{
	node *front;
	node *rear;
	int count;
};

queue* createQueue(){
	queue *q = new queue;
	q->front = 0;
	q->rear = 0;
	q->count = 0;

	return q;
}
bool EmptyQueue(queue *q){
	return q->front == 0;
}
void EnQueue(queue *&q, int data){
	//create node
	node *p = new node;
	p->data = data;
	p->next = 0;
	//enqueue
	if (q->front == 0){
		q->front = p;
		q->rear = p;
		q->count = 1;
		return;
	}
	q->rear->next = p;
	q->rear = q->rear->next;
	q->count++;
}
void DeQueue(queue *&q, int &data){
	if (EmptyQueue(q))
		return;
	node *temp = q->front;
	data = q->front->data;
	q->front = q->front->next;
	delete temp;
}
void clearQueue(queue *q){
	int data = 0;
	while (!EmptyQueue(q)){
		DeQueue(q, data);
	}
	delete q;
}

namespace s0{
	void s0(arceus *arc, bool &fake){
		int n = 0;
		for (piece *i = arc->piece_of_life; i != 0; i = i->next){
			n++;
		}
		fake = (n == 16) ? true : false;
	}
}

namespace s1{//ab khong thuoc [1 , 16]

	pokemon *khaiBaoSucManh(int attribute, int exp){
		pokemon *p = new pokemon;

		p->attribute = attribute;
		p->exp = exp;
		p->next = 0;

		return p;
	}

	void thamGiaTeamPokemon(pokemon *&poke, pokemon *p){
		if (poke == 0){
			poke = p;
			return;
		}
		pokemon *tail = 0;
		for (pokemon *i = poke; i != 0; i = i->next){
			tail = i;
		}
		tail->next = p;
	}

	void s1(pokemon *&poke, int code){
		int exp = code / 1000;
		int attribute = code / 10 - exp * 100;
		if (!(1 <= attribute&&attribute <= 16)) return;
		pokemon *p = khaiBaoSucManh(attribute, exp);
		thamGiaTeamPokemon(poke, p);
	}
}

namespace s2{//ab khong thuoc [1 , 16]
	void s2(pokemon *&poke, int code){
		int soLuong = code / 10000;//5
		int exp = code / 1000 - soLuong * 10;//5
		int attribute = code / 10 - code / 1000 * 100;
		if (!(1 <= attribute&&attribute <= 16)) return;
		for (int i = 0; i < soLuong; i++){
			pokemon *p = s1::khaiBaoSucManh(attribute, exp);
			s1::thamGiaTeamPokemon(poke, p);
		}

	}
}

namespace s3{//attack
	/*
	tan cong:
	- neu co AB (vo hieu hoa don tan cong)	-> hp -= 0
	neu khong								-> hp -= exp
	- exp--
	- exp == 0								-> bi loai khoi danh sach
	- hp == 0								-> ket thuc combat
	-
	*/
	bool ArceusIsAttribute(arceus *arc, int attribute){
		for (piece *i = arc->piece_of_life; i != 0; i = i->next)
			if (i->attribute == attribute)
				return true;
		return false;
	}

	void themVaoDauDSTeam(pokemon *&poke, pokemon *p){
		if (poke == 0){
			poke = p;
			return;
		}
		p->next = poke;
		poke = p;
	}

	void s3(arceus *&arc, pokemon *&poke, int code){//XAB
		int exp = code / 100;
		int attribute = code % 100;
		if (!(1 <= attribute&&attribute <= 16)) return;
		arc->hp = arc->hp - (!ArceusIsAttribute(arc, attribute) ? exp : 0);
		if (arc->hp <= 0){
			arc->hp = 0;
			return;
		}
		exp--;

		if (exp > 0){
			pokemon *p = s1::khaiBaoSucManh(attribute, exp);
			themVaoDauDSTeam(poke, p);
		}
	}
}

namespace s4{
	/*
	ca team tan cong
	- neu co AB (vo hieu hoa don tan cong)	-> hp -= 0
	neu khong								-> hp -= exp
	- exp--
	- exp == 0								-> bi loai khoi danh sach
	- hp == 0								-> ket thuc combat
	*/

	void delPoke(pokemon *prev, pokemon *&index, pokemon *&head){
		if (prev == 0){
			pokemon *temp = head;
			head = head->next;
			delete temp;
			return;
		}

		prev->next = index->next;
		delete index;
		index = 0;
	}
	//xoa nhung pokemon co exp = 0
	void delExp0(pokemon *&poke, bool &isDel){
		pokemon *prev = 0;
		for (pokemon *i = poke; i != 0;){
			if (i->exp <= 0){
				delPoke(prev, i, poke);
				i = poke;
				prev = 0;
				isDel = true;
			}
			else{
				prev = i;
				i = i->next;
			}
		}
	}

	void s4(arceus *&arc, pokemon *&poke){
		for (pokemon *i = poke; i != 0; i = i->next){
			bool isDel = false;
			arc->hp = arc->hp - (!s3::ArceusIsAttribute(arc, i->attribute) ? i->exp : 0);

			if (arc->hp <= 0) {
				arc->hp = 0;
				return;
			}

			i->exp--;
			delExp0(poke, isDel);
			if(isDel) i = poke;
			if (poke == 0) break;
		}
	}
}

namespace s5{
	bool isPrime(int n){
		for (int i = 2; i < n; i++){
			if (n % i == 0)
				return false;
		}
		return true;
	}

	/*-----------	MEGAFLAME	-----------
	* vi tri chia het cho 5 se bi tieu diet
	*/
	void megaFlame(pokemon *&poke){
		pokemon *prev = 0;
		pokemon *temp = 0;
		int count = 1;

		for (pokemon *i = poke; i != 0; i = i->next, count++){
			if (count % 5 == 0) {
				s4::delPoke(prev, i, poke);
				i = prev;
			}
			prev = i;
			if (poke == 0) break;
		}
	}

	void reverse(pokemon *&poke){
		pokemon *poke_new = 0;

		while (poke != 0){
			//addHead -> s3
			pokemon *p = s1::khaiBaoSucManh(poke->attribute, poke->exp - 1);
			s3::themVaoDauDSTeam(poke_new, p);
			//removeHead
			pokemon *temp = poke;
			poke = poke->next;
			delete temp;
		}

		poke = poke_new;
	}

	/* -----------	SUPER STORM	-----------
	* dao nguoc doi hinh
	* chi so exp giam 1 don vi
	*/
	void superStorm(pokemon *&poke){
		//reverse team
		reverse(poke);
		//giam exp 1
		for (pokemon *i = poke; i != 0; i = i->next){
			bool isDel = false;
			i->exp--;
			s4::delExp0(poke, isDel);
			if(isDel) i = poke;
			if (poke == 0)break;
		}

	}

	int fibonacci(int n){
		if (n == 0) return 0;
		return (n == 1) ? 1 : (fibonacci(n - 1) + fibonacci(n - 2));
	}

	/*-----------	MEGABLAST	-----------
	* tao ra z phan than
	* duoc chen vao vi tri thu j
	* j thuoc day os fibonacci
	* phan than chen vao sau vi tri thu j trong team pokemon -> luu dia chi cua muc tieu se bi tieu diet
	* pokemon o truoc va sau phan than se bi tieu diet
	* khong co vi tri thu j phan se duoc chen vao vi tri cuoi cung
	*/

	/*	1		2		3		4		5		6
	*	(02_2)	(03_9)	(01_9)	(10_1)	(11_2)	(02_3)
	*	1
	*			2
	*					3
	*									5
	*
	*														8
	*/
	void megaBlast(pokemon *&poke, int z){
		queue *zPhanThan = createQueue();
		for (int i = z + 1; i >= 2; i--){
			EnQueue(zPhanThan, fibonacci(i));
		}
		//
		int j;
		while (!EmptyQueue(zPhanThan)){
			DeQueue(zPhanThan, j);
			pokemon *prev = 0;
			int count = 1;
			for (pokemon *i = poke; i != 0; i = i->next, count++){

				if (count == j){
					switch (j){
					case 2:
					case 3:
						s4::delPoke(prev, i, poke);
						break;
					default:
						//i
						pokemon *temp = i;
						s4::delPoke(prev, temp, poke);
						i = (prev == 0) ? poke : prev;
						//i+1
						if (i != 0)
							if (i->next != 0){
								i = i->next;
								temp = i;
								s4::delPoke(prev, temp, poke);
							}

						break;
					}
					break;
				}
				prev = i;
			}

		}
		clearQueue(zPhanThan);

	}

	/*
	*team pokemon co 5 phan tu, z phan than gom {1, 2, 3, 5, 8, 13}
	*cac vi tri	: 1 2 3 4 5
	*jth phan than	: 1x2x3x4 5x x x
	*				:  1 2 3	 5 8 13
	*/
	/*	1	 2	  3	   4	5	 6	  7	   8	9	 10	  11
	*	06_7 11_5 11_5 11_5 11_5 11_5 03_3 03_3 03_3 13_5 16_9
	*		x	 x	  x			x			   x			  x
	*		1	 2	  3			5			   8			  13
	*	06_0 11_0 11_0 11_0 11_0 11_0 03_3 03_0 03_0 13_5 16_0
	*	   0	0	 0	  0	   0	0		  0	   0		 0
	*								  03_3			 13_5
	*/
	void danhdau(pokemon *&poke, int j){
		pokemon *run = poke;
		for (int i = 0; i < j - 1; i++){
			if (run == 0) break;
			run = run->next;
		}
		if (run){
			run->exp = 0;
			if (run->next) run->next->exp = 0;
			return;
		}
		pokemon *tail = poke;
		for (pokemon *i = poke; i != 0; i = i->next)
			tail = i;
		tail->exp = 0;
	}

	void megaBlast1(pokemon *&poke, int z){
		for (int i = 2; i <= z + 1; i++){
			int j = fibonacci(i);
			danhdau(poke, j);
		}
		bool isDel = false;
		s4::delExp0(poke, isDel);
	}

	/*-----------	EARTHQUAKE	-----------
	* cac attribute
	* bug	- dark	- dragon	- flying	- ghost	- psychic
	* 01	- 02	- 03		- 07		- 08	- 13
	* duoc mien dich
	* con lai se bi tieu diet
	*/
	void earthquake(pokemon *&poke){
		pokemon *prev = 0;
		for (pokemon *i = poke; i != 0;){
			switch (i->attribute){
			case 1:	//bug
			case 2:	//dark
			case 3:	//dragon
			case 7:	//flying
			case 8:	//ghost
			case 13://psychic
				prev = i;
				i = i->next;
				break;
			default:
				s4::delPoke(prev, i, poke);
				i = poke;
				break;
			}
		}
	}

	/*-----------	BLADEROCK	-----------
	* team xep lai thu tu de chong do
	* 1)	rock(14): len dau danh sach + giam dan (exp)
	* 2)	con lai : sau rock(14) giam dan (exp) - neu cung exp tang dan (attbute)
	* 3)	giam exp-- cho tat ca
	*/

	void delListPoke(pokemon *&poke){
		while (poke != 0){
			pokemon *temp = poke;
			poke = poke->next;
			delete temp;
		}
	}

	void bladeRock(pokemon *&poke){
		pokemon *poke1 = 0;

		//1) rock(14)
		for (pokemon *i = poke; i != 0;){
			pokemon *prev = 0,
				*prevMin = 0,
				*min14max = 0;

			for (pokemon *j = poke; j != 0; j = j->next){
				if (j->attribute == 14){
					if (min14max == 0){
						prevMin = prev;
						min14max = j;
					}
					else if (j->exp > min14max->exp){
						prevMin = prev;
						min14max = j;
					}
				}
				prev = j;
			}
			if (min14max == 0) break;//khong co pokemon nao con thuoc tinh rock(14)
			//add vao danh sach moi poke1
			pokemon *p = s1::khaiBaoSucManh(min14max->attribute, min14max->exp);
			s1::thamGiaTeamPokemon(poke1, p);
			//del min14max
			s4::delPoke(prevMin, min14max, poke);
			i = poke;
		}

		//2) con lai

		for (pokemon *i = poke; i != 0;){
			pokemon *prev = 0,
				*prevMax = 0,
				*maxEminA = 0;

			for (pokemon *j = poke; j != 0; j = j->next){
				if (maxEminA == 0){
					prevMax = prev;
					maxEminA = j;
				}
				else{
					if (maxEminA->exp < j->exp){
						prevMax = prev;
						maxEminA = j;
					}
					else if (maxEminA->exp == j->exp){
						if (maxEminA->attribute > j->attribute){
							prevMax = prev;
							maxEminA = j;
						}
					}
				}

				prev = j;
			}
			pokemon *p = s1::khaiBaoSucManh(maxEminA->attribute, maxEminA->exp);
			s1::thamGiaTeamPokemon(poke1, p);
			//del min14max
			s4::delPoke(prevMax, maxEminA, poke);
			i = poke;
		}


		//3)
		for (pokemon *i = poke1; i != 0; i = i->next) {
			bool isDel = false;
			i->exp--;
			s4::delExp0(poke1, isDel);
			if(isDel) i = poke1;
			if (poke1 == 0) break;
		}
		//gan lai poke va huy vung nho
		pokemon *temp = poke;
		poke = poke1;
		delListPoke(temp);
	}

	/*
	* 0) team == empty	-> next (bo qua)
	* 1) XYZ % 100 == 0-> Mega-flame
	* 2) XYZ isPrime	-> Super-storm
	* 3) X == Y == Z	-> Mega-blast
	* 4) Z=Y+1&&Y=X+1	-> Earthquake
	* 5)				-> Blade rock
	*/
	void s5(pokemon *&poke, int code){
		if (poke == 0)return;
		int x = -code / 100;
		int y = -code / 10 - x * 10;
		int z = -code % 10;

		if (code % 100 == 0){
			megaFlame(poke);
		}
		else if (isPrime(-code)){
			superStorm(poke);
		}
		else if (x == y && y == z){
			megaBlast1(poke, z);
		}
		else if (((x == y + 1) && (y == z + 1))
			|| ((z == y + 1) && (y == x + 1))){
			earthquake(poke);
		}
		else{
			bladeRock(poke);
		}

	}
}

namespace s6{

	//SU KIEN NAY CHI XAY RA KHI S5 XAY RA
	/*
	* Palkia se be cong khong gian dua team pokemon vao khong gian alpha
	* - co exp tang dan		se duoc dua vao truoc
	* - co exp ngang nhau		se tu trai sang phai
	* Tu khong gian alpha tro lai doi hinh pokemon moi
	* - exp giam dan
	*/
	pokemon *alpha = 0;

	void vaoTrongKhongGianAlpha(pokemon *&poke){
		pokemon *prev = 0,
			*prevMin = 0,
			*minE = 0;

		for (pokemon *i = poke; i != 0;){
			prev = 0;
			prevMin = 0;
			minE = i;
			for (pokemon*j = i; j != 0; j = j->next){
				if (j->exp < minE->exp){
					prevMin = prev;
					minE = j;
				}
				prev = j;
			}

			//vao khong gian alpha
			pokemon *p = s1::khaiBaoSucManh(minE->attribute, minE->exp);
			s1::thamGiaTeamPokemon(alpha, p);
			//
			s4::delPoke(prevMin, minE, poke);
			i = poke;
		}
	}

	pokemon* raKhoiKhongGianAlpha(){
		pokemon *poke = 0;
		for (pokemon *i = alpha; i != 0;){

			pokemon *tail = i, *prev = 0;
			for (pokemon *j = alpha; j != 0; j = j->next){
				prev = tail;
				tail = j;
			}

			//pokemon *p = s1::khaiBaoSucManh(tail->attribute, tail->exp);
			//s1::thamGiaTeamPokemon(poke, p);
			if (prev == tail){
				s1::thamGiaTeamPokemon(poke, tail);
				alpha = 0;
				i = 0;
			}
			else{
				s1::thamGiaTeamPokemon(poke, tail);
				prev->next = 0;
			}

		}
		return poke;
	}

	void s6(pokemon *&poke){
		vaoTrongKhongGianAlpha(poke);
		poke = raKhoiKhongGianAlpha();
	}
}

namespace s7{
	/*
	* sau moi su kien dua doi hinh pokemon vao stack
	* su kien s7 xay ra se lui ve X su kien
	*/
	struct listTeam{
		pokemon *poke;
		listTeam *next;
	};
	struct stack{
		listTeam *top;
		int count;
	};
	stack* createStack(){
		stack *s = new stack;
		s->top = 0;
		s->count = 0;
		return s;
	}
	bool emptyStack(stack *s){
		return s->count == 0;
	}
	void push(stack *s, pokemon *p){
		listTeam *l = new listTeam;
		l->poke = p;
		l->next = 0;

		if (s->top == 0){
			s->top = l;
			s->count++;
			return;
		}
		l->next = s->top;
		s->top = l;
		s->count++;
	}
	void pop(stack *s, pokemon *&p){
		p = s->top->poke;

		listTeam *temp = s->top;
		s->top = s->top->next;
		delete temp;

		s->count--;
	}
	void clearStack(stack *&s){
		pokemon *data = 0;
		while (!emptyStack(s)){
			pop(s, data);
		}
	}

	pokemon* backup(pokemon *p){
		pokemon *b = 0;

		for (pokemon *i = p; i != 0; i = i->next){
			pokemon *t = s1::khaiBaoSucManh(i->attribute, i->exp);
			s1::thamGiaTeamPokemon(b, t);
		}

		return b;
	}
	stack *s = createStack();
	stack *s1 = createStack();
	void s7(pokemon *&poke, int code){
		int x = -(code % 10);
		for (int i = 0; i <= x; i++){
			if (emptyStack(s)) poke = 0;
			else {
				pop(s, poke);
				pokemon *b = backup(poke);
				push(s7::s1, b);
			}
		}
	}
	void s7f(pokemon *&poke, int code){
		int x = -(code % 10);
		for (int i = 0; i <= x; i++){
			if (emptyStack(s1)) poke = 0;
			else {
				pop(s1, poke);
				pokemon *b = backup(poke);
				push(s7::s, b);
			}
		}
	}
}

namespace s71{
	void s7(arceus *arc, pokemon *&poke, int moveEvent, eventList *eventlist){
		eventList *e = eventlist;
		int palkia = 0;
		for (int i = 0; i < moveEvent; i++){
			int code = e->nEventCode;
			if (1011 <= code&&code <= 9161){
				s1::s1(poke, code);
			}
			else if (11011 <= code&&code <= 99161){
				s2::s2(poke, code);
			}
			else if (101 <= code&&code <= 916){
				s3::s3(arc, poke, code);
				if (arc->hp <= 0) return;//chet
			}
			else if (code == 9){
				if (poke != 0)//danh sach pokemon khac rong
					s4::s4(arc, poke);
				if (arc->hp <= 0) return;//chet
			}
			else if (-999 <= code&&code <= -100){
				if (palkia){
					s6::s6(poke);
					palkia--;
				}
				else{
					s5::s5(poke, code);
				}
			}
			else if (code == -77){
				palkia++;
			}
			e = e->next;
		}

	}
}

void combat(eventList* pEvent, arceus *& pArceus, pokemon *& pPokemon){
	// TO DO
	bool fake = true;
	int palkia = 0;
	int sumEvent = 0;
	//aceus khong co bat ki manh nguon song nao

	for (eventList *i = pEvent; i != 0; i = i->next){
		int code = i->nEventCode;
		if (code == 0){
			s0::s0(pArceus, fake);
			if (!fake) return;//khong gia
		}
		else if (1011 <= code&&code <= 9161){
			s1::s1(pPokemon, code);
		}
		else if (11011 <= code&&code <= 99161){
			s2::s2(pPokemon, code);
		}
		else if (101 <= code&&code <= 916){
			s3::s3(pArceus, pPokemon, code);
			if (pArceus->hp <= 0) return;//chet
		}
		else if (code == 9){
			if (pPokemon != 0)//danh sach pokemon khac rong
				s4::s4(pArceus, pPokemon);
			if (pArceus->hp <= 0) return;//chet
		}
		else if (-999 <= code&&code <= -100){
			if (pPokemon)
				if (palkia){
					s6::s6(pPokemon);
					palkia--;
				}
				else{
					s5::s5(pPokemon, code);
				}
		}
		else if (code == -77){
			palkia++;
		}
		else if (-89 <= code&&code <= -81){
			s0::s0(pArceus, fake);
			if (!fake){
				int x = -(i->nEventCode % 10);
				pokemon *poke = 0;
				s71::s7(pArceus, poke, sumEvent - x, pEvent);
				s5::delListPoke(pPokemon);
				pPokemon = poke;
				return;
			}

		}
		sumEvent++;
	}

}

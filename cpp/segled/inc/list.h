#include "device.h"
#include "segled.h"


#ifndef LIST_H
#define LIST_H

class List {

struct Item
{
	uint8_t * array;
 uint8_t * first;
	Item * next;
 uint8_t index;
	Item (uint8_t i, Item * n = nullptr);
};

	Item * first;
	Item * last;
 Item * current;
	void (*function)();
	uint16_t count;
 uint8_t size;
public:
	//List();
 List (uint8_t s);
	~List();
 uint8_t * head () const {return first->array;}
	uint8_t * tail () const {return last->array;}
	void addFirst ();
	void addLast ();
 void showNo0de (uint8_t index);
 void showCurrent ();
 void setDataNode (uint8_t * data, uint16_t index);
 void increment ();
	void iterate ();
	void iterateData ();
	void print (uint16_t);
	uint16_t & getCount (){return count;}
	void setFunction (void (*f)());
};



#endif /* LIST_H_ */

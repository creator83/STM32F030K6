#include "device.h"
#include "segled.h"


#ifndef LIST_H
#define LIST_H

class List {

struct Item
{
	uint8_t * array;
	Item * next;
 uint8_t index;
	Item (uint8_t * a, Item * n = nullptr);
};

	Item * first;
	Item * last;
 Item * current;
	void (*function)();
	uint16_t count;
 uint8_t size;
public:
	//List();
 List ();
	~List();
 uint8_t * head () const {return first->array;}
	uint8_t * tail () const {return last->array;}
	void addFirst (uint8_t * arr);
	void addLast (uint8_t * arr);
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

#include "list.h"

List::Item::Item (uint8_t i, Item * n)
:next (n), index (i)
{
  first = array = new uint8_t [4];
  for (uint8_t i=0;i<4;++i)
  {
    *array++ = 0;
  }
}


/*List::List()
:count (0), first (nullptr), last (nullptr),size(0)
{
}*/

List::List (uint8_t s)
:size(s), count (0), first (nullptr), last (nullptr), current (nullptr)
{
 
}

List::~List()
{
	Item * current = nullptr;
	Item * next = first;
	while (next->next != nullptr)
	{
		current = next;
		next = next->next;
		delete current;
	}
	current = last;
	delete current;
}



void List::addFirst ()
{
	Item * newItem = new Item (count, first);
	if (first == nullptr)
	{
		last = newItem;
	}
	first = newItem;
	
 ++count;
}

void List::addLast ()
{
	Item * newItem = new Item (count);
	if (last == nullptr)
	{
		first = newItem;
	}
	else
	{
		last->next = newItem;
	}
	last = newItem;
	++count;
}

void List::iterate ()
{
	Item * next = first;
	//uint16_t counter = count;
	function ();
	for (uint16_t i=0;i<count;++i)
	{
		//next->object->draw();
		next = next->next;
	}
}

void List::iterateData ()
{
	Item * next = first;
	for (uint16_t i=0;i<count;++i)
	{
		//if (Data * ptr = dynamic_cast <Data *>(next->object)) next->object->draw();
		next = next->next;
	}
}
void List::showNo0de (uint8_t index)
{
 
}

void List::increment ()
{
 
}
void List::print (uint16_t n)
{
	Item * current = nullptr;
	Item * next = first;
	while (n--)
	{
		current = next;
		next = next->next;
	}
	//next->object->draw();
}

void List::setFunction (void (*f)())
{
	function = f;
}


#include "tree.h"



Tree::Item::Item(List *o, Item * p , Item * b , Item * s)
:object (o), parent (p), brother (b), son (s)
{
}


Tree::Tree(List *o)
{
Item * newItem = new Item (o);
	root = newItem;
	currentItem = newItem;

}

Tree::~Tree()
{
	Item * current = nullptr;
	Item * next = root;
	//while
}

/*
void Tree::addItem (List *o, Tbutton * but, Item *p)
{
	Item * newItem = new Item (o, but, p);
	Item * next = nullptr;
	if (p->son == nullptr)
	{
		p->son = newItem;
	}
	else
	{
		next = p->son;
		while (next->brother !=nullptr)
		{
			next = next->brother;
		}
		next->brother = newItem;
	}
}*/

void Tree::addSon (List *o)
{
	Item * newItem = new Item (o);
	currentItem->son = newItem;
	newItem->parent = currentItem;
	currentItem = newItem;

	//++count;
}

void Tree::addBrother (List *o)
{
	Item * newItem = new Item (o);
	currentItem->brother = newItem;
	newItem->parent = currentItem->parent;
	currentItem = newItem;
	//++count;
}

void Tree::setCurrent (List *o)
{
	/*Item * temp = root;
	Item * bro = nullptr;
	currentItem = root;
	if (currentItem->object == o)
	{
		return;
	}
	currentItem = currentItem->son;
	for (uint16_t i=0;i<count;++i)
	{
		if (currentItem->object == o)
		{
			return;
		}
		if (currentItem->brother != nullptr)
		{
			currentItem = currentItem->brother;
		}
		else
		{
			getBack ();
			currentItem = currentItem->son;
			bro = currentItem->brother;
			currentItem = currentItem->son;
		}

	}



	while (bro->brother != nullptr)
	{

		{
			currentItem = temp;
			return;
		}
		bro = bro->brother;
	}

	if (temp->object == o)
	{
		currentItem = temp;
	}
	else
	{
		if (temp->son != nullptr)
		{

		}
	}*/
}

void Tree::treeAction ()
{
	//currentItem->buttons->calculateTouch();
}

void Tree::getBack ()
{
	currentItem = currentItem->parent;
}

void Tree::getForward (uint16_t val)
{

	if (currentItem->son == nullptr)
	{
		return;
	}
	Item * temp = currentItem->son;
	for (uint8_t i=0;i<val;++i)
	{
		temp = temp->brother;
	}
	currentItem = temp;
}

void Tree::getRoot ()
{
	currentItem = root;
}

void Tree::useCurrent ()
{
	currentItem->object->iterate();
}


void getForward (Tree &t)
{

	if (t.currentItem->son == nullptr)
	{
		return;
	}
	Tree::Item * temp = t.currentItem->son;
	uint16_t val;
	//uint16_t val = t.currentItem->buttons->getResult();
	for (uint16_t i=0;i<val;++i)
	{
		temp = temp->brother;
	}
	t.currentItem = temp;
}

void getForward (Tree &t, uint16_t val)
{
	if (t.currentItem->son == nullptr)
	{
		return;
	}
	Tree::Item * temp = t.currentItem->son;
	for (uint16_t i=0;i<val;++i)
	{
		temp = temp->brother;
	}
	t.currentItem = temp;
}

void getBack (Tree &t)
{
	t.currentItem = t.currentItem->parent;
}

void getRoot (Tree &t)
{
	t.currentItem = t.root;
}


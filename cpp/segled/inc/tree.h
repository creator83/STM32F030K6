#include "device.h"
#include "list.h"


#ifndef TREE_H
#define TREE_H

class Tree {
public:
	//enum class action {act, back, home};
struct Item
{
	List * object;
	//Tbutton * buttons;
	Item * parent;
	Item * brother;
	Item * son;
	Item (List *o, Item * p = nullptr, Item * b = nullptr, Item * s = nullptr);
};
private:
	//uint16_t count;
public:
	Item * root;
	Item * currentItem;

public:
	Tree(List *o);
	~Tree();
	void addItem (List *, Item *);
	void addSon (List *o);
	void addBrother (List *o);
	void setCurrent (List *);

	void treeAction ();

	void getBack ();
	void getForward (uint16_t val);
	void getRoot ();
	void useCurrent ();

	friend void getForward (Tree &);
	friend void getForward (Tree &, uint16_t val);
	friend void getBack (Tree &);
	friend void getRoot (Tree &);
};

void getForward (Tree &);
void getForward (Tree &, uint16_t val);
void getBack (Tree &);
void getRoot (Tree &);


#endif /* LIST_H_ */

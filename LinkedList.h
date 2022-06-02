/*
 * LinkedList.h
 *
 *  	Created on: 	Oct 20, 2020
 *      Author: 		Ziya Karakaya
 *
 *      Version: 		0.5
 *      Last Update on: Mar 15, 2021
 *      Description: 	TODO
 *
 *		Update notes (v0.4):
 *		* Renamed Node to LLNode in order to prevent redefinition, when used with other ADTs.
 *
 *		Update notes (v0.3):
 *      * I have added deleteFirst operation. Similarly you can add deleteLast.
 *      * I made this version more optimized by adding searchAndFindPrev function in protected part
 *        It takes 3 parameters:
 *        	* first parameter: value to be searched
 *        	* second parameter: to store its node address
 *        	* third parameter: to store its previous node address
 *        This way we search, assign node address and prev node address in one pass.
 *
 *      License:		GPLv3
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <cassert>

namespace std {

template<typename T>
struct LLNode{
	T 			data;
	LLNode<T>* 	next;
};

template<typename T>
class LinkedList {
protected:
	LLNode<T>*   	head;
	LLNode<T>*   	tail;
	int 		count;
public:
	LinkedList();
	virtual ~LinkedList();
	LinkedList(const LinkedList &other);
	LinkedList& operator=(const LinkedList &other);

	bool isEmpty() const;
	int length() const;

	LLNode<T>* search(const T& val);
	void insertFirst(const T &val);
	void insertLast(const T &val);

	void insertAt(const int idx, const T &val);
	void insertAfter(const T &sVal, const T &val);
	void insertBefore(const T &sVal, const T &val);

	
	void deleteNode(const T& item);
	
	void deleteFirst();
	void clearList();

	T front() const;
	T back() const;

	template <typename S>
	friend ostream& operator<<(ostream& out, const LinkedList<S> &list);

	void reversePrint();

protected:
	void recursiveReversePrint(LLNode<T> *p);

};

template <typename T>
LinkedList<T>::LinkedList() {
	head = tail = NULL;
	count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	clearList();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList &other) {
	head = tail = NULL;
	LLNode<T> *p = other.head;

	while (p != NULL){
		insertLast(p->data);
		p = p->next;
	}
	count = other.count;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList &other) {
	clearList();
	if (other.count == 0)
		return *this;

	LLNode<T> *p = other.head;
	while(p != NULL){
		insertLast(p->data);
		p = p->next;
	}
	return *this;
}


template <typename T>
bool LinkedList<T>::isEmpty() const{
	return (count == 0);
}

template <typename T>
int LinkedList<T>::length() const{
	return count;
}

template <typename T>
LLNode<T>* LinkedList<T>::search(const T &val){
	bool found = false;
	LLNode<T> *p = head;
	while ((p != NULL) && !found){
		if (p->data == val)
			found = true;
		else
			p = p->next;
	}
	return p;
}

template <typename T>
void LinkedList<T>::insertFirst(const T &val){
	LLNode<T> *p = new LLNode<T>;
	p->data= val;
	p->next = head;
	head = p;
	if (tail == NULL)
		tail = p;

	count++;
}

template <typename T>
void LinkedList<T>::insertLast(const T &val){
	LLNode<T> *p = new LLNode<T>;
	p->data = val;
	p->next = NULL;

	if (head != NULL){
		tail->next = p;
		tail = p;
	}
	else{
		head = tail = p;
	}
	count++;
}

template <typename T>
void LinkedList<T>::insertAt(const int idx, const T &val){
	if (idx > count){
//		cout << "Given index is greater than the number of element, so appending to list"<<endl;
		insertLast(val);
	}
	else if (idx <= 1){
//		cout << "Given index value is less than or equal to 1, so inserting as the first element"<<endl;
		insertFirst(val);
	}
	else{ // insert at given position
		LLNode<T> *prevNode = head;
		int cnt=2;
		while (cnt < idx){
			prevNode = prevNode->next;
		} // we found (idx-1)'th node

		LLNode<T> *newNode = new LLNode<T>;
		newNode->data = val;
		newNode->next = prevNode->next;
		prevNode->next = newNode;
	}
	count++;
}

template <typename T>
void LinkedList<T>::insertAfter(const T &sVal, const T &val){
	LLNode<T> *searchItem = search(sVal); // search for sVal in the list
	if (searchItem == NULL){
		cout << "The value "<<sVal<<" is not found in the list, so nothing will be inserted."<<endl;
	}
	else{ // we found searched item
		LLNode<T> *newNode = new LLNode<T>;
		newNode->data = val;
		newNode->next = searchItem->next;
		searchItem->next = newNode;
		count++;
	}
}

template <typename T>
void LinkedList<T>::deleteNode(const T& item)
{
	LLNode<T> *p, *q;//p:current, q:next node
	bool found=false;
	//if the list is empty
	if (head == NULL)
		cout << "Cannot delete from empty list." << endl;
	else
	{
		if (head->data == item) // delete first node
		{
			p = head; // first node to be deleted
			head = head->next; //new head will be adjusted as next node
			delete p;
			count--;
			// if the list has only one node- after deletion the list becomes empty
			if (head == NULL)
				tail = NULL;
			
		}
		else// the item to be deleted is not the first node, somewhere in the list or last
		{
			found = false;
			//two pointers defined
			p = head;// p showing first node
			q = head->next;// q showing the second node

			while (q != NULL && !found)//search for the item to be deleted
			{
				if (q->data == item)
				{
					found = true;
				}
				else
				{
					p = q;
					q = q->next;
				}
			}
			if (found)//if found delete the node
			{
				p->next = q->next;
				count--;
				
				if (tail == q)//node to be deleted was the last node
					tail = p;//update the last node
				delete q;// delete the node from list
			}
			else//if not found
			{
				cout << "Item to be deleted is not in the list." << endl;
			}
		}
	}
}




template <typename T>
void LinkedList<T>::deleteFirst(){
	if (!isEmpty()){
		LLNode<T> *p = head;
		head = head->next;
		if(head==NULL)
			tail=NULL;
		delete p;
		count--;
	}
	else cout<<"Linked List is already empty."<<endl;
}

template <typename T>
void LinkedList<T>::clearList() {
	LLNode<T> *p;

	while (head != NULL){
		p = head;
		head = head->next;
		delete p;
	}
	tail = NULL;
	count = 0;
}

template <typename T>
T LinkedList<T>::front() const{
	assert(head != NULL&&"Linked List has no elements");
	return head->data;
}

template <typename T>
T LinkedList<T>::back() const{
	assert(tail != NULL);
	return tail->data;
}

template <typename T>
ostream& operator<<(ostream& out, const LinkedList<T> &list){
	LLNode<T> *p = list.head;
	while(p != NULL){
		out << p->data << " ";
		p = p->next;
	}
	return out;
}

template<class T>
void LinkedList<T>::reversePrint() {
	recursiveReversePrint(head);
}


template<class T>
void LinkedList<T>::recursiveReversePrint(LLNode<T> *p) {
	if (p != NULL) {
		recursiveReversePrint(p->next); //recursive call
		cout << p->data << " ";
	}
}

} /* namespace std */

#endif /* LINKEDLIST_H_ */

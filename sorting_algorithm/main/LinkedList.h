#pragma once
#include"Node.h"

template <class T> class LinkedList {
private:
	// define type for readability
	typedef T valueType;
	typedef T& referenceType;
	typedef Node<T> nodeType;
	typedef LinkedList<T> listType;
	typedef LinkedList<T>& listReferenceType;
	Node<T>* first;
	Node<T>* last;
	int size;


public:
	LinkedList(); // constructor
	LinkedList(LinkedList &sourceLinkedList); // copy constructor
	~LinkedList(); // destructor

	// operations
	nodeType* getPointerTo(const int nodePosition);
	void displayLinkedList();
	bool isEmpty();
	int getLength();
	int searchNode(const valueType searchQuery);
	valueType getFirst();
	valueType getLast();
	valueType get(const int position);
	void insertFirst(const valueType inputData);
	void insertLast(const valueType inputData);
	void insert(const valueType inputData, const int position);
	void removeFirst();
	void removeLast();
	void remove(const int position);
	void clear();
	void copyList(listReferenceType source);
	listReferenceType operator= (listReferenceType source);

};



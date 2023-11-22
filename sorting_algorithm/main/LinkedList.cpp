#include "LinkedList.h"
#include <iostream>
using namespace std;

template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<double>;
template class LinkedList<char>;
template class LinkedList<wchar_t>;
template class LinkedList<bool>;
template class LinkedList<std::string>;


template<class T> // avg/worst case O(n): valid input / success, best case O(1): failure / invalid input
Node<T>* LinkedList<T>::getPointerTo(const int nodePosition) // get the node with the corresponding position
{
	if (nodePosition >= size || nodePosition < 0) { // guarantee fail searches
		return nullptr;
	}

	Node<T>* result = first; // get the first node pointer, and cycle the list until find the index (i) matches the nodePositon parameter
	for (int i = 0; i < nodePosition; i++) {
		result = result->getNextPointer();
	}
	// this will guarantee the correct result so no failure check here
	return result;
}

template<class T> // O(n)
void LinkedList<T>::displayLinkedList()
{
	// cycle the pointer below, extract and print it's data before moving on to the next node
	Node<T>* interation = this->first;
	for (int i = 0; i < size; i++) {
		cout << interation->getData() << " ";
		interation = interation->getNextPointer();

	}
	cout << endl;
}

//O(1)
template <class T> bool LinkedList<T>::isEmpty() { 
	//size = 0 -> return true (1), size > 0 -> return false (0), there are no realistic case where size < 0 (size is private)
	return size == 0; // the data is always reliable so no check for errors
}

//O(1)
template <class T> int LinkedList<T>::getLength() {
	return size;	// return the private size variable from the class, the data is always reliable so no check for errors
}

template<class T> // O(n)
int LinkedList<T>::searchNode(const valueType searchQuery)
{
	if (!isEmpty()) {
		// cycle the nodes until:
		// A. a valid node -> end the loop and return it's position
		// B. reached the end without encountering A -> return an "error" position (mine is -1)
		Node<T>* currentNode = first;
		for (int i = 0; i < size; i++) {
			if (currentNode->getData() == searchQuery) {
				return i;
			}
			currentNode = currentNode->getNextPointer();
		}
	}

	// worst case: unable to find a valid node
	return -1;
}

template <class T> T LinkedList<T>::getFirst() { // O(1)
	return first->getData(); // call the node's operation to get it's data, this node
	// this node has a high usage traffic so it need a dedicated operation to optimise
	// component for output
}

template <class T> T LinkedList<T>::getLast() { // O(2)
	return last->getData();	// the same idea as getFirst() operation
}

template <class T> T LinkedList<T>::get(const int position) { // O(n)
	// 1. find the node using getPointerTo -> 2. return it's data using node's operation
	Node<T>* target = nullptr;
	target = getPointerTo(position); // this cost O(n)
	if (target == nullptr) { // getPointerTo can have failures, nullptr / NULL ->getData() will cause runtime error
		return NULL; //disadvantage: can be interpreted as 0 which can cause misunderstanding, know no other workaround
	};
	return target->getData();
}

template<class T> // O(1)
LinkedList<T>::LinkedList() // initialize list's variables with starter data
{
	this->first = nullptr;
	this->last = nullptr;
	this->size = 0;
}

template<class T> // O(n)
LinkedList<T>::LinkedList(LinkedList& sourceLinkedList) // initialize a l_list with another list's nodes's content
// the nodes in two list are seperated memory blocks
{
	LinkedList<T>* newLinkedList = new LinkedList;
	copyList(sourceLinkedList);
}

template<class T>
LinkedList<T>::~LinkedList() // O(n)
{
	//free the children node's memory
	clear();
}

template <class T> void LinkedList<T>::insertFirst(const valueType inputData) { // O(1)
	// create a new node with inputed data and set it's next node as the previous first node of the list
	// assign the new node as the new first node
	// change the size to match the new list
	Node<T>* newNode = new Node<T>;
	newNode->setData(inputData);
	newNode->setPointer(this->first);
	if (isEmpty()) { // if list is empty, we treat the last node the same as the first current node
		// first should already be nullptr so we don't have to do anything extra
		this->last = newNode;
	}
	this->first = newNode;
	this->size++;
}

template <class T> void LinkedList<T>::insertLast(const valueType inputData) { // O(1)
	// create a new node with inputed data, it's next node is already nullptr 
	// assign the new node as the current last node's next node
	// assign the new node as the new last node
	// change the size to match the new list
	Node<T>* newNode = new Node<T>;
	newNode->setData(inputData);
	newNode->setPointer(nullptr); // precaution measure, redundant
	if (isEmpty()) { // if list is empty, we stop caring about the current last node, and assign the first and last as the new node
		this->first = newNode;
	}
	else {
		this->last->setPointer(newNode);
	}
	last = newNode;
	this->size++;
}

template <class T> void LinkedList<T>::insert(const valueType inputData, const int position) { // O(n)
	if (position > this->size || position < 0) { // guarantee failures
		return;
	}
	// if the position fall into 0 or n-1, we cannot complete the operation, so we redirect those cases to other ops
	if (position == 0) { 
		insertFirst(inputData);
		return;
	}

	if (position == size) {
		insertLast(inputData);
		return;
	}
	
	// search the node with the previous position
	Node<T>* target = getPointerTo(position - 1);
	if (target == nullptr) {
		return;
	};
	// create a new node with input data and the pointer to the current node with the input position
	Node<T>* newNode = new Node<T>(inputData, target->getNextPointer());
	// change the prev node pointer to the new node
	target->setPointer(newNode);
	// change the size
	this->size++;
}

template <class T> void LinkedList<T>::removeFirst() { // O(1)
	// delete the first node and change the first node pointer in the class to the deleted node next in line
	// change the size
	if (!isEmpty()) {
		if (size == 1) {
			last = nullptr;
		}
		Node<T>* newFirst = first->getNextPointer();
		delete first;
		first = newFirst;
		size--;
	}
}

template <class T> void LinkedList<T>::removeLast() { // O(1)
	// delete last node
	// change it's prev node next pointer to nullptr
	// assign that prev node as the new last node
	// change size
	if (!isEmpty()) {
		if (size == 1) {
			delete last;
			last = first = nullptr;
		}
		else {
			Node<T>* newLast = getPointerTo(size - 2);
			newLast->setPointer(nullptr);
			delete last;
			last = newLast;
		}
		size--;
	}

}

template <class T> void LinkedList<T>::remove(const int position) { //O(n)
	// similar idea to insert
	if (!isEmpty() && position < size) {
		if (position == 0) {
			removeFirst();
			return;
		}

		if (position == size - 1) {
			removeLast();
			return;
		}

		// get prev and next
		// delete targeted node
		// "connect" prev and next
		Node<T>* neighborNodePrev = getPointerTo(position - 1);
		if (neighborNodePrev == nullptr) {
			return;
		};

		Node<T>* targetNode = neighborNodePrev->getNextPointer();
		Node<T>* neighborNodeNext = targetNode->getNextPointer();
		delete targetNode;
		neighborNodePrev->setPointer(neighborNodeNext);
		size--;

	}
}

template <class T> void LinkedList<T>::clear() { //O(n)
	// delete the first node until the list is empty
	while (size > 0) {
		removeFirst();
	}
}

template<class T>
void LinkedList<T>::copyList(listReferenceType source) // O(n)
{
	// cycle the source list's nodes
	// extract it's data, use it as an input to create new node in the original list
	Node<T>* currentNode = source.first;
	for (int i = 0; i < source.size; i++) {
		insertLast(currentNode->getData());
		currentNode = currentNode->getNextPointer();
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(listReferenceType source) // O(n)
{
	// easier way to call copyList
	if (this != &source) {
		if (!isEmpty()) {
			clear();
		}

		copyList(source);

	}
	return *this;
	
}



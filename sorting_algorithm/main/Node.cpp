#include "Node.h"
#include <iostream>
using namespace std;

template class Node<int>; 
template class Node<float>;
template class Node<double>;
template class Node<char>;
template class Node<wchar_t>;
template class Node<bool>;
template class Node<std::string>;

template<class T>
Node<T>::Node() // initialize node with starter datas (nextNode = nullptr) for future uses, O(1)
{
	this->nextNode = nullptr; 
}

template<class T>
Node<T>::Node(constReferenceType inputData, pointerType inputPointer) // initialize node with input data, use for insertion, O(1),
{
	this->data = inputData;
	this->nextNode = inputPointer;
}

template<class T>
Node<T>::~Node() // "detach" nextNode pointer, mostly redundant, O(1)
{
	nextNode = nullptr;
}

template<class T> // modify node data, O(1)
void Node<T>::setData(constReferenceType inputData)
{
	this->data = inputData;
}

template<class T> // modify node next pointer, O(1)
void Node<T>::setPointer(pointerType inputPointer)
{
	this->nextNode = inputPointer;
}

template<class T>
T Node<T>::getData() // extract node data without any modifications, use for output, O(1)
{
	return this->data;
}

template<class T>
Node<T>* Node<T>::getNextPointer() // extract next-in-line node w/o mods, components in searchs / insert / delete / output / ... functions, O(1)
{
	return this->nextNode;
}




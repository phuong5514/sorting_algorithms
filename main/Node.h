#pragma once

template <class T> class Node {
private:
	// define type for readability
	typedef T valueType;
	typedef T& referenceType;
	typedef T const& constReferenceType;

	typedef Node<T>* pointerType;
	typedef Node<T> const* constPointerType;

	// node 
	valueType data;
	pointerType nextNode;
public:
	// constructors / destructor
	Node();
	Node(constReferenceType inputData, pointerType inputPointer = nullptr); //create new node with inputed data
	~Node();

	//operation
	void setData(constReferenceType inputData); // modify node data
	void setPointer(pointerType inputPointer = nullptr); // modify node nextNode pointer

	valueType getData(); // return node data
	pointerType getNextPointer(); // return nextNode pointer
};


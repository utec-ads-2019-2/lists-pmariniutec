#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killSelf() {
	  delete next;
	  delete prev;
	  delete this;
    }

	Node(T val) : data(val), next(nullptr), prev(nullptr) { }
};

#endif

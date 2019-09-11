#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"
#include <stdexcept>
#include <string>
#include <iostream>

template <typename T>
class CircularLinkedList : public List<T> {
  public:
	CircularLinkedList() : List<T>() {}

	T front() {
	  if (this->head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return this->head->data;
	}

	T back() {
	  if (this->head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return this->tail->data;
	}

	void push_front(T value) {
	  auto newNode = new Node<T>(value); 

	  newNode->next = this->head; 
	  newNode->prev = this->tail; 

	  this->tail->next = this->head->prev = newNode; 

	  this->head = newNode; 
	  this->nodes++;
	}

	void push_back(T value) {
	  if (this->head == nullptr) {
		auto newNode = new Node<T>(value);
		newNode->next = newNode->prev = newNode;
		this->head = this->tail = newNode;
	  } else {
		auto newNode = new Node<T>(value);
		auto last = this->tail;
		newNode->next = this->head;
		this->head->prev = newNode;
		newNode->prev = last;
		last->next = newNode;
		this->tail = newNode;
	  }

	  this->nodes++;
	}

	void pop_front() {
	  auto tmp = this->head;
	  auto newFirst = tmp->next;
	  this->tail->next = newFirst;
	  this->head = newFirst;
	  this->head->prev = this->tail;
	  this->nodes--;
	  delete tmp;
	}

	void pop_back() {
	  if (empty()) {
		std::out_of_range("List is empty");
	  } else if (this->nodes == 1) {
		delete this->tail;
		this->head = this->tail = nullptr;
	  } else {
		auto tmp = this->tail;
		auto newLast = tmp->prev;
		newLast->next = this->head;
		this->head->prev = newLast;
		this->tail = newLast;
		delete tmp;
	  }

	  this->nodes--;
	}

	T operator[](int index) {
	  auto curr = this->head;
	  for (int i = 0; i < index; ++i) {
		curr = curr->next; 
	  }
	  return curr->data;
	}

	bool empty() {
	  return this->nodes <= 0;
	}

	int size() {
	  return this->nodes;
	}

	void clear() {
	  auto curr = this->head;
	  while (curr->next != this->head) {
		auto tmp = curr;
		curr = curr->next;
		delete tmp;
		this->nodes--;
	  }
	  this->head = this->tail = nullptr;
	  delete curr;
	  this->nodes--;
	}

	void sort() {
	  Node<T>* curr = this->head;
	  Node<T>* tmp;

	  for (int i = 0; i < size(); ++i) {
		tmp = curr->next;
		while (tmp != this->head) {
		  if (curr->data > tmp->data) {
			std::swap(tmp->data, curr->data);
		  }
		  tmp = tmp->next;
		}
		curr = curr->next;
	  }
	}

	// Utility function to insert at the end starting from a specified HEAD
	void insertEnd(Node<T>** head, Node<T>* newNode) {
	  if (*head == nullptr) {
		newNode->next = newNode->prev = newNode;
		*head = newNode;
		return;
	  }

	  Node<T>* last = (*head)->prev;

	  newNode->next = *head;
	  (*head)->prev = newNode;
	  newNode->prev = last;
	  last->next = newNode;
	}

	void reverse() {
	  if (this->head == nullptr)
		throw std::out_of_range("Head is null. Can't reverse list");

	  Node<T>* newHead = nullptr;

	  Node<T>* last = this->tail;
	  Node<T>* curr = last;
	  Node<T>* prev;

	  while (curr->prev != last) {
		prev = curr->prev;
		insertEnd(&newHead, curr);
		curr = prev;
	  }
	  insertEnd(&newHead, curr);

	  this->head = newHead;
	  this->tail = curr;
	}

	std::string name() {
	  return "Circular Linked List";
	}

	void merge(CircularLinkedList<T> cl) {
	  if (this->head == nullptr) {
		this->head = cl.head;
		this->tail = cl.tail;
	  } else {
		this->tail->next = cl.head;
		this->head->prev = cl.tail;
		cl.tail->next = this->head;
		cl.head->prev = this->tail;
	  }

	  this->nodes += cl.nodes;
	}

	BidirectionalIterator<T> begin() {
	  return { this->head };
	}

	BidirectionalIterator<T> end() {
	  return { this->tail };
	}

};

#endif

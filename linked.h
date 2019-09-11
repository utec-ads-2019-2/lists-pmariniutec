#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"
#include <stdexcept>
#include <string>
#include <iostream>

template <typename T>
class LinkedList : public List<T> {
  public:
	LinkedList() : List<T>() {}

	T front() {
	  if (this->head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return this->head->data;
	}

	T back() {
	  if (this->tail == nullptr)
		throw std::out_of_range("Tail Out of range");
	  return this->tail->data;
	}

	void push_front(T value) {
	  auto node = new Node<T>(value);
	  if (this->head != nullptr) {
		node->next = this->head;
		this->head = node->next;
	  } else {
		this->head = node;
		this->tail = node;
	  }
	  this->nodes++;
	}

	void push_back(T value) {
	  auto node = new Node<T>(value);
	  if (this->tail != nullptr) {
		auto tmp = this->tail;
		tmp->next = node;
		this->tail = node;
		this->tail->prev = tmp;
	  } else {
		this->head = this->tail = node;
	  }
	  this->nodes++;
	}

	void pop_front() {
	  if (empty()) {
		std::out_of_range("List is empty");
	  }
	  auto tmp = this->head;
	  this->head = tmp->next;
	  this->head->prev = nullptr;
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
		auto tmp = this->head;
		while (tmp->next->next != nullptr) {
		  tmp = tmp->next;
		}
		this->tail = tmp;
		delete this->tail->next;
		this->tail->next = nullptr;
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
	  while (curr->next != nullptr) {
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
	  insertionSort();
	}

	void sortedInsert(Node<T>** headRef, Node<T>* newNode) {
	  Node<T>* current;

	  if (*headRef == nullptr) {
		*headRef = newNode;
	  } else if ((*headRef)->data >= newNode->data) {
		newNode->next = *headRef;
		newNode->next->prev = newNode;
		*headRef = newNode;
	  } else {
		current = *headRef;

		while (current->next != nullptr && current->next->data < newNode->data)
		  current = current->next;

		newNode->next = current->next;

		if (current->next != nullptr)
		  newNode->next->prev = newNode;

		current->next = newNode;
		newNode->prev = current;
	  }
	}

	void insertionSort() {
	  Node<T>* sorted = nullptr;

	  Node<T>* current = this->head;
	  while (current != nullptr) {
		Node<T>* next = current->next;
		current->prev = current->next = nullptr;
		sortedInsert(&sorted, current);
		current = next;
	  }
	  this->head = sorted;
	}

	void reverse() {
	  if (this->head == nullptr) {
		throw std::out_of_range("Head is null. Can't reverse");
	  }
	  Node<T>* prv = nullptr;
	  Node<T>* cur = this->head;
	  Node<T>* nxt;
	  while (cur != nullptr) {
		nxt = cur->next;
		cur->next = prv;
		prv = cur;
		cur = nxt;
	  }
	  this->tail = this->head;
	  this->head = prv;
	}

	std::string name() {
	  return "Linked List";
	}

	void merge(LinkedList<T> ll) {
	  if (this->head == nullptr) {
		this->head = ll.head;
		this->tail = ll.tail;
	  } else {
		this->tail->next = ll.head;
		ll.head->prev = this->tail;
	  }

	  this->nodes += ll.nodes;
	}

	BidirectionalIterator<T> begin() {
	  return { this->head };
	}

	BidirectionalIterator<T> end() {
	  return { this->tail };
	}
};

#endif

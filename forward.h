#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"
#include <stdexcept>
#include <string>

template <typename T>
class ForwardList : public List<T> {
  public:
	ForwardList() : List<T>() {}

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
		this->tail->next = node;
		this->tail = node;
	  } else {
		this->head = node;
		this->tail = node;
	  }
	  this->nodes++;
	}

	void pop_front() {
	  auto tmp = this->head;
	  this->head = tmp->next;
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
	  bubbleSort();   
	}

	void bubbleSort() {
	  int swapped;
	  Node<T>* ptr1;
	  Node<T>* lptr = nullptr;

	  if (this->head == NULL)
		return;

	  do {
		swapped = 0;
		ptr1 = this->head;

		while (ptr1->next != lptr) {
		  if (ptr1->data > ptr1->next->data) {
			std::swap(ptr1->data, ptr1->next->data);
			swapped = 1;
		  }
		  ptr1 = ptr1->next;
		}
		lptr = ptr1;
	  } while (swapped);
	}

	void reverse() {
	  auto current = this->head;
	  Node<T>* prev = nullptr;
	  Node<T>* next = nullptr;

	  while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	  }

	  this->tail = this->head;
	  this->head = prev;
	}

	std::string name() {
	  return "Forward List";
	}

	void merge(ForwardList<T> fl) {
	  if (this->head == nullptr) {
		this->head = fl.head;
		this->tail = fl.tail;
	  } else {
		this->tail->next = fl.head;
	  }

	  this->nodes += fl.nodes;
	}

	ForwardIterator<T> begin() {
	  return { this->head };
	}

	ForwardIterator<T> end() {
	  return { this->tail };
	}
};

#endif

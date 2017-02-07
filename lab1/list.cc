#include "list.h"
#include <iostream>

List::List() : first(nullptr) {}

List::~List() {
  Node *currNode = first;
  Node *tmp;

  while (currNode != nullptr) {
    tmp = currNode->next;
    delete currNode;
    currNode = tmp;
  }
}

bool List::exists(int d) const {
  Node *currNode = first;

  while (currNode != nullptr) {
    if (currNode->value == d) {
      return true;
    }
    currNode = currNode->next;
  }

  return false;
}

int List::size() const {
  Node *currNode = first;
  int size = 0;

  while (currNode != nullptr) {
    currNode = currNode->next;
    size++;
  }

  return size;
}

bool List::empty() const { return first == nullptr; }

void List::insertFirst(int d) { first = new Node(d, first); }

void List::remove(int d, DeleteFlag df) {
  bool found = false;
  Node *currNode = first;
  Node *prevNode = first;

  while (currNode) {
    switch (df) {
      case DeleteFlag::LESS:
        found = currNode->value < d;
        break;
      case DeleteFlag::EQUAL:
        found = currNode->value == d;
        break;
      case DeleteFlag::GREATER:
        found = currNode->value > d;
        break;
    }

    if (found) {
      if (currNode == prevNode) {
        first = currNode->next;
      } else {
        prevNode->next = currNode->next;
      }
      delete currNode;
      return;
    }

    prevNode = currNode;
    currNode = currNode->next;
  }
}

void List::print() const {
  Node *currNode = first;

  std::cout << "[";
  while (currNode != nullptr) {
    std::cout << currNode->value;
    currNode = currNode->next;

    if (currNode != nullptr) {
      std::cout << ", ";
    }
  }
  std::cout << "]";
}

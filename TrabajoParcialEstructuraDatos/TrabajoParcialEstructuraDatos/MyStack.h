#pragma once
#include <string>
using namespace std;

template <typename T>
class MyStack {
	struct Node {
		T elem;
		Node* next;

		Node(T elem, Node* next = nullptr) : elem(elem), next(next) {}
	};

	Node* myTop;

public:
	MyStack() :myTop(nullptr) {}
	~MyStack() {
		while (!is_empty()) pop();
	}

	bool is_empty() {
		return myTop == nullptr;
	}

	bool push(T elem) {
		myTop = new Node(elem, myTop);
		return true;
	}

	bool pop() {
		if (!is_empty()) {
			Node* aux = myTop;
			myTop = myTop->next;
			delete aux;
			return true;
		}
		return false;
	}

	T top() { return myTop->elem; }

};



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
	int lon;

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
		++lon;
		return true;
	}

	bool pop() {
		if (!is_empty()) {
			Node* aux = myTop;
			myTop = myTop->next;
			delete aux;
			--lon;
			return true;
		}
		return false;
	}

	T top() {
		if (!is_empty()) {
			return myTop->elem;
		}
		return 0;
	}

};

// usar pila para almacenar strings con el nombre de los archivos guardados automaticamente cada vez que hay una colision jugador-caja y usar esos strings en una funcion load/carga
// evento para cuando se cumpla la condicion de victoria
// triple colision




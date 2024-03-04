//#include <vector>

#pragma once

class graph { // abstract base class without data structure
public:
	graph(int n) : n(n) { }
	int get_n() const { return n; }
	virtual void add_edge(int v1, int v2) = 0;
	virtual bool has_edge(int v1, int v2) const = 0;

	friend std::ostream& operator << (std::ostream& lhs, graph& rhs) {
		lhs << "E = { ";
		bool is_first{ true };
		for (int i{ 0 }; i < rhs.n; i++) {
			for (int j{ 0 }; j < rhs.n; j++) {
				if (rhs.has_edge(i, j)) {
					if (!is_first) {
						lhs << ", ";
					}

					lhs << " <" << i << ", " << j << ">";
					is_first = false;
				}
			}
		}

		return lhs << " }";
	}

private:
	int n; // n is the max. number of vertices, labelled 0 .. n - 1
}; // graph

class node {
public:
	int v{ -1 }; // vertex number, range 0 .. n – 1 for any graph(n)
	node* next{ nullptr };
	node() : v{ -1 }, next{ nullptr } {
	}
	node(int v, node* next = nullptr) : v(v), next(next) { }
}; // node

class al_graph : public graph {
public:
	al_graph(int n) : graph(n), m_nodes{ new node * [n] } {
		for (int i = 0; i < n; i++) {
			m_nodes[i] = nullptr;
		}
	}

	~al_graph() {
		for (int i = 0; i < get_n(); i++) {
			node* n = m_nodes[i];
			while (n != nullptr) {
				node* tmp = n;
				n = n->next;
				delete tmp;
			}
		}

		delete[] m_nodes;
	}

	virtual void add_edge(int v1, int v2) override {
		node* n = m_nodes[v1];
		/*node new_n{v2};
		if (n == nullptr) {
			m_nodes[v1] = new node{ v2 };
		}
		else {
			while (n->next != nullptr) {
				n = n->next;
			}
			n->next = new node{ v2 };
		}*/

		node* last = m_nodes[v1];
		while (last != nullptr && last->next != nullptr) {
			last = last->next;
		}

		if (last == nullptr) {
			m_nodes[v1] = new node{ v2 };
		}
		else {
			last->next = new node{ v2 };
		}
	}
	
	virtual bool has_edge(int v1, int v2) const override {
		node* src = m_nodes[v1];
		if (src == nullptr)
			return false;

		node* n = src;
		while (n != NULL && n->v != v2) {
			n = n->next;
		}

		return n != NULL;
	}

private:
	//std::vector<node*> v;
	node** m_nodes{ nullptr };
};
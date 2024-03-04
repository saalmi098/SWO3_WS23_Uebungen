#include <iostream>

#include "./klausur2022.h"
#include "./klausur2021.h"

void klausur2022() {
	person p{ 3443080958, "Max", "Mustermann" };
	person p2{ 3443080958, "Susi", "Sorglos" };
	std::cout << p << '\n';
	std::cout << p2 << '\n';

	//p = p2;
	//person p3{ p };

	std::cout << "equals? " << (p == p2) << '\n';
	std::cout << "< ? " << (p < p2);

	// ============================================

	element_vector v{ 5 };
	element_int e1{ 3 };
	element_str e2{ "Hello" };
	v.add(e1);
	v.add(e2);

	vector<int> v2{ 5 };
	v2.add(2);
	v2.add(3);

	vector<std::string> v3{ 5 };
	v3.add("Hello");
	v3.add("World");

	// Vergleich:
	// Komfort: Mit Vererbung sehr flexibel, aber mehr Code zu schreiben u. mehr Klassen benötigt
	//			z.B. kann man verschiedene Datentypen in einen Vektor zusammenfassen
	//
	// Sicherheit: Statische Typprüfungen bei Vererbung, aber auch Compilerfehler bei Templates
	//
	// Effizienz: Vererbung/Polymorphie benötigt dyn. Bindung (etwas langsamer),
	//			  Templates nur statische Bindung (kein Overhead)
}

void klausur2021() {
	al_graph g{ 4 };
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 1);

	std::cout << g.has_edge(0, 1) << "\n";
	std::cout << g.has_edge(0, 2) << "\n";
	std::cout << g.has_edge(1, 2) << "\n";
	std::cout << g.has_edge(2, 3) << "\n";
	std::cout << g.has_edge(3, 1) << "\n";

	std::cout << g.has_edge(0, 3) << "\n";
	std::cout << g.has_edge(2, 1) << "\n";
	std::cout << g.has_edge(3, 3) << "\n";
}

int main() {
	//klausur2022();
	klausur2021();
	return 0;
}
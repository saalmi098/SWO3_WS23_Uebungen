#include <vector>
#include <iostream>

void foo(std::vector<int> v) { // kopiert vector bei Aufruf (Call By Value)
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	
	for (int i{ 0 }; i < v.size(); ++i) { // würde genauso gehen: i < std::size(v1)
		std::cout << v[i] << ' ';
	}
	printf("\n");

	for (int const & e : v) {
		std::cout << e << ' ';
	}
	printf("\n");

	//auto b = v.begin(); // Begin-Iterator -> Iterator, der am 1. Element eines Vektors steht
	//auto e = v.end(); // End-Iterator, steht 1 über (!!) dem letzten Element (sonst würde b != e) unten
						// unten nicht alle Elemente ausgeben
	// Achtung: Iterator ist kein Pointer!! (es ist nur so ähnlich wie ein Pointer) -> "duck typing"
	// Pointer ist ein Iterator, aber ein Iterator ist kein Pointer
	// Iterator ist abstrakter

	// Schreibweise ohne auto:
	std::vector<int>::iterator b{ v.begin() };
	std::vector<int>::iterator e{ v.end() };

	// Von hinten nach vorne iterieren:
	// std::vector<int>::reverse_iterator b {v.rbegin()};
	// std::vector<int>::reverse_iterator e {v.rend()};
	// while-Schleife ist dann genau gleich wie unten (also auch mit b++)

	while (b != e) {
		std::cout << *b << ' '; // Iterator derefernzieren
		++b; // Iterator zum nächsten Element springen
	}
}

int main() {
	//std::vector<int> v1{ 1, 2, 3, 4 };
	std::vector v1{ 1, 2, 3, 4 }; // Datentyp <int> kann wegen initializer list weggelassen werden
								  // würde nicht mehr gehen bei std::vector v1{ 1, 2, 3.3, 4.2 }
	foo(v1);
}
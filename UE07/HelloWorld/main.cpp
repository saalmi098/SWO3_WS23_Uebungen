#include <iostream>
#include <string>
#include <fstream>
#include "./rational.h"

//void print(std::string str) {			// String "by value"
//void print(std::string * str) {		// String "by reference" in C
//void print(std::string const & str) {	// String "by refeference" (nur C++)
void print(std::string const & str, std::ostream & out = std::cout) {
	//std::cout << str << '\n';
	//str = "abcdef"; // ...möglich solange str nicht "const"

	out << str << '\n';
}

void test_1() {
	std::cout << "Hello World!\n"; // std:: ... Namespace
	// cout ... globale Var. vom Typ ostream (outputstream)

	std::string		str  {"Hallo"};
	std::string		str2 {};
	std::string &	str3 {str}; // Var str3 ist Referenz auf str (wie Pointer) -> Synonym
	std::cout << str << '\n';
	std::cout << str3 << '\n';

	std::cin >> str;
	std::cout << "Input: " << str << '\n';

	str2 += str + str3; // man muss nicht mehr wie in C Speicher allokieren, strcopy(), ...
}

void test_2() {
	// Aufruf print mit "C-String", 1. Variante von print() nimmt aber std::string
	// funktioniert wegen "Conversion-By-Constructor" (es gibt in std::string einen
	// Konstruktor, der einen C-String nimmt)
	// https://www.geeksforgeeks.org/g-fact-35/
	print("Hansi"); // geht nur mit Signatur ohne Pointer bzw. mit "const &"
					// verwendet default-Parameter Wert "std::cout"

	// s ist schon ein std::string -> keine Conversion mehr notwendig
	// s wird aber Call-By-Value übergeben -> String wird kopiert bei Aufruf
	// -> Pointer auf String übergeben
	// -> Vorteil: String wird nicht mehr kopiert
	// -> Nachteil: Pointer...
	// -> Lösung: & Operator bei Parameter ... "by reference" (best of both worlds)
	//    (= technisch gleich wie Pointer, jedoch muss man diesen nicht mehr explizit verwenden)
	std::string s{"Susi"}; // s...std::string, "Susi" ... C-String
	std::ofstream file{ "./output.txt" }; // ofstream macht autom. open/close
	
	//print(&s); // für Signatur mit Pointer
	print(s, file);
}

void test_3() {
	//rational const r; // => {0, 1}
	rational const r{ 42 }; // => {42, 1}
	//rational const r{ 42, 13 };
	// -> Laufzeitsystem reserviert Speicher für "r" am Call-Stack (da lokale Var.)

	std::ofstream file{ "./output.txt", std::ios::app }; // std::ios::app ... append mode
	//r.write(file);

	//r.write(file) << " some text\n";

	file << "r: " << r << " some text\n"; // operator overloading notwendig (für shift-left op.)
}

int main() {
	//test_1();
	//test_2();
	test_3();
}
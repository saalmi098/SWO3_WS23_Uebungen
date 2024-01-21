#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std::string_literals;

/*int max(int const a, int const b, int const c) {
	return std::max(a, std::max(b, c));
}

double max(double const a, double const b, double const c) {
	return std::max(a, std::max(b, c));
}

std::string max(std::string const & a, std::string const & b, std::string const & c) {
	return std::max(a, std::max(b, c));
}*/

// T ... Variable, die einen Datentyp enthält
// der Compiler erstellt für jeden Datentyp, für den max aufgerufen wird, eine Überladung (1 für int, 1 für int, ...)
template<typename T> T max(T const a, T const b, T const c) {
	return std::max(a, std::max(b, c));
}

template<typename T> class rational {
	T z;
	T n;
};

//class range final {
//	begin()
//	end()
//};

template <typename T> using unary_function	= void (T const &);
template <typename T> using unary_predicate	= bool (T const&);

template <typename I, typename F, typename P> void for_each_if(
	I b,
	I const e,
	F f,
	P const p) {
	//for (auto const& elem : range{ b, e }) 
	// - for mit Doppelpunkt braucht einen Datentyp, der begin(), end() und == Operator implementiert

	for (; b != e; ++b) {
		if (p(*b))
			f(*b);
	}
}

void test_templates() {
	// Datentyp-Parameter in spitzer Klammer kann man weglassen, wenn der Compiler diesen aus
	// der Parameter-Liste er#schließen kann
	std::cout << max /*<int>*/ (42, 99, 17) << '\n';
	std::cout << max /*<double>*/ (4.2, 9.9, 1.7) << '\n';

	//std::cout << max <char const *> ("Hansi", "Karli", "Susi") << '\n'; // Vergleicht Speicheradressen
				// max = jener, dessen Speicheradresse am weitesten hinten ist
	
	//std::cout << max <std::string>("Hansi", "Karli", "Susi") << '\n';
	std::cout << max <std::string>(std::string{ "Hansi" }, std::string{ "Karli" }, std::string{ "Susi" }) << '\n';

	// einfachere Syntax mit string literals
	std::cout << max("Hansi"s, "Susi"s, "Karli"s) << '\n'; // "Hansi" ... char*, "Hansi"s ... std::string

	rational <int> r;
	rational <long unsigned> r2;
}

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
	std::vector<int>::iterator b{v.begin()};
	std::vector<int>::iterator e{ v.end() };

	// Von hinten nach vorne iterieren:
	// std::vector<int>::reverse_iterator b {v.rbegin()};
	// std::vector<int>::reverse_iterator e {v.rend()};
	// while-Schleife ist dann genau gleich wie unten (also auch mit b++)

	while (b != e) {
		std::cout << *b << ' '; // Iterator dereferenzieren
		++b; // Iterator zum nächsten Element springen
	}
}

void test_std_vector() {
	//std::vector<int> v1{ 1, 2, 3, 4 };
	std::vector v1{ 1, 2, 3, 4 }; // Datentyp <int> kann wegen initializer list weggelassen werden
	// würde nicht mehr gehen bei std::vector v1{ 1, 2, 3.3, 4.2 }
	foo(v1);
}

template <typename E> class array_iterator {
public:
	using value_type = E; // für for_each_if() Funktion

	array_iterator(E* const position) : m_position{ position } {
	}

	bool operator == (array_iterator const& rhs) const {
		return m_position == rhs.m_position;
	}

	bool operator != (array_iterator const& rhs) const {
		return !(*this == rhs);
	}

	E& operator * () const {
		return *m_position;
	}

	array_iterator& operator ++ () { // prefix (benötigt für Iterator-For-Loop)
		++m_position;
		return *this;
	}

	array_iterator operator ++ (int) { // postfix
		array_iterator tmp{ *this };
		m_position++;
		return tmp;
	}

private:
	E* m_position{ nullptr }; // non-owning pointer
};

template <typename E, int N> class array {
public:
	array() : m_p_data{ new E[N] {} } {

	}

	~array() {
		delete [] m_p_data;
	}

	E& operator[] (int const i) {
		if (i < 0 || i >= N)
			throw std::range_error{ "index out of bounds (" + std::to_string(i) + ")"};
		
		return m_p_data[i];
	}

	[[nodiscard]] static int size() {
		return N; // size braucht keinen this-Pointer -> static
	}
	
	array_iterator<E> begin() const {
		return { m_p_data };
	}

	array_iterator<E> end() const {
		return { m_p_data + N }; // one-past-end
	}

private:
	E* m_p_data{ nullptr };
};

template <typename T> void print(T const & t) {
	std::cout << "'" << t << "'\n";
}

template<typename T> struct printer {
	void operator () (T const & value) const {
		print(value);
	}
};

struct predicate {
	auto operator () (std::string const& str) const {
		return str.size() == 4;
	}
};

void test_array() {
	array<std::string, 5> a1{};
	//array<std::string, 20> a2{}; // a1 und a2 haben 2 verschiedene Datentypen
		// a1 ... array of 10 strings, a2 ... array of 20 strings

	//a1 = a2; // nur möglich, wenn man einen = Operator implementiert, der 2 versch. Datentypen nimmt

	a1[0] = "Hansi";
	a1[1] = "Susi";
	a1[2] = "Karli";
	a1[4] = "Seppi";

	for (int i{ 0 }; i < a1.size(); ++i) {
		std::cout << "'" << a1[i] << "'\n";
	}
	std::cout << "---------------------------------\n";

	array_iterator <std::string>		b{ a1.begin() };
	array_iterator <std::string> const	e{ a1.end() };

	std::cout << "---------------------------------\n";

	while (b != e)
		std::cout << *b++ << ' ';
	std::cout << '\n';

	std::cout << "---------------------------------\n";

	for (auto const& elem : a1)
		std::cout << elem << ' ';
	std::cout << '\n';

	std::cout << "---------------------------------\n";

	std::cout << "\nFor Each:\n";
	std::for_each(a1.begin(), a1.end(), print<std::string>); // dem for_each muss man
	// in spitzen Klammern mitgeben, welches print aufgerufen werden soll

	std::cout << "---------------------------------\n";

	for_each_if(a1.begin(), a1.end(), [](std::string const& str) { // lambda expression (type parameter "F")
		std::cout << "l: " << str << '\n';
	}, [](std::string const& str) { // lambda expression (type parameter "P")
		return str.size() == 4; // gibt nur mehr "Susi" aus
	});

	std::cout << "---------------------------------\n";
	
	for_each_if(a1.begin(), a1.end(), printer<std::string>{}, predicate{});
}

void test_callable() {
	auto f{ [](int const i) {
		std::cout << i;
	} }; // Variable f enthält eine lambda-Funktion

	f(42);
}

//static int sum{}; // Problem: globale Variablen
//static char letter{};
//void sum_up(std::string const& str) {
//	sum += str.size();
//}
//
//bool starts_with(std::string const& str) {
//	return !str.empty() && str[0] == letter;
//}

class size_adder {
public:
	size_adder(int& s) : m_sum{ s } {
	}

	void operator () (std::string const& str) {
		m_sum += str.size();
	}

private:
	int & m_sum;
};

class starts_with_checker {
public:
	starts_with_checker(char const l) : m_letter{ l } {
	}

	bool operator () (std::string const& str) const {
		return !str.empty() && str[0] == m_letter;
	}

private:
	char const m_letter{};
};

void test_array2() {
	array<std::string, 5> a{};
	a[0] = "Hansi";
	a[1] = "Susi";
	a[2] = "Karli";
	a[4] = "Seppi";
	
	//for_each_if(a.begin(), a.end(), sum_up, starts_with);

	int i{}; // wird an size_adder als Referenz übergeben
	for_each_if(a.begin(), a.end(), size_adder { i }, starts_with_checker{'S'});
	std::cout << "Anzahl der Zeichen: " << i << '\n';

	std::cout << "---------------------------------\n";

	for_each_if(a.begin(), a.end(), [&i](std::string const& str) { // in eckige Klammern: "capture list"
		i += str.size();
	}, starts_with_checker{'S'});
	std::cout << "Anzahl der Zeichen: " << i << '\n';
}

int main() {
	//test_std_vector();

	//test_templates();

	//try {
	//	test_array();
	//}
	//catch (std::exception const & x) {
	//	std::cerr << "Error: " << x.what() << '\n' << std::flush;
	//}

	//test_callable();

	test_array2();
}
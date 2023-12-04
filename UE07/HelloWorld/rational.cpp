#include "./rational.h"

#include <cassert> // = #include <assert.h> in C
#include <format>

// klasse::methode
rational::rational(int const num, int const den)
	: m_num{ num }, m_den{ den } {
	// : var { var } , ... initializer list
	// m_num wird mit num initialisiert, m_den mit den
	// macht das selbe wie unten, aber spart die Default-Zuweisung (0/1),
	// die unten eh wieder überschrieben wird
	
	//m_num = num;
	//m_den = den;

	assert(m_den != 0); // besser wäre Exception werfen
}

std::ostream & rational::write(std::ostream & out) const {
	// m_num = 123; // nicht möglich, wegen const in Signatur
	return out << std::format("{{{}/{}}}", m_num, m_den);
}

/*std::ostream& operator << (std::ostream& lhs, rational const& rhs) {
	return rhs.write(lhs);
}*/
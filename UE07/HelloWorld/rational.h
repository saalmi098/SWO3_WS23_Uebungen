#pragma once

#include <iostream>

// final ... nicht ableitbar
class rational final {
	public:
		// const kann man hier weglassen, da dies nur für den
		// Implementierer relevant ist, den Aufrufer ist es egal
		rational(int num = 0, int den = 1);
		std::ostream & write(std::ostream & out = std::cout) const; // const damit Methode das Objekt nicht ändert,
							// für das es aufgerufen wird
		
		//friend std::ostream& operator << (std::ostream& lhs, rational const& rhs);
	private:
		int m_num {0}; // numerator (zaehler), default 0
		int m_den {1}; // denominator (nenner), default 1
};

// operator overloading
//std::ostream & operator << (std::ostream & lhs, rational const & rhs);
// Nachteil: außerhalb der Klasse, daher kein Zugriff auf private Variablen von rational
// Lösung: friend function (s. oben)
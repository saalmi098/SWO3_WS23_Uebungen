#pragma once

#include <iostream>

// final ... nicht ableitbar
class rational final {
	public:
		rational() = default;

		// const kann man hier weglassen, da dies nur für den
		// Implementierer relevant ist, den Aufrufer ist es egal
		rational(int num /* = 0 */, int den = 1);

		std::ostream & write(std::ostream & out = std::cout) const; // const: Diese Methode ändert das Objekt nicht, für das sie aufgerufen wird
		
		// Anm.: Kein Hidden Friend, sondern Klassen-Methode
		// rational & Rückgabetyp, damit man mit dem Objekt weiterarbeiten kann
		rational& operator *= (rational const& rhs) {
			m_num *= rhs.m_num;
			m_den *= rhs.m_den;

			// man koennte hier auch * operator verwenden, wenn man in * nicht das *= aufruft
			//return *this = (*this * rhs);
			return *this;
		}

		// const, da übergebene rationals nicht geändert werden müssen
		// und & damit man eine Referenz bekommt (erspart das kopieren des rational-Objekts bei CBV)
		friend rational operator * (rational lhs, rational const & rhs) {
			// rational tmp{ lhs }; return tmp *= rhs;
			// return rational {lhs} *= rhs; // Problem: manuelles Erstellen einer Kopie von lhs
			// Wir brauchen eine Kopie, daher brauchen wir nicht CBR übergeben
			// -> "const &" bei lhs löschen, damit man automatisch eine Kopie bekommt
			return lhs *= rhs;
			
			return {lhs.m_num * rhs.m_num, lhs.m_den * rhs.m_den};
		}

		friend bool operator == (rational const & lhs, rational const & rhs) {
			return lhs.m_num * rhs.m_den == lhs.m_den * rhs.m_num;
		}

		friend std::ostream& operator << (std::ostream& lhs, rational const & rhs) { // "hidden friend"
			return rhs.write(lhs);
		}

		int const & get_num() const {
			return m_num;
		}

		void set_num(int const num) {
			// if (num > ...) {
			m_num = num;
			// }
		}

		int & num() {  // setter und getter (entspricht Variable public machen)
			return m_num;
		}

	private:
		int m_num {0}; // numerator (zaehler), default 0
		int m_den {1}; // denominator (nenner), default 1
};

// operator overloading
//std::ostream & operator << (std::ostream & lhs, rational const & rhs);
// Nachteil: außerhalb der Klasse, daher kein Zugriff auf private Variablen von rational
// Lösung: friend function innerhalb der Klasse (s. oben)
//			-> lhs = aktuelles Objekt
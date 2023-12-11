#include <cstring>

class string final {
	public:
		// initializer initialisiert immer in der Reihenfolge in der die Datenkomponenten in der Klasse liegen
		string(char const * p_str = "") :	m_size {std::strlen(p_str)},
											m_p_buffer {new char[strlen(p_str) + 1]} {
			
			strcpy_s(m_p_buffer, m_size + 1, p_str);
		}

		string (string const & src) : string(src.m_p_buffer) { // Delegation an Default-Konstruktor
		}

		//string (string const &) = delete; // würde den Copy-Konstruktor löschen -> man kann string nicht
											// kopieren -> "non copyable strings"

		// Destruktor
		~string() {
			delete [] m_p_buffer;
		}

		string & operator = (string const & rhs) {
			if (this != &rhs) { // Schutz vor Mehrfachzuweisung (self assignment, z.B. s2 = s2)
				m_size = rhs.m_size;

				delete[] m_p_buffer;
				m_p_buffer = new char[rhs.m_size + 1];
				strcpy_s(m_p_buffer, m_size + 1, rhs.m_p_buffer);

				return *this;
			}
		}

	private:
		std::size_t	 m_size		{0};
		char * m_p_buffer		{nullptr};

};

int main() {
	string s1 {};
	string s2 { "Hansi" };
	string s3 {s2};
	string s4{ "Susi" };

	s2 = s2; // self assignment

	s2 = s4;
}
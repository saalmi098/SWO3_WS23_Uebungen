#include <cstdio>

class base_class {
public:
	virtual ~base_class() = default;

	virtual void foo() {
	}

	int m_value{ 42 };
};

class another_derived_class : public base_class {
};

class derived_class : public base_class {
	public:
		int m_data = 32;

		void foo() {
		}
};

void bar(base_class & b) {
	b.foo(); // solange foo nicht virtual ist: keine dyn. Bindung -> führt foo von base_class aus
			 // (also vom statischen DT und nicht vom dynamischen DT) = statische Bindung
			 // "virtual" aktiviert das Binden anhand des dynamischen DT = "dynamische Bindung für foo"
			 // "ohne virtual kein OOP"
	b.m_value = 0;
	printf("%d\n", b.m_value);
	//b.m_data = 0; // nicht möglich

	//derived_class d {dynamic_cast <derived_class &> (b)};
	derived_class * d { dynamic_cast <derived_class *> (&b) };

	if (d) {
		d->m_data = 0;
	}


}

int main() {
	derived_class			d;
	another_derived_class	ad;
	bar(d);
	bar(ad);
	printf("%d\n", d.m_data);

	base_class		b1{ d }; // Datentyp = base_class; Default Konstruktor macht memberwise copy
							 // es wird nur m_value zugewiesen (nicht m_data) -> "slicing" (kein OOP)
	base_class &	b2{ d }; // Polymorphismus (statischer/dynamischer Datentyp)
							 // b2 hat 2 Datentypen: statischer DT=base_class; dynamischer DT=derived_class
	base_class *	b3 {&d}; // Polymorphismus (statischer/dynamischer Datentyp)
							 // im Speicher passiert genau das gleiche wie bei b2
}
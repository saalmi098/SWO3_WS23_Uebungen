#if !defined GEO_H // Schutz vor Mehrfach-Inklusion (include guard)
#define      GEO_H

// int i = 0; // globale Variable; jedes Modul, das geo.h einbindet, bekommt Var. i
// wenn mehrere Module geo.h verwenden, erkennt das der Linker und gibt eine Fehlermeldung aus
// = external linkage

// static int i = 0; // internal linkage
// es gibt weiterhin 3 globale Variablen "i", aber der Linker sieht sie nicht, alle leben in ihrem Modul

double area(double const a, double const b); // function prototype
double volume(double const a, double const b, double const c); // function prototype

#endif
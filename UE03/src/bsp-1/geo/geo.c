#include "./geo.h"

double area(double const a, double const b) {
    return a * b;
}
double volume(double const a, double const b, double const c) {
    return area(a, b) * c;
    // Anm.: volume VOR area implementieren funktioniert auch, da Funktions-Prototypen im Header-File definiert sind
}

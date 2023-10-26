#include "./weight.h"
#include "../geo/geo.h"

double weight(double const a, double const b, double const c, double const density) {
    return volume(a, b, c) * density;
}
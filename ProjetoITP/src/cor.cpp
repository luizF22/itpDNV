#include "cor.h"

Cor::Cor() : r(0), g(0), b(0) {}

Cor::Cor(unsigned char r, unsigned char g, unsigned char b) 
    : r(r), g(g), b(b) {}

bool Cor::ehPreta() const {
    return (r == 0) && (g == 0) && (b == 0);
}
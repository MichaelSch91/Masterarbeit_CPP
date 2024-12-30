#ifndef ZAHLENDARSTELLUNG_H
#define ZAHLENDARSTELLUNG_H

#include <iostream>
#include <cmath>
//todo
class Zahlendarstellung {
public:
	Zahlendarstellung(int s, int m, int e);

	double toDouble() const;

private:
	int sign;  // Vorzeichen
	int mantissa;  // Mantisse
	int exponent; // Exponent
	static constexpr int b = 2;  // Basis
	static constexpr int bias = 127;  // Biaswert für Exponent

	double berechneMantisse() const;
};

#endif
#include <cmath>
#include <iostream>
#include "Zahlendarstellung.h"


Zahlendarstellung::Zahlendarstellung(int s, int e, int m) : sign(s), exponent(e), mantissa(m) {};

int Zahlendarstellung::getSign() {
	return this->sign;
}
void Zahlendarstellung::setSign(int s) {
	this->sign = s;
}

int Zahlendarstellung::getMantissa() {
	return this->mantissa;
}
void Zahlendarstellung::setMantissa(int m) {
	this->mantissa = m;
}

int Zahlendarstellung::getExponent() {
	return this->exponent;
}
void Zahlendarstellung::setExponent(int e) {
	this->exponent = e;
}

int Zahlendarstellung::getBase() {
	return this->base;
}
int Zahlendarstellung::getBias(){
	return this->bias;
}
int Zahlendarstellung::getMantissa_bits() {
	return this->mantissa_bits;
}
int Zahlendarstellung::getExponent_bits() {
	return this->exponent_bits;
}

// Allgemeine Implementierung,
// im Gegensatz zu IEEE754 wird hier auf den +1 Shift der Mantisse bei Exponent >= 1 verzichtet
double Zahlendarstellung::calcX() const {
	return pow(-1,this->sign) * pow(this->base,(this->exponent - this->bias)) * (this->mantissa/pow(this->base,this->mantissa_bits));
}

double Zahlendarstellung::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}






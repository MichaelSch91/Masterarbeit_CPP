#include <cmath>
#include <iostream>
#include "Default32squareroot.h"

// todo

Default32squareroot::Default32squareroot(int base, int bias, int mantissa_bits, int exponent_bits) : base(base), bias(bias), mantissa_bits(mantissa_bits), exponent_bits(exponent_bits) {};

Default32squareroot::Default32squareroot(int base, int bias, int mantissa_bits, int exponent_bits, int s, int m, int e) : base(base), bias(bias), mantissa_bits(mantissa_bits), exponent_bits(exponent_bits), sign(s), mantissa(m), exponent(e) {};

double Default32squareroot::setValues(int s, int m, int e) {
	this->sign = s;
	this->mantissa = m;
	this->exponent = e;
}

int Default32squareroot::getSign() {
	return this->sign;
}
void Default32squareroot::setSign(int s) {
	this->sign = s;
}

int Default32squareroot::getMantissa() {
	return this->mantissa;
}
void Default32squareroot::setMantissa(int m) {
	this->mantissa = m;
}

int Default32squareroot::getExponent() {
	return this->exponent;
}
void Default32squareroot::setExponent(int e) {
	this->exponent = e;
}

int Default32squareroot::getBase() {
	return this->base;
}
int Default32squareroot::getBias() {
	return this->bias;
}
int Default32squareroot::getMantissa_bits() {
	return this->mantissa_bits;
}
int Default32squareroot::getExponent_bits() {
	return this->exponent_bits;
}

double Default32squareroot::calcX() const {
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
}

double Default32squareroot::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}
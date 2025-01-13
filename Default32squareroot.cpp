#include <cmath>
#include <iostream>
#include "Default32squareroot.h"

// todo

Default32squareroot::Default32squareroot(int ba, int bi, int mant_bits, int exp_bits) : base(ba), bias(bi), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(0), exponent(0), mantissa(0) {};

Default32squareroot::Default32squareroot(int ba, int bi, int mant_bits, int exp_bits, int s, int e, int m) : base(ba), bias(bi), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(s), exponent(e), mantissa(m) {};

void Default32squareroot::setValues(int s, int e, int m) {
	this->sign = s;
	this->exponent = e;
	this->mantissa = m;
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

double Default32squareroot::calcX() {
	if (this->getExponent() == 0) {
		return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
	}
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (1 + this->mantissa / pow(this->base, this->mantissa_bits));
}

double Default32squareroot::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}
#include <cmath>
#include <iostream>
#include "Default32.h"

Default32::Default32(int ba, int bi, int mant_bits, int exp_bits) : base(ba), bias(bi), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(0), mantissa(0), exponent(0) {};

Default32::Default32(int ba, int bi, int mant_bits, int exp_bits, int s, int m, int e) : base(ba), bias(bi), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(s), mantissa(m), exponent(e) {};

void Default32::setValues(int s, int m, int e) {
	this->sign = s;
	this->mantissa = m;
	this->exponent = e;
}

int Default32::getSign() {
	return this->sign;
}
void Default32::setSign(int s) {
	this->sign = s;
}

int Default32::getMantissa() {
	return this->mantissa;
}
void Default32::setMantissa(int m) {
	this->mantissa = m;
}

int Default32::getExponent() {
	return this->exponent;
}
void Default32::setExponent(int e) {
	this->exponent = e;
}

int Default32::getBase() {
	return this->base;
}
int Default32::getBias() {
	return this->bias;
}
int Default32::getMantissa_bits() {
	return this->mantissa_bits;
}
int Default32::getExponent_bits() {
	return this->exponent_bits;
}

double Default32::calcX() const {
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
}

double Default32::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}
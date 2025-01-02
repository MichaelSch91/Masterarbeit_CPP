#include <cmath>
#include <iostream>
#include "Float32.h"


Float32::Float32(int s, int m, int e) : sign(s), mantissa(m), exponent(e) {
	this->sign = s;
	this->mantissa = m;
	this->exponent = e;
};

int Float32::getSign() {
	return this->sign;
}
void Float32::setSign(int s) {
	this->sign = s;
}

int Float32::getMantissa() {
	return this->mantissa;
}
void Float32::setMantissa(int m) {
	this->mantissa = m;
}

int Float32::getExponent() {
	return this->exponent;
}
void Float32::setExponent(int e) {
	this->exponent = e;
}

int Float32::getBase() {
	return this->base;
}
int Float32::getBias() {
	return this->bias;
}
int Float32::getMantissa_bits() {
	return this->mantissa_bits;
}
int Float32::getExponent_bits() {
	return this->exponent_bits;
}

double Float32::calcX() const {
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
}

double Float32::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}
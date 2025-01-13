#include <cmath>
#include <iostream>
#include "ExperimentalDefault.h"

ExperimentalDefault::ExperimentalDefault(int ba, int bi, int mant_bits, int exp_bits) : base(ba), bias(bi), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(0), exponent(0), mantissa(0) {};

ExperimentalDefault::ExperimentalDefault(int ba, int mant_bits, int exp_bits, int s, long e, long m) : base(ba), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(s), exponent(e), mantissa(m), bias(this->berechneBias(ba, exp_bits)) {};

ExperimentalDefault::ExperimentalDefault(int ba, int bi, int mant_bits, int exp_bits, int s, long e, long  m) : base(ba), bias(bi), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(s), exponent(e), mantissa(m) {};

void ExperimentalDefault::setValues(int s, long e, long m) {
	this->sign = s;
	this->exponent = e;
	this->mantissa = m;
}

int ExperimentalDefault::getSign() {
	return this->sign;
}
void ExperimentalDefault::setSign(int s) {
	this->sign = s;
}

long ExperimentalDefault::getMantissa() {
	return this->mantissa;
}
void ExperimentalDefault::setMantissa(long m) {
	this->mantissa = m;
}

long ExperimentalDefault::getExponent() {
	return this->exponent;
}
void ExperimentalDefault::setExponent(long e) {
	this->exponent = e;
}

int ExperimentalDefault::getBase() {
	return this->base;
}
int ExperimentalDefault::getBias() {
	return this->bias;
}
int ExperimentalDefault::getMantissa_bits() {
	return this->mantissa_bits;
}
int ExperimentalDefault::getExponent_bits() {
	return this->exponent_bits;
}

long double ExperimentalDefault::calcX() {
	if (this->getExponent() == 0) {
		return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
	}
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (1 + this->mantissa / pow(this->base, this->mantissa_bits));
}

long double ExperimentalDefault::calcX_with_In_Out() const {
std::cout << "(-1) ^" << this->sign << " * " << this->base << " ^ (" << this->exponent << " - " << this->bias << ") * (" << this->mantissa << " / (" << this->base << " ^ " << this->mantissa_bits << "))";
std::cout << " = " << pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits)) << '\n';
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
}

double ExperimentalDefault::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}

int ExperimentalDefault::berechneBias(int base, int exponent_bits) {
	return std::floor((pow(base, exponent_bits) / 2) - 1);
}
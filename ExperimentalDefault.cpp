#include <cmath>
#include <iostream>
#include "ExperimentalDefault.h"

ExperimentalDefault::ExperimentalDefault(int ba, int mant_bits, int exp_bits) : base(ba), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(0), exponent(0), mantissa(0) {
	this->exponent_max = this->berechneExponent_max();
	this->mantissa_max = this->berechneMantissa_max(); 
	this->bias = this->berechneBias();
};

ExperimentalDefault::ExperimentalDefault(int ba, int mant_bits, int exp_bits, int s, long e, long m) : base(ba), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(s), exponent(e), mantissa(m), exponent_max(this->berechneExponent_max()), mantissa_max(this->berechneMantissa_max()), bias(this->berechneBias()) {};

ExperimentalDefault::ExperimentalDefault(int ba, int bi, int mant_bits, int exp_bits, int s, long e, long  m) : base(ba), bias(bi), mantissa_bits(mant_bits), exponent_bits(exp_bits), sign(s), exponent(e), mantissa(m), exponent_max(this->berechneExponent_max()), mantissa_max(this->berechneMantissa_max()) {};

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
		return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * this->berechneMantisseDezimalwert_denormalized();
	}
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * this->berechneMantisseDezimalwert_normalized();
}



long double ExperimentalDefault::calcX_with_In_Out() {
std::cout << "(-1) ^" << this->sign << " * " << this->base << " ^ (" << this->exponent << " - " << this->bias << ") * (" << this->mantissa << " / (" << this->base << " ^ " << this->mantissa_bits << "))";
std::cout << " = " << pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits)) << '\n';
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
}

long double ExperimentalDefault::berechneMantisseDezimalwert_denormalized() {
	return (long double) this->getMantissa() / (this->getMantissa_max() + 1);
}

long double ExperimentalDefault::berechneMantisseDezimalwert_normalized() {
	// std::cout << "mantissa: " << (long double)1.0 + (long double)this->getMantissa() / (long double)(this->getMantissa_max() + 1) <<'\n';
	return (long double) 1.0 + (long double)this->getMantissa() / (long double)(this->getMantissa_max() + 1);
}

int ExperimentalDefault::berechneBias() {
	return std::floor((pow(this->getBase(), this->getExponent_bits()) / 2) - 1);
}

unsigned long long ExperimentalDefault::berechneExponent_max() {
	return (pow(this->base, this->exponent_bits)-1);
}

unsigned long long ExperimentalDefault::berechneMantissa_max() {
	return (pow(this->base, this->mantissa_bits)-1);
}

unsigned long long ExperimentalDefault::getMantissa_max() {
	return this->mantissa_max;
}

unsigned long long ExperimentalDefault::getExponent_max() {
	return this->exponent_max;
}

void ExperimentalDefault::printAttributes() {
	std::cout << "Sign = " << this->getSign() << " Exponent = " << this->getExponent() << " Mantisse = " << this->getMantissa() << '\n';
}
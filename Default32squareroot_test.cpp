#include <cmath>
#include <iostream>
#include <random>
#include <tuple>
#include "Sqrt_helper.h"
#include "Default32squareroot.h"
#include "Default32squareroot_test.h"

Default32squareroot_test::Default32squareroot_test(int ba) : base(ba) { };

int Default32squareroot_test::getBase(){
	return this->base;
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Default32squareroot_test::test_Default32squareroot_operator_plus() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA - flB;

	for (int i = 0; i < 10000; i++) {
		s1 = 0; //rand() % 2;
		s2 = 0; //rand() % 2;
		//e1 = rand() % 254;
		//e2 = rand() % 254;
		e1 = 126 + rand() % 5; // Werte um 0
		e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;
		m2 = rand() % 8'388'608;


		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA + flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A + B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() + flB.calcX())) > 0.00005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() + flB.calcX())) << '\n';
			std::cout << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() + flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A + B = " << (flA.calcX() + flB.calcX()) << " Default32squareroot A + B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Plus: " << counter << " Fehler" << '\n';
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Default32squareroot_test::test_Default32squareroot_operator_minus() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA - flB;

	for (int i = 0; i < 100'000; i++) {
		s1 = rand() % 2;
		s2 = rand() % 2;
		e1 = rand() % 254;
		e2 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;
		m2 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA - flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A - B = " << flC.calcX() << '\n';
		if ((flC.calcX() < 0) and ((flA.calcX() - flB.calcX()) > 0) or (flC.calcX() > 0) and ((flA.calcX() - flB.calcX()) < 0)) {
			std::cout << "Falsches Vorzeichen!" << '\n';
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Default32squareroot A - B = " << flC.calcX() << '\n';
		}
		if (abs(flC.calcX() - (flA.calcX() - flB.calcX())) > 0.0005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() - flB.calcX())) << '\n';
			std::cout << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() - flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Default32squareroot A - B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Minus: " << counter << " Fehler" << '\n';
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Default32squareroot_test::test_Default32squareroot_operator_multiply() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA - flB;

	for (int i = 0; i < 10000; i++) {
		s1 = rand() % 2;
		s2 = rand() % 2;
		e1 = rand() % 254;
		e2 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;
		m2 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA * flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A * B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() * flB.calcX())) > 0.00005) {
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() * flB.calcX())) << '\n';
			std::cout << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() * flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A * B = " << (flA.calcX() * flB.calcX()) << " Default32squareroot A * B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
}

void Default32squareroot_test::test_Default32squareroot_calcX() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Default32squareroot flA(s1, e1, m1);

	for (int i = 0; i < 10000; i++) {
		s1 = rand() % 2;
		e1 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		std::cout << "A = " << flA.calcX() << '\n';
		if (abs(flA.calcX() - flA.simpleCalcX()) > 0.00005) {
			std::cout << "Abweichung!" << '\n';
			std::cout << " A simpleCalcX = " << flA.simpleCalcX() << " A calcX = " << flA.calcX() << '\n' << '\n' << '\n';
		}
	}
}

void Default32squareroot_test::test_Default32squareroot_convert_to_Default32squareroot() {
	int counter = 0;
	double a_random_double = (double)rand() / 10'000;
	Default32squareroot square(this->getBase());

	for (int i = 0; i < 1000; i++) {
		a_random_double = (double)rand() / (rand() % 10000);
		// std::cout << "Random Number = " << a_random_double << '\n';
		square = Default32squareroot::convert_to_Default32squareroot(this->getBase(), a_random_double);
		if (abs(square.calcX() - a_random_double) > square.deviation_due_to_exp()) {
			counter++;
			std::cout << "Abweichung!" << '\n';
			std::cout << "Random Double = " << a_random_double << " Ergebnis nach Convert = " << square.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Convert: " << counter << " Fehler" << '\n';
}

void Default32squareroot_test::test_Default32squareroot_convert_to_Default32squareroot_In_and_Out() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot conversion(this->getBase());

	for (int i = 0; i < 10000; i++) {
		s1 = rand() % 2;
		e1 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		conversion = Default32squareroot::convert_to_Default32squareroot(this->getBase(), flA.calcX());
		std::cout << "In = " << flA.calcX() << " Out = " << conversion.calcX() << '\n';

		if (!(flA == conversion)) { // todo != überladen
			counter++;
			std::cout << "Abweichung!" << '\n';
			std::cout << "In Sign = " << flA.getSign() << " In Exp = " << flA.getExponent() << " In Mant = " << flA.getMantissa() << '\n'
				<< "Out Sign = " << conversion.getSign() << " Out Exp = " << conversion.getExponent() << " Out Mant = " << conversion.getMantissa() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Convert In Out: " << counter << " Fehler" << '\n';
}


// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Default32squareroot_test::test_Default32squareroot_operator_plus_with_conversion() {
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister Engine mit Seed von random_device
	std::uniform_int_distribution<int> binary_dist(0, 1); // Für s1 und s2
	std::uniform_int_distribution<int> exponent_dist(0, 253); // Für e1 und e2 (0 bis 253)
	std::uniform_int_distribution<int> mantissa_dist(0, 8388607); // Für m1 und m2
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA + flB;

	Default32squareroot flCompare(0, 0, 0);

	for (int i = 0; i < 10000; i++) {
		// s1 = binary_dist(gen);
		// s2 = binary_dist(gen);
		//e1 = exponent_dist(gen);
		//e2 = exponent_dist(gen);
		e1 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		e2 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		m1 = mantissa_dist(gen);
		m2 = mantissa_dist(gen);

		std::cout << "m1 = " << m1 << " m2 = " << m2 << '\n';


		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA + flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A + B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() + flB.calcX())) > 0.00005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() + flB.calcX())) << '\n' << '\n';
			flCompare = flCompare.convert_to_Default32squareroot(2, (flA.calcX() + flB.calcX()));
			std::cout << "Should be: " << '\n';
			flCompare.printAttributes();
			std::cout << "But is: " << '\n';
			flC.printAttributes();
			std::cout << '\n' << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() + flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A + B = " << (flA.calcX() + flB.calcX()) << " Default32squareroot A + B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Plus: " << counter << " Fehler" << '\n';
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Default32squareroot_test::test_Default32squareroot_operator_minus_with_conversion() {
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister Engine mit Seed von random_device
	std::uniform_int_distribution<int> binary_dist(0, 1); // Für s1 und s2
	std::uniform_int_distribution<int> exponent_dist(0, 253); // Für e1 und e2 (0 bis 253)
	std::uniform_int_distribution<int> mantissa_dist(0, 8388607); // Für m1 und m2
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC(0, 0, 0);

	Default32squareroot flCompare(0, 0, 0);

	for (int i = 0; i < 10000; i++) {
		// s1 = binary_dist(gen);
		// s2 = binary_dist(gen);
		//e1 = exponent_dist(gen);
		//e2 = exponent_dist(gen);
		e1 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		e2 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		m1 = mantissa_dist(gen);
		m2 = mantissa_dist(gen);

		std::cout << "m1 = " << m1 << " m2 = " << m2 << '\n';


		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA - flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A - B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() - flB.calcX())) > 0.00005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() - flB.calcX())) << '\n' << '\n';
			flCompare = flCompare.convert_to_Default32squareroot(2, (flA.calcX() - flB.calcX()));
			std::cout << "Should be: " << '\n';
			flCompare.printAttributes();
			std::cout << "But is: " << '\n';
			flC.printAttributes();
			std::cout << '\n' << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() - flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Default32squareroot A - B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Minus: " << counter << " Fehler" << '\n';
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Default32squareroot_test::test_Default32squareroot_operator_multiply_with_conversion() {
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister Engine mit Seed von random_device
	std::uniform_int_distribution<int> binary_dist(0, 1); // Für s1 und s2
	std::uniform_int_distribution<int> exponent_dist(0, 253); // Für e1 und e2 (0 bis 253)
	std::uniform_int_distribution<int> mantissa_dist(0, 8388607); // Für m1 und m2
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC(0, 0, 0);

	Default32squareroot flCompare(0, 0, 0);

	for (int i = 0; i < 10000; i++) {
		// s1 = binary_dist(gen);
		// s2 = binary_dist(gen);
		// e1 = exponent_dist(gen);
		// e2 = exponent_dist(gen);
		e1 = 60 + (gen() % 130); // Werte um 0 (alte rand() Variante)
		e2 = 60 + (gen() % 130); // Werte um 0 (alte rand() Variante)
		m1 = mantissa_dist(gen);
		m2 = mantissa_dist(gen);

		// std::cout << "m1 = " << m1 << " m2 = " << m2 << '\n';


		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		flC = flA * flB;
		flCompare = flCompare.convert_to_Default32squareroot(2, (flA.calcX() * flB.calcX()));
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A * B = " << flC.calcX() << '\n';
		if (!flC.equals(flCompare)) {
			counter++;
			// std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() * flB.calcX())) << '\n' << '\n';
			std::cout << "Should be: " << '\n';
			flCompare.printAttributes();
			std::cout << "But is: " << '\n';
			flC.printAttributes();
			/*
			std::cout << '\n' << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() * flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			*/
			std::cout << " A * B = " << (flA.calcX() * flB.calcX()) << " Default32squareroot A - B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Minus: " << counter << " Fehler" << '\n';
}
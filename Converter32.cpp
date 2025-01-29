#include <cmath>
#include <iostream>
#include "Converter32.h"

/*
Default32squareroot Converter32::convert_to_Default32squareroot(int base, long double x) {
	Default32squareroot result(base, 0, 0, 0);

	if (x < 0) {
		result.setSign(1);
	}
	for (int exp = result.getExponent_min(); exp <= result.getExponent_max(); exp++) {
		if ((x >= Default32squareroot(base, result.getSign(), exp, result.getMantissa_min()).calcX()) and (x <= Default32squareroot(base, result.getSign(), exp, result.getMantissa_max()).calcX())) {
			result.setExponent(exp);
			break;
		}
	}
	// Mantisse hochzählen bis Wert innerhalb mit Abweichung kleiner als deviation_due_to_exp() gefunden wird
	// schnelle suche,in dem erst der Wertebereich der Mantisse in 100er oder 1000er Schritten eingegrenzt wird?
	
	// todo
	return result;

}
*/
//
// Created by debyecao on 11/25/20.
//

#include "Helpers.hpp"
#include <iomanip>
#include <sstream>

std::string Helpers::FloatToString(float f, int precision)
{
	std::stringstream stream;

	stream << std::fixed << std::setprecision(precision) << f;

	return stream.str();
}
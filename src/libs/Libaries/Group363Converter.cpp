#include "Group363Converter.h"

int Group363Converter::degreesToBits(float degrees) {

	return int(degrees * 4096 / 360);
}
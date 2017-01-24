#pragma once
#include <string.h>

enum Color {
	GOLD,
	GREEN,	
	BLUE,
	RED,
	PURPLE
};

static const Color StringToColor(const char* const input) {
	if (strcmp(input, "geel") == 0) {
		return GOLD;
	}
	else if (strcmp(input, "groen") == 0) {
		return GREEN;
	}
	else if (strcmp(input, "blauw") == 0) {
		return BLUE;
	}
	else if (strcmp(input, "rood") == 0) {
		return RED;
	}
	else {
		return PURPLE;
	}
}

static const char* const ColorToString(Color const input) {
	switch (input)
	{
	case GOLD:
		return "geel";
		break;
	case GREEN:
		return "groen";
		break;
	case BLUE:
		return "blauw";
		break;
	case RED:
		return "rood";
		break;
	default:
		return "paars";
		break;
	}
}
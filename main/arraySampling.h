#pragma once

enum states
{
	sorted,
	reversed,
	random
};

int* generateArray(int n, states state);
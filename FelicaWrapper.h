#pragma once

#include <felica.h>
#include <string>
using namespace std;

class FelicaWrapper {
	public:
		FelicaWrapper();

		int Initialize();
		int Dispose();

		int GetResource(string& IDm, string& PMm, unsigned int timeout);
};
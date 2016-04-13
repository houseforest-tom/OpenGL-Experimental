#include "log.h"
#include <iostream>
#include <cstdint>

#if defined(_WIN64) || defined(_WIN32)
#include <Windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

namespace planet {
	using namespace std;

	void logMessage(string const& message, Loglevel loglevel) {
		static uint16_t color;
		color = (loglevel == Loglevel::message ? 15 : (loglevel == Loglevel::warning ? 14 : 12));

		#if defined(_WIN64) || defined(_WIN32)
		SetConsoleTextAttribute(hConsole, color);
		#endif

		cout << message << endl;
	}
}
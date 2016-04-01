#pragma once

#include <string>

namespace planet {

    // Log levels.
	enum class Loglevel {
		message,
		warning,
		error
	};

	// Log a message to the console.
	void logMessage(std::string const& message, Loglevel loglevel = Loglevel::message);
}
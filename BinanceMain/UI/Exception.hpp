#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include "Macro.hpp"
#include "Element.hpp"
#include "Button.hpp"


class Exception
{
public:
	int line;
	std::string file;
	std::string message;

	Exception(std::string message, std::string file, int line);
};

#endif /* EXCEPTION_H_ */

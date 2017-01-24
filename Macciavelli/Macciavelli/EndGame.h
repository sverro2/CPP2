#pragma once
#include <exception>

class EndGame : public std::exception
{
public:
	virtual const char* what() const throw() override;
};


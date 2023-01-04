#pragma once
#include <string>
struct User
{
	std::string name;
	User(std::string name) :name(name) {};
	operator std::string()
	{
		return name;
	}
};


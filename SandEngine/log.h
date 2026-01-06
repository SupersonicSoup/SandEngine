#pragma once
#include <string>
#include <iostream>

class log
{
public:
	static log& getInstance()
	{
		static log instance;
		return instance;
	}

	static void println(std::string s)
	{
		std::cout << s << std::endl;
	}

	static void error(std::string s)
	{
		std::cout << "[ERROR] " << s << std::endl;
	}
private:
	log() {}

	log(log const&);
	void operator=(log const&);
};
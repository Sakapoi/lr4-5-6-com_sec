#include <iostream>
#include <ctime>
std::string alphabet = "";
char random_symbol()
{
	return alphabet[rand() % alphabet.length()];
}

int main()
{
	srand(time(0)); 

	for (char i = 'a'; i <= 'z'; i++)
	{
		alphabet += i;
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		alphabet += i;
	}
	for (char i = '0'; i <= '9'; i++)
	{
		alphabet += i;
	}

	std::string password = "";
	for (int i = 0; i < 8; i++)
	{
		password += random_symbol();
	}
	std::cout << "Random password: " << password << std::endl;
	system("pause");
	return 0;
}
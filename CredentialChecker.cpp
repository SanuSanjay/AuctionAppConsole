
#include "CredentialVerifier.h"


char CredentialVerifier::validSize(std::string username, std::string password, int size) 
{
	if (username.length() > size && password .length() > size) 
	{
		return 'E';
	}
	if (username.length() > size) 
	{
		return 'U'; 
	}
	if (password.length() > size) 
	{
		return 'P';
	}
	return 'V';
}

bool CredentialVerifier::errormsg(char msg) 
{
	switch (msg) 
	{
	case 'E':
		std::cout << "Username and password too long" << '\n';
		return false;

	case 'U':
		std::cout << "Username too long" << '\n';
		return false;

	case 'P':
		std::cout << "Password too long" << '\n';
		return false;

	case 'V':
		//Username and password meet the constraints
		return true;
	}
	return false;
}

bool CredentialVerifier::validPassword(const std::string& password) 
{
	bool isNum = false, isCaps = false, isSpecial = false;

	for (char c : password) 
	{
		if (std::isdigit(c)) 
		{
			isNum = true;
		}
		if (std::isupper(c)) 
		{
			isCaps = true;
		}
		if (!std::isalnum(c)) 
		{
			isSpecial = true;
		}
	}

	if (isNum && isCaps && isSpecial) 
	{
		return true;
	}
	else 
	{
		std::cout << "Password must contain at least one number, one uppercase letter, and one special character" << '\n';
		return false;
	}
}


bool CredentialVerifier::CredentialChecker(std::string oUser, std::string oPass, std::string Iuser, std::string Ipass)
{
	bool LoginSuccess = false;
	if (oUser == Iuser && oPass == Ipass) 
	{
		LoginSuccess = true;
	}
	else 
	{
		LoginSuccess = false;
	}

	return LoginSuccess;
}
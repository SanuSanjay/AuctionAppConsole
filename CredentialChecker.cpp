
#include "CredentialVerifier.h"


char CredentialVerifier::valid_size(std::string username, std::string password, int size) 
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

bool CredentialVerifier::error_message(char message) 
{
	switch (message) 
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

bool CredentialVerifier::valid_password(const std::string& password) 
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


bool CredentialVerifier::credential_checker(std::string original_user, std::string original_password, std::string username_input, std::string password_input)
{
	bool LoginSuccess = false;
	if (original_user == username_input && original_password == password_input) 
	{
		LoginSuccess = true;
	}
	else 
	{
		LoginSuccess = false;
	}

	return LoginSuccess;
}
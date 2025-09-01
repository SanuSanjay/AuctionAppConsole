
#include "CredentialVerifier.h"


char CredentialVerifier::valid_size(std::string username, std::string password, int max_size, int min_size) 
{
	if (username.length() > max_size && password .length() > max_size) 
	{
		return 'L'; // username or password are too long
	}

	if (username.length() < min_size || password.length() < min_size) 
	{
		return 'S'; // username or password are too short
	}

	return 'V';
}

bool CredentialVerifier::error_message(char message) 
{
	switch (message) 
	{
	case 'L':
		std::cout << "\nUsername or password too long" << '\n';
		return false;

	case 'S':
		std::cout << "\nUsername and password must be at least 6 characters long" << '\n';

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
		std::cout << "Minimum lenght lenght of password is 6 characters and maximum for username and password is 32 characters" << '\n';
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
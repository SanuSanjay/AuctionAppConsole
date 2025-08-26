#ifndef CREDENTIAL_VERIFIER_H
#define CREDENTIAL_VERIFIER_H

#include "All_Includes.h"


class CredentialVerifier 
{
public :
	char valid_size(std::string username, std::string password, int size);
	bool error_message(char msg);
	bool valid_password(const std::string& password);
	bool credential_checker(std::string oUser, std::string oPass, std::string Iuser, std::string Ipass);
};

#endif // !CREDENTIAL_VERIFIER_H

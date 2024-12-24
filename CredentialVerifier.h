#ifndef CREDENTIAL_VERIFIER_H
#define CREDENTIAL_VERIFIER_H

#include<string>
#include <algorithm>
#include<cctype>
#include<iostream>
#include<iomanip>
#include<string.h>
#include<new>



class CredentialVerifier {
public :
	char validSize(std::string* username, std::string* password, int size);
	bool validPassword(const std::string& password);
	bool CredentialChecker(std::string* oUser, std::string* oPass, std::string* Iuser, std::string* Ipass);
};

#endif // !CREDENTIAL_VERIFIER_H

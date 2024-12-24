
#include "CredentialVerifier.h"


char CredentialVerifier::validSize(std::string* username, std::string* password, int size) {
	if (username->length() > size && password ->length() > size) {
		return 'E';
	}
	if (username->length() > size) {
		return 'U';
	}
	if (password->length() > size) {
		return 'P';
	}
	return 'V';
}

bool CredentialVerifier::validPassword(const std::string& password) {
	bool isNum = false, isCaps = false, isSpecial = false;
	for (char c : password) {
		if (std::isdigit(c)) {
			isNum = true;
			break;
		}
	}
	for (char c : password) {
		if (std::isupper(c)) {
			isCaps = true;
			break;
		}
	}
	for (char c : password) {
		if (!std::isalnum(c)) {
			isSpecial = true;
			break;
		}
	}

	if (isNum == false || isCaps == false || isSpecial == false) {
		return false;
	}
	return true;
}


bool CredentialVerifier::CredentialChecker(std::string* oUser, std::string* oPass, std::string* Iuser, std::string* Ipass)
{
	bool LoginSuccess = false;
	if (*oUser == *Iuser && *oPass == *Ipass) {
		LoginSuccess = true;
	}
	else {
		LoginSuccess = false;
	}

	return LoginSuccess;
}
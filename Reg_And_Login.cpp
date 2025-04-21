


#include "AuctionApp.h"
#include "CredentialVerifier.h"


string RegisteredUserDetails :: AccountRegistration() 
{
	CredentialVerifier verify;
	string username;
	string password;
	cout << setw(65) << right << setfill(' ') << "WELCOME USER" << '\n';
	cout << setw(85) << right << setfill(' ') << "Create and account to start buying and auctioning" << '\n';

acc_creation:
	cout << setw(89) << right << setfill(' ') << "Enter a username and password to register your account " << '\n';
	cout << setw(75) << right << setfill(' ') << "The maximum length for each is 32 " << '\n';
	cout << setw(95) << right << setfill(' ') << "The password must contain a capital letter, number and a special character " << '\n';

	cout << "Username : ";  getline(cin, username);
	cout << "Password : ";  getline(cin, password);

	char msg = verify.validSize(username, password, MaxSize);
	if (!verify.errormsg(msg)) 
	{
		goto acc_creation;
	}

	bool isValid = verify.validPassword(password);

	if (isValid) {
		cout << setw(90) << right << setfill(' ') << "Your account was successfully created,Please login to the new account" << '\n';
		accDetailStorer(username , password);
		return "success";
	}
	else
		cout << setw(83) << right << setfill(' ') << "Password does not meet minimum requirements!" << '\n';
	cout << '\n';
	goto acc_creation;

}

void RegisteredUserDetails::accDetailStorer(string user, string pass) 
{
	Reg_UserName = user;
	Reg_Password = pass;
	AccountLogin();
}

string RegisteredUserDetails::AccountLogin() const 
{ 
	UserAccDetails user;
	int attempts = 5;
	CredentialVerifier obj;
	string result;
	string tempUser;
	string tempPass;

verification:
	cout << "Enter your Username and password to use the app :" << '\n';

	getline(cin, tempUser);
	getline(cin, tempPass);

	char msg = obj.validSize(tempUser, tempPass, MaxSize);

	cout << '\n';
	cout << "Verifying Credentials ......" << '\n';

	if (!obj.errormsg(msg)) {goto verification;}


	if (obj.CredentialChecker(Reg_UserName, Reg_Password, tempUser, tempPass) == true) 
	{
		cout << "Login Credentials are valid! Logging into your account" << '\n';
		cout << '\n';
		result = "success";
	}

	else 
	{
		cout << "Login Credentials are not valid!" << '\n';
		cout << attempts-- << " attempts remaining" << '\n';
		cout << '\n';

		if (attempts == 0) 
		{
			cout << "Login failed, too many failed attempts!" << '\n'; result = "failed";
			return result;
		}

		goto verification;
	}

	return result;
}
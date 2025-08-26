


#include "AuctionApp.h"
#include "CredentialVerifier.h"


string RegisteredUserDetails :: account_registration() 
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

	char msg = verify.valid_size(username, password, max_size_c);
	if (!verify.error_message(msg)) 
	{
		goto acc_creation;
	}

	bool is_valid = verify.valid_password(password);

	if (is_valid) {
		cout << setw(90) << right << setfill(' ') << "Your account was successfully created,Please login to the new account" << '\n';
		account_detail_storer(username , password);
		return "success";
	}
	else
		cout << setw(83) << right << setfill(' ') << "Password does not meet minimum requirements!" << '\n';
	cout << '\n';
	goto acc_creation;

}

void RegisteredUserDetails::account_detail_storer(string user, string pass) 
{
	reg_username_ = user;
	reg_password_ = pass;
	account_login();
}

string RegisteredUserDetails::account_login() const 
{ 
	UserAccDetails user;
	int attempts = 5;
	CredentialVerifier obj;
	string result;
	string temp_user;
	string temp_pass;

verification:
	cout << "Enter your Username and password to use the app :" << '\n';

	getline(cin, temp_user);
	getline(cin, temp_pass);

	char msg = obj.valid_size(temp_user, temp_pass, max_size_c);

	cout << '\n';
	cout << "Verifying Credentials ......" << '\n';

	if (!obj.error_message(msg)) {goto verification;}


	if (obj.credential_checker(reg_username_, reg_password_, temp_user, temp_pass) == true) 
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

#include "CredentialVerifier.h"
#include<string.h>
#include<fstream>


using std::cout;
using std::cin;
using std::string;
using std::right;
using std::setfill;
using std::setw;
using std::getline;


/*1.Welcome Screen
  -> Need to press enter to continue
  -> Login screen (needs username and psw)
  -> username = user and psw = auction (case sensitive) (COMPLETED)

  2.Auction Screen with bid and buyout option   <-
  -> Contains different types of paintings to be bought

  3.Screen to add a listing for your own painting
  -> need to specify minimum bid amount and buyout price

  4.Add a countdown for a minute after placing a bid
  -> A bid can be randomly placed within the minute for a maximum of 3 times before user wins the bid

  5.When the player wins the bid create a text file storing the name of the painting and the price paid for the painting
  -> The text file contains all the paintings bought and put on auction by the user.

  6.Exit the program when all tasks are complete
  */


const int MaxSize = 32;

class RegisteredUserDetails {
private:
	 string* Reg_UserName;
	 string* Reg_Password;
public:
	 string AccountRegistration();
	 string AccountLogin();
};


class AuctionPaintings {
protected:
	struct Painting {
		string PaintingName;
		float price;
		bool currentBid;
		bool isBoughtOut;
		Painting* link;
	}first;
public:
	string Append();
	void PrintContents();
};

//string AuctionPaintings::Append() {
//	cout << "Hello chat" << '\n';
//}
//
//void AuctionPaintings::PrintContents() {
//	cout << "hello chat" << '\n';
//}



 string RegisteredUserDetails :: AccountRegistration(){
	CredentialVerifier verify;
	Reg_UserName = new  string[MaxSize];
	Reg_Password = new  string[MaxSize];
	
	 cout <<  setw(65) <<  right <<  setfill(' ') << "WELCOME USER" << '\n';
	 cout <<  setw(85) <<  right <<  setfill(' ') << "Create and account to start buying and auctioning" << '\n';

	 acc_creation:
	 cout <<  setw(89) <<  right <<  setfill(' ') << "Enter a username and password to register your account " << '\n';
	 cout << setw(75)  <<  right <<  setfill(' ') << "The maximum length for each is 32 " << '\n';
	 cout << setw(95) << right << setfill(' ') << "The password must contain a capital letter, number and a special character " << '\n';

	 cout << "Username : ";  getline( cin, *Reg_UserName);
	 cout << "Password : ";  getline( cin, *Reg_Password);

	 char msg = verify.validSize(Reg_UserName, Reg_Password, MaxSize);
	 if (!verify.errormsg(msg)) {
		 goto acc_creation;
	 }

	 bool test = verify.validPassword(*Reg_Password);

	 if (test == true) {
		 cout << setw(90) << right << setfill(' ') << "Your account was successfully created,Please login to the new account" << '\n';
		 return "success";
	 }
	 else
		cout << setw(83) << right << setfill(' ') << "Password does not meet minimum requirements!" << '\n';
		cout << '\n';
		goto acc_creation;

}

 string RegisteredUserDetails::AccountLogin() {
	int attempts = 5;
	 CredentialVerifier obj;
	 string result;
	 string* tempUser = new  string[MaxSize];
	 string* tempPass = new  string[MaxSize];

	verification:
	 cout << "Enter your Username and password to use the app :" << '\n';

	 getline( cin, *tempUser);
	 getline( cin, *tempPass);

	 char msg = obj.validSize(tempUser, tempPass, MaxSize);

	 cout << '\n';
	 cout << "Verifying Credentials ......" << '\n';

	 if (!obj.errormsg(msg)) {
		 goto verification;
	 }


	if (obj.CredentialChecker(Reg_UserName, Reg_Password, tempUser, tempPass) == true) {
		 cout << "Login Credentials are valid! Logging into your account" << '\n';
		 cout << '\n';
		result = "success";
		goto cleanUp;
	}

	else {
		 cout << "Login Credentials are not valid!" << '\n';
		 cout << attempts-- << " attempts remaining" << '\n';
		 cout << '\n';

		if (attempts == 0) { 
			 cout << "Login failed, too many failed attempts!" << '\n'; result = "failed";
			goto cleanUp; 
		}

		goto verification;
	}

cleanUp :
	tempUser = nullptr;  
	tempPass = nullptr;

	delete[] tempUser;
	delete[] tempPass;
	return result;
}


int main() {
	 RegisteredUserDetails obj{};
	 string result = obj.AccountRegistration();
	 cout << result << '\n';
	 string out = obj.AccountLogin();
	 cout << out << '\n';

	return 0;
}


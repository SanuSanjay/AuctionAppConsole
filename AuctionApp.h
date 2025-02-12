#ifndef AUCTION_APP_H
#define AUCTION_APP_H

#include "All_Includes.h"


class UserAccDetails  {
public:
	string Reg_UserName;
	string Reg_Password;
	double MoneyBalance = 0;
	int cartItems = 0, listed = 0;
	int ownedItems = 0;
};


class RegisteredUserDetails : public UserAccDetails{
public:
	const int MaxSize = 32;
	void accDetailStorer(string user, string pass);
	string AccountRegistration();
	string AccountLogin() const;
	string getRegUser() const { return Reg_UserName; } //Allows the objects of different classes to get user info
	string getRegPass() const { return Reg_Password; } //Allows the objects of different classes to get user info
};

class ListedPaintings {
public:
	RegisteredUserDetails* userDetails;
	//stores the information of the paintings listed
	vector<string> Paintings;
	vector<string> Artists;
	vector<double> Prices;

	//stores the information of the paintings bought by the user
	vector<string> Users_Paintings;
	vector<string> User_Artists;
	vector<double> PriceBought;
	int userIndex;

	//stores the percentage bump for bid and buyout
	double bidPercentageBump;
	double buyoutPercentageBump;
	int index;

	//Default constructor
	ListedPaintings() {};
	ListedPaintings(RegisteredUserDetails* user) : userDetails(user) {}

	//Function to store the default paintings
	void DefaultPainting();
	void PrintPaintings();
};

class AuctionApp : public UserAccDetails {
public:
	RegisteredUserDetails* userDetails;
	ListedPaintings* paintings;

	AuctionApp(RegisteredUserDetails* user, ListedPaintings* paintings): userDetails(user), paintings(paintings) {}
	void functionToProcess();
	void DisplayUserInfo() const;
	void AddMoney();
	bool BalanceCheck(double);
	string addToCart();
	string InitialBid();
	bool BidSuccess(int);
	int ConsecutiveBid(int);
	void UpdateListings(int);
	string Buyout();
	string AddListing();
};


#endif
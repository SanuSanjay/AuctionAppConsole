#ifndef AUCTION_APP_H
#define AUCTION_APP_H

#include "All_Includes.h"

class UserAccDetails  {
protected :
	string Reg_UserName;
	string Reg_Password;
	float MoneyBalance = 0;
	int items = 0, listed = 0;
	
public : 
	void DisplayUserInfo() const ;
};


class RegisteredUserDetails : public UserAccDetails{
public :
	const int MaxSize = 32;
	void accDetailStorer(string user, string pass);
	string AccountRegistration();
	string AccountLogin() const;
};

class AuctionApp : public UserAccDetails {
public :
	void functionToProcess();
	void AddMoney();
	string Bid();
	string Buyout();
	string AddListing();
};


#endif
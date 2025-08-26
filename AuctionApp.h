#ifndef AUCTION_APP_H
#define AUCTION_APP_H

#include "All_Includes.h"


class UserAccDetails  
{
public:
	string reg_username_;
	string reg_password_;
	double money_balance_ = 0;
	int cart_items_ = 0, listed = 0;
	int owned_items_ = 0;
};


class RegisteredUserDetails : public UserAccDetails
{
public:
	const int max_size_c = 32;
	void account_detail_storer(string user, string pass);
	string account_registration();
	string account_login() const;
	string get_reg_user() const { return reg_username_; } //Allows the objects of different classes to get user info
	string get_reg_pass() const { return reg_password_; } //Allows the objects of different classes to get user info
};

struct PaintingsInfo
{
	string painting_name;
	string artist_name;
	double price;
};

struct UserOwnedPaintings
{
	string painting_name;
	string artist_name;
	double price_paid;

	UserOwnedPaintings(const string& p, const string& a, double price)
		: painting_name(p), artist_name(a), price_paid(price) {
	}
};

class ListedPaintings 
{
public:
	RegisteredUserDetails* user_details;
	//stores the information of the paintings listed
	vector<PaintingsInfo> painting_info_;

	//stores the information of the paintings bought by the user
	vector<UserOwnedPaintings> user_owned_paintings_;

	// To check if the painting exists when buying
	vector<string> painting_in_cart_;

	//stores the percentage bump for bid and buyout
	double bid_percentage_bump_;
	double buyout_percentage_bump_;
	int index;

	//constructor
	ListedPaintings(RegisteredUserDetails* user) : user_details(user), bid_percentage_bump_(0.15), buyout_percentage_bump_(0.50), index(5) {}

	//Function to store the default paintings
	void default_paintings();
	void print_paintings();
};

class AuctionApp : public UserAccDetails 
{
public:
	RegisteredUserDetails* user_details;
	ListedPaintings* paintings;

	AuctionApp(RegisteredUserDetails* user, ListedPaintings* paintings): user_details(user), paintings(paintings) {}
	void function_to_process();
	void display_user_info() const;
	void add_money();
	bool balance_check(double);
	string add_to_cart();
	string buy_from_cart();
	void update_cart(int);
	bool painting_available(int);
	string initial_bid(int);
	bool bid_success(int);
	int consecutive_bid(int);
	void update_listings(int);
	string buyout(int);
	string add_listings();
};


#endif
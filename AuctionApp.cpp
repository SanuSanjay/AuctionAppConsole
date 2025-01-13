
#include "AuctionApp.h"



void UserAccDetails::DisplayUserInfo() const {
	cout << "Username :" << Reg_UserName << '\n';
	cout << "Wallet balance :" << MoneyBalance << '\n';
	cout << "Items in cart : " << items << '\n';
	cout << "Paintings listed by you : " << listed << '\n';
	cout << '\n';
	cout << '\n';
}

void AuctionApp::functionToProcess() {
	cout << "Enter the number corresponding to the action you want to perform" << '\n';
	cout << "1. Add money to wallet" << '\n';
	cout << "2. Bid on a painting" << '\n';
	cout << "3. Buyout a painting" << '\n';
	cout << "4. List a painting" << '\n';
	cout << "5. Exit" << '\n';

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		AddMoney();
		break;

	case 2:
		Bid();
		break;

	case 3:
		Buyout();
		break;

	case 4:
		AddListing();
		break;
	case 5:
		exit(0);
	default:
		cout << "Invalid choice" << '\n';
	}
}

void AuctionApp::AddMoney() {
	cout << "Enter the amount you want to add to your wallet : ";
	float amount;
	cin >> amount;
	MoneyBalance += amount;
	cout << "Amount added successfully" << '\n';
	cout << "Your current balance is : " << MoneyBalance << '\n';
	cout << '\n';
	functionToProcess();
}


string AuctionApp::Bid() {
	return "hello";
}

string AuctionApp::Buyout() {
	return "hello";
}

string AuctionApp::AddListing() {
	return "hello";
}

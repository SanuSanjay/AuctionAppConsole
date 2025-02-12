
#include "AuctionApp.h"

namespace tracker {
	int counter = 3;
	double totalBidAmount = 0;
	static void resetCounter() {
		counter = 3;
	}
	static void resetTotalBidAmount() {
		totalBidAmount = 0;
	}
}

void AuctionApp::DisplayUserInfo() const {
	cout << "Username :" << userDetails->getRegUser() << '\n';
	cout << "Wallet balance :" << MoneyBalance << '\n';
	cout << "Items in cart : " << cartItems << '\n';
	cout << "Paintings listed by you : " << listed << '\n';
	cout << "Paintings owned : " << '\n';

	// Use the size() function to iterate over the vector
	//I want to kms
	for (size_t i = 0; i < paintings->Users_Paintings.size(); i++) {
		cout << "Painting name is " << paintings->Users_Paintings[i] << '\n';
		cout << "Artis name is : " << paintings->User_Artists[i] << '\n';
		cout << "Amount paid for the painting : " << paintings->PriceBought[i] << '\n';
	}

	cout << '\n';
	cout << '\n';
}


void AuctionApp::functionToProcess() {
	cout << "Enter the number corresponding to the action you want to perform" << '\n';
	cout << "0. To print paintings listed for auction" << '\n';
	cout << "1. Print your current account details" << '\n';
	cout << "2. Add money to wallet" << '\n';
	cout << "3. Bid on a painting" << '\n';
	cout << "4. Buyout a painting " << '\n';
	cout << "5. List a painting" << '\n';
	cout << "6. Exit the program" << '\n';

	int choice;
	cin >> choice;

	switch (choice) {
	case 0:
		paintings->PrintPaintings();
		cout << '\n';
		functionToProcess();
		break;
	case 1:
		DisplayUserInfo();
		functionToProcess();
		break;
	case 2:
		AddMoney();
		break;
	case 3:
		InitialBid();
		break;
	case 4:
		Buyout();
		break;
	case 5:
		AddListing();
		break;
	case 6:
		exit(0);
		break;
	default:
		cout << "Invalid choice" << '\n';
		system("pause");
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


string AuctionApp::InitialBid() {
bid:
	int bidchoice; char choice;
	cout << "Your current account balance is : " << MoneyBalance << '\n';
	cout << "Enter the number corresponding to the painting you want to bid on : ";
	cin >> bidchoice;

	if (bidchoice > paintings->index || bidchoice <= 0) {
		cout << "Invalid choice! Please re-enter your choice" << '\n';
		goto bid;
	}

	cout << "The bid amount for the painting is : " << paintings->Prices[static_cast<std::vector<double, std::allocator<double>>::size_type>(bidchoice) - 1] << '\n';
	cout << "Do you want to proceed with the bid? (Y/N) : ";
	cin >> choice;

	if (choice == 'Y' || choice == 'y') {
		if (paintings->Prices[static_cast<std::vector<double, std::allocator<double>>::size_type>(bidchoice) - 1] > MoneyBalance) {
			cout << "Insufficient balance! Please add money to your wallet" << '\n';
			cout << '\n'; cout << '\n';
			functionToProcess();
			return "Insufficent funds";
		}

		else {
			tracker::totalBidAmount = paintings->Prices[static_cast<std::vector<double, std::allocator<double>>::size_type>(bidchoice) - 1];
			MoneyBalance -= tracker::totalBidAmount;
			cout << "Bid placed successfully" << '\n';
			cout << "Your current balance is : " << MoneyBalance << '\n';
			cout << '\n';
			BidSuccess(bidchoice);
			cout << '\n'; cout << '\n';
			functionToProcess();
			return "completed";
		}
	}

	else if (choice == 'N' || choice == 'n') {
		cout << "Bid cancelled" << '\n';
		cout << '\n';
		functionToProcess();
		return "cancelled";
	}

	else {
		cout << "Invalid choice! Please re-enter your choice" << '\n';
		goto bid;
	}
	return "completed";
}



bool AuctionApp::BidSuccess(int paintingIndex) {
	char choice; int attempts = 3;
	cout << "Waiting for the auction to end ......" << '\n';
	std::this_thread::sleep_for(std::chrono::seconds(5));

	if ((int)rand() % 2 == 0) {
		cout << '\n';
		cout << "Congratulations! Your bid was successful" << '\n';
		cout << "The painting will be added to your collection" << '\n';
		cout << "Current Money balance is : " << MoneyBalance << '\n';
		UpdateListings(paintingIndex);
		functionToProcess();
		return true;
	}
	else {
		cout << "Sorry! Someone placed a higher bid than you" << '\n';
		cout << "Would you like to place a larger bid than them?" << '\n';
		cout << "Proceed with the bid? (Y/N) : ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			ConsecutiveBid(paintingIndex);
		}
		else {
			cout << "Bid cancelled" << '\n';
			MoneyBalance += tracker::totalBidAmount;
			cout << "Amount withdrawn and added to your wallet" << '\n';
			tracker::resetTotalBidAmount();
			cout << "Your current balance is : " << MoneyBalance << '\n';
			functionToProcess();
			return false;
		}
	}
	return true;
}


int AuctionApp::ConsecutiveBid(int index) {
retry:
	char choice;
	cout << "Amount to be paid as extra bid : " << tracker::totalBidAmount * paintings->bidPercentageBump << '\n';
	cout << "Proceed with the bid? (Y/N) : ";
	cin >> choice;

	while (tracker::counter >= 0)
		if (choice == 'Y' || choice == 'y') {
			if (BalanceCheck(tracker::totalBidAmount)) {
				MoneyBalance -= tracker::totalBidAmount * paintings->bidPercentageBump;
				tracker::totalBidAmount += tracker::totalBidAmount * paintings->bidPercentageBump;
				cout << "Bid placed successfully" << '\n';
				cout << "Your current balance is : " << MoneyBalance << '\n';
				tracker::counter--;
				BidSuccess(index);
			}
		}
		else if (choice == 'N' || choice == 'n') {
			cout << "Bid cancelled" << '\n';
			cout << "Amount withdrawn and added to your wallet" << '\n';
			MoneyBalance += tracker::totalBidAmount;
			tracker::resetTotalBidAmount();
			cout << '\n';
			functionToProcess();
		}
		else {
			cout << "Invalid choice! Please re-enter your choice" << '\n';
			goto retry;
		}
	tracker::resetCounter();
	return 1;
}

bool AuctionApp::BalanceCheck(double bidAmount) {
	if ((bidAmount * paintings->bidPercentageBump) > MoneyBalance) {
		cout << "Insufficient balance! Please add money to your wallet" << '\n';
		cout << "Bid amount withdrawn and added to your wallet" << '\n';
		MoneyBalance += tracker::totalBidAmount;
		functionToProcess();
		return false;
	}
	else {
		return true;
	}
}

string AuctionApp::Buyout() {
buyout:
	int bidchoice; char choice;
	cout << "Your current account balance is : " << MoneyBalance << '\n';
	cout << "Enter the number corresponding to the painting you want buyout : ";
	cin >> bidchoice;

	double totalAmount = paintings->Prices[static_cast<std::vector<double, std::allocator<double>>::size_type>(bidchoice) - 1] + paintings->Prices[static_cast<std::vector<double, std::allocator<double>>::size_type>(bidchoice) - 1] * paintings->buyoutPercentageBump;

	cout << "The amount to be paid of the painting is :" << totalAmount << '\n';
	cout << "Do you want to proceed with the buyout? (Y/N) : ";
	cin >> choice;

	if (choice == 'Y' || choice == 'y') {
		if (totalAmount > MoneyBalance) {
			cout << "Insufficient balance! Please add money to your wallet" << '\n';
			cout << '\n'; cout << '\n';
			functionToProcess();
			return "Insufficent funds";
		}

		else {
			MoneyBalance -= totalAmount;
			cout << '\n';
			cout << "Congratulations! Your buyout was successful" << '\n';
			cout << "The painting will be added to your collection" << '\n';
			cout << "Current Money balance is : " << MoneyBalance << '\n';
			cout << '\n';
			UpdateListings(bidchoice);
			functionToProcess();
			return "completed";
		}
	}

	else if (choice == 'N' || choice == 'n') {
		cout << "Buyout cancelled" << '\n';
		cout << '\n';
		functionToProcess();
		return "cancelled";
	}

	else {
		cout << "Invalid choice! Please re-enter your choice" << '\n';
		goto buyout;
	}
	return "success";
}

string AuctionApp::AddListing() {
	string painting;
	double price;

	cout << "Enter the name of the painting you want to list : ";
	cin >> painting;
	cout << "Enter the price of the painting : ";
	cin >> price;

	ownedItems++;
	paintings->Paintings.push_back(painting);
	paintings->Artists.push_back(userDetails->getRegUser());
	paintings->Prices.push_back(price);

	paintings->index++;
	listed++;

	functionToProcess();
	return "Painting added to the list";
}

void AuctionApp::UpdateListings(int index) {

	//Adding the painting to the list of paintings bought by the user
	paintings->Users_Paintings.push_back(paintings->Paintings[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(index) - 1]);
	paintings->User_Artists.push_back(paintings->Artists[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(index) - 1]);
	paintings->PriceBought.push_back(tracker::totalBidAmount);

	tracker::resetTotalBidAmount();

	//Removing the painting from the list of paintings
	paintings->Artists.erase(paintings->Artists.begin() + index - 1);
	paintings->Paintings.erase(paintings->Paintings.begin() + index - 1);
	paintings->Prices.erase(paintings->Prices.begin() + index - 1);
	paintings->index--;
}


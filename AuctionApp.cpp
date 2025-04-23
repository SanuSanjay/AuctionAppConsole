
#include "AuctionApp.h"

namespace tracker {
	int counter = 3;
	int cartItems = 0;
	vector<int> ListingIndex;
	double totalPaintingAmount = 0;

	static void resetCounter() {
		counter = 3;
	}
	static void resetTotalPaintingAmount() {
		totalPaintingAmount = 0;
	}
	static void correctIndices() {
		ListingIndex.erase(ListingIndex.begin() + cartItems - 1);
		cartItems-= 1;
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
choice:
	cout << "Enter the number corresponding to the action you want to perform" << '\n';
	cout << "0. To print paintings listed for auction" << '\n';
	cout << "1. Print your current account details" << '\n';
	cout << "2. Add money to wallet" << '\n';
	cout << "3. Bid on a painting" << '\n';
	cout << "4. Buyout a painting" << '\n';
	cout << "5. Add painting to cart" << '\n';
	cout << "6. To buy paintings in the cart" << '\n';
	cout << "7. List a painting" << '\n';
	cout << "8. Exit the program" << '\n';

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
		InitialBid(-1,false);
		break;
	case 4:
		Buyout(-1,false);
		break;
	case 5:
		AddToCart();
		break;
	case 6:
		BuyFromCart();
		break;
	case 7:
		AddListing();
		break;
	case 8:
		cout << "Program terminated! " << '\n';
		exit(0);
	default:
		cout << "Invalid choice" << '\n';
		cout << "Re-enter the number" << '\n';
		goto choice;
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


string AuctionApp::InitialBid(int cart,bool isCartItem) {
bid:
	int bidchoice; char choice;
	cout << "Your current account balance is : " << MoneyBalance << '\n';
	if (cart == -1) {
		cout << "Enter the number corresponding to the painting you want to bid on : ";
		cin >> bidchoice;
	}
	else {
		bidchoice = tracker::ListingIndex[cart - 1];
	}

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
			tracker::totalPaintingAmount = paintings->Prices[static_cast<std::vector<double, std::allocator<double>>::size_type>(bidchoice) - 1];
			MoneyBalance -= tracker::totalPaintingAmount;
			cout << "Bid placed successfully" << '\n';
			cout << "Your current balance is : " << MoneyBalance << '\n';
			cout << '\n';
			BidSuccess(bidchoice, isCartItem);
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



bool AuctionApp::BidSuccess(int paintingIndex,bool isCartItem) {
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
			ConsecutiveBid(paintingIndex, isCartItem);
		}
		else {
			cout << "Bid cancelled" << '\n';
			MoneyBalance += tracker::totalPaintingAmount;
			cout << "Amount withdrawn and added to your wallet" << '\n';
			tracker::resetTotalPaintingAmount();
			cout << "Your current balance is : " << MoneyBalance << '\n';
			functionToProcess();
			return false;
		}
	}
	return true;
}


int AuctionApp::ConsecutiveBid(int index, bool isCartItem) {
retry:
	char choice;
	cout << "Amount to be paid as extra bid : " << tracker::totalPaintingAmount * paintings->bidPercentageBump << '\n';
	cout << "Proceed with the bid? (Y/N) : ";
	cin >> choice;

	while (tracker::counter >= 0)
		if (choice == 'Y' || choice == 'y') {
			if (BalanceCheck(tracker::totalPaintingAmount)) {
				MoneyBalance -= tracker::totalPaintingAmount * paintings->bidPercentageBump;
				tracker::totalPaintingAmount += tracker::totalPaintingAmount * paintings->bidPercentageBump;
				cout << "Bid placed successfully" << '\n';
				cout << "Your current balance is : " << MoneyBalance << '\n';
				tracker::counter--;
				BidSuccess(index, isCartItem);
			}
		}
		else if (choice == 'N' || choice == 'n') {
			cout << "Bid cancelled" << '\n';
			cout << "Amount withdrawn and added to your wallet" << '\n';
			MoneyBalance += tracker::totalPaintingAmount;
			tracker::resetTotalPaintingAmount();
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
		MoneyBalance += tracker::totalPaintingAmount;
		functionToProcess();
		return false;
	}
	else {
		return true;
	}
}

string AuctionApp::Buyout(int cart, bool isCartItem) {
buyout:
	int buyoutChoice = 0; char choice;
	if (cart == -1) {
		cout << "Your current account balance is : " << MoneyBalance << '\n';
		cout << "Enter the number corresponding to the painting you want buyout : ";
		cin >> buyoutChoice;
	}

	if (cart > 0) {
		buyoutChoice = tracker::ListingIndex[cart - 1];
	}

	if (buyoutChoice > paintings->Prices.size() || buyoutChoice <= 0) {
		cout << "Index Out Of Bound! " << '\n';
		return "Index out of bound";
	}

	auto index = buyoutChoice - 1;

	double basePrice = paintings->Prices[index];
	double totalAmount = basePrice + (basePrice * paintings->buyoutPercentageBump);

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
			tracker::totalPaintingAmount = totalAmount;
			if (isCartItem) {
				UpdateCart(buyoutChoice);
				UpdateListings(buyoutChoice);
			}
			UpdateListings(buyoutChoice);
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

string AuctionApp::AddToCart() {
	int temp;
	cout << "To add paintings to your cart choose the corresponding number to it :" << '\n';
	cin >> temp;

	if (temp <= 0 || temp > paintings->index) {
		cout << "Index out of bound!" << '\n';
		return "Index out of bound";
	}

	tracker::ListingIndex.push_back(temp);
	paintings->Painting_In_Cart.push_back(paintings->Paintings[static_cast<std::vector<std::string>::size_type>(temp) - 1]);
	tracker::cartItems += 1;
	

	cout << "Painting added to cart successfully!" << '\n';
	functionToProcess();
	return "success";
}

string AuctionApp::BuyFromCart() {
start:
	int index, choice;
	cout << "Paintings in your cart are: " << '\n';

	if (tracker::cartItems == 0) {
		cout << "Cart is empty, please add an item or continue with other functions " << '\n';
		functionToProcess();
	}

	for (int i = 0; i < tracker::cartItems; i++) {
		cout << i + 1 << ". " << paintings->Painting_In_Cart[i] << '\n';
	}

	cout << "Enter the index for the painting to be bought from the cart: " << '\n';
	cin >> index;

	if (index <= 0 || index > tracker::cartItems) {
		cout << "Index out of bound, please try again!" << '\n';
		goto start;
	}

	cout << "Checking if the painting is still listed " << '\n';
	std::this_thread::sleep_for(std::chrono::seconds(2));

	if (PaintingAvailable(index)) {
		cout << "Enter 1 to bid for the painting " << '\n';
		cout << "Enter 2 to buyout the painting " << '\n';
		cin >> choice;

		switch (choice) {
		case 1:
			if (InitialBid(index,true) == "completed") {
				//UpdateCart needs 
				UpdateCart(index);
				UpdateListings(index);
				functionToProcess();
				return "success";
			}
			break;
		case 2:
			if (Buyout(index,true) == "completed") {
				//UpdateCart needs fixing
				UpdateCart(index);
				UpdateListings(index);
				functionToProcess();
				return "success";
			}
			break;
		default:
			cout << "Invalid Option! " << '\n';
			goto start;
			return "failed";
		}
	}
	else {
		cout << "Painting has already been bought by someone else!" << '\n';
		cout << "Removing item from the cart " << '\n';
		//This call works for some reason
		UpdateCart(index);
		goto start;
		return "failed";
	}
	return "failed";
}

void AuctionApp::UpdateCart(int index) {
	if (index <= 0 || index > tracker::cartItems) {
		cout << "Invalid index for updating cart" << '\n';
		return;
	}

	paintings->Painting_In_Cart.erase(paintings->Painting_In_Cart.begin() + index - 1);
	tracker::correctIndices();
}


bool AuctionApp::PaintingAvailable(int index) {
	if (tracker::cartItems <= 0 || tracker::cartItems > paintings->Painting_In_Cart.size()) {
		return false;
	}

	int cartIndex = tracker::cartItems - 1; // Use a valid index
	//int listingIndex = tracker::ListingIndex[cartIndex] - 1; // Use a valid index

	/*if (listingIndex < 0 || listingIndex >= paintings->Paintings.size()) {
		return false;
	}*/

	for (int i = 0; i < paintings->Paintings.size(); i++) {
		if (paintings->Painting_In_Cart[cartIndex] == paintings->Paintings[i]) {
			return true;
		}
	}	

	//return paintings->Painting_In_Cart[cartIndex] == paintings->Paintings[listingIndex];
	return false;
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

	const size_t vector_Index = static_cast<size_t>(index - 1);

	//Adding the painting to the list of paintings bought by the user
	paintings->Users_Paintings.push_back(paintings->Paintings[vector_Index]);
	paintings->User_Artists.push_back(paintings->Artists[vector_Index]);
	paintings->PriceBought.push_back(tracker::totalPaintingAmount);

	tracker::resetTotalPaintingAmount();

	//Removing the painting from the list of paintings
	paintings->Artists.erase(paintings->Artists.begin() + vector_Index);
	paintings->Paintings.erase(paintings->Paintings.begin() + vector_Index);
	paintings->Prices.erase(paintings->Prices.begin() + vector_Index);
	paintings->index--;

	functionToProcess();
}


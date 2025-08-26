
#include "AuctionApp.h"

namespace tracker
{
	int cart_items_ = 0;
	vector<int> listing_index_;
	double total_painting_amount_ = 0;

	static void reset_total_painting_amount()
	{
		total_painting_amount_ = 0;
	}
	static void correct_indices()
	{
		listing_index_.erase(listing_index_.begin() + cart_items_ - 1);
		cart_items_ -= 1;
	}
}

void AuctionApp::display_user_info() const
{
	cout << "Username :" << user_details->get_reg_user() << '\n';
	cout << "Wallet balance :" << money_balance_ << '\n';
	cout << "Items in cart : " << user_details->cart_items_ << '\n';
	cout << "Paintings listed by you : " << listed << '\n';
	cout << "Paintings owned : " << '\n';

	for (size_t i = 0; i < paintings->user_owned_paintings_.size(); i++)
	{
		cout << "Painting name is " << paintings->user_owned_paintings_[i].painting_name << '\n';
		cout << "Artis name is : " << paintings->user_owned_paintings_[i].artist_name << '\n';
		cout << "Amount paid for the painting : " << paintings->user_owned_paintings_[i].price_paid << '\n';
	}

	cout << '\n';
	cout << '\n';
}


void AuctionApp::function_to_process()
{
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

	int is_cart_item = -1;

	switch (choice)
	{
	case 0:
		paintings->print_paintings();
		cout << '\n';
		function_to_process();
		break;
	case 1:
		display_user_info();
		function_to_process();
		break;
	case 2:
		add_money();
		break;
	case 3:
		initial_bid(is_cart_item);
		break;
	case 4:
		buyout(is_cart_item);
		break;
	case 5:
		add_to_cart();
		break;
	case 6:
		buy_from_cart();
		break;
	case 7:
		add_listings();
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

void AuctionApp::add_money()
{
	cout << "Enter the amount you want to add to your wallet : ";
	float amount;
	cin >> amount;
	money_balance_ += amount;
	cout << "Amount added successfully" << '\n';
	cout << "Your current balance is : " << money_balance_ << '\n';
	cout << '\n';
	function_to_process();
}


string AuctionApp::initial_bid(int cart)
{
bid:
	int bid_choice; char choice;
	cout << "Your current account balance is : " << money_balance_ << '\n';
	//-1 means its not from cart
	if (cart == -1)
	{
		cout << "Enter the number corresponding to the painting you want to bid on : ";
		cin >> bid_choice;
	}
	else
	{
		bid_choice = tracker::listing_index_[cart - 1];
	}

	if (bid_choice > paintings->index || bid_choice <= 0)
	{
		cout << "Invalid choice! Please re-enter your choice" << '\n';
		goto bid;
	}

	cout << "The bid amount for the painting is : " << paintings->painting_info_[static_cast<std::vector<double, std::allocator<double>>::size_type>(bid_choice) - 1].price << '\n';
	cout << "Do you want to proceed with the bid? (Y/N) : ";
	cin >> choice;

	if (choice == 'Y' || choice == 'y')
	{
		if (paintings->painting_info_[static_cast<std::vector<double, std::allocator<double>>::size_type>(bid_choice) - 1].price > money_balance_) {
			cout << "Insufficient balance! Please add money to your wallet" << '\n';
			cout << '\n'; cout << '\n';
			function_to_process();
			return "Insufficent funds";
		}

		else
		{
			tracker::total_painting_amount_ = paintings->painting_info_[static_cast<std::vector<double, std::allocator<double>>::size_type>(bid_choice) - 1].price;
			money_balance_ -= tracker::total_painting_amount_;
			cout << "Bid placed successfully" << '\n';
			cout << "Your current balance is : " << money_balance_ << '\n';
			cout << '\n';
			bid_success(bid_choice);
			cout << '\n'; cout << '\n';
			function_to_process();
			return "completed";
		}
	}

	else if (choice == 'N' || choice == 'n')
	{
		cout << "Bid cancelled" << '\n';
		cout << '\n';
		function_to_process();
		return "cancelled";
	}

	else
	{
		cout << "Invalid choice! Please re-enter your choice" << '\n';
		goto bid;
	}
	return "completed";
}



bool AuctionApp::bid_success(int paintingIndex)
{
	char choice;
	cout << "Waiting for the auction to end ......" << '\n';
	std::this_thread::sleep_for(std::chrono::seconds(3));

	if ((int)rand() % 2 == 0)
	{
		cout << '\n';
		cout << "Congratulations! Your bid was successful" << '\n';
		cout << "The painting will be added to your collection" << '\n';
		cout << "Current Money balance is : " << money_balance_ << '\n';
		update_listings(paintingIndex);
		function_to_process();
		return true;
	}

	cout << "Sorry! Someone placed a higher bid than you" << '\n';
	cout << "Would you like to place a larger bid than them?" << '\n';
	cout << "Proceed with the bid? (Y/N) : ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		consecutive_bid(paintingIndex);
	}
	else
	{
		cout << "Bid cancelled" << '\n';
		money_balance_ += tracker::total_painting_amount_;
		cout << "Amount withdrawn and added to your wallet" << '\n';
		tracker::reset_total_painting_amount();
		cout << "Your current balance is : " << money_balance_ << '\n';
		function_to_process();
	}
	return true;
}


int AuctionApp::consecutive_bid(int index)
{
retry:
	char choice;
	cout << "Amount to be paid as extra bid : " << tracker::total_painting_amount_ * paintings->bid_percentage_bump_ << '\n';
	cout << "Proceed with the bid? (Y/N) : ";
	cin >> choice;

	while (1)
		if (choice == 'Y' || choice == 'y')
		{
			if (balance_check(tracker::total_painting_amount_))
			{
				money_balance_ -= tracker::total_painting_amount_ * paintings->bid_percentage_bump_;
				tracker::total_painting_amount_ += tracker::total_painting_amount_ * paintings->bid_percentage_bump_;
				cout << "Bid placed successfully" << '\n';
				cout << "Your current balance is : " << money_balance_ << '\n';
				bid_success(index);
			}
		}
		else if (choice == 'N' || choice == 'n')
		{
			cout << "Bid cancelled" << '\n';
			cout << "Amount withdrawn and added to your wallet" << '\n';
			money_balance_ += tracker::total_painting_amount_;
			tracker::reset_total_painting_amount();
			cout << '\n';
			function_to_process();
		}
		else
		{
			cout << "Invalid choice! Please re-enter your choice" << '\n';
			goto retry;
		}
	return 1;
}

bool AuctionApp::balance_check(double bidAmount)
{
	if ((bidAmount * paintings->bid_percentage_bump_) > money_balance_)
	{
		cout << "Insufficient balance! Please add money to your wallet" << '\n';
		cout << "Bid amount withdrawn and added to your wallet" << '\n';
		money_balance_ += tracker::total_painting_amount_;
		function_to_process();
		return false;
	}
	else
	{
		return true;
	}
}

string AuctionApp::buyout(int cart)
{
buyout:
	int buyoutChoice = 0; char choice;
	if (cart == -1)
	{
		cout << "Your current account balance is : " << money_balance_ << '\n';
		cout << "Enter the number corresponding to the painting you want buyout : ";
		cin >> buyoutChoice;
	}

	if (cart > 0)
	{
		buyoutChoice = tracker::listing_index_[cart - 1];
	}

	if (buyoutChoice > paintings->painting_info_.size() || buyoutChoice <= 0)
	{
		cout << "Index Out Of Bound! " << '\n';
		return "Index out of bound";
	}

	auto index = buyoutChoice - 1;

	double basePrice = paintings->painting_info_[index].price;
	double totalAmount = basePrice + (basePrice * paintings->buyout_percentage_bump_);

	cout << "The amount to be paid of the painting is :" << totalAmount << '\n';
	cout << "Do you want to proceed with the buyout? (Y/N) : ";
	cin >> choice;

	if (choice == 'Y' || choice == 'y')
	{
		if (totalAmount > money_balance_)
		{
			cout << "Insufficient balance! Please add money to your wallet" << '\n';
			cout << '\n'; cout << '\n';
			function_to_process();
			return "Insufficent funds";
		}

		else
		{
			money_balance_ -= totalAmount;
			cout << '\n';
			cout << "Congratulations! Your buyout was successful" << '\n';
			cout << "The painting will be added to your collection" << '\n';
			cout << "Current Money balance is : " << money_balance_ << '\n';
			cout << '\n';
			tracker::total_painting_amount_ = totalAmount;
			if (cart > -1)
			{
				update_cart(buyoutChoice);
				update_listings(buyoutChoice);
			}
			update_listings(buyoutChoice);
			return "completed";

		}
	}

	else if (choice == 'N' || choice == 'n')
	{
		cout << "Buyout cancelled" << '\n';
		cout << '\n';
		function_to_process();
		return "cancelled";
	}

	else
	{
		cout << "Invalid choice! Please re-enter your choice" << '\n';
		goto buyout;
	}
	return "success";
}

string AuctionApp::add_to_cart()
{
	int temp;
	cout << "To add paintings to your cart choose the corresponding number to it :" << '\n';
	cin >> temp;

	if (temp <= 0 || temp > paintings->index)
	{
		cout << "Index out of bound!" << '\n';
		return "Index out of bound";
	}

	tracker::listing_index_.push_back(temp);
	paintings->painting_in_cart_.emplace_back(paintings->painting_info_[static_cast<std::vector<std::string>::size_type>(temp) - 1].painting_name);
	tracker::cart_items_ += 1;


	cout << "Painting added to cart successfully!" << '\n';
	function_to_process();
	return "success";
}

string AuctionApp::buy_from_cart()
{
start:
	int index, choice;
	cout << "Paintings in your cart are: " << '\n';

	if (tracker::cart_items_ == 0)
	{
		cout << "Cart is empty, please add an item or continue with other functions " << '\n';
		function_to_process();
	}

	for (int i = 0; i < tracker::cart_items_; i++)
	{
		cout << i + 1 << ". " << paintings->painting_in_cart_[i] << '\n';
	}

	cout << "Enter the index for the painting to be bought from the cart: " << '\n';
	cin >> index;

	if (index <= 0 || index > tracker::cart_items_)
	{
		cout << "Index out of bound, please try again!" << '\n';
		goto start;
	}

	cout << "Checking if the painting is still listed " << '\n';
	std::this_thread::sleep_for(std::chrono::seconds(2));

	if (painting_available(index))
	{
		cout << "Enter 1 to bid for the painting " << '\n';
		cout << "Enter 2 to buyout the painting " << '\n';
		cin >> choice;

		switch (choice) {
		case 1:
			if (initial_bid(index) == "completed") {
				update_cart(index);
				update_listings(index);
				function_to_process();
				return "success";
			}
			break;
		case 2:
			if (buyout(index) == "completed")
			{
				update_cart(index);
				update_listings(index);
				function_to_process();
				return "success";
			}
			break;
		default:
			cout << "Invalid Option! " << '\n';
			goto start;
			return "failed";
		}
	}
	else
	{
		cout << "Painting has already been bought by someone else!" << '\n';
		cout << "Removing item from the cart " << '\n';
		update_cart(index);
		goto start;
		return "failed";
	}
	return "failed";
}

void AuctionApp::update_cart(int index)
{
	if (index <= 0 || index > tracker::cart_items_)
	{
		cout << "Invalid index for updating cart" << '\n';
		return;
	}

	paintings->painting_in_cart_.erase(paintings->painting_in_cart_.begin() + index - 1);
	tracker::correct_indices();
}


bool AuctionApp::painting_available(int index)
{
	if (tracker::cart_items_ <= 0 || tracker::cart_items_ > paintings->painting_in_cart_.size())
	{
		return false;
	}


	for (int i = 0; i < paintings->painting_info_.size(); i++)
	{
		if (paintings->painting_in_cart_[index - 1] == paintings->painting_info_[i].painting_name)
		{
			return true;
		}
	}

	return false;
}


string AuctionApp::add_listings()
{
	string painting;
	double price;

	cout << "Enter the name of the painting you want to list : ";
	cin >> painting;
	cout << "Enter the price of the painting : ";
	cin >> price;

	owned_items_++;
	paintings->painting_info_.emplace_back(PaintingsInfo{ painting, user_details->get_reg_user(), price });
	paintings->index++;
	listed++;

	function_to_process();
	return "Painting added to the list";
}

void AuctionApp::update_listings(int index)
{

	const size_t vector_Index = static_cast<size_t>(index - 1);

	//Adding the painting to the list of paintings bought by the user

	paintings->user_owned_paintings_.emplace_back(
		paintings->painting_info_[vector_Index].painting_name,
		paintings->painting_info_[vector_Index].artist_name,
		tracker::total_painting_amount_
	);

	tracker::reset_total_painting_amount();

	//Removing the painting from the list of paintings
	paintings->painting_info_.erase(paintings->painting_info_.begin() + vector_Index);
	paintings->index--;

	function_to_process();
}


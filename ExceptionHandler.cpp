#include "AuctionApp.h"

void AuctionApp::validate_option(int& choice)
{
	while (true) {
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
			std::cout << "Invalid input. Please enter a number." << std::endl;
		} else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any extra input
			break; // Valid input, exit the loop
		}
	}
}

void AuctionApp::validate_input(float& amount)
{
	while (true) {
		std::cout << "Enter the amount: ";
		std::cin >> amount;
		if (std::cin.fail() || amount < 0) {
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "Invalid input. Please enter a positive number." << std::endl;
		} else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			break; 
		}
	}
}
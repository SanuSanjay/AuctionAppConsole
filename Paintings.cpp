
#include "AuctionApp.h"


//Function which stores the first 5 default paintings of the app
 void ListedPaintings::default_paintings() 
 {

	 painting_info_.emplace_back(PaintingsInfo{ "Mona Lisa", "Leonardo Da Vinci", 100000 });
	 painting_info_.emplace_back(PaintingsInfo{ "Interchange", "Willem de Kooning", 300000 });
	 painting_info_.emplace_back(PaintingsInfo{ "The Card Players", "Paul Cézanne", 173000 });
	 painting_info_.emplace_back(PaintingsInfo{ "When Will You Marry?", "Paul Gauguin", 235000 });
	 painting_info_.emplace_back(PaintingsInfo{ "Number 17A", "Jackson Pollock", 164500 });
	
}

void ListedPaintings::print_paintings() 
{
	for (int i = 0; i < index; i++) 
	{
		cout << (i+1) <<".";
		cout << "Painting : " << painting_info_[i].painting_name << '\n';
		cout << "Artist : " << painting_info_[i].artist_name << '\n';
		cout << "Starting Bid Price : " << painting_info_[i].price << '\n';
		cout << "Buyout Price : " << painting_info_[i].price + painting_info_[i].price * buyout_percentage_bump_ << '\n';
		cout << '\n';
	}
}
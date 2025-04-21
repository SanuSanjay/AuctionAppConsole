
#include "AuctionApp.h"


//Function which stores the first 5 default paintings of the app
 void ListedPaintings::DefaultPainting() 
 {

	Paintings.push_back("Mona Lisa");
	Artists.push_back("Leonardo Da Vinci");
	Prices.push_back(100000);

	Paintings.push_back("Interchange");
	Artists.push_back("Willem de Kooning");
	Prices.push_back(300000);

	Paintings.push_back("The Card Players");
	Artists.push_back("Paul Cézanne");
	Prices.push_back(173000);

	Paintings.push_back("When Will You Marry?");
	Artists.push_back("Paul Gauguin");
	Prices.push_back(235000);

	Paintings.push_back("Number 17A");
	Artists.push_back("Jackson Pollock");
	Prices.push_back(164500);

	
	//PrintPaintings();
}

void ListedPaintings::PrintPaintings() 
{
	for (int i = 0; i < index; i++) 
	{
		cout << (i+1) <<".";
		cout << "Painting : " << Paintings[i] << '\n';
		cout << "Artist : " << Artists[i] << '\n';
		cout << "Starting Bid Price : " << Prices[i] << '\n';
		cout << "Buyout Price : " << Prices[i] + Prices[i] * buyoutPercentageBump << '\n';
		cout << '\n';
		//system("pause > 0");
	}
}
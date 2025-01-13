
#include "Paintings.h"


//Default constructor which stores the first 5 paintings of the app
ListedPaintings::ListedPaintings() {
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

	bidPercentageBump = 0.15;
	buyoutPercentageBump = 0.40;
	index = 5;
}

void ListedPaintings::PrintPaintings() {
	for (int i = 0; i < index; i++) {
		cout << (i+1) <<".";
		cout << "Painting : " << Paintings[i] << '\n';
		cout << "Artist : " << Artists[i] << '\n';
		cout << "Price : " << Prices[i] << '\n';
		cout << '\n';
	}
}
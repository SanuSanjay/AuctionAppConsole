#ifndef PAINTINGS_H
#define PAINTINGS_H

#include "All_Includes.h"


class ListedPaintings {
protected :
	vector<string> Paintings;
	vector<string> Artists;
	vector<double> Prices;
	double bidPercentageBump;
	double buyoutPercentageBump;
	int index;
public : 
	ListedPaintings();
	void PrintPaintings();
};


#endif // PAINTINGS_H!
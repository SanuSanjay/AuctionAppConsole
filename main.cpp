
#include "CredentialVerifier.h"
#include "AuctionApp.h"

/*1.Welcome Screen
  -> Need to press enter to continue
  -> Login screen (needs username and psw)
  -> username = user and psw = auction (case sensitive) (COMPLETED)

  2.Auction Screen with bid and buyout option   <-
  -> Contains different types of paintings to be bought

  3.Screen to add a listing for your own painting
  -> need to specify minimum bid amount and buyout price

  4.Add a countdown for a minute after placing a bid
  -> A bid can be randomly placed within the minute for a maximum of 3 times before user wins the bid

  5.When the player wins the bid create a text file storing the name of the painting and the price paid for the painting
  -> The text file contains all the paintings bought and put on auction by the user.

  6.Exit the program when all tasks are complete
  */



int main() {
    RegisteredUserDetails obj;
    obj.AccountRegistration();

    ListedPaintings Paint(&obj);
    AuctionApp Auction(&obj,&Paint);

    Auction.DisplayUserInfo();

    Paint.DefaultPainting();
    Paint.PrintPaintings();
    Auction.functionToProcess();

    return 0;
}

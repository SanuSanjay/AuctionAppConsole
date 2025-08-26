
#include "CredentialVerifier.h"
#include "AuctionApp.h"



int main() 
{
    RegisteredUserDetails obj;
    obj.account_registration();

    ListedPaintings Paint(&obj);
    AuctionApp Auction(&obj,&Paint);

    Auction.display_user_info();

    Paint.default_paintings();
    Paint.print_paintings();
    Auction.function_to_process();

    return 0;
}

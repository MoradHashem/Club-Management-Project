#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsAddNewMemberScreen.h"
#include "clsMemberListScreen.h"
#include "clsDeleteMemberScreen.h"
#include "clsRenewMemberScreen.h"
#include "clsFindMemberScreen.h"
#include "clsExpiredMemberScreen.h"
#include "clsEndingSoonMemberScreen.h"
#include <iomanip>
using namespace std;

class clsMainScreen :protected clsScreen
{


private:
    enum enMainMenueOptions {
        eListMembers = 1, eAddNewMember = 2, eDeleteMember = 3,
        eRenewMember = 4, eFindMember = 5, eListExpiredMembers = 6,
        eListEndingSoonMembers = 7
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllMembersScreen()
    {
          //cout << "\nMember List Screen Will be here...\n";
        clsMemberListScreen::ShowMembersList();

    }

    static void _ShowAddNewMembersScreen()
    {
         //cout << "\nAdd New Member Screen Will be here...\n";
        clsAddNewMemberScreen::ShowAddNewMemberScreen();
    }

    static void _ShowDeleteMemberScreen()
    {
        //cout << "\nDelete Member Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteMemberScreen();
    }

    static void _ShowRenewMemberScreen()
    {
        //cout << "\nUpdate Member Screen Will be here...\n";
        clsRenewMemberScreen::ShowRenewMemberScreen();
    }

    static void _ShowFindMemberScreen()
    {
         //cout << "\nFind Member Screen Will be here...\n";
        clsFindMemberScreen::ShowFindMemberScreen();
    }

    static void _ShowAllExpiredMembersScreen()
    {
         //cout << "\nExpired Member Screen Will be here...\n";
        clsExpiredMemberScreen::ShowExpiredMembersList();
    }

    static void _ShowAllEndingSoonMembersScreen()
    {
         //cout << "\nEnding Soon Member Screen Will be here...\n";
        clsEndingSoonMemberScreen::ShowEndingSoonMembersList();
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListMembers:
        {
            system("cls");
            _ShowAllMembersScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewMember:
            system("cls");
            _ShowAddNewMembersScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteMember:
            system("cls");
            _ShowDeleteMemberScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eRenewMember:
            system("cls");
            _ShowRenewMemberScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindMember:
            system("cls");
            _ShowFindMemberScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eListExpiredMembers:
            system("cls");
            _ShowAllExpiredMembersScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eListEndingSoonMembers:
            system("cls");
            _ShowAllEndingSoonMembersScreen();
            _GoBackToMainMenue();
            break;  
        }

    }



public:


    static void ShowMainMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\tMorad Club");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Member List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Member.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Member.\n";
        cout << setw(37) << left << "" << "\t[4] Renew Membership Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Member.\n";
        cout << setw(37) << left << "" << "\t[6] Show Expired Member.\n";
        cout << setw(37) << left << "" << "\t[7] Show Ending Soon Members.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }

};


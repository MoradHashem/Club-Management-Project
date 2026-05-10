#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankMember.h"
#include <iomanip>

class clsMemberListScreen :protected clsScreen
{

private:
    static void PrintMemberRecordLine(clsBankMember Member)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << Member.MemberID;
        cout << "| " << setw(20) << left << Member.FullName();
        cout << "| " << setw(20) << left << Member.SubscriptionType;
        cout << "| " << setw(16) << left << Member.DataOfJoin;
        cout << "| " << setw(16) << left << Member.ExpiryData;
        

    }

public:


    static void ShowMembersList()
    {

        vector <clsBankMember> vMembers = clsBankMember::GetMembersList();
        string Title = "\t  Member List Screen";
        string SubTitle = "\t    (" + to_string(vMembers.size()) + ") Member(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Member ID";
        cout << "| " << left << setw(20) << "Member Name";
        cout << "| " << left << setw(20) << "Subscription Type";
        cout << "| " << left << setw(16) << "Data Of Join";
        cout << "| " << left << setw(16) << "Expiry Data";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vMembers.size() == 0)
            cout << "\t\t\t\tNo Members Available In the System!";
        else

            for (clsBankMember Member : vMembers)
            {

                PrintMemberRecordLine(Member);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;



        cout << "\t\t\t\t\t\t\t\t  Count Members = " << vMembers.size();

    }

};
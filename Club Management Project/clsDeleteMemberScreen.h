#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankMember.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
{
private:

	static void _PrintMember(clsBankMember Member)
	{
		cout << "\nMember Card:";
		cout << "\n___________________";
		cout << "\nFull Name           : " << Member.FullName();
		cout << "\nMember ID           : " << Member.MemberID;
		cout << "\nSubscription Type   : " << Member.SubscriptionType;
		cout << "\nData of Join        : " << Member.DataOfJoin;
		cout << "\nExpiry Data         : " << Member.ExpiryData;
		cout << "\n___________________\n";
	}

public:

	static void ShowDeleteMemberScreen()
	{

		_DrawScreenHeader("\t Delete Member Screen");

		string MemberID = "";

		cout << "\n Please Enter Member ID : ";
		MemberID = clsInputValidate::ReadString();

		while (!clsBankMember::IsMemberExist(MemberID))
		{
			cout << "\nMember ID is not found, choose another one : ";
			MemberID = clsInputValidate::ReadString();
		}

		clsBankMember Member = clsBankMember::Find(MemberID);
		_PrintMember(Member);

		cout << "\nAre you sure you want to delete this Member y/n ? ";

		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (Member.Delete())
			{
				cout << "\nMember Deleted Successfully :-)\n";
				_PrintMember(Member);
			}
			else
			{
				cout << "\nError Member was not Deletes\n";
			}
		}
	}
};

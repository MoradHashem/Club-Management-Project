#pragma once
#include <iostream>
#include "clsBankMember.h"
#include "clsInputValidate.h"
#include "clsPerson.h"
#include "clsScreen.h"

class clsFindMemberScreen : protected clsScreen
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

	static void ShowFindMemberScreen()
	{		

		_DrawScreenHeader("\t Find Member Screen");

		string MemberID = "";

		cout << "\n Please Enter Member ID : ";
		MemberID = clsInputValidate::ReadString();

		while (!clsBankMember::IsMemberExist(MemberID))
		{
			cout << "\nMember ID is not found, choose another one : ";
			MemberID = clsInputValidate::ReadString();
		}

		clsBankMember Member = clsBankMember::Find(MemberID);

		if (!Member.IsEmpty())
		{
			cout << "\nMember Found :-)\n";
		}
		else
		{
			cout << "\nMember Was not Found :-(\n";
		}

		_PrintMember(Member);
	}

};


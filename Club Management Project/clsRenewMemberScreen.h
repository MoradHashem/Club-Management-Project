#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankMember.h"
#include "clsDate.h"
#include "clsInputValidate.h"

class clsRenewMemberScreen : protected clsScreen
{
private:

	static void _ReadMemberInfo(clsBankMember& Member)
	{
		cout << "\nEnter New Data : ";
		Member.DataOfJoin = clsInputValidate::ReadString();

		cout << "\nEnter Subscription Type   (Annual, Monthly, Weekly) : ";
		Member.SubscriptionType = clsInputValidate::ReadString();


		if (Member.SubscriptionType == "Weekly")
		{
			clsDate Obj(Member.DataOfJoin);
			Obj.IncreaseDateByXDays(7);
			Member.ExpiryData = Obj.DateToString();
		}

		if (Member.SubscriptionType == "Monthly")
		{
			clsDate Obj(Member.DataOfJoin);
			Obj.IncreaseDateByXDays(30);
			Member.ExpiryData = Obj.DateToString();
		}

		if (Member.SubscriptionType == "Annual")
		{
			clsDate Obj(Member.DataOfJoin);
			Obj.IncreaseDateByXDays(365);
			Member.ExpiryData = Obj.DateToString();
		}
	}


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

	static void ShowRenewMemberScreen()
	{

		_DrawScreenHeader("Renew Member Screen");

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

		cout << "\nAre you sure you want to Renew this Member y/n ? ";

		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\n\nRenew Member Info : ";
			cout << "\n_________________________\n";

			_ReadMemberInfo(Member);

			clsBankMember::enSaveResults SaveResult;

			SaveResult = Member.Save();

			switch (SaveResult)
			{
			case clsBankMember::enSaveResults::svSucceeded:
			{
				cout << "\nYour membership has been renewed successfully :-)\n";
				_PrintMember(Member);
				break;
			}
			case clsBankMember::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nerror member was not saveed because it's Empty";
				break;
			}
			}
		}
	}
};


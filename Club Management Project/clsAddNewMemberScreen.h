#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsBankMember.h"
#include "clsInputValidate.h"
#include "clsDate.h"
#include<iomanip>

class clsAddNewMemberScreen : protected clsScreen
{
private:

	static void _ReadClirntInfo(clsBankMember& Member)
	{
		cout << "\nEnter FirstName : ";
		Member.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName : ";
		Member.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Subscription Type   (Annual, Monthly, Weekly) : ";
		Member.SubscriptionType = clsInputValidate::ReadString();

		cout << "\nEnter Data of Join   (dd/mm/yyyy) : ";
		Member.DataOfJoin = clsInputValidate::ReadString();


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

	static void ShowAddNewMemberScreen()
	{
		

		_DrawScreenHeader("\t  Add New Member Screen");

		string MemberID = "";

		cout << "\nPlease Enter Member ID : ";
		MemberID = clsInputValidate::ReadString();

		while (clsBankMember::IsMemberExist(MemberID))
		{
			cout << "\nMember ID is Already Used, Choose another one : ";
			MemberID = clsInputValidate::ReadString();
		}

		clsBankMember NewMember = clsBankMember::GetAddNewMemberObject(MemberID);

		_ReadClirntInfo(NewMember);

		
		clsBankMember::enSaveResults SaveResult;

		SaveResult = NewMember.Save();

		switch (SaveResult)
		{
		case clsBankMember::enSaveResults::svSucceeded:
		{
			

			_PrintMember(NewMember);
			break;
		}
		case clsBankMember::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		case clsBankMember::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		}
	}



};
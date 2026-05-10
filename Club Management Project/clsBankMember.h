#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankMember : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;


    string _MemberID;
    string _SubscriptionType;
    string _DataOfJoin;
    string _ExpiryData;
    bool _MarkedForDelete = false;


    static clsBankMember _ConvertLineToMemberObject(string Line, string Seperator = "#//#")
    {
        vector <string> vMemberData;
        vMemberData = clsString::Split(Line, Seperator);

        return clsBankMember(enMode::UpdateMode, vMemberData[0], vMemberData[1], vMemberData[2],
            vMemberData[3], vMemberData[4], vMemberData[5]);

    }


    static string _ConverMemberObjectToLine(clsBankMember Member, string Seperator = "#//#")
    {

        string stMemberRecord = "";
        stMemberRecord += Member.FirstName + Seperator;
        stMemberRecord += Member.LastName + Seperator;
        stMemberRecord += Member.MemberID + Seperator;
        stMemberRecord += Member.SubscriptionType + Seperator;
        stMemberRecord += Member.DataOfJoin + Seperator;
        stMemberRecord += Member.ExpiryData;

        return stMemberRecord;

    }


    static  vector <clsBankMember> _LoadMembersDataFromFile()
    {

        vector <clsBankMember> vMembers;

        fstream MyFile;
        MyFile.open("Members.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankMember Member = _ConvertLineToMemberObject(Line);

                vMembers.push_back(Member);
            }

            MyFile.close();

        }

        return vMembers;

    }

    static void _SaveMembersDataToFile(vector <clsBankMember> vMembers)
    {

        fstream MyFile;
        MyFile.open("Members.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankMember Member : vMembers)
            {
                if (Member.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverMemberObjectToLine(Member);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankMember> _vMembers;
        _vMembers = _LoadMembersDataFromFile();

        for (clsBankMember& C : _vMembers)
        {
            if (C.MemberID == MemberID)
            {
                C = *this;
                break;
            }

        }

        _SaveMembersDataToFile(_vMembers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverMemberObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Members.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankMember _GetEmptyMemberObject()
    {
        return clsBankMember(enMode::EmptyMode, "", "", "", "", "", "");
    }

public:


    clsBankMember(enMode Mode, string FirstName, string LastName,
        string MemberID, string SubscriptionType,
        string DataOfJoin, string ExpiryData) :
        clsPerson(FirstName, LastName)

    {
        _Mode = Mode;
        _MemberID = MemberID;
        _SubscriptionType = SubscriptionType;
        _DataOfJoin = DataOfJoin;
        _ExpiryData = ExpiryData;
        
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    void SetMemberID(string MemberID)
    {
        _MemberID = MemberID;
    }

    string GeMemberID()
    {
        return _MemberID;
    }
    __declspec(property(get = GeMemberID, put = SetMemberID)) string MemberID;


    void SetSubscriptionType(string SubscriptionType)
    {
        _SubscriptionType = SubscriptionType;
    }

    string GetSubscriptionType()
    {
        return _SubscriptionType;
    }
    __declspec(property(get = GetSubscriptionType, put = SetSubscriptionType)) string SubscriptionType;

    void SetDataOfJoin(string DataOfJoin)
    {
        _DataOfJoin = DataOfJoin;
    }

    string GetDataOfJoin()
    {
        return _DataOfJoin;
    }
    __declspec(property(get = GetDataOfJoin, put = SetDataOfJoin)) string DataOfJoin;

    void SetExpiryData(string ExpiryData)
    {
        _ExpiryData = ExpiryData;
    }

    string GetExpiryData()
    {
        return _ExpiryData;
    }
    __declspec(property(get = GetExpiryData, put = SetExpiryData)) string ExpiryData;


    static clsBankMember Find(string MemberID)
    {


        fstream MyFile;
        MyFile.open("Members.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankMember Member = _ConvertLineToMemberObject(Line);
                if (Member.MemberID == MemberID)
                {
                    MyFile.close();
                    return Member;
                }

            }

            MyFile.close();

        }

        return _GetEmptyMemberObject();
    }

    static clsBankMember Find(string Name, string MemberID)
    {



        fstream MyFile;
        MyFile.open("Members.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankMember Member = _ConvertLineToMemberObject(Line);
                if (Member.FullName() == Name && Member.MemberID == MemberID)
                {
                    MyFile.close();
                    return Member;
                }

            }

            MyFile.close();

        }
        return _GetEmptyMemberObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankMember::IsMemberExist(_MemberID))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }



    }

    static bool IsMemberExist(string MemberID)
    {

        clsBankMember Member = clsBankMember::Find(MemberID);
        return (!Member.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankMember> _vMembers;

        _vMembers = _LoadMembersDataFromFile();

        for (clsBankMember& Member : _vMembers)
        {
            if (Member.MemberID == _MemberID)
            {
                Member._MarkedForDelete = true;
                break;
            }

        }

        _SaveMembersDataToFile(_vMembers);

        *this = _GetEmptyMemberObject();

        return true;

    }

    static clsBankMember GetAddNewMemberObject(string MemberID)
    {
        return clsBankMember(enMode::AddNewMode, "", "", MemberID, "", "", "");
    }

    static vector <clsBankMember> GetMembersList()
    {
        return _LoadMembersDataFromFile();
    }


    static vector <clsBankMember> GetExpiredMembersList()
    {
        vector <clsBankMember> vMembers1 = _LoadMembersDataFromFile();
        vector <clsBankMember> vMembers2;


        for (clsBankMember Member : vMembers1)
        {
            clsDate Data1(Member.ExpiryData), Data2;

            if (Data1.IsDate1BeforeDate2(Data2))
            {
                vMembers2.push_back(Member);
            }

        }

        return vMembers2;
    }


    static vector <clsBankMember> GetEndingSoondMembersList()
    {
        vector <clsBankMember> vMembers1 = _LoadMembersDataFromFile();
        vector <clsBankMember> vMembers2;


        for (clsBankMember Member : vMembers1)
        {
            clsDate Date1(Member.ExpiryData);
            clsDate Date2;

            if (!Date1.IsDate1BeforeDate2(Date2))
            {
                int Diff = clsDate::GetDifferenceInDays(Date2, Date1);

                if ((Diff >= 0 && Diff <= 7) || Member.SubscriptionType == "Weekly")
                {
                    vMembers2.push_back(Member);
                }
            }

        }

        return vMembers2;
    }


};
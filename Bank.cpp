#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;



void ShowMenu(void);
void MakeAccount(void);
void DepositMoney(void);
void WithDrawMoney(void);
void ShowAllAccInfo(void);
void SaveToFile(const char* filename);


enum
{
    MAKE=1,
    DEPOSIT,
    WITHDRAW,
    INQUIRE,
    SAVE,
    EXIT
};


typedef struct
{
    int accID;
    int balance;
    char cusName[NAME_LEN];
} Account;

Account accArr[100];
int accNum = 0;


int main(void) {
    int choice;

    while (true) {
        ShowMenu();
        cout << "Choose: ";
        cin >> choice;
        cout << endl;


        switch (choice)
        {
            case MAKE:
                MakeAccount();
                break;
            case DEPOSIT:
                DepositMoney();
                break;
            case WITHDRAW:
                WithDrawMoney();
                break;
            case INQUIRE:
                ShowAllAccInfo();
                break;
            case SAVE:
                SaveToFile("file.txt");
                cout << "Data saved to file successfully." << endl << endl;
                break;
            case EXIT:
                return 0;
            default:
                cout << "Illegal selection" << endl;
        }
    }

    return 0;
}


void ShowMenu(void) {
    cout << "---Menu---" << endl;
    cout << "1. Opening of an account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdrawal" << endl;
    cout << "4. Output all account information" << endl;
    cout << "5. Save data to file" << endl;
    cout << "6. Program termination" << endl;
}


void MakeAccount(void) {
    int id;
    char name[NAME_LEN];
    int balance;

    cout << "[Opening of an account]" << endl;
    cout << "Account ID: "; cin >> id;
    cout << "Name: "; cin >> name;
    cout << "Deposit amount: "; cin >> balance;
    cout << endl;


    accArr[accNum].accID = id;
    accArr[accNum].balance = balance;
    strcpy_s(accArr[accNum].cusName, name);
    accNum++;
}


void DepositMoney(void) {
    int money;
    int id;
    cout << "[Deposit]" << endl;
    cout << "Account ID: "; cin >> id;
    cout << "Deposit amount: "; cin >> money;


    for (int i = 0; i < accNum; i++) {
        if (accArr[i].accID == id) {
            accArr[i].balance += money;
            cout << "Deposit completed" << endl << endl;
            return;
        }
    }
    cout << "Invalid ID" << endl << endl;
}


void WithDrawMoney(void) {
    int money;
    int id;
    cout << "[Withdrawal]" << endl;
    cout << "Account ID: "; cin >> id;
    cout << "Withdrawal amount: "; cin >> money;


    for (int i = 0; i < accNum; i++) {
        if (accArr[i].accID == id) {
            if (accArr[i].balance < money) {
                cout << "A lack of balance" << endl << endl;
                return;
            }

            accArr[i].balance -= money;
            cout << "Withdrawal completed" << endl << endl;
            return;
        }
    }
    cout << "Invalid ID" << endl << endl;
}


void ShowAllAccInfo(void) {
    for (int i = 0; i < accNum; i++) {
        cout << "Account ID: " << accArr[i].accID << endl;
        cout << "Name: " << accArr[i].cusName << endl;
        cout << "Balance: " << accArr[i].balance << endl;
    }
}


void SaveToFile(const char* filename) {
    ofstream file(filename, ios::out);
    if (file.is_open()) {
        for (int i = 0; i < accNum; i++) {
            file << accArr[i].accID << " "
                 << accArr[i].cusName << " "
                 << accArr[i].balance << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file for saving data." << endl;
    }
}

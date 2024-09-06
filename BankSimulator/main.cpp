#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount{
	private:
		int accountNumber;
		string Owner;
		double balance;
	public:
		BankAccount(int, string, double);
		void deposit(double);
		void withdraw(double);
		double getBalance() const;
		int getAccountNumber() const;
		string getOwner() const;
};
BankAccount::BankAccount(int number, string owner, double balance){
	this->accountNumber = number;
	this->Owner = owner;
	this->balance = balance;
}

void BankAccount::deposit(double amount){
	this->balance += amount;
	cout << "Ai depus " << amount << "in cont"<<endl;
}

void BankAccount::withdraw(double amount){
	if(this->balance >= amount){
		this->balance -= amount;
        	cout << "Ai extras " << amount << "din cont"<<endl;
	}
	else{
		cout << "Fonduri insuficient"<<endl;
	}
}

double BankAccount::getBalance() const{
	return this->balance;
}

int BankAccount::getAccountNumber() const{
	return this->accountNumber;
}

string BankAccount::getOwner() const{
	return this->Owner;
}

class Bank{
	private:
		vector<BankAccount> accounts;
	public:
		Bank();
		void addAccount(const BankAccount&);
		void deleteAccount(int);
		BankAccount* findAccount(int);
		void listAccounts() const;
};

Bank::Bank(){}

void Bank::addAccount(const BankAccount &account){
	accounts.push_back(account);
}

void Bank::deleteAccount(int accountNumber){
	for(auto it = accounts.begin(); it != accounts.end(); it++){
		if(it -> getAccountNumber() == accountNumber){
			accounts.erase(it);
			break;
		}
	}
}

void Bank::listAccounts() const{
	for(auto &account : accounts){
		cout<<"Account Number: " << account.getAccountNumber() << ", Owner: " << account.getOwner() << ", Balance: " << account.getBalance()<<endl;
	}
}

BankAccount* Bank::findAccount(int accountNumber){
	for(auto& account : accounts){
		if(account.getAccountNumber() == accountNumber){
			return &account;
		}
	}
	return nullptr;
}

class BankUI{
	private:
		Bank bank;
	public:
		BankUI(const Bank &);
		void showMenu();
		void handleUserInput();
		void createAccount();
		void performDeposit();
		void performWithdraw();
		void checkBalance();
		void listAllAccounts();
		void deleteAccount();
};

BankUI::BankUI(const Bank &bank){
	this->bank = bank;
}

void BankUI::showMenu(){
	cout << "1. Create Account" << endl;
	cout << "2. Deposit" << endl;
	cout << "3. Withdraw" << endl;
	cout << "4. Check Balance" << endl;
	cout << "5. List All Accounts" << endl;
	cout << "6. Delete Account" << endl;
	cout << "0. Exit" << endl;
}

void BankUI::handleUserInput(){
	int choice;
	do{
		showMenu();
		cin >> choice;
		switch(choice){
			case 1:
				createAccount();
				break;
			case 2:
				performDeposit();
				break;
			case 3:
				performWithdraw();
				break;
			case 4:
				checkBalance();
				break;
			case 5:
				listAllAccounts();
				break;
			case 6:
				deleteAccount();
				break;
			case 0:
				cout << "Exit...." << endl;
				break;
			default:
				cout << "Invalid option" << endl;
				break;
		}
	}while(choice != 0);
}
void BankUI::createAccount(){
	int accountNumber;
	string ownerName;
	double balance;

	cout << "Introdu numarul contului: ";
	cin >> accountNumber;
	cin.ignore();

	cout << "Introdu proprietarul contului: ";
	getline(cin, ownerName);
	cout << "Introdu suma de inceput: ";
	cin >> balance;

	BankAccount account(accountNumber, ownerName, balance);
	bank.addAccount(account);
	cout << "Cont adaugat cu succes!" << endl;
}
void BankUI::performDeposit(){
	int accountNumber;
	double amount;

	cout << "Introdu numarul contului: ";
	cin >> accountNumber;

	cout << "Introdu suma pe care doresti sa o depui: ";
	cin >> amount;

	BankAccount* account = bank.findAccount(accountNumber);
	if(account){
		account->deposit(amount);
		cout << "Ai depus cu succes suma de: " << amount << "lei."<<endl;
	}
	else{
		cout<<"Contul nu a fost gasit."<<endl;
	}
}
void BankUI::performWithdraw(){
	int accountNumber;
	double amount;

	cout << "Introdu numarul contului: ";
	cin >> accountNumber;

	cout << "Introdu suma pe care doresti sa o scoti: ";
	cin >> amount;

	BankAccount* account = bank.findAccount(accountNumber);
	if(account){
		account->withdraw(amount);
	}
	else{
		cout << "Contul nu a fost gasit." << endl;
	}
}

void BankUI::checkBalance(){
	int accountNumber;
	cout << "Introdu numarul contului: ";
	cin >> accountNumber;

	BankAccount* account = bank.findAccount(accountNumber);

	if(account){
		cout << "Balance: " << account->getBalance() << endl;
	}
	else{
		cout << "Contul nu a fost gasit." << endl;
	}
}

void BankUI::listAllAccounts(){
	bank.listAccounts();
}

void BankUI::deleteAccount(){
	int accountNumber;
	cout << " Introdu numarul contului: ";
	cin >> accountNumber;

	bank.deleteAccount(accountNumber);
}

int main(){
	Bank bank;
	BankUI ui(bank);

	ui.handleUserInput();
	return 0;
}

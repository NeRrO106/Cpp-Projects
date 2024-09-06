#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Book{
	private:
		int id;
		string titlu;
		string autor;
		bool isAvailable;
		static int nextId;
	public:
		Book(string, string);
		int getId() const;
		string getTitlu() const;
		string getAutor() const;
		bool getIsAvailable() const;
		void borrowBook();
		void returnBook();
};
int Book::nextId = 0;
Book::Book(string titlu, string autor){
	this->titlu = titlu;
	this->autor = autor;
	isAvailable = true;
	id = nextId;
	nextId++;
}

int Book::getId() const{
	return id;
}

string Book::getTitlu() const{
	return titlu;
}

string Book::getAutor() const{
	return autor;
}

bool Book::getIsAvailable() const{
	return isAvailable;
}

void Book::borrowBook(){
	isAvailable = false;
}

void Book::returnBook(){
	isAvailable = true;
}

class Membru{
	private:
		int id;
		string nume;
		static int nextId;
	public:
		Membru(string);
		int getId() const;
		string getNume() const;
};

int Membru::nextId = 0;

Membru::Membru(string nume){
	this->nume = nume;
	id = nextId;
	nextId++;
}

int Membru::getId() const{
	return id;
}

string Membru::getNume() const{
	return nume;
}


class Library{
	private:
		vector<Book> books;
		vector<Membru> members;
		unordered_map<int, int> borrowRec;
	public:
		void addBook(const Book&);
		void addMember(const Membru&);
		void listBooks() const;
		void listMembers() const;
		void borrowBook(int, int);
		void returnBook(int);
		void listBorrowBooks() const;
};

void Library::addBook(const Book& book){
	books.push_back(book);
}

void Library::addMember(const Membru& member){
	members.push_back(member);
}

void Library::borrowBook(int bookId, int memberId){
	for(auto& book : books){
		if(book.getId() == bookId){
			if(book.getIsAvailable()){
				book.borrowBook();
				borrowRec[bookId] = memberId;
				cout << "Carte imprumutata cu succes." << endl;
			}
			else{
				cout << "Cartea este imprumutata deja." << endl;
			}
			return;
		}
	}
	cout << "Cartea nu a fost gasita." << endl;
}

void Library::returnBook(int bookId){
	for(auto& book : books){
		if(book.getId() == bookId){
			if(!book.getIsAvailable()){
				book.returnBook();
				borrowRec.erase(bookId);
				cout << "Cartea a fost returnata cu succes." << endl;
			}
			else{
				cout << "Cartea nu este imprumutata." << endl;
			}
			return;
		}
	}
	cout << "Cartea nu a fost gasita." << endl;
}

void Library::listBooks() const{
	if(books.size() == 0){
		cout << "Nu sunt incarti inregistrate" << endl;
		return;
	}
	for(const auto& book : books){
		cout << "ID: " << book.getId() << ", Titlu: " << book.getTitlu() << ", Autor: " << book.getAutor() << ", Available: " << (book.getIsAvailable() ? "Da" : "Nu") << endl;
	}
}

void Library::listMembers() const{
	if(members.size() == 0){
		cout << "Nu sunt membri inregistrati" << endl;
		return;
	}
	for(const auto& member : members){
		cout << "ID: " << member.getId() << ", Nume: " << member.getNume() << endl;
	}
}

void Library::listBorrowBooks() const{
	if(borrowRec.size() == 0){
		cout << "Nu sunt carti imprumutate." << endl;
		return;
	}
	for(const auto& record : borrowRec){
		int bookId = record.first;
		int memberId = record.second;
		cout << "Cartea cu id-ul: " << bookId << ",a fost imprumutata de membrul cu id-ul: " << memberId << "." << endl;
	}
}

class LibraryUI{
	private:
		Library library;
	public:
		void showMenu();
		void handleUserInput();
		void addBook();
		void addMember();
		void borrowBook();
		void returnBook();
		void listBooks();
		void listMembers();
		void listBorrowBooks();
};

void LibraryUI::showMenu(){
	cout << "1. Adauga carte" << endl;
	cout << "2. Adauga membru" << endl;
	cout << "3. Imprumuta o carte" << endl;
	cout << "4. Returneaza carte" << endl;
	cout << "5. Afiseaza toate cartile" << endl;
	cout << "6. Afiseaza toti membri" << endl;
	cout << "7. Afiseaza cartile imprumutate" << endl;
	cout << "0. Exit" << endl;
}

void LibraryUI::handleUserInput(){
	int choice;
	do{
		showMenu();
		cin >> choice;
		switch(choice){
			case 1:
				addBook();
				break;
			case 2:
				addMember();
				break;
			case 3:
				borrowBook();
				break;
			case 4:
				returnBook();
				break;
			case 5:
				listBooks();
				break;
			case 6:
				listMembers();
				break;
			case 7:
				listBorrowBooks();
				break;
			case 0:
				cout << "Exit...." << endl;
				break;
			default:
				cout << "Optiune invalida" << endl;
				break;
		}
	}while(choice != 0);
}
void LibraryUI::addBook(){
	string titlu, autor;
	cout << "Introdu titlul carti: ";
	cin.ignore();
	getline(cin, titlu);
	cout << "Introdu autorul carti: ";
	getline(cin, autor);
	Book book(titlu, autor);
	library.addBook(book);
	cout << "Carte inregistrata cu succes" << endl;
}
void LibraryUI::addMember(){
	string nume;
	cout << "Introdu numele membrului: ";
	cin.ignore();
	getline(cin, nume);
	Membru membru(nume);
	library.addMember(membru);
	cout << "Membru inregistrat cu succes" << endl;
}
void LibraryUI::borrowBook(){
	int bookId, memberId;
	cout << "Introdu id-ul carti: " << endl;
	cin >> bookId;
	cout << "Introdu id-ul membrului: " << endl;
	cin >> memberId;
	library.borrowBook(bookId, memberId);
}
void LibraryUI::returnBook(){
	int bookId;
	cout << "Introdu id-ul carti: " << endl;
	cin >> bookId;
	library.returnBook(bookId);
}
void LibraryUI::listBooks(){
	library.listBooks();
}
void LibraryUI::listMembers(){
	library.listMembers();
}
void LibraryUI::listBorrowBooks(){
	library.listBorrowBooks();
}

int main(){
	LibraryUI ui;
	ui.handleUserInput();
	return 0;
}

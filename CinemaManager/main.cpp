#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Film{
	private:
		string titlu;
		int durata;
		float rating;
	public:
		Film(string, int, float);
		string getTitlu() const;
		int getDurata() const;
		float getRating() const;
};
Film::Film(string titlu, int durata, float rating){
	this->titlu = titlu;
	this->durata = durata;
	this->rating = rating;
}

string Film::getTitlu() const{
	return titlu;
}

int Film::getDurata() const{
	return durata;
}

float Film::getRating() const{
	return rating;
}

class Sala{
	private:
		int numarSala;
		int numarLocuri;
		vector<vector<bool>> locuri;
	public:
		Sala(int, int);
		bool verificaDisponibilitate(int, int) const;
		void rezervaLoc(int, int);
		void anuleazaRezervare(int, int);
		void afiseazaLocuri() const;
		int getNumarSala() const;
};

Sala::Sala(int numarSala, int numarLocuri){
	this->numarSala = numarSala;
	this->numarLocuri = numarLocuri;
	int numarRanduri = numarLocuri / 10;
	locuri.resize(numarRanduri, vector<bool>(10, false));
}

bool Sala::verificaDisponibilitate(int rand, int loc) const{
	if(rand >= locuri.size() || loc >= locuri[0].size()){
		cout << "Rand sau loc invalid." << endl;
		return false;
	}
	return !locuri[rand][loc];
}
void Sala::rezervaLoc(int rand, int loc){
	if(verificaDisponibilitate(rand, loc)){
		locuri[rand][loc] = true;
		cout << "Locul " << loc << " din randul " << rand << " a fost rezervat." << endl;
	}
	else{
		cout << "Locul " << loc << " din randul " << rand << " este deja ocupat." << endl;
	}
}
void Sala::anuleazaRezervare(int rand, int loc){
	if(rand >=locuri.size() || loc >= locuri[0].size()){
		cout << "Rand sau loc invalid!" << endl;
	}
	else if(!locuri[rand][loc]){
		cout << "Locul " << loc << " de pe randul " << rand << " nu este rezervat." << endl;
	}
	else{
		locuri[rand][loc] = false;
		cout << "Rezervarea pentru locul " << loc << " de pe randul " << rand << " a fost anulata cu succes" << endl;
	}
}
void Sala::afiseazaLocuri() const{
	cout << "Sala " << numarSala << " - Locuri: " << endl;
	for(int i = 0; i < locuri.size(); i++){
		for(int j = 0; j < locuri[0].size(); j++){
			cout << "Rand " << i << " Loc " << j <<": " << (locuri[i][j] ? "Ocupat" : "Liber") << endl;
		}
	}
}
int Sala::getNumarSala() const{
	return numarSala;
}

class ProgramFilm{
	private:
		Film film;
		Sala sala;
		string oraInceput;
	public:
		ProgramFilm(Film, Sala, string);
		Film getFilm() const;
		Sala getSala() const;
		string getOraInceput() const;
};

ProgramFilm::ProgramFilm(Film film, Sala sala, string oraInceput) : film(film), sala(sala), oraInceput(oraInceput){}
Film ProgramFilm::getFilm() const { return film; }
Sala ProgramFilm::getSala() const { return sala; }
string ProgramFilm::getOraInceput() const { return oraInceput; }

class Rezervare{
	private:
		int idRezervare;
		string numeUtilizator;
		ProgramFilm program;
		int rand, loc;
	public:
		Rezervare(int, string, ProgramFilm, int, int);
		int getIdRezervare() const;
		string getNumeUtilizator() const;
		ProgramFilm getProgramFilm() const;
		int getRand() const;
		int getLoc() const;
};

Rezervare::Rezervare(int id, string numeUtilizator, ProgramFilm program, int rand, int loc)
	: idRezervare(id), numeUtilizator(numeUtilizator), program(program), rand(rand), loc(loc){}

int Rezervare::getIdRezervare() const{ return idRezervare; }
string Rezervare::getNumeUtilizator() const{ return numeUtilizator; }
ProgramFilm Rezervare::getProgramFilm() const{ return program; }
int Rezervare::getRand() const{ return rand; }
int Rezervare::getLoc() const{ return loc;}

class Utilizator{
	private:
		string nume;
		vector<Rezervare> rezervari;
	public:
		Utilizator(string);
		string getNume() const;
		void adaugaRezervare(const Rezervare&);
		void anuleazaRezervare(int);
		void afiseazaRezervari() const;
		bool esteRezervarea(int) const;
};

Utilizator::Utilizator(string nume) : nume(nume) {}
string Utilizator::getNume() const { return nume; }
void Utilizator::adaugaRezervare(const Rezervare &rezervare){ rezervari.push_back(rezervare); }
void Utilizator::anuleazaRezervare(int id){
	for(auto it = rezervari.begin(); it != rezervari.end(); it++){
		if(it->getIdRezervare() == id){
			rezervari.erase(it);
			break;
		}
	}
}
void Utilizator::afiseazaRezervari() const{
	for(const auto &rezervare : rezervari){
		cout << " RezervareID: " << rezervare.getIdRezervare() << ", Film: " << rezervare.getProgramFilm().getFilm().getTitlu() <<", Sala: " << rezervare.getProgramFilm().getSala().getNumarSala() << ", Ora: " << rezervare.getProgramFilm().getOraInceput() <<", Rand: " << rezervare.getRand() << ", Loc: " << rezervare.getLoc() << endl;
	}
}

bool Utilizator::esteRezervarea(int id) const{
	for(const auto &rez : rezervari){
		if(rez.getIdRezervare() == id) return true;
	}
	return false;
}
class Cinema{
	private:
		vector<Film> filme;
		vector<Sala> sali;
		vector<ProgramFilm> programe;
		vector<Rezervare> rezervari;
		vector<Utilizator> utilizatori;
		int nextIdRezervari;
	public:
		Cinema();
		void adaugaFilm(const Film&);
		void adaugaSala(const Sala&);
		void adaugaUtilizator(const Utilizator&);
		void adaugaProgramFilm(const ProgramFilm&);
		void afiseazaFilme() const;
		void afiseazaSali() const;
		void afiseazaPrograme() const;
		void rezervaBilet(const string&, const ProgramFilm&, int rand, int loc);
		void anuleazaRezervare(int);
		void afiseazaRezervarileUtilizatorului(const string&) const;
};

Cinema::Cinema():nextIdRezervari(1){}
void Cinema::adaugaFilm(const Film& film) { filme.push_back(film); }
void Cinema::adaugaSala(const Sala& sala) { sali.push_back(sala); }
void Cinema::adaugaUtilizator(const Utilizator& utilizator) { utilizatori.push_back(utilizator); }
void Cinema::adaugaProgramFilm(const ProgramFilm& program) { programe.push_back(program); }

void Cinema::afiseazaFilme() const{
	for(const auto &film : filme){
		cout << "Film: " << film.getTitlu() << ", Durata: " << film.getDurata() << " minute" << ", rating: " << film.getRating() <<endl;
	}
}

void Cinema::afiseazaSali() const{
	for(const auto &sala: sali){
		sala.afiseazaLocuri();
	}
}
void Cinema::afiseazaPrograme() const{
	for(const auto& program : programe){
		cout << "Film: " << program.getFilm().getTitlu() << ", Sala: " << program.getSala().getNumarSala() << ", Ora: " << program.getOraInceput() << endl;
	}
}

void Cinema::rezervaBilet(const string &numeUtilizator, const ProgramFilm &program, int rand, int loc){
	Utilizator* utilizator = nullptr;
	for(auto& u : utilizatori){
		if(u.getNume() == numeUtilizator){
			utilizator = &u;
			break;
		}
	}

	if(utilizator == nullptr){
		cout << "Utilizatorul nu a fost gasit!" << endl;
		return;
	}
	for(auto &sala : sali){
		if(sala.getNumarSala() == program.getSala().getNumarSala()){
			if(sala.verificaDisponibilitate(rand, loc)){
				sala.rezervaLoc(rand, loc);
				Rezervare rezervare(nextIdRezervari++, numeUtilizator, program, rand, loc);
				rezervari.push_back(rezervare);
				utilizator->adaugaRezervare(rezervare);
				cout << "Rezervarea a fost realizata cu succes pentru utilizatorul: " << numeUtilizator << endl;
			}
			else{
				cout << "Locul este deja ocupat!" << endl;
			}
		}
		return;
	}
	cout << "Sala nu a fost gasita!" << endl;
}
void Cinema::anuleazaRezervare(int id){
	for(auto it = rezervari.begin(); it != rezervari.end(); it++){
		if(it->getIdRezervare() == id){
			for(auto &sala : sali){
				if(sala.getNumarSala() == it->getProgramFilm().getSala().getNumarSala()){
					sala.anuleazaRezervare(it->getRand(), it->getLoc());
					break;
				}
			}
			for(auto& u : utilizatori){
				if(u.esteRezervarea(id)){
					u.anuleazaRezervare(id);
				}
			}
			rezervari.erase(it);
			cout << "Rezervare anulata cu succes!" << endl;
			return;
		}
	}
	cout << "Rezervarea nu a fost gasita!" << endl;
}
void Cinema::afiseazaRezervarileUtilizatorului(const string& numeUtilizator) const{
	for(auto& u : utilizatori){
		if(u.getNume() == numeUtilizator){
			u.afiseazaRezervari();
			return;
		}
	}
	cout << "Utilizatorul nu a fost gasit." << endl;
}

void meniu(){
	int choice;
	do{
		cout << "Meniul Cinemaului: " << endl;
		cout << "1. Adauga Film" << endl;
		cout << "2. Adauga Sala" << endl;
		cout << "3. Adauga Program" << endl;
		cout << "4. Adauga Utilizator" << endl;
		cout << "5. Rezerva Bilete" << endl;
		cout << "6. Anuleaza Bilete" << endl;
		cout << "7. Afiseaza Rezervarile unui Utilizator" << endl;
		cout << "8. Afiseaza toate filmele" << endl;
		cout << "9. Afiseaza toate salile" << endl;
		cout << "10. Afiseaza toate programele" << endl;
		cout << "0. Exit.."<< endl;
		cout << "Introdu optiunea ta" << endl;
		cin >> choice;
	}while(choice != 0);
}
int main(){
	Cinema cinema;

	Film film1("Inception",148, 4.5);
	Film film2("The Dark Knight", 152, 7.8);

	cinema.adaugaFilm(film1);
	cinema.adaugaFilm(film2);

	Sala sala1(1, 50);
	Sala sala2(2, 100);

	cinema.adaugaSala(sala1);
	cinema.adaugaSala(sala2);

	ProgramFilm program1(film1, sala1, "10:00");
	ProgramFilm program2(film2, sala2, "13:00");

	cinema.adaugaProgramFilm(program1);
	cinema.adaugaProgramFilm(program2);

	Utilizator utilizator1("Andrei");
	Utilizator utilizator2("Dan");

	cinema.adaugaUtilizator(utilizator1);
	cinema.adaugaUtilizator(utilizator2);

	cinema.rezervaBilet("Andrei", program1, 2, 5);
	cinema.rezervaBilet("Dan", program2, 3, 10);

	cinema.afiseazaRezervarileUtilizatorului("Andrei");
	cinema.afiseazaRezervarileUtilizatorului("Alin");
	cinema.afiseazaFilme();
	cinema.afiseazaSali();
	cinema.afiseazaPrograme();
	return 0;
}

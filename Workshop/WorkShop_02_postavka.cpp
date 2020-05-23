#include<iostream>

using namespace std;

class Vrijeme {
	int _sati;
	int _minute;
	int _sekunde;
public:

	//Konstruktor bez parametara
	//Konstruktor sa 3 parametra (sati, minute i sekunde)
	//Konstruktor sa 2 parametra (sati i minute)

	//Funkciju Info sa neobaveznim parametrom tipa bool koji odre�uje da li �e vrijeme biti ispisano u punom formatu
	//(hh:mm:ss) ili u skra�enom formatu (hh:mm). Default-no funkcija vr�i ispis u punom formatu.


	//Funkciju Add koja kao rezultat vra�a novi objekat tipa vrijeme koji predstavlja 
	//sumu vremena poslije�enog kao parametar i instance this.


	//Funkciju Add koja kao rezultat vra�a novi objekat tipa vrijeme koji predstavlja 
	//sumu parametra izra�enog u minutama i vremena instance this.


	//Funkciju CompareTo koja vra�a vrijednost tipa int u zavisnosti od toga da li je vrijeme instance this prije, jednako ili poslije
	//vremena proslije�enog kao parametar.
	//Mogu�e povratne vrijednosti:
	//-1 - vrijeme instance this nastupa prije vremena v2
	// 0 - vrijeme instance this je jednako vremenu v2
	// 1 - vrijeme instance this nastupa nakon vremena v2

};


/*
Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene �lanaka me�u korisnicima.
Izdvojene su sljede�e funkcionalnosti:
- Administrator sistema je zadu�en za upravljanje korisni�kim nalozima (Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka).
- Svaki �lanak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda) mo�e sadr�avati vi�e tagova, ali pripada samo jednoj oblasti.
- �lanke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije tako�er mogu ostaviti komentar (Tekst, Datum, Popularnost) na odre�eni �lanak.
*/

/*
Na osnovu datih klasa implementirati opisane funkcionalnosti sistema. Po potrebi dopuniti klase novim atributima i/ili funkcijama.
*/

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	//Potrebne konstruktor i destruktor funkcije

	//Funkciju Info
};

enum TipKorisnika { Administrator, Guest };
class Korisnik
{
	char _ime[30];
	char _korisnickoIme[20];
	char* _lozinka;
	TipKorisnika _tipKorisnika; //Administrator, Guest
public:
	//Potrebne konstruktor i destruktor funkcije

	//Funkciju za promjenu korisni�ke lozinke

	//Funkciju Info

};

class Komentar
{
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:
	//Potrebne konstruktor i destruktor funkcije

	//Funkciju za izmjenu popularnosti komentara

	//Funkciju Info

};

class Clanak
{
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];
	char _oblast[100];
	Korisnik* _autor;
	Komentar* _komentari;
	int _brojKomentara;
public:

	//Funkciju za dodavanje tagova za �lanak

	/*Funkciju za promjenu sadr�aja i vremena promjene �lanka. Kao verifikaciju dozvole potrebno je proslijediti korisni�ko ime autora �lanka.
	Samo kreator �lanka ima permisije da mijenja njegov sadr�aj.
	*/

	//Funkciju za dodavanje komentara

	//Funkciju Info

};

int main()
{
	//Kreirati testni program koji demonstrira implementirane funckionalnosti


	return 0;
}
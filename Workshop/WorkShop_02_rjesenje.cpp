#include<iostream>

using namespace std;
const char* crt = "----------------------------------------------------";

class Vrijeme {
	int _sati;
	int _minute;
	int _sekunde;
public:

	Vrijeme(): _sati(0),_minute(0),_sekunde(0) {}
	
	Vrijeme(int sati, int minute, int sekunde): 
		_sati(sati), _minute(minute), _sekunde(sekunde)
		{	}
	
	Vrijeme(int sati, int minute):
		_sati(sati), _minute(minute)
		{	}
	
	void Info(bool format=true)
	{
		if (_sekunde > 60)
		{
			_sekunde -= 60; _minute++;
		}
		if (_minute > 60)
		{
			_minute -= 60; _sati++;
		}
		if (_sati > 24) 
		{
			_sati -= 24;
		}

		if (format) 
		{
			cout << _sati << "h " << _minute << "m " << _sekunde <<"s "<< endl;
		}
		else
		{
			cout << _sati << "h " << _minute <<"m "<< endl;
		}
	}

	Vrijeme Add(const Vrijeme& novo)
	{
		this->_sekunde = novo._sekunde + this->_sekunde;
		this->_minute = novo._minute + this->_minute;
		this->_sati = novo._sati + this->_sati;

		return *this;
	}

	Vrijeme Add(int minute)
	{
		this->_sekunde = this->_sekunde;
		this->_minute = minute + this->_minute;
		this->_sati = this->_sati;

		return *this;
	}

	int CompareTo(const Vrijeme& v2)
	{
		if (this->_sati < v2._sati) return -1;
		if (this->_sati > v2._sati) return 1;
		if (this->_sati == v2._sati) {
			if (this->_minute < v2._minute) return -1;
			if (this->_minute > v2._minute) return 1;
			if (this->_minute == v2._minute) {
				if (this->_sekunde < v2._sekunde) return -1;
				if (this->_sekunde > v2._sekunde) return 1;
				if (this->_sekunde == v2._sekunde) return 0;
			}
		}
	}
	friend ostream& operator<<(ostream&, const Vrijeme&);
};

ostream& operator<<(ostream& cout, const Vrijeme& vrijeme)
{
	cout << vrijeme._sati << "h " << vrijeme._minute << "m " << vrijeme._sekunde << "s " << endl;
	
	return cout;
}

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	Datum(int dan=1,int mjesec=1, int godina=2000): _dan(dan),_mjesec(mjesec),_godina(godina)
		{}

	friend ostream& operator<<(ostream&, const Datum&);
};

ostream& operator<<(ostream& cout, const Datum& datum)
{
	cout << datum._dan << ".dan " << datum._mjesec << ".mjesec " << datum._godina << ".godina" << endl;

	return cout;
}

enum TipKorisnika { Administrator, Guest };
const char* TipKorisnikaChar[2] = { "Administrator","Guest" };

class Korisnik
{
	char _ime[30];
	char _korisnickoIme[20];
	char* _lozinka;
	TipKorisnika _tipKorisnika; //Administrator, Guest
public:
	Korisnik() : 
		_tipKorisnika(Guest)
	{
		strcpy_s(_ime, 30, "Nema");
		strcpy_s(_korisnickoIme, 20, "Nema");
		_lozinka = new char[10];
		strcpy_s(_lozinka, 10, "Nema");
	}

	Korisnik(const char* ime, const char* user, const char* lozinka, const char* tip)
	{
		strcpy_s(_ime, ime);
		strcpy_s(_korisnickoIme, user);
		_lozinka = new char[strlen(lozinka) + 1];
		strcpy_s(_lozinka, strlen(lozinka) + 1, lozinka);
		if (tip == TipKorisnikaChar[0])
		{
			_tipKorisnika = Administrator;
		}
		else
		{
			_tipKorisnika = Guest;
		}
	}
	
	Korisnik(const Korisnik& original)
	{
		strcpy_s(_ime, original._ime);
		strcpy_s(_korisnickoIme, original._korisnickoIme);
		_lozinka = new char[strlen(original._lozinka) + 1];
		strcpy_s(_lozinka, strlen(original._lozinka) + 1, original._lozinka);
		_tipKorisnika = original._tipKorisnika;
	}

	char* getIme() { return _ime; }
	char* getLozinku() { return _lozinka; }

	~Korisnik()
	{
		delete[] _lozinka; _lozinka = nullptr;
	}

	void PromjenaLozinke(const char* nova)
	{
		int brojPokusaja = 3;
		char novaLozinka[15];

		while (brojPokusaja)
		{
			brojPokusaja--;
			cout << "Unesite Vasu staru lozinku:" << endl;
			cout << "Broj pokusaja: " << brojPokusaja+1 << endl;
			cin.getline(novaLozinka, 15);
			if (strcmp(_lozinka, novaLozinka) == 0)
			{
				delete[] _lozinka;
				_lozinka = new char[strlen(nova) + 1];
				strcpy_s(_lozinka, strlen(nova) + 1, nova);
				cout << crt << endl;
				cout << "Lozinka je uspjesno promjenjena!" << endl;
				return;
			}
		}
		cout << crt << endl;
		cout << "Niste uspjeli pogoditi lozinku" << endl;
		cout << crt << endl;
	}

	friend ostream& operator<<(ostream&, const Korisnik&);

};

ostream& operator<<(ostream& cout, const Korisnik& korisnik)
{
	cout << "Ime i prezime: " << korisnik._ime << endl;
	cout << "Korisnicko ime: " << korisnik._korisnickoIme << endl;
	cout << "Lozinka: " << korisnik._lozinka << endl;
	cout << "Tip korisnika: " << TipKorisnikaChar[korisnik._tipKorisnika]<< endl;

	return cout;
}

class Komentar
{
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:

	Komentar(): _popularnost(0)
	{
		_tekst = new char[10];
		strcpy_s(_tekst, 10, "Nema");
		_autor = new Korisnik;
	}

	Komentar(const char* tekst,Datum datum,Vrijeme satnica,Korisnik autor, int popularnost):
		_datum(datum),_satnica(satnica),_popularnost(popularnost),_autor(new Korisnik (autor))
	{
		_tekst = new char[strlen(tekst) + 1];
		strcpy_s(_tekst, strlen(tekst) + 1, tekst);
	}
	Komentar(const Komentar& original):
		_datum(original._datum), _satnica(original._satnica), _popularnost(original._popularnost), _autor(original._autor)
	{
		_tekst = new char[strlen(original._tekst) + 1];
		strcpy_s(_tekst, strlen(original._tekst) + 1, original._tekst);
	}
	~Komentar() 
	{
		delete[] _tekst; _tekst = nullptr;
	}

	void IzmijeniPopularnost(int vrijednost)
	{
		_popularnost = vrijednost;
	}

	friend ostream& operator<<(ostream&, const Komentar&);
};

ostream& operator<<(ostream& cout, const Komentar& komentar)
{
	cout << "Komentar: " << komentar._tekst << endl;
	cout << "Datum: " << komentar._datum;
	cout << "Vrijeme: " << komentar._satnica;
	cout << "Popularnost: " << komentar._popularnost << endl;
	cout << "Autor:\n" << *komentar._autor << endl;

	return cout;
}

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

	Clanak() : 
		_naslov("Nema naslova"),_brojPregleda(0),_oblast("Nema oblasti"),_brojKomentara(0)
	{
		_sadrzaj = new char[11];
		strcpy_s(_sadrzaj, 11, "Nema");
		for (size_t i = 0; i < 10; i++)
		{
			_tagovi[i] = new char[11];
			strcpy_s(_tagovi[i], 11, "Nema");
		}
		_autor = new Korisnik;
		_komentari = new Komentar;
	}

	Clanak(const char* naslov, const char* sadrzaj, Datum datum, Vrijeme satnica,const char* oblast,Korisnik autor,Komentar komentari) :
		_datum(datum),_satnica(satnica),_brojPregleda(0),_autor(new Korisnik (autor)),_komentari(new Komentar (komentari)),_brojKomentara(0)
	{
		strcpy_s(_naslov, 150, naslov);
		_sadrzaj = new char[strlen(sadrzaj) + 1];
		strcpy_s(_sadrzaj, strlen(sadrzaj) + 1, sadrzaj);
		for (size_t i = 0; i < 10; i++)
		{
			_tagovi[i] = new char[11];
			strcpy_s(_tagovi[i], 11, "Nema");
		}
		strcpy_s(_oblast, 100, oblast);
	}

	~Clanak()
	{
		delete[] _sadrzaj; _sadrzaj = nullptr;
		for (size_t i = 0; i < 10; i++)
		{
			if (_tagovi[i] != nullptr)
			{
				delete _tagovi[i]; _tagovi[i] = nullptr;
			}
			else
			{
				_tagovi[i] = nullptr;
			}
		}
	}

	void DodajTag(const char* tag)
	{
		for (size_t i = 0; i < 10; i++)
		{
			_tagovi[i] = new char[strlen(tag) + 1];
			strcpy_s(_tagovi[i], strlen(tag) + 1, tag);
			if (strcmp(_tagovi[i],"Nema")==0)
			{
				return;
			}
		}
	}
	bool PromijeniSadrzaj(const char* sadrzaj, Vrijeme novo, Korisnik autorizacija) {
		if (strcmp(this->_autor->getIme(), autorizacija.getIme()) != 0) { cout << "Greska pri autorizaciji!\n"; return false; }
		if (strcmp(this->_autor->getLozinku(), autorizacija.getLozinku()) != 0) { cout << "Greska pri autorizaciji!\n"; return false; }
		delete[]_sadrzaj; _sadrzaj = new char[strlen(sadrzaj) + 1];
		strcpy_s(_sadrzaj, strlen(sadrzaj) + 1, sadrzaj);
		_satnica = novo;
		return true;
	}

	void DodajKomentar(const Komentar& comment) {
		Komentar* temp = new Komentar[_brojKomentara + 1];
		for (size_t i = 0; i < _brojKomentara; i++)
		{
			temp[i] = _komentari[i];
		}
		temp[_brojKomentara] = comment;
		_komentari = temp;
		_brojKomentara++;
		cout << "Komentar uspjesno dodan!\n";
	}

	void Info()
	{
		cout << "Naslov: " << _naslov << endl;
		cout << "Sadrzaj: " << _sadrzaj << endl;
		cout << "Datum: " << _datum << endl;
		cout << "Vrijeme: " << _satnica << endl;
		cout << "Broj preleda: " << _brojPregleda << endl;
		cout << "Tagovi: " <<endl; 
		for (size_t i = 0; i < 10; i++)
		{
			cout << _tagovi[i] << endl;
		}
		cout << "Oblast: " << _oblast << endl;
		cout << "Autor: " << *_autor << endl;
		cout << "Komentari: " << *_komentari << endl;
		cout << "Broj komentara: " << _brojKomentara << endl;
	}

};

void main()
{
	Vrijeme v1;
	Vrijeme v2(10, 15, 35);
	Vrijeme v3(8, 54);
	Vrijeme prekoracenje(25, 65, 65);
	Vrijeme v4(11, 15, 20);

	cout << crt << endl;
	cout << "Kada se desi prekoracenje\n25h 65m 65s\n" << endl;
	prekoracenje.Info();
	cout<<crt << endl;
	cout << "Ispis u punom formatu\n" << endl;
	v4.Info();
	cout << crt << endl;
	cout << "Ispis u skracenom formatu\n" << endl;
	v4.Info(false);
	cout << crt << endl;
	cout << "Ispis vremena prije sabiranja\n" << endl;
	v4.Info();
	v2.Info();
	v4.Add(v2);
	cout << "\nIspis vremena nakon sabiranja\n" << endl;
	v4.Info();
	cout << crt << endl;
	cout << "Ispis vremena prije dodavanja 5 minuta\n" << endl;
	v4.Info();
	v4.Add(5);
	cout << "\nIspis vremena nakon dodavanja 5 minuta\n" << endl;
	v4.Info();
	cout << crt << endl;
	cout << "-1 - vrijeme instance this nastupa prije vremena v2" << endl;
	cout << "0 - vrijeme instance this je jednako vremenu v2" << endl;
	cout << "1 - vrijeme instance this nastupa nakon vremena v2\n" << endl;
	cout << "v2 ";
	v2.Info();
	cout << "\nv4 ";
	v4.Info();
	cout << "\nVrijeme v2 nastupa prije vremena v4\n" << endl;
	cout << v2.CompareTo(v4) << endl;
	system("pause");
	system("CLS");
	cout << crt << endl;
	cout << crt << endl;
	Datum d1(7, 1, 2020);
	cout << d1;
	system("pause");
	system("CLS");
	cout << crt << endl;
	Korisnik Faruk("Faruk", "Fuke", "1234","Guest");
	cout << "\nIspis korisnika prije promjene lozinke\n" << endl;
	cout << Faruk;
	Faruk.PromjenaLozinke("987654321");
	cout << "\nIspis korisnika nakon promjene lozinke\n" << endl;
	cout << Faruk;
	cout << crt << endl;
	cout << crt << endl;
	system("pause");
	system("CLS");
	cout << "Komentar prije izmjene popularnosti:\n" << endl;
	Komentar k1("Ovo je prvi komentar", d1, v2, Faruk, 10);
	Komentar k2("Ovo je drugi komentar", d1, v2, Faruk, 10);
	cout << k1 << endl;
	cout << crt << endl;
	cout << "Komentar nakon izmijenjene popularnosti:\n" << endl;
	k1.IzmijeniPopularnost(5);
	cout << k1 << endl;
	cout << crt << endl;
	cout << crt << endl;
	system("pause");
	system("CLS");
	Clanak c1("Naslov clanka", "Sadrzaj clanka", d1, v2, "Oblast clanka", Faruk, k1);
	c1.Info();
	c1.DodajTag("Novi tag");
	c1.DodajTag("Novi tag2");
	c1.DodajKomentar(k2);
	c1.PromijeniSadrzaj("Najnoviji sadrzaj", v4, Faruk);
	c1.Info();
	system("pause");
}
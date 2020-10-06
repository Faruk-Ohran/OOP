#include <iostream>
using namespace std;


/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR �E BITI OZNACENO KAO "RE"
3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJE�ILO GUBLJENJE URA�ENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U, OSIM U SLU�AJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMO�NE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URA�ENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

const char* crt = "\n----------------------------------------------------\n";
class Datum {
	int* _dan, * _mjesec, * _godina;
public:
	Datum(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	Datum(const Datum& d) {
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
	}
	Datum& operator=(const Datum& d) {
		if (this != &d)
		{
			*_dan = *d._dan;
			*_mjesec = *d._mjesec;
			*_godina = *d._godina;
		}
		return *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Datum obj) {
		COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina;
		return COUT;
	}
};

template<class T, int velicina>
class FITArray {
	T _niz[velicina];
	int _trenutno;
	bool _dozvoliDupliciranje;
public:
	//OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE
	FITArray(bool dozvoliDupliciranje = true) { _dozvoliDupliciranje = dozvoliDupliciranje; _trenutno = 0; }
	int GetTrenutno() const { return _trenutno; }
	T* GetNiz() { return _niz; }

	bool operator+=(const T&);

	friend ostream& operator<<<>(ostream& , const FITArray&);
	void operator-=(const T&);
	FITArray operator()(int,int);
};

template<class T, int velicina>
FITArray<T, velicina> FITArray<T, velicina>::operator()(int OD, int DO) {
	FITArray<T,velicina> rezKol(_dozvoliDupliciranje);
	for (size_t i = OD; i <= (OD >= _trenutno? _trenutno-1:DO); i++)
	{
		rezKol += _niz[i];
	}
	return rezKol;
}

template<class T, int velicina>
bool FITArray<T,velicina>::operator+=(const T& el) {
	if (velicina == _trenutno) return false;
	if (!_dozvoliDupliciranje) {
		for (size_t i = 0; i < _trenutno; i++) {
			if (_niz[i] == el) return false;
		}
	}

	_niz[_trenutno++] = el;
	return true;
}

template<class T, int velicina>
ostream& operator<<(ostream& cout, const FITArray<T,velicina>& kol) {
	for (size_t i = 0; i < kol._trenutno; i++) {
		cout << kol._niz[i] << endl;
	}
	return cout;
}

template<class T, int velicina>
void FITArray<T, velicina>::operator-=(const T& el) {
	for (size_t i = 0; i < _trenutno; i++) {
		if (_niz[i] == el) {
			for (size_t j = i; j < _trenutno-1; j++){
				_niz[j] = _niz[j + 1];
			}
			_trenutno--;
			
			if (!_dozvoliDupliciranje)
				return;
			else
				i--;
		}
	}
}
 
class PolozeniPredmet {
	char* _naziv;
	int _ocjena;
	Datum _datumPolaganja;
public:
	PolozeniPredmet(): _datumPolaganja(1,1,2000) {
		_naziv = nullptr;
		_ocjena = 5;
	}

	PolozeniPredmet(const Datum& datum, const char* naziv, int ocjena): _datumPolaganja(datum) {
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
		_ocjena = ocjena;
	}

	PolozeniPredmet& operator=(const PolozeniPredmet& p) {
		if (this != &p) {
			delete[]_naziv;

			if (p._naziv != nullptr) {
				int vel = strlen(p._naziv) + 1;
				_naziv = new char[vel];
				strcpy_s(_naziv, vel, p._naziv);
			}
			else
				_naziv = nullptr;
			_ocjena = p._ocjena;

			_datumPolaganja = p._datumPolaganja;
		}
		return *this;
	}

	~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }
	friend ostream& operator<<(ostream& COUT,const PolozeniPredmet& obj) {
		COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
		return COUT;
	}

	int GetOcjena() { return _ocjena; }

	friend bool operator==(const PolozeniPredmet&, const PolozeniPredmet&);
};

bool operator==(const PolozeniPredmet& p1, const PolozeniPredmet& p2) {
	return strcmp(p1._naziv, p2._naziv) == 0 && p1._ocjena == p2._ocjena;
}

class Student {
	static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
	const int _indeks;
	char* _imePrezime;
	FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
public:
	Student(const char* imePrezime):_indeks(++_indeksCounter),_polozeniPredmeti(false) {
		int vel = strlen(imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imePrezime);
	}
	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}

	Student& operator=(const Student& s) {
		if (this != &s) {
			int vel = strlen(s._imePrezime) + 1;
			_imePrezime = new char[vel];
			strcpy_s(_imePrezime, vel, s._imePrezime);

			_polozeniPredmeti = s._polozeniPredmeti;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& COUT, Student& obj) {
		COUT << obj._indeks << " " << obj._imePrezime << endl << obj._polozeniPredmeti;
		return COUT;
	}

	bool DodajPredmet(const PolozeniPredmet& p) {
		return _polozeniPredmeti += p;
	}

	float GetProsjek() {
		float prosjek = 0;

		if (_polozeniPredmeti.GetTrenutno() == 0) return 0;

		for (size_t i = 0; i < _polozeniPredmeti.GetTrenutno(); i++)
		{
			prosjek += _polozeniPredmeti.GetNiz()[i].GetOcjena();
		}
		prosjek /= _polozeniPredmeti.GetTrenutno();
		return prosjek;
	}
};

int Student::_indeksCounter = 160000;

void main() {
	const int max = 20;

	Datum jucer(20, 11, 2017), danas(21, 11, 2017), sutra(22, 11, 2017);
	cout << jucer << danas << sutra << endl;
	jucer = danas;
	cout << jucer << danas << sutra << endl;

	//parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
	FITArray<int, max> nizIntegera(false);

	for (size_t i = 0; i < max - 1; i++)
		nizIntegera += i;//dodaje novog clana niza

	if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
		cout << "Element nije dodan u niz" << endl;

	cout << crt << nizIntegera << crt; //ispisuje sve clanove niza

	nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
	nizIntegera -= 17;

	FITArray<int, max> noviNizIntegera(nizIntegera);
	 
	cout << crt << noviNizIntegera << crt;

	/*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. u slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije OD pa do posljednje dostupnog elementa */
	cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;

	Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");

	PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7);

	adel.DodajPredmet(prII);
	adel.DodajPredmet(prIII);
	cout << adel << endl;
	////vraca prosjecnu ocjenu studenta
	cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;

	jasmin = adel;
	cout << jasmin << endl;
	cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;
	system("pause");
}
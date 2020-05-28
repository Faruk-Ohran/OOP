#include <iostream>
using namespace std;

const char* crt = "\n-------------------------------\n";

class KupljeniArtikal {
	char* _naziv;
	float _cijena;
	int _kolicina;
public:
	KupljeniArtikal(): _naziv(nullptr), _cijena(0), _kolicina(0)
	{}

	KupljeniArtikal(const char* naziv, float cijena): _cijena(cijena), _kolicina(1) 
	{
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
	}

	~KupljeniArtikal() 
	{
		delete[] _naziv;
		_naziv = nullptr;
	}

	KupljeniArtikal& operator=(const KupljeniArtikal& a)
	{
		if (this != &a)
		{
			delete[] _naziv;

			int vel = strlen(a._naziv) + 1;
			_naziv = new char[vel];
			strcpy_s(_naziv, vel, a._naziv);

			_cijena = a._cijena;
			_kolicina = a._kolicina;
		}
		return *this;
	}

	KupljeniArtikal& operator+=(float cijena) 
	{
		_cijena += cijena;

		return *this;
	}

	KupljeniArtikal& operator++() 
	{
		_kolicina++;

		return *this;
	}

	void UvecajKolicinu(int kol)
	{
		_kolicina += kol;
	}

	int GetKolicina() const{ return _kolicina; }
	float GetCijena() const { return _cijena; }

	friend bool operator==(const KupljeniArtikal&, const KupljeniArtikal&);
	friend ostream& operator<<(ostream&, const KupljeniArtikal&);
};

bool operator==(const KupljeniArtikal& a1, const KupljeniArtikal& a2)
{
	return strcmp(a1._naziv, a2._naziv) == 0;
}

ostream& operator<<(ostream& cout, const KupljeniArtikal& a)
{
	cout << a._naziv << "\t" << a._kolicina << "\t" << a._cijena << endl;

	return cout;
}

class Racun {
	static int _brojacRacuna;
	const int _brojRacuna;
	KupljeniArtikal* _artikli;
	int _trenutno;
public:
	Racun(): _brojRacuna(++_brojacRacuna), _artikli(nullptr), _trenutno(0)
	{

	}

	~Racun() {
		delete[] _artikli;
		_artikli = nullptr;
	}

	Racun& operator+=(const KupljeniArtikal& a)
	{
		
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (_artikli[i] == a)
			{
				_artikli[i].UvecajKolicinu(a.GetKolicina());

				return *this;
			}
		}

		KupljeniArtikal* temp = new KupljeniArtikal[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp[i] = _artikli[i];
		}

		delete[] _artikli;
		_artikli = temp;
		_artikli[_trenutno++] = a;

		return *this;
	}

	KupljeniArtikal* GetArtikli(float ukupnaCijena, int& brojPronadjenih)
	{
		brojPronadjenih = 0;

		for (size_t i = 0; i < _trenutno; i++)
		{
			if (_artikli[i].GetKolicina() * _artikli[i].GetCijena() > ukupnaCijena)
			{
				brojPronadjenih++;
			}
		}
		if (brojPronadjenih == 0)
			return  nullptr;

		KupljeniArtikal* rezArtikli = new KupljeniArtikal[brojPronadjenih];
		int indexNiz = 0;

		for (size_t i = 0; i < _trenutno; i++)
		{
			if (_artikli[i].GetKolicina() * _artikli[i].GetCijena() > ukupnaCijena)
			{
				rezArtikli[indexNiz++] = _artikli[i];
			}
		}

		return rezArtikli;

	}

	friend ostream& operator<<(ostream&, const Racun&);

};

int Racun::_brojacRacuna = 0;

ostream& operator<<(ostream& cout, const Racun& racun) 
{
	cout << "Broj racuna: " << racun._brojacRacuna << endl;
	cout << "Naziv\tKol\tCijena\n\n";

	float iznos = 0;
	for (size_t i = 0; i < racun._trenutno; i++)
	{
		cout << racun._artikli[i] << endl;
		iznos += racun._artikli[i].GetKolicina() * racun._artikli[i].GetCijena();
	}

	cout << "Iznos racuna: " << iznos << endl;

	return cout;
}

void main(){
	KupljeniArtikal cokolada("Milka", 2.29);
	KupljeniArtikal sok("Jucy", 1.38);
	KupljeniArtikal cigarete("Drina", 4.32);
	KupljeniArtikal mlijeko("Meggle", 2.87);
	
	cokolada += 0.27;
	++cokolada;
	++sok;
	
	Racun racun;
	racun += cokolada;
	racun += sok;
	racun += sok;
	racun += cigarete;
	racun += mlijeko;

	cout << racun << endl;

	int brojPronadjenih = 0;
	float ukupnaCijena = 5.10;

	cout << crt << "Artikli skuplji od >> " << ukupnaCijena << crt;

	KupljeniArtikal* artikli = racun.GetArtikli(ukupnaCijena, brojPronadjenih);
	if (artikli != nullptr) {
		for (size_t i = 0; i < brojPronadjenih; i++)
		{
			cout << artikli[i] << endl;
		}
	}

	delete[] artikli;
	artikli = nullptr;

	system("pause");
}
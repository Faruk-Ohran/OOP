#include <iostream>
using namespace std;

const char* crt = "\n-------------------------------\n";

class KupljeniArtikal {
	char* _naziv;
	float _cijena;
	int _kolicina;
	//konstruktor, destruktor i potrebne funkcije
};

class Racun {
	static int _brojacRacuna;
	const int _brojRacuna; //brojevi racuna krecu od 1
	KupljeniArtikal* _artikli; //niz povecavamo prilikom svakog dodavanja artikla
	int _trenutno;
};

void main() {
	KupljeniArtikal cokolada("Milka", 2.29);//naziv i cijena artikla
	KupljeniArtikal sok("Jucy", 1.38);
	KupljeniArtikal cigarete("Drina", 4.32);
	KupljeniArtikal mlijeko("Meggle", 2.87);

	cokolada += 0.27;//povecavamo cijenu artikla, sada je cijena 2,56BAM
	++cokolada;//povecavamo kolicinu artikla, sada je kolicina 2
	++sok;

	Racun racun;
	racun += cokolada;//dodajemo 2 cokolade po cijeni od 2,56BAM
	racun += sok;
	racun += sok;//ako vise puta pokusamo dodati isti artikal, 
	//treba da se uveca samo njegova kolicina na racunu 
	//tj. artikli se ne smiju ponavljati
	racun += cigarete;
	racun += mlijeko;

	cout << racun << endl;//ispis racuna mozete vidjeti na slici

	int brojPronadjenih = 0;
	float ukupnaCijena = 5.10;

	cout << crt << "Artikli skuplji od >> " << ukupnaCijena << crt;
	//treba da vrati sve artikle cija je ukupna cijena na racunu (cijena*kolicina) veca od poslane tj. 5,10BAM
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
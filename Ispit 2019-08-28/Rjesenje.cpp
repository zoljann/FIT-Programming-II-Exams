#include<regex>
#include<string>
#include<vector>
#include<regex>
#include<mutex>
#include<exception>
#include<thread>
#include<iostream>
using namespace std;
const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
enum SortirajPo { T1, T2 };
const char* ispisRazreda[] = { "PRVI", "DRUGI", "TRECI", "CETVRTI" };
char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_trenutno = 0; //moramo brojac postaviti na 0 
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_omoguciDupliranje = omoguciDupliranje;
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = obj._trenutno;
		_omoguciDupliranje = obj._omoguciDupliranje;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj) {
			delete[]_elementi1;
			delete[]_elementi2;
			_trenutno = obj._trenutno;
			_omoguciDupliranje = obj._omoguciDupliranje;
			_elementi1 = new T1[_trenutno];
			_elementi2 = new T2[_trenutno];
			for (int i = 0; i < _trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}
		}
		return *this;
	}
	bool PostojeLiIsti(T1 el1, T2 el2) {
		for (int i = 0; i < _trenutno; i++)
		{
			if (!_omoguciDupliranje && _elementi1[i] == el1 && _elementi2[i] == el2)
				return true;
		}
		return false;
	}
	void AddElement(T1 el1, T2 el2) {
		if (PostojeLiIsti(el1, el2))
			throw exception("Ne mozes dodati iste elemente!");
		T1* temp1 = _elementi1;
		T2* temp2 = _elementi2;
		_elementi1 = new T1[_trenutno + 1];
		_elementi2 = new T2[_trenutno + 1];
		for (int i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = temp1[i];
			_elementi2[i] = temp2[i];
		}
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;
		delete[]temp1; delete[]temp2; temp1 = nullptr; temp2 = nullptr;
		_trenutno++;
	}
	void SortirajRastuci(const SortirajPo& T) {
		bool flag = true;
		if (T == 1) {
			T2 temp;
			while (flag) {
				flag = false;
				for (int i = 0; i < _trenutno - 1; i++) {
					if (_elementi2[i] < _elementi2[i + 1]) {
						temp = _elementi2[i];
						_elementi2[i] = _elementi2[i + 1];
						_elementi2[i + 1] = temp;
						flag = true;
					}

				}
			}
		}
		if (T == 0) {
			T1 temp;
			while (flag) {
				flag = false;
				for (int i = 0; i < _trenutno - 1; i++) {
					if (_elementi1[i] < _elementi1[i + 1]) {
						temp = _elementi1[i];
						_elementi1[i] = _elementi1[i + 1];
						_elementi1[i + 1] = temp;
						flag = true;
					}

				}
			}
		}
	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (int i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};
class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	DatumVrijeme(const DatumVrijeme& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
		if (this != &obj) {
			_dan = new int(*obj._dan);
			_mjesec = new int(*obj._mjesec);
			_godina = new int(*obj._godina);
			_sati = new int(*obj._sati);
			_minuti = new int(*obj._minuti);
		}
		return *this;
	}
	bool operator==(const DatumVrijeme& obj) {
		return *_godina == *obj._godina && *_mjesec == *obj._mjesec && *_dan == *obj._dan && *_minuti == *obj._minuti && *_sati == *obj._sati;
	}
	float toDane()const {
		return *_godina * 365 + *_mjesec * 30 + *_dan + *_sati / 24 + *_minuti / 1440;
	}
	float toMinute() {
		return toDane() * 1440;
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}

};
class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	Predmet(const Predmet& obj) {
		_naziv = Alociraj(obj._naziv);
		_ocjena = obj._ocjena;
		_napomena = obj._napomena;
	}
	Predmet& operator=(const Predmet& obj) {
		if (this != &obj) {
			delete[]_naziv;
			_naziv = Alociraj(obj._naziv);
			_ocjena = obj._ocjena;
			_napomena = obj._napomena;
		}
		return *this;
	}
	bool operator==(Predmet& obj) {
		return strcmp(_naziv, obj._naziv) == 0;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() { return _naziv; }
	int GetOcjena() { return _ocjena; }

	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
};
class Uspjeh {
	eRazred* _razred;
	//formalni argument DatumVrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(eRazred razred) {
		_razred = new eRazred(razred);
	}
	Uspjeh(const Uspjeh& obj) {
		_razred = new eRazred(*obj._razred);
		_predmeti = new Kolekcija<Predmet, DatumVrijeme>(obj._predmeti);
	}
	Uspjeh& operator=(const Uspjeh& obj) {
		if (this != &obj) {
			_razred = new eRazred(*obj._razred);
			_predmeti = new Kolekcija<Predmet, DatumVrijeme>(obj._predmeti);
		}
		return *this;
	}
	float ProsjekRazreda() {
		float prosjek = 0;
		if (_predmeti.getTrenutno() == 0)
			return prosjek;
		for (size_t i = 0; i < _predmeti.getTrenutno(); i++)
		{
			prosjek += _predmeti.getElement1(i).GetOcjena();
		}
		return prosjek / _predmeti.getTrenutno();
	}
	~Uspjeh() { delete _razred; _razred = nullptr; }

	Kolekcija<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	eRazred* GetERazred() { return _razred; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << *obj._razred << " " << obj._predmeti << endl;
		return COUT;
	}
};
mutex muteks;
class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
	bool ValidirajEmail(string email) {
		return regex_match(email, regex("[a-zA-Z]+@(outlook|edu.fit).(com|ba)"));
	}
	void SaljemMejl(eRazred razred) {
		muteks.lock();
		cout << "FROM: info@kursevi.ba\nTO: " << GetEmail() << endl;
		cout << "Postovani " << GetImePrezime() << ", evidentirali ste uspjeh za " << ispisRazreda[razred] <<" razred."<< endl;
		cout << "Pozdrav.\nFIT Team.\n" << endl;
		muteks.unlock();
	}
	void SaljemSMS(eRazred razred, float prosjekR) {
		muteks.lock();
		cout << "Svaka cast za uspjeh " << prosjekR << " u " << ispisRazreda[razred] << endl;
		muteks.unlock();
	}
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		_emailAdresa = ValidirajEmail(emailAdresa) ? emailAdresa : "notSet@edu.fit.ba";
		_brojTelefona = brojTelefona;
	}
	Kandidat(const Kandidat& obj) {
		_imePrezime = Alociraj(obj._imePrezime);
		_emailAdresa = obj._emailAdresa;
		_brojTelefona = obj._brojTelefona;
	}
	Kandidat& operator=(const Kandidat& obj) {
		if (this != &obj) {
			delete[]_imePrezime;
			_imePrezime = Alociraj(obj._imePrezime);
			_emailAdresa = obj._emailAdresa;
			_brojTelefona = obj._brojTelefona;
		}
		return *this;
	}
	bool ProvjeriJesuLiIsti(eRazred razred, Predmet& predmet) {
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (razred == *_uspjeh[i].GetERazred()) {
				for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
				{
					if (predmet == _uspjeh[i].GetPredmeti()->getElement1(j))
						return true;
				}
			}
		}
		return false;
	}
	bool ProvjeriRazmak(eRazred razred, Predmet& predmet, DatumVrijeme& datum) {
		for (int i = 0; i < _uspjeh.size(); i++)
		{
			if (razred == *_uspjeh[i].GetERazred()) {
				for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
				{
					if (datum.toMinute() - _uspjeh[i].GetPredmeti()->getElement2(j).toMinute() < 5)
						return true;
				}
			}
		}
		return false;
	}
	bool AddPredmet(eRazred razred, Predmet& predmet, DatumVrijeme& datum) {
		for (size_t i = 0; i < _uspjeh.size(); i++)
		{
			if (razred == *_uspjeh[i].GetERazred()) {
				if (ProvjeriJesuLiIsti(razred, predmet))
					return false;
				if (ProvjeriRazmak(razred, predmet, datum))
					return false;

				_uspjeh[i].GetPredmeti()->AddElement(predmet, datum);
				thread t1(&Kandidat::SaljemMejl, this, razred);
				t1.join();
				if (_uspjeh[i].ProsjekRazreda() > 4.5) {
					thread t2(&Kandidat::SaljemSMS, this, razred, _uspjeh[i].ProsjekRazreda());
					t2.join();
				}
				return true;
			}
		}
		Uspjeh u(razred);
		u.GetPredmeti()->AddElement(predmet, datum);
		_uspjeh.push_back(u);
		thread t1(&Kandidat::SaljemMejl, this, razred);
		t1.join();
		if (u.ProsjekRazreda() > 4.5) {
			thread t2(&Kandidat::SaljemSMS, this, razred, u.ProsjekRazreda());
			t2.join();
		}
		return true;
	}
	vector<Predmet> operator()(DatumVrijeme d1, DatumVrijeme d2) {
		vector<Predmet> temp;
		for (int i = 0; i < _uspjeh.size(); i++) {
			for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) {
				if (_uspjeh[i].GetPredmeti()->getElement2(j).toDane() > d1.toDane() &&
					_uspjeh[i].GetPredmeti()->getElement2(j).toDane() < d2.toDane()) {
					temp.push_back(_uspjeh[i].GetPredmeti()->getElement1(j));
				}
			}
		}

		return temp;

	}
	Uspjeh* operator[](eRazred razred)
	{
		for (vector<Uspjeh>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
		{
			if (*i->GetERazred() == razred)
				return i._Ptr;
		}
		return nullptr;
	}

	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR AE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEEILO GUBLJENJE URA?ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO?ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIENI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUEAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOANE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAEENO.
	7. IMATE POTPUNU SLOBODU DA U MAIN FUNKCIJI, ZA POTREBE TESTIRANJA, DODAJETE VISE POZIVA ILI SALJETE DRUGE VRIJEDNOSTI PARAMETARA
	****************************************************************************/

	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);

	const int kolekcijaTestSize = 9;
	Kolekcija<int, int> kolekcija1(false);
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, 20 - i);

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata, metoda AddElement baca izuzetak
		kolekcija1.AddElement(6, 15);
	}
	catch (exception& err) {
		cout << err.what() << endl;
	}
	cout << kolekcija1 << endl;

	//na osnovu vrijednosti parametra sortira clanove kolekcije u rastucem redoslijedu 
	kolekcija1.SortirajRastuci(SortirajPo::T2);
	cout << kolekcija1 << endl;


	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	cout << kolekcija3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << Matematika << endl;

	/*
	email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	za provjeru koristiti regex
	*/
	Kandidat jasmin("Jasmin Azemovic", "jasmin@outlook.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
	Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062019_1015))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Fiziku jer nije proslo 5 minuta od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.

	ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
		cout << "USPJEH ISPISATI KORISTECI OSTREAM_ITERATOR" << endl;
		cout << jasmin << endl;
		//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
		//cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;
	
		//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
		vector<Predmet> jasminUspjeh = jasmin(DatumVrijeme(18, 06, 2019, 10, 15), DatumVrijeme(21, 06, 2019, 10, 10));
		for (int i = 0; i < jasminUspjeh.size(); i++)
			cout << jasminUspjeh[i] << endl;
	
		Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
		if (uspjeh_Irazred != nullptr)
			cout << *uspjeh_Irazred << endl;

	cin.get();
	system("pause>0");
}
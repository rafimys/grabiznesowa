#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "RandomNameGenerator.hpp"

using namespace std;

#define wygrana 10000 //wartosc jaka musi miec firma zeby wygrac gre
#define N 4 //z ilu miesiecy robic srednia przychodow
#define stan_start 5000 //poczatkowy stan konta
#define M 3 // m razy wartosc spolki tyle mozna zaciagnac dlug
#define CI 10 //wydajenosc inzyniera
#define CMag 10 //wydajnosc magazyniera
#define CMkt 10 //wydajnosc marketera
#define Cr 10 //wydajnosc robotnika
#define wynI 100
#define wynMag 100
#define wynMkt 100
#define wynR 100



class kredyt {
public:
    kredyt() {}
    kredyt(double ile, int naile) {
        pozostale_raty = naile;
        rata = ile / naile;
    }
    double splac_rate(int ilerat) {
        double ile;
        if (pozostale_raty == 0) {
            ile=0;
        }

        if (pozostale_raty == 0) {
            ile= 0;
        }
        else { ile= rata * ilerat; }
        pozostale_raty = pozostale_raty - ilerat;
        return ile;
    }
    int pozostale() {
        return pozostale_raty;
    }
private:
    int pozostale_raty;
    double rata;
};

class pracownik {
public:
    pracownik() {
        imie = get_random_name();
        kim = 0;
    }
    virtual void print();
    //metoda oznamiajaca kto kim jest i jkie wynagrodzenie mu zaplacic
    virtual int kto() {
        return kim;
    }
    ~pracownik() {}

protected:
    //double c;
    int kim;
    string imie;
};
void(pracownik::* bfnprint)() = &pracownik::print;
void pracownik::print() { cout << imie << endl; };

class inz : public pracownik {
public:
    inz() {
        kim = 1;
        imie = get_random_name();
        wydzial = "MEIL";
    }
    void print() { cout << imie << " inzynier jego wydzial to " << wydzial << " wynagrodzenie " << wynI << endl; }
    int kto() { return kim; };
private:
    string wydzial;
};

class mag : public pracownik {
public:
    mag() {
        //losowanie licencji na wozek
        srand((unsigned)time(NULL));
        int r = 1 + rand() % 2;
        if (r == 1) {
            wozek = true;
        }
        else {
            wozek = false;
        }
        kim = 2;
    }
    void print() override { cout << imie << " magazynier " << wozek << " pozwolenie na wozek" << " wynagrodzenie " << wynMag << endl; }
    int kto() override { return kim; };

private:
    bool wozek;
};

class mkt : public pracownik {
public:
    mkt() {
        //losowanie liczbyobserwujacych
        srand((unsigned)time(NULL));
        int r = 1000 + rand() % 2000;
        obs = r;
        kim = 3;
    }
    void print() { cout << imie << " marketowiec jego liczba obserwujacych to " << obs << " wynagrodzenie " << wynMkt << endl; }
    int kto() { return kim; };
private:
    int obs;
};

class rob : public pracownik {
public:
    rob() {
        //losowanie rozmiar buta
        srand((unsigned)time(NULL));
        double m = 50 + rand() % 67;
        double n = 2 + rand() % 3;
        rozmiar = m / n;
        kim = 4;
    }
    void print();
    int kto() { return kim; };
private:
    double rozmiar;
};

void rob::print() { cout << imie << " robotnik jego rozmiar buta to " << rozmiar << " wynagrodzenie " << wynR << endl; };

class firma {
public:
    firma() {
        stan = stan_start;
        n_kred = 0;
        n_prac = 0;
    }
    //metoda zzatrudnienia pracownika
    void zat(string typ) {
        bool czy = false;
        pracownik* p;
        if (typ == "inzynier") {
            p = new inz;
            cout << "zatrudniles ";
            p->print();
            czy = true;
        }
        if (typ == "magazynier") {
            p = new mag;
            cout << "zatrudniles ";
            p->print();
            czy = true;
        }
        if (typ == "marketer") {
            p = new mkt;
            cout << "zatrudniles ";
            p->print();
            czy = true;
        }
        if (typ == "robotnik") {
            p = new rob;
            cout << "zatrudniles ";
            p->print();
            czy = true;
        }
        if (czy == false) {
            cout << "zle wpisana nazwa kogo chcesz zatrudnic napisz inzynier, magazynier, marketer, robotnik" << endl;
        }
        else {
            prac.push_back(p);
            n_prac++;
        }

    }
    //metoda drukujaca pracownikow
    void drukuj_prac() {
        pracownik* p;
        for (int i = 0; i < n_prac; i++) {
            p = prac[i];
            (p->*bfnprint)();
        }
    }
    //metoda ktora placi pracownikom
    void zaplac_wyn() {
        pracownik* p;
        double ile_zaplacic = 0;
        for (int i = 0; i < n_prac; i++) {
            p = prac[i];
            switch (p->kto()) {
            case 1:
                ile_zaplacic = ile_zaplacic + wynI;
                break;
            case 2:
                ile_zaplacic = ile_zaplacic + wynMag;
                break;
            case 3:
                ile_zaplacic = ile_zaplacic + wynMkt;
                break;
            case 4:
                ile_zaplacic = ile_zaplacic + wynR;
                break;
            }
        }
        stan = stan - ile_zaplacic;
    }
    //metoda ktora pozwala na wziecie kredytu
    void wez_kred(double kwota, int czas_splaty) {
        k.push_back(kredyt(kwota, czas_splaty));
        n_kred++;
        double rata = kwota / czas_splaty;
        cout << "wziety kredyt na kwote " << kwota << " czas splaty to " << czas_splaty << " jedna rata wynosi " << rata << endl;
    }

    //metoda optrzymywania przychodow
    void otrzy_przych() {
        pracownik* p;
        int ilosc_prod = 0;
        int pojemnosc_mag = 0;
        int cena_prod = 0;
        int sprzedane = 0;
        for (int i = 0; i < n_prac; i++) {
            p = prac[i];
            switch (p->kto()) {
            case 1:
                cena_prod = cena_prod + CI;
                break;
            case 2:
                pojemnosc_mag = pojemnosc_mag + CMag;
                break;
            case 3:
                sprzedane = sprzedane + CMkt;
                break;
            case 4:
                ilosc_prod = ilosc_prod + Cr;
                break;
            }
        }
        if (ilosc_prod > pojemnosc_mag) {
            ilosc_prod = pojemnosc_mag;
        }
        if (ilosc_prod < sprzedane) {

            sprzedane = ilosc_prod;
        }
        stan = stan + sprzedane * cena_prod;
        his_przy.push_back(sprzedane * cena_prod);
    }
    //metoda ktora pozwala na splacenie raty
    void splac_rate() {
        kredyt kr;
        double ile_zaplacic;
        for (int i = 0; i < n_kred; i++) {
            kr = k[i];
            ile_zaplacic = kr.splac_rate(1);
            k[i] = kr;
            stan = stan - ile_zaplacic;
            cout << "splacicles 1 rate kredytu " << i << " pozostale raty " << kr.pozostale() << endl;
        }
    }
    //metoda ktora pozwala przeczytac stan konta
    const double get_stan() {
        return stan;
    }
    //metoda pozwalajaca otrzymac wartosc firmy
    double wartosc_firmy() {
        double stanny = 0;
        if (his_przy.size() >= N) {
            for (int i = his_przy.size() - N; i < his_przy.size(); i++) {
                stanny = stanny + his_przy[i];
            }
            return stanny / N;
        }
        cout << "za malo miesiecy aby oszacowac wartosc spolki" << endl;
        return 1000;

    }
    double oblicz_przychud() {
        pracownik* p;
        int ilosc_prod = 0;
        int pojemnosc_mag = 0;
        int cena_prod = 0;
        int sprzedane = 0;
        for (int i = 0; i < n_prac; i++) {
            p = prac[i];
            switch (p->kto()) {
            case 1:
                cena_prod = cena_prod + CI;
                break;
            case 2:
                pojemnosc_mag = pojemnosc_mag + CMag;
                break;
            case 3:
                sprzedane = sprzedane + CMkt;
                break;
            case 4:
                ilosc_prod = ilosc_prod + Cr;
                break;
            }
        }
        if (ilosc_prod > pojemnosc_mag) {
            ilosc_prod = pojemnosc_mag;
        }
        if (pojemnosc_mag < sprzedane) {
            sprzedane = pojemnosc_mag;
        }
        return sprzedane * cena_prod;
    }

    ~firma() {
        for (int i = 0; i <= n_prac; i++) {
            delete prac[i];
        }
    }
     
private:

    int ktory_mies;
    double stan; //stan konta
    int n_kred = 0; //liczba kredytow
    vector<kredyt> k; //lista wzietych kredytow
    int n_prac; // liczba pracownikow
    vector<pracownik*> prac; //wskazniki do pracownikow
    vector<double> his_przy; //lista przychodu co miesiac dynamicznie alokowana lista
};

class gra {
public:
    gra() {
        f = new firma;
        stan = true;
    }
    bool get_stan() {
        if (f->wartosc_firmy() > wygrana) {
            return false;
            cout << "gra zostal wygrana";
        }
        else {
            if (f->get_stan() <= 0) {
                cout << "przegrales gre";
                return false;
            }
            return true;
        }
    }
    void akcja_gracza(string akcja) {
        if (akcja == "lp") {
            f->drukuj_prac();
        }
        if (akcja == "zinz") {
            f->zat("inzynier");
        }
        if (akcja == "zmag") {
            f->zat("magazynier");
        }
        if (akcja == "zmkt") {
            f->zat("marketer");
        }
        if (akcja == "zrob") {
            f->zat("robotnik");
        }
        if (akcja == "kred") {
            double wartosc;
            int n_rata;
            cout << "napisz na jaka wartosc bierzesz kredyt" << endl;
            cin >> wartosc;
            cout << "napisz na ile rat bierzesz kredyt" << endl;
            cin >> n_rata;
            f->wez_kred(wartosc, n_rata);
        }
        if (akcja == "kt") {
            f->otrzy_przych();
            f->splac_rate();
            f->zaplac_wyn();
            double kont = f->get_stan();
            double przychud = f->oblicz_przychud();
            cout << "przychud w tym miesiacu to " << przychud << endl;
            cout << "stan twojego konta to " << kont << endl;
            cout << "skonczyles ture" << endl;
        }
    }
    ~gra() {
        delete f;
    }


private:
    bool stan;
    firma* f;
};

int main() {
    /*mag ma;
    ma.print();
    cout << "***********************" << endl;
    cout << "testy firmy"<<endl;

    firma f;
    cout<< f.get_stan()<<endl;

    cout << "***********************" << endl;
    f.zat("robotnik");
    f.zat("marketer");
    f.zat("marketer");
    f.zat("inzynier");
    f.zat("magazynier");
    f.zaplac_wyn();
    cout << f.get_stan() << endl;
    f.drukuj_prac();
    cout << "***********************" << endl;
    f.otrzy_przych();
    cout << f.get_stan() << endl;
    cout << "***********************" << endl;
    f.wez_kred(100, 3);
    f.splac_rate();
    cout << "***********************" << endl;
    cout << "splacanie drugiej raty";
    f.splac_rate();
    f.splac_rate();
    cout << "***********************" << endl;
    f.otrzy_przych();
    f.otrzy_przych();
    f.otrzy_przych();
    cout << f.get_stan() << endl;
    cout << f.wartosc_firmy();*/
    bool czy_kolejna_gra = true;
    while (czy_kolejna_gra) {
        gra g;
        bool stan = true;
        while (stan) {
            cout << "wybierz akcje jaka chcesz zrobic" << endl;
            cout << "lp - wylistuj pracowników(imiona i wynagrodzenia)" << endl;
            cout << "zinz - zatrudnij inzyniera" << endl;
            cout << "zmag - zatrudnij magazyniera" << endl;
            cout << "zmkt - zatrudnij marketowca" << endl;
            cout << "zrob - zatrudnij robotnika" << endl;
            cout << "kred - wez kredyt (w nastepnym kroku podaj kwote i czas splaty)" << endl;
            cout << "kt - koniec tury" << endl;
            bool kt = true;
            while (kt) {
                string akcja;
                cout << "wybierz akcje" << endl;
                cin >> akcja;
                g.akcja_gracza(akcja);
                if (akcja == "kt") {
                    kt = false;
                }
            }
            stan = g.get_stan();
        }
        string akcja2;
        cout << "chcesz zagrac kolejna gre tak/nie" << endl;
        cin >> akcja2;
        if (akcja2 == "tak") {
            czy_kolejna_gra = true;
        }
        else {
            czy_kolejna_gra = false;
        }
    }
    return 0;
}
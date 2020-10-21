#include <iostream>

#include <string>

using namespace std;

//class that describes the behavior of a train-type object
class Tren {
private:
	const int nrTren; //constant attribute - unique train number
	string ruta; // describe train's route
	int nrStatii; //additional variable, added for crossing the stations vector
	string * statii; //dynamic array with the name of the stations 
	int nrCalatori; //additional variable, added for crossing the prices vector
	float pret[20]; //static array containing prices paid by the travellers for the ticket
	//for exemplify the way of working of the program, I will consider a maximum number of 20 travellers
	//0 eur collected, represents the tickets with a full discount
	bool rangTren; //bool variable for train type: Regio/InterRegio
	string rang; //true=R, false=IR
public:
	static int contor; //static variable that helps on creating a train number

    //destructor
	~Tren() {
		if (this->statii != NULL)
			delete[] this->statii;
		this->contor--;
	}

	//4 types of constructor

	//default constructor
	Tren() : nrTren(contor++ + 1000) {
		this->ruta = "Necunoscut";
		this->nrStatii = 0;
		this->nrCalatori = 0;
		this->statii = NULL;
	}

	Tren(bool rangTren, string ruta, int nrStatii, string * statii) : nrTren(contor++ + 1000), nrCalatori(0) {
		this->rangTren = rangTren;
		if (this->rangTren)
			this->rang = "R";
		else
			this->rang = "IR";
		this->ruta = ruta;
		this->nrStatii = nrStatii;
		this->statii = new string[this->nrStatii];
		for (int i = 0; i < this->nrStatii; i++)
			this->statii[i] = statii[i];
	}

	Tren(bool rangTren, string ruta, int nrStatii, string * statii, int nrCalatori, float pret[10]) : nrTren(contor++ + 1000) {
		this->rangTren = rangTren;
		if (this->rangTren)
			this->rang = "R";
		else
			this->rang = "IR";
		this->ruta = ruta;
		this->nrStatii = nrStatii;
		this->statii = new string[this->nrStatii];
		for (int i = 0; i < this->nrStatii; i++)
			this->statii[i] = statii[i];

		this->nrCalatori = nrCalatori;
		for (int i = 0; i < nrCalatori; i++)
			this->pret[i] = pret[i];
	}

	Tren(const Tren & t) : nrTren(t.nrTren) {
		this->rang = t.rang;
		this->rangTren = t.rangTren;
		this->ruta = t.ruta;
		this->nrStatii = t.nrStatii;
		this->statii = new string[this->nrStatii];
		if (statii != NULL) {
			for (int i = 0; i < this->nrStatii; i++)
				this->statii[i] = t.statii[i];
		}
		else
			this->statii = NULL;

		this->nrCalatori = t.nrCalatori;
		for (int i = 0; i < this->nrCalatori; i++)
			this->pret[i] = t.pret[i];
	}

	//override operator =
	Tren operator = (const Tren & t) {
		this->rang = t.rang;
		this->ruta = t.ruta;
		this->nrStatii = t.nrStatii;
		if (this->statii != NULL)
			delete[] this->statii;
		this->statii = new string[this->nrStatii];
		if (statii != NULL) {
			for (int i = 0; i < this->nrStatii; i++)
				this->statii[i] = t.statii[i];
		}
		else
			this->statii = NULL;

		this->nrCalatori = t.nrCalatori;
		for (int i = 0; i < this->nrCalatori; i++)
			this->pret[i] = t.pret[i];

		return *this;
	}

	//getters and setters

	int getNrTen() {
		return this->nrTren;
	}

	bool getRangTren() {
		return this->rangTren;
	}

	void setRangTren(bool rangTren) {
		this->rangTren = rangTren;
		if (this->rangTren)
			this->rang = "R";
		else
			this->rang = "IR";
	}

	string getRuta() {
		return this->ruta;
	}

	void setRuta(string ruta) {
		this->ruta = ruta;
	}

	int getNrStatii() {
		return this->nrStatii;
	}

	void setNrStatii(int nrStatii) {
		this->nrStatii = nrStatii;
	}

	void getStatii() {
		if (this->statii != NULL)
			for (int i = 0; i < this->nrStatii; i++)
				cout << this->statii[i] << " ";
	}

	void setStatii(string * statii) {
		if (this->statii != NULL)
			delete[] this->statii;
		this->statii = new string[this->nrStatii];
		for (int i = 0; i < this->nrStatii; i++)
			this->statii[i] = statii[i];
	}

	int getNrCalatori() {
		return this->nrCalatori;
	}

	void setNrCalatori(int nrCalatori) {
		this->nrCalatori = nrCalatori;
	}

	void getPret() {
		for (int i = 0; i < this->nrCalatori; i++)
			cout << this->pret[i] << " ";
	}

	void setPret(float pret[20]) {
		for (int i = 0; i < this->nrCalatori; i++)
			this->pret[i] = pret[i];
	}

	//2 methods
	float incasariMedii() {
		float s = 0;
		for (int i = 0; i < this->nrCalatori; i++)
			s += this->pret[i];
		return s / this->nrCalatori;
	}

	float incasariTotale() {
		float sum = 0;
		if (this->nrCalatori > 0) {
			for (int i = 0; i < this->nrCalatori; i++)
				sum += this->pret[i];
			return sum;
		}

	}

	//10 overrides

	Tren operator + (float val) {
		this->nrCalatori++;
		if (this->nrCalatori < 20)
			this->pret[this->nrCalatori - 1] = val;
		return *this;
	}

	Tren operator += (string val) {
		string * copie;
		copie = new string[this->nrStatii + 1];
		for (int i = 0; i < this->nrStatii; i++)
			copie[i] = this->statii[i];
		if (this->statii != NULL)
			delete[] this->statii;
		this->nrStatii++;
		this->statii = new string[this->nrStatii];
		for (int i = 0; i < this->nrStatii; i++)
			this->statii[i] = copie[i];
		this->statii[this->nrStatii - 1] = val;
		return *this;
	}

	Tren operator * (int val) {
		this->pret[this->nrCalatori - 1] *= 2;
		return *this;
	}

	float operator()() {
		float max = 0;
		for (int i = 0; i < this->nrCalatori; i++)
			if (this->pret[i] > max)
				max = this->pret[i];
		return max;
	}

	explicit operator float() {
		float min = 0;
		for (int i = 0; i < this->nrCalatori; i++)
			if (min > this->pret[i])
				min = this->pret[i];
		return min;
	}

	string operator[](int i) {
		return this->statii[i];
	}

	Tren operator++() {
		this->pret[this->nrCalatori - 1] += 10;
		return *this;
	}

	Tren operator++(int) {
		Tren copie = *this;
		this->pret[this->nrCalatori - 1] += 10;
		return copie;
	}

	bool operator <= (Tren & t) {
		if (this->incasariTotale() <= t.incasariTotale())
			return 0;
		else
			return 1;
	}

	bool operator!() {
		if (!this->nrCalatori)
			return 0;
		else
			return 1;
	}

	friend ostream & operator << (ostream & out,
		const Tren & t);
	friend istream & operator >> (istream & in, Tren & t);

};

//override << and >>
ostream & operator << (ostream & out,
	const Tren & t) {
	out << t.rang << t.nrTren << " circula pe ruta " << t.ruta << ". Trenul va opri in statiile: ";
	for (int i = 0; i < t.nrStatii; i++)
		out << " " << t.statii[i];
	out << "\nDe pe urma celor " << t.nrCalatori << " calatori s-au incasat sumele: ";
	if (t.nrCalatori > 0) {
		for (int i = 0; i < t.nrCalatori; i++)
			out << " " << t.pret[i];
	}
	else out << "Fara bilete vandute!";
	return out;
}

istream & operator >> (istream & in, Tren & t) {
	cout << "\nRang tren(0-REGIO, 1-INTERREGIO): "; in >> t.rangTren; in.ignore();
	cout << "Ruta: "; in >> t.ruta;
	cout << "Nr. statii: "; in >> t.nrStatii; in.ignore();
	if (t.statii != NULL)
		delete[] t.statii;
	t.statii = new string[t.nrStatii];
	for (int i = 0; i < t.nrStatii; i++) {
		cout << "Statie[" << i << "]: "; in >> t.statii[i];
	}
	cout << "Nr. Calatori: "; in >> t.nrCalatori;
	for (int i = 0; i < t.nrCalatori; i++) {
		cout << "Pret: "; in >> t.pret[i];
	}

	return in;
}
int Tren::contor = 0;

void main() {
	string statii[]{
	  "Videle",
	  "Craiova",
	  "Orsova",
	  "Timisoara"
	};
	string statii2[]{
	  "Ploiesti",
	  "Campina",
	  "Brasov"
	};
	Tren t1(true, "Bucuresti-Brasov-Sibiu", 3, statii2);
	float pret[7] = {
	  50.5,
	  70,
	  55,
	  40.6,
	  30,
	  32,
	  0
	};
	Tren t2(false, "Bucuresti-Timisoara", 4, statii, 7, pret);
	cout << "\nStatii: ";
	t2.getStatii();
	cout << endl;
	cout << t1.getRangTren() << endl;
	cout << t1.getNrTen() << endl;
	t1.setRangTren(false);
	cout << t1.getRuta() << endl;
	t2.setRuta("Bucuresti-Timsoara Nord");
	cout << t2.getNrStatii() << endl;
	t1.setNrStatii(4);
	string statii3[]{
	  "Breaza",
	  "Sinaia",
	  "Predeal",
	  "Brasov"
	};
	t1.setStatii(statii3);
	t2.setNrCalatori(8);
	cout << t2.getNrCalatori() << endl;
	float pret1[8] = {
	  50.5,
	  0,
	  55,
	  0,
	  40.6,
	  30,
	  0,
	  32
	};
	t2.setPret(pret1);
	t2.getPret();
	cout << endl << "Trenuri in circulatie: " << Tren::contor;
	Tren t4(t1);
	cout << endl << t4;
	Tren t3 = t2;
	t1 = t2;
	t2.setRangTren(true);
	cout << endl << t2;

	t3 + 34.7; //add a tiket
	t4 += "Sibiu"; //add a station
	t2 * 2; //multiply with 2 the last price
	cout << endl << t2;
	cout << "\nIncasari totale: " << t2.incasariTotale();
	cout << "\nIncasari medii: " << t2.incasariMedii();
	cout << "\nPretul maxim: " << t2();
	cout << "\nPretul minim: " << (float)(t2);
	cout << endl << t2[3]; //Show the 3th station

	Tren t5 = ++t2; //rise the last price with 10
	cout << endl << t5;
	Tren t6 = t2++; //the object t6 is created using t4, with copy constructor; after that, the last price is increased with 10


	if (t5 <= t2)
		cout << "\nIncasarile din t5 sunt mai mici sau egale decat incasarile din t2.";
	else
		cout << "\nIncasarile din t5 nu sunt mai mici sau egale decat incasarile din t2.";

	if (!t3)
		cout << "\nTrenul t3 nu are calatori.";
	else
		cout << "\nTrenul t3 are calatori.";

	cin >> t2;
	cout << t2;

	cout << endl << endl << endl;
}
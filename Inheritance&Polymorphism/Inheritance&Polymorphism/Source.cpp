#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//HAS-A      --> un biciclist are o bicicleta(sau mai multe)
class Bicicleta {
private:
	char* denumire;
	float pret;
	int dimR; //dimensiune roti
public:

	Bicicleta()
	{
		this->denumire = NULL;
		this->pret = 0;
		this->dimR = 0;
	}
	Bicicleta(const char* n, float p, int dim)
	{
		if (n != NULL)
		{
			this->denumire = new char[strlen(n) + 1];
			strcpy(this->denumire, n);
		}
		else this->denumire = NULL;
		this->pret = p;
		this->dimR = dim;
	}
	Bicicleta(const Bicicleta& b)
	{
		if (b.denumire != NULL)
		{
			this->denumire = new char[strlen(b.denumire) + 1];
			strcpy(this->denumire, b.denumire);
		}
		else this->denumire = NULL;
		this->pret = b.pret;
		this->dimR = b.dimR;
	}
	Bicicleta& operator=(const Bicicleta& b)
	{
		if (this->denumire != NULL)
			this->denumire = NULL;
		if (b.denumire != NULL)
		{
			this->denumire = new char[strlen(b.denumire) + 1];
			strcpy(this->denumire, b.denumire);
		}
		else this->denumire = NULL;
		this->pret = b.pret;
		this->dimR = b.dimR;

		return *this;
	}

	~Bicicleta()
	{
		if (this->denumire != NULL)
			delete[] this->denumire;
	}

	friend ostream& operator<<(ostream& out, const Bicicleta& b)
	{

		if (b.denumire != NULL)
			out << "\nDenumire: " << b.denumire;
		else out << "---";
		out << "\nPret: " << b.pret;
		out << "\nDim roti: " << b.dimR;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Bicicleta& b)
	{
		char buffer[20];
		in.getline(buffer, 20);
		delete[] b.denumire;
		b.denumire = new char[strlen(buffer) + 1];
		strcpy(b.denumire, buffer);
		in >> b.pret;
		in >> b.dimR;
		return in;
	}

	void writeToBinFile(fstream& f)
	{
		int lg = strlen(this->denumire) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->denumire, lg);
		f.write((char*)&this->pret, sizeof(float));
		f.write((char*)&this->dimR, sizeof(int));

	}
	void readFromBinFile(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		if (this->denumire != NULL)
			this->denumire = NULL;
		this->denumire = new char[lg];
		f.read(this->denumire, lg);
		f.read((char*)&this->pret, sizeof(float));
		f.read((char*)&this->dimR, sizeof(int));
	}

};

//clasa "container"
class Biciclist {
private:
	char* nume;
	int varsta;
	int nrBiciclete;
	Bicicleta** listaBiciclete;
public:
	Biciclist()
	{
		this->nume = NULL;
		this->varsta = 0;
		this->nrBiciclete = 0;
		this->listaBiciclete = NULL;
	}
	Biciclist(const char* n, int v, int nrB, Bicicleta** listaB)
	{
		if (n != NULL)
		{
			this->nume = new char[strlen(n) + 1];
			strcpy(this->nume, n);
		}
		else this->nume = NULL;
		this->varsta = v;
		this->nrBiciclete = nrB;
		if (listaB != NULL)
		{
			this->listaBiciclete = new Bicicleta*[this->nrBiciclete];
			for (int i = 0; i < this->nrBiciclete; i++)
				this->listaBiciclete[i] = new Bicicleta(*listaB[i]);
		}
		else this->listaBiciclete = NULL;
	}
	Biciclist(const Biciclist& b)
	{
		if (b.nume != NULL)
		{
			this->nume = new char[strlen(b.nume) + 1];
			strcpy(this->nume, b.nume);
		}
		else this->nume = NULL;
		this->varsta = b.varsta;
		this->nrBiciclete = b.nrBiciclete;
		if (b.listaBiciclete != NULL)
		{
			this->listaBiciclete = new Bicicleta*[this->nrBiciclete];
			for (int i = 0; i < this->nrBiciclete; i++)
				this->listaBiciclete[i] = new Bicicleta(*b.listaBiciclete[i]);
		}
		else this->listaBiciclete = NULL;
	}
	Biciclist& operator=(const Biciclist& b)
	{
		if (this->nume != NULL)
			this->nume = NULL;
		if (b.nume != NULL)
		{
			this->nume = new char[strlen(b.nume) + 1];
			strcpy(this->nume, b.nume);
		}
		else this->nume = NULL;
		this->varsta = b.varsta;
		this->nrBiciclete = b.nrBiciclete;
		if (this->listaBiciclete != NULL)
			delete[] this->listaBiciclete;
		if (b.listaBiciclete != NULL)
		{
			this->listaBiciclete = new Bicicleta*[this->nrBiciclete];
			for (int i = 0; i < this->nrBiciclete; i++)
				this->listaBiciclete[i] = new Bicicleta(*b.listaBiciclete[i]);
		}
		else this->listaBiciclete = NULL;

		return *this;
	}

	void writeToBinFile(fstream& f)
	{
		if (f.is_open())
		{
			int lg;
			lg = strlen(this->nume) + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(this->nume, lg);
			f.write((char*)&this->varsta, sizeof(int));
			f.write((char*)&this->nrBiciclete, sizeof(int));
		}
		else cout << "Eroare deschidere fisier";
	}

	void readFromBinFile(fstream& f)
	{
		if (f.is_open())
		{
			int lg;
			f.read((char*)&lg, sizeof(int));
			if (this->nume != NULL) this->nume = NULL;
			this->nume = new char[lg];
			f.read(this->nume, lg);
			f.read((char*)&this->varsta, sizeof(int));
			f.read((char*)&this->nrBiciclete, sizeof(int));

		}
		else cout << "Eroare deschidere fisier";
	}

	~Biciclist()
	{
		if (this->nume != NULL)
			delete[] this->nume;
		if (this->listaBiciclete != NULL)
		{
			for (int i = 0; i < this->nrBiciclete; i++)
				delete this->listaBiciclete[i];
			delete[] this->listaBiciclete;
		}
	}

	friend ostream& operator<<(ostream& out, const Biciclist& b)\
	{
		out << "\nNume: " << b.nume;
		out << "\nVarsta: " << b.varsta;
		out << "\nNr biciclete: " << b.nrBiciclete;
		if (b.listaBiciclete != NULL)
		{
			out << "\n\nBiciclistul detine urmatoarele biciclete: ";
			for (int i = 0; i < b.nrBiciclete; i++)
			{
				out << "\nB" << i + 1 << ":";
				out << *b.listaBiciclete[i];
			}
		}
		return out;
	}



};

//IS-A          --> un autoturism este autovehciul. un autobuz este autovehicul. 
class Utilizabil {
public:
	virtual void writeInfo(fstream& file) = 0;
	virtual void readInfo(fstream& file) = 0;
	virtual void toTextFile(ofstream& file) = 0;
	virtual void fromTextFile(ifstream& file) = 0;
};

class Autovehicul :public Utilizabil {
protected:
	int an_fabricatie = 0;
	int total_km_parcursi = 0;
	int nr_zile_utilizare = 0;
	float* consum = NULL; // consum pe zi (litri benzina)
public:
	Autovehicul()
	{
		//cout << "\nconstructor fara param autovehicul";
	}
	Autovehicul(int anFab, int km, int nrZ, float* c)
	{
		//cout << "\nconstructor cu parametri autovehicul";
		this->an_fabricatie = anFab;
		this->total_km_parcursi = km;
		this->nr_zile_utilizare = nrZ;
		if (c != NULL)
		{
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				this->consum[i] = c[i];
		}
		else this->consum = NULL;
	}
	Autovehicul(const Autovehicul& a)
	{
		//cout << "\nconstructor de copiere autovehicul";
		this->an_fabricatie = a.an_fabricatie;
		this->total_km_parcursi = a.total_km_parcursi;
		this->nr_zile_utilizare = a.nr_zile_utilizare;
		if (a.consum != NULL)
		{
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				this->consum[i] = a.consum[i];
		}
		else this->consum = NULL;
	}
	Autovehicul& operator=(const Autovehicul& a)
	{
		//cout << "\nop= autovehicul";
		this->an_fabricatie = a.an_fabricatie;
		this->total_km_parcursi = a.total_km_parcursi;
		this->nr_zile_utilizare = a.nr_zile_utilizare;
		if (this->consum != NULL)
			this->consum = NULL;
		if (a.consum != NULL)
		{
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				this->consum[i] = a.consum[i];
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Autovehicul& a)
	{
		out << "\nAn fabricatie: " << a.an_fabricatie;
		out << "\nTotal km: " << a.total_km_parcursi;
		out << "\nNr.zile utilizare: " << a.nr_zile_utilizare;
		out << "\nConsumul pe zile";
		if (a.consum != NULL)
			for (int i = 0; i < a.nr_zile_utilizare; i++)
				out << "\nZiua " << i + 1 << " :" << a.consum[i];
		else
			out << "---";

		return out;
	}

	~Autovehicul()
	{
		//cout << "\nDestructor autovehicul";
		if (this->consum != NULL)
			delete[] this->consum;
	}





};

class Autobuz :public Autovehicul
{
private:
	char* marca;
	int nrLocuri;

public:
	Autobuz() :Autovehicul()
	{
		//cout << "\napel constructor fara parametri autobuz";
		this->marca = NULL;
		this->nrLocuri = 0;
	}
	Autobuz(int anFab, int km, int nrZ, float* c, const char *m, int nrL) :Autovehicul(anFab, km, nrZ, c)
	{
		//cout << "\napel constructor cu parametri Autobuz";
		if (m != NULL)
		{
			this->marca = new char[strlen(m) + 1];
			strcpy(this->marca, m);
		}
		else this->marca = NULL;
		this->nrLocuri = nrL;
	}
	Autobuz(const Autobuz& a) :Autovehicul(a)
	{
		cout << "copy autobuz";
		if (a.marca != NULL)
		{
			this->marca = new char[strlen(a.marca) + 1];
			strcpy(this->marca, a.marca);
		}
		else this->marca = NULL;
		this->nrLocuri = a.nrLocuri;
	}
	Autobuz& operator=(const Autobuz& a)
	{
		cout << "op= autobuz";
		this->an_fabricatie = a.an_fabricatie;
		this->total_km_parcursi = a.total_km_parcursi;
		this->nr_zile_utilizare = a.nr_zile_utilizare;
		if (this->consum != NULL)
			this->consum = NULL;
		if (a.consum != NULL)
		{
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				this->consum[i] = a.consum[i];
		}
		else this->consum = NULL;
		if (this->marca != NULL) this->marca = NULL;
		if (a.marca != NULL)
		{
			this->marca = new char[strlen(a.marca) + 1];
			strcpy(this->marca, a.marca);
		}
		else this->marca = NULL;
		this->nrLocuri = a.nrLocuri;

		return *this;
	}
	friend ostream& operator<<(ostream& out, const Autobuz& a)
	{
		cout << "\nAn fabricatie: "; cout << a.an_fabricatie;
		cout << "\nTotal km parcursi: "; cout << a.total_km_parcursi;
		cout << "\nNr zile utilizare: "; cout << a.nr_zile_utilizare;
		cout << "\nConsumul pe zile:";
		if (a.consum != NULL)
			for (int i = 0; i < a.nr_zile_utilizare; i++)
			{
				cout << "\nZiua " << i + 1 << ": ";
				cout << a.consum[i];
			}
		if (a.marca != NULL)
			out << "\nMarca: " << a.marca;
		else out << "---";
		out << "\nNr. locuri: " << a.nrLocuri;
		return out;
	}

	void writeInfo(fstream& file)
	{
		if (file.is_open())
		{
			file.write((char*)&this->an_fabricatie, sizeof(int));
			file.write((char*)&this->total_km_parcursi, sizeof(int));
			file.write((char*)&this->nr_zile_utilizare, sizeof(int));
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				file.write((char*)&this->consum[i], sizeof(float));

			int lg = strlen(this->marca) + 1;
			file.write((char*)&lg, sizeof(int));
			file.write(this->marca, lg);

			file.write((char*)&this->nrLocuri, sizeof(int));

		}
		else cout << "\nEroare la deschidere";

	}
	void readInfo(fstream& file)
	{
		if (file.is_open()) {
			file.read((char*)&this->an_fabricatie, sizeof(int));
			file.read((char*)&this->total_km_parcursi, sizeof(int));
			file.read((char*)&this->nr_zile_utilizare, sizeof(int));
			if (this->consum != NULL)
				this->consum = NULL;
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				file.read((char*)&this->consum[i], sizeof(float));
			if (this->marca != NULL) this->marca = NULL;
			int lg;
			file.read((char*)&lg, sizeof(int));
			this->marca = new char[lg];
			file.read(this->marca, lg);
			file.read((char*)&this->nrLocuri, sizeof(int));
		}
		else cout << "Eroare deschidere fisier!";
	}

	void toTextFile(ofstream& file)
	{
		if (file.is_open())
		{
			file << "An fab: " << this->an_fabricatie;
			file << "\nTotal km: " << this->total_km_parcursi;
			file << "\nNr. zile utilizare: " << this->nr_zile_utilizare;
			file << "\nConsumul pe zile:";
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				file << "\nZiua " << i + 1 << ": " << this->consum[i];
			file << "\nMarca: " << this->marca;
			file << "\nNr.locuri: " << this->nrLocuri;

		}
		else cout << "Eroare deschidere fisier";
	}

	void fromTextFile(ifstream& file)
	{
		if (file.is_open())
		{
			file >> this->an_fabricatie;
			file >> this->total_km_parcursi;
			file >> this->nr_zile_utilizare;
			if (this->consum != NULL)
				this->consum = NULL;
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				file >> this->consum[i];
			if (this->marca != NULL) this->marca = NULL;
			char buffer[100];
			file >> buffer;
			this->marca = new char[strlen(buffer) + 1];
			strcpy(this->marca, buffer);
			file >> this->nrLocuri;

		}
		else cout << "Eroare deschidere fisier";
	}

	~Autobuz()
	{
		//cout << "\ndestructor autobuz";
		if (this->marca != NULL)
			delete[] this->marca;
	}
};

class Autoturism :public Autovehicul {
private:
	char* combustibil;
	float pret;
public:
	Autoturism() :Autovehicul()
	{
		this->combustibil = NULL;
		this->pret = 0;
	}
	Autoturism(int anFab, int km, int nrZ, float* c, const char* comb, float p) :Autovehicul(anFab, km, nrZ, c)
	{
		if (comb != NULL)
		{
			this->combustibil = new char[strlen(comb) + 1];
			strcpy(this->combustibil, comb);
		}
		else this->combustibil = NULL;
		this->pret = p;
	}
	Autoturism(const Autoturism& a) :Autovehicul(a)
	{
		cout << "copy autoturism";
		if (a.combustibil != NULL)
		{
			this->combustibil = new char[strlen(a.combustibil) + 1];
			strcpy(this->combustibil, a.combustibil);
		}
		else this->combustibil = NULL;
		this->pret = a.pret;
	}

	Autoturism& operator=(const Autoturism& a)
	{
		cout << "op= autoturism";
		this->an_fabricatie = a.an_fabricatie;
		this->total_km_parcursi = a.total_km_parcursi;
		this->nr_zile_utilizare = a.nr_zile_utilizare;
		if (this->consum != NULL)
			this->consum = NULL;
		if (a.consum != NULL)
		{
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				this->consum[i] = a.consum[i];
		}
		else this->consum = NULL;
		if (this->combustibil != NULL)
			this->combustibil = NULL;
		if (a.combustibil != NULL)
		{
			this->combustibil = new char[strlen(a.combustibil) + 1];
			strcpy(this->combustibil, a.combustibil);
		}
		else this->combustibil = NULL;
		this->pret = a.pret;

		return *this;
	}


	friend ostream& operator<<(ostream& out, const Autoturism& a)
	{
		cout << "\nAn fabricatie: "; cout << a.an_fabricatie;
		cout << "\nTotal km parcursi: "; cout << a.total_km_parcursi;
		cout << "\nNr zile utilizare: "; cout << a.nr_zile_utilizare;
		cout << "\nConsumul pe zile:";
		if (a.consum != NULL)
			for (int i = 0; i < a.nr_zile_utilizare; i++)
			{
				cout << "\nZiua " << i + 1 << ": ";
				cout << a.consum[i];
			}
		if (a.combustibil != NULL)
			out << "\nCombustibil: " << a.combustibil;
		else cout << "\nCombustibil: " << "---";
		out << "\nPret: " << a.pret;
		return out;
	}

	void writeInfo(fstream& file)
	{
		if (file.is_open())
		{
			file.write((char*)&this->an_fabricatie, sizeof(int));
			file.write((char*)&this->total_km_parcursi, sizeof(int));
			file.write((char*)&this->nr_zile_utilizare, sizeof(int));
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				file.write((char*)&this->consum[i], sizeof(float));

			int lg = strlen(this->combustibil) + 1;
			file.write((char*)&lg, sizeof(int));
			file.write(this->combustibil, lg);

			file.write((char*)&this->pret, sizeof(float));

		}
		else cout << "\nEroare la deschidere";

	}
	void readInfo(fstream& file)
	{
		file.read((char*)&this->an_fabricatie, sizeof(int));
		file.read((char*)&this->total_km_parcursi, sizeof(int));
		file.read((char*)&this->nr_zile_utilizare, sizeof(int));
		if (this->consum != NULL)
			this->consum = NULL;
		this->consum = new float[this->nr_zile_utilizare];
		for (int i = 0; i < this->nr_zile_utilizare; i++)
			file.read((char*)&this->consum[i], sizeof(float));

		if (this->combustibil != NULL) this->combustibil = NULL;
		int lg;
		file.read((char*)&lg, sizeof(int));
		this->combustibil = new char[lg];
		file.read(this->combustibil, lg);
		file.read((char*)&this->pret, sizeof(float));
	}

	void toTextFile(ofstream& file)
	{
		if (file.is_open())
		{
			file << "An fab: " << this->an_fabricatie;
			file << "\nTotal km: " << this->total_km_parcursi;
			file << "\nNr. zile utilizare: " << this->nr_zile_utilizare;
			file << "\nConsumul pe zile:";
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				file << "\nZiua " << i + 1 << ": " << this->consum[i];
			file << "\nCombustibil: " << this->combustibil;
			file << "\nPret: " << this->pret;

		}
		else cout << "\nEroare deschidere fisier";
	}

	void fromTextFile(ifstream& file)
	{
		if (file.is_open())
		{
			file >> this->an_fabricatie;
			file >> this->total_km_parcursi;
			file >> this->nr_zile_utilizare;
			if (this->consum != NULL)
				this->consum = NULL;
			this->consum = new float[this->nr_zile_utilizare];
			for (int i = 0; i < this->nr_zile_utilizare; i++)
				file >> this->consum[i];
			if (this->combustibil != NULL) this->combustibil = NULL;
			char buffer[100];
			file >> buffer;
			this->combustibil = new char[strlen(buffer) + 1];
			strcpy(this->combustibil, buffer);
			file >> this->pret;

		}
		else cout << "\nEroare deschidere fisier";
	}

	~Autoturism()
	{
		if (this->combustibil != NULL)
			delete[] this->combustibil;
	}

};



void main()
{
	//HAS-A
	Bicicleta b1 = Bicicleta("DHS", 950, 24);
	Bicicleta b2 = Bicicleta("B-Twin", 1075, 26);
	Bicicleta b3 = Bicicleta("BMX", 1500, 24);

	Bicicleta** listaBiciclete = new Bicicleta*[3];
	listaBiciclete[0] = &b1;
	listaBiciclete[1] = &b2;
	listaBiciclete[2] = &b3;

	Biciclist biker = Biciclist("Jack Smith", 30, 3, listaBiciclete);
	cout << biker;
	//scriere in fisier binar
	fstream bikerOut("biker.bin", ios::out | ios::binary);
	biker.writeToBinFile(bikerOut);
	bikerOut.close();

	//citire din fisier binar
	fstream bikerIn("biker.bin", ios::in | ios::binary);
	Biciclist biker2;
	biker2.readFromBinFile(bikerIn);
	bikerIn.close();
	cout << "\n\n biker2 citit din fisier binar: ";
	cout << biker2;

	//scriere in fisier binar
	fstream bOut("bikeOut.bin", ios::out | ios::binary);
	b1.writeToBinFile(bOut);
	bOut.close();
	////citire din fisier binar
	fstream bIn("bikeOut.bin", ios::in | ios::binary);
	Bicicleta b4;
	b4.readFromBinFile(bIn);
	bIn.close();
	cout << "\n\n b4 citit din fisier binar: ";
	cout << b4;

	//afisare in fisier text 
	ofstream bikerTxtOut("bikerOut.txt");
	bikerTxtOut << biker;

	ofstream bikeTextOut("bikeOut.txt");
	bikeTextOut << biker;
	bikerTxtOut.close();
	bikeTextOut.close();

	Bicicleta b5;
	ifstream fisTextIn("bikeIn.txt");
	fisTextIn >> b5;
	cout << "\n\n b5 citit din fisier text: ";
	cout << b4;



	//IS-A
	float cons[] = { 12,10,25,30 };
	float cons2[] = { 20,40,35 };
	float cons3[] = { 30,15 };

	Autobuz ab1(2005, 12000, 3, cons2, "Mercedes", 16);
	Autobuz ab2(2015, 5250, 2, cons3, "Volkswagen", 20);
	Autoturism at1(2010, 7500, 4, cons, "motorina", 9900);
	Autoturism at2(2005, 67500, 3, cons2, "benzina", 6500);

	//Exemplificare virtualizare + scriere/citire in/din fisier binar
	Autovehicul* listaAuto[4];
	listaAuto[0] = &ab1; // autobuz
	listaAuto[1] = &ab2; //autobuz
	listaAuto[2] = &at1; //autoturism
	listaAuto[3] = &at2; //autoturism

	//clasa Autobuz
	cout << "\n\n";
	fstream fileAutobuz("autobuz.bin", ios::out | ios::binary);
	listaAuto[0]->writeInfo(fileAutobuz);
	fileAutobuz.close();

	fileAutobuz.open("autobuz.bin", ios::in | ios::binary);
	ab2.readInfo(fileAutobuz);
	fileAutobuz.close();
	cout << ab2;

	//clasa Autoturism
	cout << "\n\n";
	fstream fileAutoturism("autoturism.bin", ios::out | ios::binary);
	listaAuto[2]->writeInfo(fileAutoturism);
	fileAutoturism.close();

	fileAutoturism.open("autoturism.bin", ios::in | ios::binary);
	at2.readInfo(fileAutoturism);
	fileAutoturism.close();
	cout << at2;

	cout << "\n\n";

	//Citire/scriere - fisier text
	//Autobuz
	ofstream autobuzOut("autobuzOut.txt");
	listaAuto[0]->toTextFile(autobuzOut);
	autobuzOut.close();


	/* Continut autobuzIn.txt:
		2003
		13462
		3
		25
		14
		37
		Volvo
		25
	*/
	ifstream autobuzIn("autobuzIn.txt");
	Autobuz ab3;
	ab3.fromTextFile(autobuzIn);
	cout << ab3;
	//Autoturism
	ofstream autoturismOut("autoturismOut.txt");
	listaAuto[3]->toTextFile(autoturismOut);
	autoturismOut.close();

	/* Continut autoturismIn.txt:
	1985
	125000
	3
	21
	35
	30
	BMW
	5
	*/
	ifstream autoturismIn("autoturismIn.txt");
	Autoturism at3;
	at3.fromTextFile(autoturismIn);
	cout << at3;


}
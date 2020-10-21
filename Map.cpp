#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int adunare(int a, int b)
{
	return a * b;
}

bool compara(int a, int b)
{
	return a > b; // daca pun < sortez crescator
}

void main()
{
	vector <int> v; // include vector
	v.push_back(20);
	v.push_back(10);
	v.push_back(60);
	v.push_back(40);

	sort(v.begin(), v.end()); //include algorithm

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	sort(v.begin(), v.end(),compara); //include algorithm
	cout << endl << endl;

	vector<int>::iterator i;
	for (i = v.begin(); i != v.end(); i++)
	{
		cout << *i << " ";
	}

	cout << endl << endl;

	int suma = accumulate(v.begin(), v.end(), 1, adunare); //include numeric
	cout << suma << endl;

	map<string, string> dictionar; //include map;
	dictionar.insert(pair<string, string>("multumesc", "sucran"));
	dictionar.insert(pair<string, string>("casa", "bet"));
	dictionar.insert(pair<string, string>("salut", "merhaba"));

	cout << dictionar["multumesc"] << endl;

	map<string, string>::iterator it;

	it = dictionar.begin();
	while (it != dictionar.end())
	{
		cout << it->first << " - " << it->second << endl;
		it++;
	}
}
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<iterator>
#include <queue>
using namespace std;

const int UN = 1;
const int UN_FIXE = 10;//correspond à un 1 vide
const int ZERO = 0;
const int ZERO_FIXE = 100;//correspond à un 0 vide
const int NUL = -1;//correspond à une case vide

bool verifierSiUnsEgalZeros(vector<int> v)
{
	return count(v.begin(), v.end(), UN) + count(v.begin(), v.end(), UN_FIXE) 
	== count(v.begin(), v.end(), ZERO) + count(v.begin(), v.end(), ZERO_FIXE);
}



string vectorToString(vector<int> v)
{
	stringstream ss;
	copy(v.begin(), v.end(), ostream_iterator<int>(ss, ""));
	return ss.str();
}

bool verifierSymbolesDeSuite(vector<int> v)
{
	if (verifierSiUnsEgalZeros(v))
	{
		size_t unsDeSuite = vectorToString(v).find("111");
		size_t zerosDeSuite = vectorToString(v).find("000");
		if (unsDeSuite != string::npos || zerosDeSuite != string::npos)
			return false;
		else
			return true;
	}
	else
		return false;
}

vector<int> stringToVectorOfInt(string str)
{
	vector<int> v;

	for (size_t i = 0; i < str.size(); ++i)
	{                                 
		v.push_back(str[i] - '0');
	}
		

	return v;
}

// This function uses queue data structure to print binary numbers
void generatePrintBinary(int n)
{
	// Create an empty queue of strings
	queue<string> q;

	// Enqueue the first binary number
	q.push("1");

	// This loops is like BFS of a tree with 1 as root
	// 0 as left child and 1 as right child and so on
	while (n--)
	{
		// print the front of queue
		string s1 = q.front();
		q.pop();
		if(s1.length() == 10 && verifierSymbolesDeSuite(stringToVectorOfInt(s1)))
			std::cout << s1 << "\n";

		string s2 = s1;  // Store s1 before changing it

						 // Append "0" to s1 and enqueue it
		q.push(s1.append("0"));

		// Append "1" to s2 and enqueue it. Note that s2 contains
		// the previous front
		q.push(s2.append("1"));
	}
}



int main()
{
	//vector<int> v = { 0,0,0,0,0,1,1,1,1,1 };
	//string str("1101001");
	//vector<int> v = stringToVectorOfInt(str);
	//for (int i = 0; i < 4; i++)
		//cout << v[i] << endl;
	//cout << verifierSiUnsEgalZeros(v) << endl;
	//cout << vectorToString(v) << endl;
	//cout << verifierSymbolesDeSuite(v) << endl;
	int n = 868;
	generatePrintBinary(n);

	//int i = std::stoi("1101100100", nullptr, 2);
	//cout << i << endl;
	system("pause");
}




#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

#define ulong  unsigned long 

ulong getRandom()
{
	srand(time(NULL));
	return (ulong)rand();
}
ulong gcd(ulong a, ulong b)
{
	ulong tmp;
	while (b != 0)
	{
		tmp = a;
		a = b;
		b = tmp % a;
	}
	return a;
}

ulong calculateE(ulong z)
{
	ulong i = 100000 + (getRandom() % 10000000);
	for(; i < 10000000; ++i)
		if(gcd(i, z) == 1) return i;
	throw string("Could not calculate encryption key.\n");
}
ulong calculateD(ulong z, ulong e)
{
	ulong i = 100000 + (getRandom() % 10000000);
	for(; i < 10000000; ++i)
		if(e != i && ((e * i) % z) == 1) return i;
	throw string("Could not calculate value of decryption key.\n");
}
ulong convert(ulong m, ulong p, ulong n)
{
	ulong t = 1;
	for(int i=0;i<p;++i)
	{
		t = t * m;
		t %= n;
	}
	return (t % n);
}
int main()
{
	ulong p, q, n, z, e, d;
	cout << "Enter p and q such that (p * q) > 128: " << endl;
	cin >> p >> q;

	n = p * q;
	z = (p - 1) * (q - 1);
	
	try { e = calculateE(z); }
	catch(string s) { cout << s; return 0; }
	cout << "E = " << e << endl;

	try { d = calculateD(z, e); }
	catch(string s) { cout << s; return 0; }
	cout << "D = " << d << endl;

	cout << "N = " << n << endl;
	cout << "Z = " << z << endl;	

	string s;	
	cout << "Enter the message: ";
	cin >> s;

	vector<ulong> plain;
	vector<ulong> cipher;

	cout << "PLAIN TEXT" << endl;
	for(int i=0 ;i<s.length(); ++i)
	{
		plain.push_back((ulong)(s.at(i))); 
		cout << plain.at(i) << endl;
		cipher.push_back(convert(plain.at(i), e, n)); 
	}

	cout << "CIPHER TEXT" << endl;
	for(int i=0 ;i<s.length(); ++i)
		cout << cipher.at(i) << endl;	
	
	cout << "DECRYPTED TEXT" << endl;
	for(int i=0 ;i<s.length(); ++i)
	{
		ulong tmp = convert(cipher.at(i), d, n);
		cout << tmp << endl;
	}
}

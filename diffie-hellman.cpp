#include <iostream>

using namespace std;

long power(long a, long b, long mod)
{
	long result = a;
	for(long i = 0; i < b - 1; ++i)
	{
		result *= a;
		result %= mod;
	}
	return result % mod;
}

int main()
{
	long g, p;
	cout << "\nEnter values of p and g: ";
	cin >> g >> p;

	cout << "\nEnter secret for A: ";
	long a; cin >> a;

	cout << "\nEnter secret for B: ";
	long b; cin >> b;

	long A;
	A = power(g, a, p) % p;

	long B;
	B = power(g, b, p) % p;

	cout << "\nPublic keys calculated.";
	cout << "\nFor A: " << A;
	cout << "\nFor B: " << B;

	cout << "\nExchanged public keys. Calculate shared secret. ";

	long sA = power(g, B, p) % p; 
	long sB = power(g, A, p) % p;

	if(sA == sB) 
		cout << "\nExchanged shared secret: " << sA;
	else cout << "\nKey exchange failed.";
}

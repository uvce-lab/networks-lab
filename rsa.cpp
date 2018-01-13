#define VERBOSE

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <limits.h>
#include <tuple>
#include <time.h>

using namespace std;

void demo(string);

class Utilities
{
public:
	//Calculate greatest common divisor of a and b
    static long gcd (long a, long b)
    {
        unsigned int tmp;
        while (b != 0) {
            tmp = a;
            a = b;
            b = tmp % b;
        }
        return a;
    }

	//Convert provided vector to a string, for easy printing
    static string longVectorToString(vector<long>* data)
    {
        stringstream buffer;
        auto size = data->size();
        for(int i=0;i<size; ++i)
            buffer << (char)(data->at(i) % 128) << ' ';
        return buffer.str();
    }

	//Convert string to a vector of long elements, for encrypting.
    static vector<long>* stringToLongVector(string str)
    {
        vector<long>* res = new vector<long>();
        for(int i=0;i<str.size();++i)
            res->push_back((long)abs(str.at(i)));
        return res;
    }
};

//Rivest, Shamir and Adleman Cryptosystem
class RSA
{
	long P, Q, N, Z, E, D, max;

	//Generate prime numbers upto n
    vector<long>* _sieveOfEratosthenes(long n)
    {
        vector<long> *primes = new vector<long>();
        long up = (long)sqrt(n);
        bool *isComposite = new bool[n + 1];
        memset(isComposite, 0, sizeof(bool) * (n + 1));
        for (long m = 2; m <= up; m++)
        {
            if (!isComposite[m])
            {  
                for (long k = m; k <= n; k += m)
                    isComposite[k] = true;
            }
        }
        for (long m = 2; m <= n; m++)
            if (!isComposite[m])
                primes->push_back(m);
        return primes;
    }

	//Choose two prime numbers from the provided values
    tuple<long, long> _choosePQ(vector<long>* primes)
    {
        long a, b;
        long s = primes->size();
        do
        {
            a = (s/4) + rand() % (s/4);
            b = (s/4) + rand() % (s/4);
        }   while(a == b);
        return tuple<long, long>(primes->at(a), primes->at(b));
    }

	//Choose suitable value of E as coprime to Z
    long _chooseE()
    {
        for(int i = (INT_MAX / 64); i >= 2 ; --i)
        {
            if (Utilities::gcd(i, Z) == 1) return i;
        }
        //Could not find valid value for E
        throw exception();
    }

	//Choose suitable value of D as E*D = 1 (mod Z)
    long _chooseD()
    {
        for(long i = 2; i < (INT_MAX / 64); ++i)
        {
            if ((E * i) % Z == 1)
                return i;
        }
        //Could not find valid value for D
        throw exception();
    }
    
	//Encrypt a single value
    long _encrypt(long ch)
    { return _powerMod(ch, E, N); }
    
	//Decrypt a single value
    long _decrypt(long ch)
    { return _powerMod(ch, D, N); }

    //Calculate a raised to b modulo c
    long _powerMod(long a, long b, long c)
    {
        #ifdef VERBOSE
            cout << "Calculating... " << a << " ^ " << b << " % " << c;
			fflush(stdout);
        #endif

        long res = 1;
        for(int i=0;i<b; ++i)
        {
            res = res * a;
            res %= c;
        }
		res %= c;

		#ifdef VERBOSE
			cout << " = " << res << endl;
		#endif
        return res;
    }   
	
	//Calculate values of P, Q, N, Z, E and D
	bool _calculateValues()
	{
		try
		{
			srand(time(NULL));
			this->max = 20000 + rand() % 5000;
			auto primes = this->_sieveOfEratosthenes(max);
			auto pq = this->_choosePQ(primes);
			P = std::get<0>(pq);
			Q = std::get<1>(pq);
			N = P * Q;
			Z = (P - 1) * (Q - 1);

			E = this->_chooseE();
			D = this->_chooseD();
			delete primes;
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
public:
    RSA()
    {
		bool calculated = false;
		do {
			calculated = _calculateValues();
		} while (!calculated);

        #ifdef VERBOSE
        cout << "Calculated Values:\nP = " << P << "\nQ = " << Q << "\nE = " << E << "\nN = " << N << " \nD = " << D << "\nZ = " << Z <<endl;
        #endif
    }
    vector<long>* encrypt(vector<long>* plain)
    {
        vector<long>* cipher = new vector<long>();
        for (int i=0;i<plain->size(); ++i)
            cipher->push_back(_encrypt(plain->at(i)));
        return cipher;
    }
    vector<long>* decrypt(vector<long>* cipher)
    {
        vector<long>* plain = new vector<long>();
        for (int i=0;i<cipher->size(); ++i)
            plain->push_back(_decrypt(cipher->at(i)));
        return plain;
    }
};

void demo(string message)
{
    RSA encrypter;
    
    auto plain = Utilities::stringToLongVector(message);
    cout << "Original text: " << Utilities::longVectorToString(plain) << endl;
    
    auto cipher = encrypter.encrypt(plain);
    cout << "Encrypted text: " << Utilities::longVectorToString(cipher) << endl;
    
    auto decrypted = encrypter.decrypt(cipher);
    cout << "Decrypted text: " << Utilities::longVectorToString(decrypted) << endl;
}

int main()
{
    string message;
    cout << "Enter the message: ";
    getline(cin, message);
    demo(message);
}
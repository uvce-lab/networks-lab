#define VERBOSE

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

class BitArray
{
    vector<bool> *_data;
    int size;

  public:
    BitArray(int size)
    {
        this->_data = new vector<bool>(size, 0);
        this->size = size;
    }

    BitArray(const string &str)
    {
        auto size = str.length();

        for (int i = 0; i < size; ++i)
            if (str[i] != '1' && str[i] != '0')
                throw "invalid character in bitstring";

        this->size = str.length();
        this->_data = new vector<bool>();

        for (int i = 0; i < str.length(); ++i)
            _data->push_back((str[i] == '1'));
    }

    BitArray(const BitArray &bitArray)
    {
        this->size = bitArray.size;
        this->_data = new vector<bool>();

        for (int i = 0; i < size; ++i)
            _data->push_back(bitArray._data->at(i));
    }

    void Append(BitArray other)
    {
        for (int i = 0; i < other.size; ++i)
            _data->push_back(other._data->at(i));
        size += other.size;
    }

    BitArray Last(int bits)
    {
        if (bits > size)
            throw "number of bits requested is larger than the size of the bitarray";

        BitArray result(0);
        result.size = bits;

        for (int i = size - bits, j = 0; j < bits; ++i, ++j)
            result._data->push_back(this->_data->at(i));
        return result;
    }

    friend ostream &operator<<(ostream &os, const BitArray &b)
    {
        for (int i = 0; i < b.size; ++i)
            os << (b._data->at(i) ? '1' : '0');
        return os;
    }

    friend BitArray operator/(const BitArray &dividend, const BitArray &divisor)
    {
        if (divisor.size > dividend.size)
            throw "divided's length cannot be less than divisor's";

#ifdef VERBOSE
        cout << "\n\nCALCULATE: "
             << dividend << " / " << divisor << endl;
#endif

        BitArray num(dividend);
        const BitArray empty(divisor.size);

#ifdef VERBOSE
        cout << num << endl;
#endif

        for (int i = 0; i <= (dividend.size - divisor.size); ++i)
        {
            auto div = (num._data->at(i) ? &divisor : &empty);

            for (int j = 0; j < divisor.size; ++j)
                num._data->at(i + j) = num._data->at(i + j) ^ (*div)._data->at(j);

#ifdef VERBOSE
            for (int k = 0; k < i; ++k)
                cout << ' ';
            cout << (*div) << endl;
            cout << num << endl;
#endif
        }

#ifdef VERBOSE
        cout << "\n\n";
#endif
        return num.Last(divisor.size - 1);
    }

    std::string toString()
    {
        std::stringstream ss;
        for (auto i = _data->begin(); i != _data->end(); ++i)
            ss << (*i ? '1' : '0');
        return ss.str();
    }
};

class CRC_CCITT
{
  public:
    static BitArray generate(BitArray data)
    {
        BitArray divisor(string("10001000000100001"));
        data.Append(BitArray(16));
        return data / divisor;
    }
};

int main()
{
    string bits;
    cout << "Enter the data bits: ";
    cin >> bits;

    auto data = BitArray(bits);
    auto crc = CRC_CCITT::generate(data);
    data.Append(crc);
    cout << "CRC at sender: " << crc << endl;
    cout << "Data to be sent: " << data << endl;

    cout << "\nReceived data: " << data << endl;
    cout << "CRC at receiver: " << CRC_CCITT::generate(BitArray(data)) << endl;
}
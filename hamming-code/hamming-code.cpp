#include <stdio.h>
#include <iostream>
#include <vector>

#include <string.h>
#include <stdlib.h>

using namespace std;

vector<int> fixError(vector<int> d)
{
    int t1 = (d[1] + d[3] + d[5] + d[7] + d[9] + d[11]) % 2;
    int t2 = (d[2] + d[3] + d[6] + d[7] + d[10] + d[11]) % 2;
    int t4 = (d[4] + d[5] + d[6] + d[7]) % 2;
    int t8 = (d[8] + d[9] + d[10] + d[11]) % 2;

    int errorPosition = 8 * t8 + 4 * t4 + 2 * t2 + t1;

    cout << "Error discovered at position: " << errorPosition;

    d[errorPosition] = d[errorPosition] == 1 ? 0 : 1;
    return d;
}

vector<int> hammingCode(vector<int> d)
{
    d[1] = (d[3] + d[5] + d[7] + d[9] + d[11]) % 2;
    d[2] = (d[3] + d[6] + d[7] + d[10] + d[11]) % 2;
    d[4] = (d[5] + d[6] + d[7]) % 2;
    d[8] = (d[9] + d[10] + d[11]) % 2;
    return d;
}

vector<int> introduceError(vector<int> d, int position)
{
    if (position >= 1 && position <= 11)
        d[position] = d[position] == 1 ? 0 : 1;
    return d;
}

vector<int> initializeCode(char *data)
{
    if (strlen(data) != 7)
    {
        printf("Enter 7 databits.");
        exit(0);
    }

    vector<int> d(12, 0);
    for (int i = 1, j = 0; i < 12; ++i)
        if (i == 3 || i == 5 || i == 6 || i == 7 || i == 9 || i == 10 || i == 11)
        {
            d[i] = data[j++] - '0';
            if (d[i] < 0 || d[i] > 1)
            {
                printf("Input contains invalid data.");
                exit(0);
            }
        }
    return d;
}

void printCode(vector<int> bits)
{
    for (int i = 1; i < 12; ++i)
        cout << bits[i];
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <d-bits (P P _ P _ _ _ P _ _ _ _)>\n", argv[0]);
        return 0;
    }

    vector<int> code = initializeCode(argv[1]);

    code = hammingCode(code);
    cout << endl
         << "Bits: ";
    printCode(code);

    cout << "\nEnter position to introduce error: (-1 to skip) ";
    int choice;
    cin >> choice;

    if (choice < 1 && choice > 11)
    {
        cout << "Invalid position.\n";
    }
    else if (choice != -1)
    {
        code = introduceError(code, choice);

        cout << "Code now is: ";
        printCode(code);
        cout << '\n';

        code = fixError(code);
        cout << "\nFixed code: ";
        printCode(code);
    }
}
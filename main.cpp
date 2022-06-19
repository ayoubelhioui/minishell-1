#include <iostream>

using namespace std;

int main()
{
    int n, i = 0;
    cin >> n;
    while (i < n)
    {
        if (i == 0 && i == n - 1)
            cout << "i hate it";
        else if (i == 0 && i != n - 1)
            cout << "i hate that ";
        else if (i == n - 1)
        {
            if (i % 2 == 0)
                cout << "i hate it";
            else 
                cout << "i love it";
        }
        else
        {
            if (i % 2 == 0)
                cout << "i hate that ";
            else
                cout << "i love that ";
        }
        i++;
    }
}
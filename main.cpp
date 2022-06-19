#include <iostream>
#include <vector>
using namespace std;
int find_position(vector <int> &vec, int a, int length)
{
    int i = 0;
    int sum  = 0;
    while (sum < a)
    {
        if (vec[i] > vec[i + 1])
        {
            i++;
            sum++;
        }
        else if (vec[i] == vec[i + 1])
        {
            sum++;
            while (vec[i] == vec[i + 1])
                i++;
        }
    }
    return (i);
}
int main()
{
    int sum = 0, a, b, i = 0;
    cin >> a >> b;
    vector<int> vec(a);
    while (i < a)
    {
        cin >> vec[i];
        i++;
    }
    i = 0;
    if (a < 5)
    {
        while (i < a)
        {
            if (vec[i] > 0)
                sum++;
            i++;
        }
        cout << sum << endl;
        return 0;
    }
    int k = find_position(vec, b, a);
    cout << k << endl;
}
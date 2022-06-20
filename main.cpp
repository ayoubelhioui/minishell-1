    #include <iostream>
    #include <vector>
    using namespace std;
int solve_it(int start_pos, int jumps_number)
{
    int n = 1;
    while (jumps_number > 0)
    {
        if (start_pos % 2 == 0)
        {
            start_pos -= n;
        }
        else
        {
            start_pos += n;
        }
        n++;
        jumps_number--;
    }
    return (start_pos);
}
int main()
{
    int test_cases;
    cin >> test_cases;
    int i = 0;
    while (i < test_cases)
    {
        int start_pos, jumps_number;
        cin >> start_pos >> jumps_number;
        cout<< solve_it(start_pos, jumps_number) << endl;
        i++;
    }
}
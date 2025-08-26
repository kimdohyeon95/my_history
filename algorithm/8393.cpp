#include <iostream>

using namespace std;

int main()
{
    int sum = 0, cnt = 0;
    
    cin >> cnt;

    for ( int i = 1; i <= cnt; i++)
    {
        sum += i;
    }

    cout << sum << endl;

    return 0;
}
#include <iostream>

using namespace std;

int main()
{
    int floor = 0;

    cin >> floor;

    for( int i = 0; i < floor; i++ )
    {
        for( int k = i; k < ( floor - 1 ); k++ )
        {
            cout << " ";
        }

        for( int k = 0; k < ( 2*i + 1); k++)
        {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
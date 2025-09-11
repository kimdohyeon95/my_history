#include <iostream>

using namespace std;

int main()
{
    int floor = 0, m = 0, s = 0, mul = 1;

    cin >> floor; 

    for( int i = 1; i <= (floor * 2) - 1; i++ )
    {
        if( i > floor) 
        {
            m = i - (2*mul);
            mul += 1;
        } 
        else 
        {
            m = i;
        }

        s = floor - m;

        for( int j = 0; j < s; j++ )
            cout << " ";
        for( int j = 0; j < m; j++)
            cout << "*";        
        cout << endl;
    }
    return 0;
}
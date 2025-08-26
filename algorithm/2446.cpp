#include <iostream>

using namespace std;

int main()
{
    int floor = 0, m = 0, s = 0, mul = 1, re_floor = 0;

    cin >> floor; 

    for( int i = 1; i <= (floor * 2) - 1; i++ )
    {
        if( i > floor) 
        {
            re_floor = i - 2*mul;            
            mul += 1;
        } 
        else 
        {
            re_floor = i;
        }

        s = re_floor - 1;
        m = 2*floor - (2*re_floor - 1);

        for( int j = 0; j < s; j++ )
            cout << " ";
        
        for( int j = 0; j < m; j++)
            cout << "*";        
        cout << endl;
    }
    return 0;
}
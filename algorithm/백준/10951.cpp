#include <iostream>

using namespace std;

int main()
{
    int a, b;

    // eof() is 
    while(!(cin >> a >> b).eof())
    {
        if ( ( a > 0 && a < 10 ) && ( b > 0 && b < 10 ) )
        {
            cout << a + b;   
        }    
    }
    
    return 0;

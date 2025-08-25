#include <iostream>

using namespace std;

int main()
{
    int a, b;

    while(true)
    {
        cin >> a >> b;
        
        if ( ( a > 0 && a < 10 ) && ( b > 0 && b < 10 ) )
        {
            cout << a + b << endl;   
        }
        else if( a == 0 && b == 0 )
        {
            break;
        }    
    }
    
    return 0;
}
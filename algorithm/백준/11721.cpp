#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string input_str = "";

    cin >> input_str;

    int length = input_str.length();
    
    for( int i = 0; i < length; i++)
    {
        cout << input_str[i]; 

        if ( i % 10 == 9 && i != 0 )
        {
            cout << endl;
        }
    }

    return 0;
}
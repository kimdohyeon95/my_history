#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int str_length = 0;
    string input_str;

    while(true)
    {
        getline( cin, input_str );

        if ( input_str == "" )
            break;
        
        cout << input_str << endl;
    }  
    
    return 0;
}
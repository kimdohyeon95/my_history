#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int str_length = 0;
    string input_str;

    while(getline( cin, input_str ))
    {
        cout << input_str << endl;
    }  
    
    return 0;
}
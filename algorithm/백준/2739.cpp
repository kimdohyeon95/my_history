#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int num = 0; 

    cin >> num; 

    for( int i = 1; i <= 9; i++)
    {
        cout << num << " * " << i << " = " << num * i << endl; 
    }

    return 0;
}
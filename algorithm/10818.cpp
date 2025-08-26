#include <iostream>

using namespace std;

int main()
{
    int t, num, max = -1000000, min = 1000000;

    scanf("%d", &t);

    for( int i = 0; i < t; i++ )
    {
        scanf("%d", &num);
        
        if( num > max ) max = num;
        if( num < min ) min = num;
    }   

    cout << min << " " << max << endl;

    return 0;
}
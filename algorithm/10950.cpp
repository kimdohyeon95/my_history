#include <iostream>

using namespace std;

int main()
{
    int test_num; 

    cin >> test_num;

    int* a = new int[test_num];
    int* b = new int[test_num];
        
    for( int i = 0; i < test_num; i++)
    {
        cin >> a[i] >> b[i];
    }

    for( int i = 0; i < test_num; i++)
    {
        if ( ( a[i] > 0 && a[i] < 10 ) && ( b[i] > 0 && b[i] < 10 ) )
        {
            cout << a[i] + b[i] << endl;   
        }    
    }
    
    delete[] a;
    delete[] b;
    
    return 0;
}
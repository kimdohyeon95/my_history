#include <iostream>

using namespace std;

int main()
{
    int test_num, act_cnt = 0, a, b; 
    char comma;

    cin >> test_num;

    while( act_cnt < test_num )
    {
        act_cnt++;

        cin >> a >> comma >> b;

        if ( ( a > 0 && a < 10 ) && ( b > 0 && b < 10 ) )
        {
            cout << a + b << endl;   
        }        
    }
    
    return 0;
}
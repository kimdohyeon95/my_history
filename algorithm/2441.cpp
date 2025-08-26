#include <iostream>

using namespace std;

int main()
{
   int num = 0;
   
   cin >> num; 

   for( int i = 0; i < num; i++)
   {
        for( int k = 0; k < i; k++)
        {
            cout << " ";
        }
        
        for( int k = i; k < num; k++ )
        {
            cout << "*";
        }

        
        cout << endl;
   }
    return 0;
}
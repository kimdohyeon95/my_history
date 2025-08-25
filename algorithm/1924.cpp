#include <iostream>

using namespace std;

int main()
{
    int month, day, sum_day = 0, date = 0;
    int day_array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    cin >> month >> day; 

    for ( int i = 0; i <  ( month - 1 ) ; i++ )
        sum_day += day_array[i];
    
    sum_day += day; 

    date = sum_day % 7;
    
    switch (date)
    {
    case 0:
        {
            cout << "SUN";
        }
        break;
    case 1:
        {
            cout << "MON";
        }
        break;
    case 2:
        {
            cout << "TUE";
        }
        break;
    case 3:
        {
            cout << "WED";
        }
        break;
    case 4:
        {
            cout << "THU";
        }
        break;
    case 5:
        {
            cout << "FRI";
        }
        break;
    case 6:
        {
            cout << "SAT";
        }
        break;

    default:
        break;
    }

    return 0;
}
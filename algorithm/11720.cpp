#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string input_str = "";
    int cnt = 0, sum = 0, input_num = 0;

    cin >> input_num;
    cin >> input_str;

    int buff_size = input_str.length();

    while( cnt < buff_size )
    {
        int num = input_str[cnt] - '0';
        
        sum += num;
        cnt++;
    }

    cout << sum << endl;

    return 0; 
}
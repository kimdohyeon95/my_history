#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int input_num = 0;

    scanf("%d", &input_num);
    for ( int i = input_num; i >= 1; i-- )
        printf("%d\n", i);


    return 0;
}
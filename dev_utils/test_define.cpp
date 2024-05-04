#include <iostream>
using namespace std;

#define STR(var) #var
#define PRINT(var) cout << STR(var) << endl

int main()
{
    int a = 0;
    PRINT(a);
    PRINT(a + 1);
    PRINT(a + 2);
    PRINT(a + 3);
    PRINT(a + 4);
    return 0;
}
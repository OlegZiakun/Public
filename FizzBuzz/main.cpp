#include <iostream>

using namespace std;

int main()
{
    auto print = [] (const bool is, const string& str) -> string { return is ? str : string(); };

    for (int i = 1; i < 50; ++i)
        cout << "i:" << i << " " << print(!(i%3), "Fizz") + print(!(i%5), "Buzz") << endl;

    return 0;
}

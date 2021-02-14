/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Jan 2021 10:46:25 PM PST
 ************************************************************************/

#include <ctime>
#include <iostream>
 
int main()
{
    std::time_t result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&result))
              << result << " seconds since the Epoch\n";
}

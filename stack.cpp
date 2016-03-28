#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

int main()
{
    stack<int> s;
    printf("stack\n");
    printf("option\ttop\tsize\n");
    s.push(12);
    printf("%d\t%d\t%d\n", 12, s.top(), s.size());
    s.push(24);
    printf("%d\t%d\t%d\n", 14, s.top(), s.size());
    s.push(36);
    printf("%d\t%d\t%d\n", 36, s.top(), s.size());
    s.pop();
    printf("pop\t%d\t%d\n", s.top(), s.size());
    s.pop();
    printf("pop\t%d\t%d\n", s.top(), s.size());
    s.pop();
    printf("pop\t%d\t%d\n", NULL, s.size());
    return 0;
}

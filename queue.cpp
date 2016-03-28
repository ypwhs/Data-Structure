#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int main()
{
    queue<int> s;
    printf("queue\n");
    printf("option\tfront\tsize\n");
    s.push(12);
    printf("%d\t%d\t%d\n", 12, s.front(), s.size());
    s.push(24);
    printf("%d\t%d\t%d\n", 14, s.front(), s.size());
    s.push(36);
    printf("%d\t%d\t%d\n", 36, s.front(), s.size());
    s.pop();
    printf("pop\t%d\t%d\n", s.front(), s.size());
    s.pop();
    printf("pop\t%d\t%d\n", s.front(), s.size());
    s.pop();
    printf("pop\t%d\t%d\n", NULL, s.size());
    return 0;
}

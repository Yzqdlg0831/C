#define _CRT_SECURE_NO_WARNINGS 1
#include<bits/stdc++.h>
using namespace std;

int c[1010];
int main()
{
    int t; 
    cin >> t;
    while (t--) {
        int n; 
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> c[i];
        }
        int left = 1, right = n;
        int count1 = 0;
        int flag = 0, x = 0;
        int a = 0, b = 0, now;
        while (left <= right) {
            if (flag == 0) {
                now = 0;
                while (x >= now && left <= right) {
                    now = now + c[left++];
                }
                a = a + now;
                flag = 1; count1++;
            }
            else {
                now = 0;
                while (x >= now && left <= right) {
                    now = now + c[right--];
                }
                b = b + now;
                flag = 0; count1++;
            }
            x = now;
        }
        cout << count1 << " " << a << " " << b << endl;
    }
    return 0;
}
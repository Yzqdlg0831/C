#define _CRT_SECURE_NO_WARNINGS 1
#define bool int
#define true 1
#define false 0

#include<stdio.h>
#include <string.h>

bool rotateString(char* s, char* goal) {
    int m = strlen(s), n = strlen(goal);
    if (m != n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = 0; j < n; j++) {
            if (s[(i + j) % n] != goal[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return true;
        }
    }
    return false;
}

int main() {

    char* s = "aacde";
    char* goal = "cdeab";
    bool a = rotateString(s, goal);
    printf("%d", a);
    return 0;
}
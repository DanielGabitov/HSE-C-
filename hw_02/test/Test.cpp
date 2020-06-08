#include "cstdio"
#include "Test.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum){
    totalNum++;
    if (!expr){
        failedNum++;
        printf("Failed at: %s in function %s(): %zu\n", filename, func, lineNum);
    }
}

bool Test::showFinalResult(){
    printf("Успешных тестов: %d\n", totalNum - failedNum);
    printf("Непройденных тестов: %d\n", failedNum);
    if (!failedNum){
        return !failedNum;
    }
    return false;
}



#include "Test.h"
#include "BoardTest.h"
#include "Board.h"

int main(){
    BoardTest bt;
    bt.runAllTests();
    return BoardTest::showFinalResult();
}

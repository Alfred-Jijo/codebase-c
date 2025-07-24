#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int status = 0;
    printf("Running all tests...\n");

    status |= system("test_macros.exe");

    if (status == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }
    return status;
}

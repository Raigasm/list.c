#include "debugprint.h"
#include "minunit.h"
#include "findfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run     = 0;
int tests_failed  = 0;
int suites_run    = 0;
int suites_failed = 0;

static char *test_check_testing_works()
{
    mu_assert("Testing does not work", 7 == 7);
    return 0;
}




int main()
{
    testFindFile();
}

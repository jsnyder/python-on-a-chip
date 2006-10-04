#include "CuTest.h"


/* Need to declare this array since no PyMite application is linked */
const unsigned char usr_nat_fxn_table[] = {};

CuSuite *getSuite_testDict(void);
CuSuite *getSuite_testList(void);


int main(void)
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, getSuite_testDict());
    CuSuiteAddSuite(suite, getSuite_testList());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    puts(output->buffer);

    /*
     * Zero failures indicates an all-good exit code.
     * Any errors gives a non-zero exit code that should stop the build
     * when this is called by the Makefile
     */
    return suite->failCount;
}

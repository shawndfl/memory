#ifndef SRC_TEST_H_
#define SRC_TEST_H_

/*
 * Only if testing
 */
#ifdef TEST
/*
 * The main entry point for unit tests.
 * This should be called from main only if
 * TEST is defined
 */
int test(int argc, char **argv);

int startTestApp();

#endif
#endif

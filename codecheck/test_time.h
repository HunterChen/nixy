#pragma once

#include "time/time.h"
#include "thread/threadops.h"

//////////////////////////////////////////////////////////////////////////

#ifndef STOPWATCH_CHECKER
#define STOPWATCH_CHECKER(op) \
    strout << "stopwatch ->: " << #op << endl; \
    sw.op(); \
    nx_foreach(NX_UNUSED i, 5) \
    { \
        nx::thread_ops::sleep(100); \
        strout << "stopwatch ->: " << sw.value() << endl; \
    }
#endif

void testStopwatch(void)
{
    TEST_CASE();

    strout << setiosflags(ios_base::showpoint);
    nx::stopwatch<> sw;
    STOPWATCH_CHECKER(start)
    STOPWATCH_CHECKER(pause)
    STOPWATCH_CHECKER(start)
    STOPWATCH_CHECKER(stop)
    STOPWATCH_CHECKER(start)
    STOPWATCH_CHECKER(start)
    strout << resetiosflags(ios_base::showpoint);
}

#undef STOPWATCH_CHECKER
#undef STOPWATCH_SLEEP

//////////////////////////////////////////////////////////////////////////

void testTime(void)
{
    TEST_FUNCTION();

    testStopwatch();
}
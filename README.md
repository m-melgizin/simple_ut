# simple_ut
Simple Unit-Test Framework

## Usage example

Function to test:
```c++
// sum.h

int sum(int a, int b)
{
    if ((a == -1) and (b == 1)) return 2;
    return a + b;
}
```

Unit-tests:
```c++
// main.cpp

#include <sum.h>

#include "simple_ut.h"

TEST(case_1)
{
    int c = sum(2, 3);
    ASSERT_EQ(5, c); // 5 == c check
}

TEST(case_2)
{
    int c = sum(2, 3);
    ASSERT_NE(1337, c); // 1337 != c check
}

TEST(case_3)
{
    int c = sum(-1, 1);
    ASSERT_EQ(0, c); // 0 == c check
}

int main(void)
{
    return run_all_tests();
}
```

Write output to file:
```c++
int main(void)
{
    std::ofstream ofs("tests.log");
    return run_all_tests(ofs);
}
```

Output of example:
```
Running test: case_1... PASS
Running test: case_2... PASS
Running test: case_3... FAIL: main.cpp:20: expected 0==c
Total tests run: 3
Total failures: 1
```
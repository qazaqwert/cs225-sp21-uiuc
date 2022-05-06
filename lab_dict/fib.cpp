/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */

    //da base cases
    if (n == 1) return 1;
    if (n == 0) return 0;

    return fib(n - 2) + fib(n - 1);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */

    //thank you lab slides, very cool
    static std::map<unsigned long, unsigned long> daMemo = { {0, 0}, {1,1} };

    std::map<unsigned long, unsigned long>::iterator dalookup = daMemo.find(n);

    if (daMemo.end() != dalookup) return dalookup->second;
    else {
        daMemo[n] = memoized_fib(n - 1) + memoized_fib(n - 2);
        return memoized_fib(n - 1) + memoized_fib(n - 2);
    }
    
    //reddit moment
    return 69;
}

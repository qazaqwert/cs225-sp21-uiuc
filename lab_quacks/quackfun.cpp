/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun
{

    /**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
    template <typename T>
    T sum(stack<T> &s)
    {
        if (s.size() == 0)
        {
            return 0;
        }
        else
        {
            T top = s.top();
            s.pop();
            T chungus = top + sum(s);

            s.push(top);
            return chungus;
        }
    }

    /**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
    bool isBalanced(queue<char> input)
    {
        if (input.empty() == 1)
        {
            return true;
        }
        stack<char> data;
        for (char c = input.front(); !input.empty(); c = input.front())
        {
            if (c == '[')
            {
                data.push(c);
            }
            else if (c == ']')
            {
                if (data.empty() || !(data.top() == '[' && c == ']'))
                {
                    return false;
                }
                data.pop();
            }
            input.pop();
        }
        // @TODO: Make less optimistic
        return data.empty();
    }

    /**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
    template <typename T>
    void scramble(queue<T> &q)
    {
        stack<T> s;
        queue<T> q2;

        int c = 2;

        q2.push(q.front());
        q.pop();

        //plan is, move data over from params to our temp queue
        //and then place it back into original
        while (!q.empty())
        {
            //when c is even, scramble data
            if ((c % 2) == 0)
            {
                int t = c;
                //first type of scramble
                while (t && !q.empty())
                {
                    s.push(q.front());
                    q.pop();
                    t--;
                }
                //second type of scramble
                while (!s.empty())
                {
                    q2.push(s.top());
                    s.pop();
                }
            }
            else
            {
                //for odd counts, do not scramble data
                int t = c;
                while (t && !q.empty())
                {
                    q2.push(q.front());
                    q.pop();
                    t--;
                }
            }
            c++;
        }
        //don't return anything, modify q in place
        q = q2;
    }
}
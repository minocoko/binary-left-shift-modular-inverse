#include <stdio.h>

#define ABS(x) (x < 0) ? (0 - x) : x

// Function to find modular inverse of a under modulo m
// Assumption: m is prime
unsigned int inv_mod(const unsigned int a, const unsigned int m)
{
    // How often does this really happen? it should "almost" never happen (but would be faster)
    if (a == 1)
    {
        return 1;
    }
    if (a == 2)
    {
        return (m + 1) >> 1;
    }
    if (a == m - 1)
    {
        return a;
    }

    // check most significant bit
    const int u_msb = 32 - __builtin_clz(m);
    const int v_msb = 32 - __builtin_clz(a);
    const int msb_diff = u_msb - v_msb;
    const long un1 = 1L << u_msb;

    long u = m;
    long abs_u = u;
    long v = a;
    long abs_v = v;

    int cu = 0;
    unsigned int two_pow_of_cu = 1;
    int cv = 0;
    unsigned int two_pow_of_cv = 1;
    long r = 0;
    long s = 1;

    do
    {
        if (abs_u < un1)
        {
            u <<= 1;
            if (cu >= cv)
            {
                r <<= 1;
            }
            else
            {
                s >>= 1;
            }
            cu++;
            two_pow_of_cu <<= 1;
        }

        if (abs_v < un1)
        {
            v <<= 1;
            if (cv >= cu)
            {
                s <<= 1;
            }
            else
            {
                r >>= 1;
            }
            cv++;
            two_pow_of_cv <<= 1;
        }

        if ((u >= 0 && v >= 0) || (u < 0 && v < 0))
        {
            // op -
            if (cu <= cv)
            {
                u = u - v;
                r = r - s;
            }
            else
            {
                v = v - u;
                s = s - r;
            }
        }
        else
        {
            // op +
            if (cu <= cv)
            {
                u = u + v;
                r = r + s;
            }
            else
            {
                v = v + u;
                s = s + r;
            }
        }


        abs_u = ABS(u);
        abs_v = ABS(v);
    } while (abs_u != two_pow_of_cu && abs_v != two_pow_of_cv);

    if (abs_v == two_pow_of_cv)
    {
        r = s;
        u = v;
    }

    if (u < 0)
    {
        r = (r < 0) ? (0 - r) : (m - r);
    }

    if (r < 0)
    {
        r = m + r;
    }

    return r;
}

int main()
{
    // const unsigned int a = 1, m = 13;                        // output 1 (1 * 1 % 13 == 1)
    // const unsigned int a = 10, m = 13;                       // output 4 (4 * 10 % 13 == 1)
    // const unsigned int a = 3, m = 997;                       // output 665 (665 * 3 % 997 == 1)
    // const unsigned int a = 2456, m = 5179;                   // output 2541 (2541 * 2456 % 5179 == 1)
    // const unsigned int a = 10, m = 49993;                    // output 14998 (14998 * 10 % 49993 == 1)
    const unsigned int a = 2397485, m = 305175781;              // output 197958680 (197958680 * 2397485 % 305175781 == 1)
    // const unsigned int a = 2, m = 2521008887u;               // output 1260504444 (1260504444 * 2 % 2521008887 == 1)
    // const unsigned int a = 65536, m = 2521008887u;           // output 1666452423 (1666452423 * 65536 % 2521008887 == 1)
    // const unsigned int a = 2147483647u, m = 2521008887u;     // output 2069798517 (2069798517 * 2147483647 % 2521008887 == 1)
    // const unsigned int a = 2147483648u, m = 2521008887u;     // output 2487746851 (2487746851 * 2147483648 % 2521008887 == 1)
    // const unsigned int a = 2147483649u, m = 2521008887u;     // output 2058376504 (2058376504 * 2147483649 % 2521008887 == 1)
    // const unsigned int a = 4294967290u, m = 4294967291u;     // ouput 4294967290 (4294967290 * 4294967290 % 4294967291 == 1)
    unsigned int result = inv_mod(a, m);
    printf("%10u * %10u %% %10u == 1\n", a, result, m);

    return 0;
}

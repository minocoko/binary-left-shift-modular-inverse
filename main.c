#include <stdio.h>

// Function to find modular inverse of a under modulo m
// Assumption: m is prime
unsigned int inv_mod(const unsigned int a, const unsigned int m)
{
    // check most significant bit
    const int u_msb = 32 - __builtin_clz(m);
    const int v_msb = 32 - __builtin_clz(a);
    const int msb_diff = u_msb - v_msb;
    const unsigned long un1 = (unsigned long)1 << u_msb;

    unsigned long u = m;
    int un = 0;

    unsigned long v = a;
    int vn = 0;

    int cu = 0;
    unsigned long two_pow_of_cu = 1;
    int cv = 0;
    unsigned long two_pow_of_cv = 1;
    unsigned long r = 0;
    int rn = 0;
    unsigned long s = 1;
    int sn = 0;

    if (msb_diff > 0)
    {
        cu = 1;
        two_pow_of_cu = 1 << 1;
        cv = msb_diff + 1;
        two_pow_of_cv = (unsigned long)1 << cv;

        u <<= 1;
        v <<= cv;

        s = (unsigned long)1 << (cv - 1);
    }

    int temp = 0;
    while (u != two_pow_of_cu && v != two_pow_of_cv)
    {
        if (u < un1)
        {
            u = u << 1;
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
        else if (v < un1)
        {
            v = v << 1;
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
        else
        {
            if (un == vn)
            {
                // op -
                if (cu <= cv)
                {
                    // u = u -v;
                    temp = (u < v);
                    u = temp ? v - u : u - v;
                    un = temp ^ un;

                    // r = r - s
                    if (rn == sn)
                    {
                        temp = (r < s);
                        r = temp ? s - r : r - s;
                        rn = temp ^ rn;
                    }
                    else if (rn == 0 && sn)
                    {
                        r = r + s;
                    }
                    else
                    {
                        r = r + s;
                        rn = 1;
                    }
                }
                else
                {
                    // v = v - u
                    temp = (v < u);
                    v = temp ? u - v : v - u;
                    vn = temp ^ vn;

                    // s = s - r
                    if (sn == rn)
                    {
                        temp = (s < r);
                        s = temp ? r - s : s - r;
                        sn = temp ^ sn;
                    }
                    else if (sn == 0 && rn)
                    {
                        s = s + r;
                    }
                    else
                    {
                        s = s + r;
                        sn = 1;
                    }
                }
            }
            else
            {
                // op +
                if (cu <= cv)
                {
                    // u = u + v
                    if (un == 0 && vn)
                    {
                        un = u < v;
                        u = un ? v - u : u - v;
                    }
                    else if (un && vn == 0)
                    {
                        un = v < u;
                        u = un ? u - v : v - u;
                    }

                    // r = r + s
                    if (rn == sn)
                    {
                        r = r + s;
                    }
                    else if (rn == 0 && sn)
                    {
                        rn = r < s;
                        r = rn ? s - r : r - s;
                    }
                    else
                    {
                        rn = s < r;
                        r = rn ? r - s : s - r;
                    }
                }
                else
                {
                    // v = v + u;
                    if (vn == 0 && un)
                    {
                        vn = v < u;
                        v = vn ? u - v : v - u;
                    }
                    else if (vn && un == 0)
                    {
                        vn = u < v;
                        v = vn ? v - u : u - v;
                    }

                    // s = s + r
                    if (sn == rn)
                    {
                        s = s + r;
                    }
                    else if (sn == 0 && rn)
                    {
                        sn = s < r;
                        s = sn ? r - s : s - r;
                    }
                    else
                    {
                        sn = r < s;
                        s = sn ? s - r : r - s;
                    }
                }
            }
        }

        if (u == 0 || v == 0)
        {
            return 0;
        }
    }

    if (v == two_pow_of_cv)
    {
        r = s;
        rn = sn;

        u = v;
        un = vn;
    }

    if (un)
    {
        if (rn)
        {
            rn = 0;
        }
        else
        {
            r = m - r;
        }
    }
    if (rn)
    {
        r = m - r;
    }

    return r;
}

int main()
{
    // unsigned int a = 10, m = 13;                     // output 4 (4 * 10 % 13 == 1)
    // unsigned int a = 3, m = 997;                     // output 665 (665 * 3 % 997 == 1)
    // unsigned int a = 2456, m = 5179;                 // output 2541 (2541 * 2456 % 5179 == 1)
    // unsigned int a = 10, m = 49993;                  // output 14998 (14998 * 10 % 49993 == 1)
    unsigned int a = 2397485, m = 305175781;            // output 197958680 (197958680 * 2397485 % 305175781 == 1)
    // unsigned int a = 2147483648u, m = 2521008887u;   // output 2487746851 (2487746851 * 2147483648 % 2521008887 == 1)
    // unsigned int a = 2147483649u, m = 2521008887u;
    unsigned int result = inv_mod(a, m);
    printf("%10u * %10u %% %10u == 1\n", a, result, m);

    return 0;
}

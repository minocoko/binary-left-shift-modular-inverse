#include <stdio.h>

// Function to find modular inverse of a under modulo m
// Assumption: m is prime
int inv_mod(const unsigned int a, const unsigned int m)
{
    unsigned int u = m;
    int un = 0;
    unsigned int v = a;
    int vn = 0;
    unsigned int r = 0;
    int rn = 0;
    unsigned int s = 1;
    int sn = 0;

    int cu = 0;
    int cv = 0;

    const int most_significant_bit = 32 - __builtin_clz(u);
    const int un1 = 2 << (most_significant_bit - 1);
    int two_pow_of_cu = 1;
    int two_pow_of_cv = 1;
    int temp = 0;
    while (u != two_pow_of_cu && v != two_pow_of_cv)
    {
        if (u < un1)
        {
            u = u << 1;
            if (cu >= cv)
            {
                r = r << 1;
            }
            else
            {
                s = s >> 1;
            }
            cu++;
            two_pow_of_cu <<= 1;
        }
        else if (v < un1)
        {
            v = v << 1;
            if (cv >= cu)
            {
                s = s << 1;
            }
            else
            {
                r = r >> 1;
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
                    un = temp | un;

                    // r = r - s
                    if (rn == sn)
                    {
                        temp = (r < s);
                        r = temp ? s - r : r - s;
                        rn = temp | rn;
                    }
                    else if (rn == 0 && sn)
                    {
                        r = r + s;
                    }
                    else
                    {
                        rn = s < r;
                        r = rn ? r - s : s - r;
                    }
                }
                else
                {
                    // v = v - u
                    temp = (v < u);
                    v = temp ? u - v : v - u;
                    vn = temp | vn;

                    // s = s - r
                    if (sn == rn)
                    {
                        temp = (s < r);
                        s = temp ? r - s : s - r;
                        sn = temp | sn;
                    }
                    else if (sn == 0 && rn)
                    {
                        s = s + r;
                    }
                    else
                    {
                        sn = r < s;
                        s = sn ? s - r : r - s;
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
    // int a = 10, m = 13;
    int a = 3, m = 7;
    int result = inv_mod(a, m);
    printf("%d\n", result);

    return 0;
}

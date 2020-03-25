#include "defines.h"

// calculate (x^n)%mod.
// O(log(n))
LL fast_multiply_mod(LL x, LL n, LL mod) {
    LL result = 1;
    LL tmp = x;
    while (n > 0) {
        if (n & 1) result = (result * tmp) % mod;
        tmp = (tmp * tmp) % mod;
        n >>= 1;
    }
    return result;
}

// a*result = 1(%mod), the mod must be a prime number.
// Fermat's little theorem: a%(prime-1) = 1(%prime) ==> the result is a^(prime-2)%prime.
// O(log(prime_mod)).
LL mod_inverse(int a, LL prime_mod) {
    return fast_multiply_mod(a, prime_mod-2, prime_mod);
}

// C(a, b), a = 5, b = 2 ==> 10.
// Calculate all combination numbers and store them in results.
// Pascal's traingle: C(a, b) = C(a-1, b-1) + C(a-1, b).
// O(a*b)
LL full_combination_mod(int a, int b, LL **results, LL mod) {
    if (results != 0 && results[a][b] != -1) return results[a][b];
    LL ret;
    if (b == 0 || b == a) {
        ret = 1 % mod;
    } else {
        ret = (full_combination_mod(a-1, b, results, mod) + 
        full_combination_mod(a-1, b-1, results, mod)) % mod;
    }
    if (results != 0) results[a][b] = ret;
    return ret;
}

// C(a, b), a = 5, b = 2 ==> 10, the mod number must be prime. 
// C(a, b) = a!/(b!*(a-b)!)
// O(log(mod))
LL combination_mod_with_factors(int a, int b, VEC<LL> &factors, LL prime_mod) {
    return (factors[a] * mod_inverse((factors[b] * factors[a-b]) % prime_mod, prime_mod)) % prime_mod;
}

// Calculate 1!, 2!, ... n! and store them in the fac vector. 
// O(n)
void factorial(int n, VEC<LL> &fac, LL mod) {
    fac.resize(n+1);
    fac[1] = 1;
    FOR(i, 2, n) fac[i] = (fac[i-1] * i) % mod;
}

// Calculate the greatest common divisor. 
// gcd(a, b) = gcd(b, a%b).
// O(log(min(a, b)))
LL gcd(LL a, LL b) {
    if (a % b == 0) return b;
    return gcd(b, a%b);
}

// Factoring the x. 
// for example: 2484 = 2 * 2 * 3 * 3 * 3 * 23
// O(sqrt(x))
void factoring(LL x, VEC<LL> &factors) {
    LL prim = 2;
    while (prim * prim <= x) {
        while (x % prim == 0) {
            factors.push_back(prim);
            x /= prim;
        }
        prim ++;
    }
    if (x != 1) factors.push_back(x);
}

// IsPrime tests if this number is a prime number.
// O(sqrt(x))
bool is_prime(LL x) {
    if (x <= 1) return false;
    for (LL i = 2; i*i <= x; i++) 
        if (x % i == 0) return false;
    return true;
}
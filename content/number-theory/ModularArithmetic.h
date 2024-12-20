/**
 * Author: AlooParatha
 * Description: ModularArithmetic.h
 */
int bp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b % 2 == 1) res = res * a % mod;
        a = a * a % mod, b /= 2;
    }
    return res;
}
int fact[MAX], inv_fact[MAX];
void fact_init() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    inv_fact[MAX - 1] = bp(fact[MAX - 1], mod - 2);
    for (int i = MAX - 2; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
    }
}
int C(int n, int k) {
    if (k > n) return 0;
    return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}
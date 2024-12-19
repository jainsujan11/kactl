/**
 * Author: Jakob Kogler, chilli, pajenegod
 * Date: 2020-04-12
 * License: CC0
 * Description: Prime sieve for generating all primes smaller than LIM.
 * Time: LIM=1e9 $\approx$ 1.5s
 * Status: Stress-tested
 * Details: Despite its n log log n complexity, segmented sieve is still faster
 * than other options, including bitset sieves and linear sieves. This is
 * primarily due to its low memory usage, which reduces cache misses. This
 * implementation skips even numbers.
 *
 * Benchmark can be found here: https://ideone.com/e7TbX4
 *
 * The line `for (int i=idx; i<S+L; idx = (i += p))` is done on purpose for performance reasons.
 * Se https://github.com/kth-competitive-programming/kactl/pull/166#discussion_r408354338
 */
void all_prime_factors(int X){
 int sp[1000000+1]; int prime[1000000+1]; 
 const int range = 1e6;
 for (int i = 2; i <= range; i++){
  if(prime[i]==0){
   sp[i] = i;
   for (int j = i*i; j <= range; j+=i){
    if(prime[j]==0)
    {
     prime[j]=1;
     sp[j] = i;
    }}}}}

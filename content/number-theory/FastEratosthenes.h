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
#pragma once

int prime[1000000+1];
const int range = 1e6;
// Seive of Eratosthenes
void isPrime()
{
    for (int i = 2; i*i <= range; i++)
    {
        if(prime[i]==0)
        {
            // its fine to start from i*i
            // 2*i,4*i,.. will be already marked by some smaller prime numb
            for (int j = 1ll*i*i; j <= range; j+=i)
            {
                prime[j]=1;
            }  
        }
    }
    // if prime[i]==0 it means i is prime
}
// To find any n is prime or not
bool isPrime(ll n)
{
    if (n <= 1)
    {
        return false;
    }
    if (n <= 3)
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (ll i = 5; i * i <= n; i = i + 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}
// code for finding number of divisors for all numbers from 2 to N.
void divisors()
{
    // TC - O(NlogN)
    for (int i = 2; i < N; i++)         
    { 
        for (int j = i; j < N; j += i)
        {
            divis[j]++;
        }
    }
}
// Code for finding divisors of a number x
vi divisor(int x)
{
    vi ans;
    int i = 1;
    while (i * i <= x)
    {
        if (x % i == 0)
        {
            ans.pb(i);
            if (x / i != i)
            {
                ans.pb(x / i);
            }
        }
        i++;
    }
    return ans;
}


// Code for finding factors of number x;
vector<pi> factor(int x)
{
    vector<pi> ans;
    for (int i = 2; i*i<=x; i++)
    {
        if(x%i==0)
        {
            int cnt=0;
            while(x%i==0)
            {
                cnt++;
                x/=i;
            }
            ans.pb({i,cnt});
        }
    }
    if(x>1) ans.pb({x,1});
    return ans;
}
// Fast Factorisation
// Code for finding all numbers upto X -- (10^6)
// Normal Approach TC-O(N*sqrt(N))
// Store Lowest prime for each number using SIEVE IDEA
// Recursively call N/p till it reaches 1
// How it will calculate in log(X) becoz max prime factors of X are log2(X)
void all_prime_factors(int X)
{
    // creating sp array
    int sp[1000000+1]; // initially zeroed
    int prime[1000000+1];  // initially zeroed
    const int range = 1e6;
    // Seive of Eratosthenes
    for (int i = 2; i <= range; i++)
    {
        if(prime[i]==0)
        {
            sp[i] = i;
            // its fine to start from i*i
            // 2*i,4*i,.. will be already marked by some smaller prime numb
            for (int j = i*i; j <= range; j+=i)
            {
                if(prime[j]==0)
                {
                    prime[j]=1;
                    sp[j] = i;
                }
            }  
        }
    }
    // if prime[i]==0 it means i is prime
    vector<int> factors[range+1];
    for (int i = 2; i < X+1; i++)
    {
        int num = i;
        while (num!=1)
        {
            factors[i].push_back(sp[num]);
            num/=sp[num];
        }
        
    }
    // final ans is stored in factors array
}

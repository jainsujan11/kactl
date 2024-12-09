/**
 * Author: AlooParatha
 * Description: ModularArithmetic.h
 */

template <const int64_t MOD = mod1>
struct modint {
    int64_t value;
    modint() = default;
    modint(int64_t value_) : value(value_%MOD) {}
    modint<MOD> operator + (modint<MOD> other) const { int64_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
    modint<MOD> operator - (modint<MOD> other) const { int64_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
    modint<MOD> operator * (modint<MOD> other) const { int64_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
    modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
    modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
    modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
    modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
    modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime*
    modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
    modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
    bool operator == (modint<MOD> other) const { return value == other.value; }
    bool operator != (modint<MOD> other) const { return value != other.value; }
    bool operator < (modint<MOD> other) const { return value < other.value; }
    bool operator > (modint<MOD> other) const { return value > other.value; }
    friend modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
    friend istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
    friend ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }
}; 
using mint = modint<>;

template<const int64_t mod = mod1>
struct combi{
  int n; vector<mint> facts, finvs, invs;
  combi(int _n): n(_n), facts(_n), finvs(_n), invs(_n){
    facts[0] = finvs[0] = 1;
    invs[1] = 1;
    for (int i = 2; i < n; i++) invs[i] =  invs[mod % i] * (-mod / i);
    for(int i = 1; i < n; i++){
      facts[i] = facts[i - 1] * i;
      finvs[i] = finvs[i - 1] * invs[i];
    }
  }
  inline mint fact(int n) { return facts[n]; }
  inline mint finv(int n) { return finvs[n]; }
  inline mint inv(int n) { return invs[n]; }
  inline mint ncr(int n, int k) { return n < k or k < 0 ? 0 : facts[n] * finvs[k] * finvs[n-k]; }
};

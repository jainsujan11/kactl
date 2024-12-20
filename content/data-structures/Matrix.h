/**
 * Author: AlooParatha
 * Description: Matrix.h
 */
template<class T> struct Matrix {
	typedef Matrix M;
	vector<vector<T>> d;
    Matrix(int n){
        d.resize(n,vector<T>(n,0));
    };
	M operator*(const M& m) const {
		M a(m.d.size());
        int N = m.d.size();
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N) {a.d[i][j] += (d[i][k]*m.d[k][j])%mod1;a.d[i][j]%=mod1;}
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
        int N = this->d.size();
		vector<T> ret(N);
		rep(i,0,N) rep(j,0,N) {ret[i] += (d[i][j] * vec[j])%mod1;ret[i]%=mod1;}
		return ret;
	}
	M operator^(ll p) const {
		M a(this->d.size()), b(*this);
        int N = this->d.size();
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b; p >>= 1;
		}
		return a;
	}
};
// KMP {{{
vector<int> prefix_function(string const& S) {
  int N = size(S);
  vector<int> pi(N, 0);
  for (int i = 1; i < N; i++) {
    int j = pi[i-1];
    while (j > 0 && S[i] != S[j]) j = pi[j-1];
    if (S[i] == S[j]) j++;
    pi[i] = j;
  }
  return pi;
}
vector<int> find_string(string const& S, string const& T) {
  vector<int> have;
  int N = size(S), M = size(T);
  auto P = prefix_function(T+"#"+S);
  for (int i = M+1; i <= N+M; i++) {
    if (P[i] == M) have.emplace_back(i-2*M);
  }
  return have;
}
int least_rotation(string const& S) {
  int N = size(S), k = 0;
  vector<int> f(2*N, -1);
  
  for (int j = 1; j < 2*N; j++) {
    int i = f[j-k-1];
    while (i != -1 && S[j%N] != S[(k+i+1)%N]) {
      if (S[j%N] < S[(k+i+1)%N]) k = j-i-1;
      i = f[i];
    }
    if (i == -1 && S[j%N] != S[(k+i+1)%N]) {
      if (S[j%N] < S[(k+i+1)%N]) k = j;
      f[j-k] = -1;
    } else {
      f[j-k] = i+1;
    }
  }
  return k;
}
//}}}

// Z {{{
vector<int> z_function(string const& S) {
  int N = size(S);
  vector<int> z(N);
  int l = 0, r = 0;
  for (int i = 1; i < N; i++) {
    if (i < r) z[i] = min(r-i, z[i-l]);
    while (i + z[i] < N && S[z[i]] == S[i+z[i]]) z[i]++;
    if (i + z[i] > r) l = i, r = i+z[i];
  }
  return z;
}
vector<int> find_string(string const& S, string const& T) {
  vector<int> have;
  int N = size(S), M = size(T);
  auto Z = z_function(T+"#"+S);
  for (int i = 0; i < N; i++) {
    if (Z[i+M+1] == M) have.emplace_back(i);
  }
  return have;
}
//}}}

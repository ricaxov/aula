// Prefix Function {{{
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
//}}}

// Z Function {{{
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

// CF-432D
vector<int> count_prefix(string const& S) {
  int N = size(S);
  vector<int> C(N+1, 0);
  auto P = prefix_function(S+'#');
  for (int i = 0; i < N; i++) C[P[i]]++;
  for (int i = N-1; i > 0; i--) C[P[i-1]] += C[i];
  for (int i = 0; i <= N; i++) C[i]++;
  return C;
}

vector<int> recover_prefix(string const& S) {
  int N = size(S);
  vector<int> have;
  auto P = prefix_function(S);
  for (int i = N-1; i >= 0; i = P[i]-1) have.emplace_back(i);
  reverse(begin(have), end(have));
  return have;
}

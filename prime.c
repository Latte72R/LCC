
int main() {
  int prm[10];
  prm[0] = 2;
  int i = 3;
  int n = 1;
  int flag_w = 1;
  int flag_f;
  int j;
  while (flag_w) {
    flag_f = 1;
    for (j = 0; j < n && flag_f; j = j + 1) {
      if (i % prm[j] == 0) {
        flag_f = 0;
      }
      if (flag_f && j == n - 1) {
        prm[n] = i;
        n = n + 1;
        flag_f = 0;
      }
    }
    if (n == 10) {
      flag_w = 0;
    }
    i = i + 1;
  }
  return prm[9];
}

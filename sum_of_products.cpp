#include <iostream>

void NextPermutation(int* indexes, int* n, int i) {
  if (i == -1) {
    return;
  }
  ++indexes[i];
  if (indexes[i] < n[i]) {
    return;
  }
  indexes[i] = 0;
  NextPermutation(indexes, n, i - 1);
}

int main(int argc, char** argv) {
  int k = argc - 1;
  int* n = new int[k];
  long long c = 1;
  for (int i = 0; i < k; ++i) {
    n[i] = std::atoi(argv[i + 1]);
    c *= n[i];
  }
  int** a = new int*[k];
  for (int i = 0; i < k; ++i) {
    a[i] = new int[n[i]];
    for (int j = 0; j < n[i]; ++j) {
      std::cin >> a[i][j];
    }
  }
  int* indexes = new int[k]{};
  long long ans = 0;
  for (int i = 0; i < c; ++i) {
    bool flag = true;
    for (int j = 0; j < k - 1; ++j) {
      for (int l = j + 1; l < k; ++l) {
        if (indexes[j] == indexes[l]) {
          flag = false;
          break;
        }
      }
      if (!flag) {
        break;
      }
    }
    if (flag) {
      long long p = 1;
      for (int j = 0; j < k; ++j) {
        p *= a[j][indexes[j]];
      }
      ans += p;
    }
    NextPermutation(indexes, n, k - 1);
  }
  std::cout << ans << '\n';
  for (int i = 0; i < k; ++i) {
    delete[] a[i];
  }
  delete[] a;
  delete[] indexes;
  delete[] n;
}

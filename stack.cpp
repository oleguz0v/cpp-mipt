#include <iostream>

char* ReadString() {
  char* str = new char[1001]{};
  int i = 0;
  while (true) {
    char c = getchar();
    if (c == ' ') {
      continue;
    }
    if (c == '\n') {
      break;
    }
    str[i] = c;
    ++i;
  }
  return str;
}

int main() {
  int size = 0;
  int cps = 1;
  char** stack = new char*[cps];
  while (true) {
    char cmd[10]{};
    std::cin >> cmd;
    if (cmd[0] == 'p' && cmd[1] == 'u') {
      char* str = ReadString();

      if (size == cps) {
        cps *= 2;
        char** new_stack = new char*[cps];
        for (int i = 0; i < size; ++i) {
          new_stack[i] = stack[i];
        }
        delete[] stack;
        stack = new_stack;
      }

      stack[size] = str;
      ++size;
      std::cout << "ok\n";
    } else if (cmd[0] == 'p') {
      if (size == 0) {
        std::cout << "error\n";
        continue;
      }
      std::cout << stack[size - 1] << '\n';
      delete[] stack[size - 1];
      --size;
    } else if (cmd[0] == 'b') {
      if (size == 0) {
        std::cout << "error\n";
        continue;
      }
      std::cout << stack[size - 1] << '\n';
    } else if (cmd[0] == 's') {
      std::cout << size << '\n';
    } else if (cmd[0] == 'c') {
      for (int i = 0; i < size; ++i) {
        delete[] stack[i];
      }
      size = 0;
      std::cout << "ok\n";
    } else if (cmd[0] == 'e') {
      for (int i = 0; i < size; ++i) {
        delete[] stack[i];
      }
      delete[] stack;
      std::cout << "bye\n";
      break;
    }
  }
}

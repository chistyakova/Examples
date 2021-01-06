#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

int main() {
  for (std::string line; std::getline(std::cin, line);) {
    char sep = '|';
    std::vector<std::string> vec(0);
    for (size_t p = 0, q = 0; p != line.npos; p = q) {
      vec.push_back(line.substr(p + (p != 0),
                                (q = line.find(sep, p + 1)) - p - (p != 0)));
    }

    std::cout << line << std::endl;

    int pfds[2];

    if (pipe(pfds) == -1) {
      perror("pipe");
      exit(1);
    }

    if (!fork()) {
      close(1);
      dup(pfds[1]);
      close(pfds[0]);
      execlp(vec[0].c_str(), vec[0].c_str(), NULL);
    } else {
      close(0);
      dup(pfds[0]);
      close(pfds[1]);
      execlp(vec[1].c_str(), vec[1].c_str(), NULL);
    }
  }
  return 0;
}

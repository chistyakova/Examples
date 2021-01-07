#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <list>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> vec(0);
  //  for (std::string line; std::getline(std::cin, line);) {
  //    char sep = '|';
  //    for (size_t p = 0, q = 0; p != line.npos; p = q) {
  //      vec.push_back(line.substr(p + (p != 0),
  //                                (q = line.find(sep, p + 1)) - p - (p !=
  //                                0)));
  //    }
  //  }
  vec = std::vector<std::string>{"numbers", "sort", "uniq"};
  // std::cout << "vec size:" << vec.size() << "\n";  // 4

  int new_fds[2];
  int old_fds[2];
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    // std::cerr << "start for\n";
    if ((it + 1) != vec.end()) pipe(new_fds);
    if (!fork()) {
      // std::cerr << "start child\n";
      if (it != vec.begin()) {
        // std::cerr << "old_fds[0]=" + std::to_string(old_fds[0]) + "\n";
        dup2(old_fds[0], 0);
        close(old_fds[0]);
        close(old_fds[1]);
      }
      if ((it + 1) != vec.end()) {
        // std::cerr << "new_fds[1]" + std::to_string(new_fds[1]) + "\n";
        close(new_fds[0]);
        dup2(new_fds[1], 1);
        close(new_fds[1]);
      }
      // std::cerr << "command-" + (*it) + "\n";
      execlp((*it).c_str(), (*it).c_str(), NULL);
      // std::cerr << "--------------------------\n";
      exit(0);
    } else {
      if (it != vec.begin()) {
        close(old_fds[0]);
        close(old_fds[1]);
      }
      if (it + 1 != vec.end()) {
        old_fds[0] = new_fds[0];
        old_fds[1] = new_fds[1];
      }
    }
  }

  if (vec.size() > 1) {
    close(old_fds[0]);
    close(old_fds[1]);
  }

  for (int i = 0; i < vec.size(); ++i) {
    // std::cout << "wait" << vec.size() << "\n";
    wait(NULL);
  }
  return 0;
}

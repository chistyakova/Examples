#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string getCommandName(std::string s) { return s.substr(0, s.find(' ')); }

std::string getKey(std::string s) {
  auto pos = s.find('-');
  if (pos != std::string::npos) {
    return s.substr(s.find('-'), s.size() - 1);
  } else {
    return "";
  }
}

int main() {
  std::vector<std::string> vec(0);
  std::string line;
  std::getline(std::cin, line);
  char sep = '|';
  for (size_t p = 0, q = 0; p != line.npos; p = q) {
    vec.push_back(
        line.substr(p + (p != 0), (q = line.find(sep, p + 1)) - p - (p != 0)));
  }
  int new_fds[2];
  int old_fds[2];
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    if ((it + 1) != vec.end()) pipe(new_fds);
    if (!fork()) {
      if (it != vec.begin()) {
        dup2(old_fds[0], 0);
        close(old_fds[0]);
        close(old_fds[1]);
      }
      if ((it + 1) != vec.end()) {
        close(new_fds[0]);
        dup2(new_fds[1], 1);
        close(new_fds[1]);
      } else {
        auto d_out =
            open("/home/box/result.out", O_RDWR | O_CREAT | O_TRUNC, 0666);
        dup2(d_out, 1);
        close(new_fds[0]);
        close(new_fds[1]);
      }

      auto command = getCommandName(*it);
      auto key = getKey(*it);

      if (key.empty())
        execlp(command.c_str(), command.c_str(), NULL);
      else
        execlp(command.c_str(), command.c_str(), key.c_str(), NULL);
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
    wait(NULL);
  }
  return 0;
}

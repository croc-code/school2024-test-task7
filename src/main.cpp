#include <commits_leader.h>

int main(int argc, char **argv) {
  (void)argc;
  auto start = std::chrono::high_resolution_clock::now();
  getLeaders(argv[1], argv[2]);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;

  std::cout << "Время выполнения функции: " << duration.count() << " секунд"
            << std::endl;
}
#include <iostream>

#include "caveman.hh"

int main(int argc, char** argv) {
  if (argc >= 3) {
    auto nbr_caves = std::stoi(argv[1]);
    auto cave_size = std::stoi(argv[2]);
    auto caveman = Caveman(nbr_caves, cave_size);
    caveman.generate_graph("samples/");
    return 0;
  } else {
    std::cerr << "Usage: You should specify respectively the number of caves and the number of nodes in a cave." << std::endl
      << "Eg: " << argv[0] << " 3 4" << std::endl
      << "Where 3 is the number of caves and 4 is the number of nodes in a cave." << std::endl;
    return -1;
  }
}

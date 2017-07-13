#include "caveman.hh"

Caveman::Caveman(int nbr_caves, int nbr_nodes_in_cave) {
  this->nbr_caves_ = nbr_caves;
  this->nbr_nodes_in_cave_ = nbr_nodes_in_cave;
  this->nbr_edges_ = nbr_caves * (nbr_nodes_in_cave * (nbr_nodes_in_cave - 1)) / 2;
  this->nbr_nodes_ = nbr_caves * nbr_nodes_in_cave;
}

bool Caveman::generate_graph(const std::string& path) {
  std::ostringstream file_path;
  file_path << path << "caveman_graph_" << nbr_caves_ << "_" << this->nbr_nodes_in_cave_;
  std::ofstream fileout;
  fileout.open(file_path.str());
  if (fileout.is_open()) {
    fileout << "st";
  } else {
    std::cerr << "Error: can't open file: " << file_path.str() << std::endl;
    return false;
  }
  fileout.close();
  return true;
}


void Caveman::print() {
  std::cout << "Caveman graph informations:" << std::endl
    << "- Number of caves = " << this->nbr_caves_ << std::endl
    << "- Number of nodes in a cave = " << this->nbr_nodes_in_cave_ << std::endl
    << "- Total number of nodes in the graph = " << this->nbr_nodes_ << std::endl
    << "- Number of edges in the graph = " << this->nbr_edges_ << std::endl;
}

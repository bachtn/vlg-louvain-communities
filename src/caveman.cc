#include "caveman.hh"

Caveman::Caveman(int nbr_caves, int cave_size) {
  this->nbr_caves_ = nbr_caves;
  this->cave_size_ = cave_size;
  this->nbr_edges_ = nbr_caves * (cave_size * (cave_size - 1)) / 2;
  this->nbr_nodes_ = nbr_caves * cave_size;
}

bool Caveman::generate_graph(const std::string& path) {
  std::ostringstream file_path;
  file_path << path << "caveman_graph_" << nbr_caves_ << "_" << this->cave_size_;
  std::ofstream fileout;
  fileout.open(file_path.str());
  if (fileout.is_open()) {
    // Write the number of nodes of the graph in the first line
    fileout << nbr_nodes_ << std::endl;
    // write the edges of the graph
    std::ostringstream edges_stream;
    generate_graph_edges(edges_stream);
    fileout << edges_stream.str();
  } else {
    std::cerr << "Error: can't open file: " << file_path.str() << std::endl;
    return false;
  }
  fileout.close();
  return true;
}

void Caveman::generate_graph_edges(std::ostringstream& edges_stream) {
  auto offset = 0;
  // Link the nodes in every cave but not the last 2 nodes (cave_size - 2)
  for (auto cave_idx = 0; cave_idx < nbr_caves_; ++cave_idx) {
    offset = cave_idx * cave_size_;
    for (auto node_idx = 0; node_idx < cave_size_ - 2; ++node_idx)
      for (auto j = node_idx + 1; j < cave_size_; ++j)
        edges_stream << node_idx + offset << " " << j + offset << std::endl;
  }

  // Link the caves between each other (the last node of the ith cave with the node before the last node in the (ith + 1) cave)
  for (auto cave_idx = 0; cave_idx < nbr_caves_ - 1; ++cave_idx) {
    offset = cave_idx * cave_size_;
    edges_stream << cave_size_ - 1  + offset << " " << 2 * cave_size_ - 2 + offset << std::endl;
  }

  // Link the 1st and last caves
  edges_stream << cave_size_ - 2 << " " << nbr_caves_ * cave_size_ - 1 << std::endl;
} 


void Caveman::print() {
  std::cout << "Caveman graph informations:" << std::endl
    << "- Number of caves = " << this->nbr_caves_ << std::endl
    << "- Number of nodes in a cave = " << this->cave_size_ << std::endl
    << "- Total number of nodes in the graph = " << this->nbr_nodes_ << std::endl
    << "- Number of edges in the graph = " << this->nbr_edges_ << std::endl;
}

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>  

class Caveman {
  public:
    Caveman(int nbr_caves, int cave_size);
    //! Prints the Caveman graph informations
    void print();
    /*! Generates the caveman graph and writes it to a file with the name "caveman_{nbr_caves}_{cave_size}"
      * and with the path passed in parameter
      * The file has the following form:
      * 1st line: number of nodes in the graph
      * following lines: list of edges (edge per line: 1 2 -> edge between node 1 and 2)
      */
    bool generate_graph(const std::string& path);
  private:
    void generate_graph_edges(std::ostringstream& edges_stream);

  private:
    int nbr_caves_;
    int cave_size_;
    int nbr_edges_;
    int nbr_nodes_;

};

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>  

class Caveman {
  public:
    Caveman(int nbr_caves, int nbr_nodes_in_cave);
    //! Prints the Caveman graph informations
    void print();
    /*! Generates the caveman graph and writes it to a file with the name "caveman_{nbr_caves}_{nbr_nodes_in_cave}"
      * and with the path passed in parameter
      * The file has the following form:
      * 1st line: number of nodes in the graph
      * following lines: list of edges (edge per line: 1 2 -> edge between node 1 and 2)
      */
    bool generate_graph(const std::string& path);

  private:
    int nbr_caves_;
    int nbr_nodes_in_cave_;
    int nbr_edges_;
    int nbr_nodes_;

};

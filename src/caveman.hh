#pragma once

#include <iostream>
#include <vector>

class Caveman {
  public:
    Caveman(int nbr_caves, int nbr_nodes_in_cave);

    void print();

  private:
    int nbr_caves_;
    int nbr_nodes_in_cave_;
    int nbr_edges_;
    int nbr_nodes_;

};

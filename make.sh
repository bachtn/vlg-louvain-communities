#!/bin/bash

# A POSIX variable
OPTIND=1         # Reset in case getopts has been used previously in the shell.

# variables:
# number of graphs to generate
nbr_graphs=1

# information about Cave Size (start index and step)
cave_size_start=3
cave_size_step=1

# information about Number of Caves in a graph
nbr_caves_start=4
nbr_caves_step=1

# Parse arguments
for arg_idx in "$@"
do
  case $arg_idx in
    --nbr_graphs=*)
      nbr_graphs="${arg_idx#*=}"
      shift # past argument=value
      ;;
    --cave_size_start=*)
      cave_size_start="${arg_idx#*=}"
      shift # past argument=value
      ;;
    --cave_size_step=*)
      cave_size_step="${arg_idx#*=}"
      shift # past argument=value
      ;;
    --nbr_caves_start=*)
      nbr_caves_start="${arg_idx#*=}"
      shift # past argument with no value
      ;;
    --nbr_caves_step=*)
      nbr_caves_step="${arg_idx#*=}"
      shift # past argument with no value
      ;;
    *)
      # unknown option
      ;;
  esac
done

# Print parsed arguments
echo "Number of graphs to genrate = '$nbr_graphs'.
The intial cave size = '$cave_size_start'.
The cave size step = '$cave_size_step'.
The initial number of caves in the graph = '$nbr_caves_start'.
The step of the number of caves = '$nbr_caves_step'.
The unparsed arguments = $@."





# make distclean
# cmake . -DCMAKE_BUILD_TYPE=DEBUG
# make
# ./vlg-louvain-communities 3 4



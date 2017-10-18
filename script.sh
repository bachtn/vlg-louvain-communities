#!/bin/bash

############################## SETTING VARIABLES
LOUVAIN_PATH="src/louvain_community"
GRAPH_FILENAME="samples/caveman_graph_"

############################## CLEAN FILES
# rm samples/*
# make distclean
# make clean -C $LOUVAIN_PATH
mkdir samples

############################## COMPILE PROGRAM
### COMPILE GRAPH GENERATION PROGRAM
cmake . -DCMAKE_BUILD_TYPE=DEBUG 1> /dev/null
make
### COMPILE LOUVAIN COMMUNITY DETECTION PROGRAM
make -C $LOUVAIN_PATH 1> /dev/null 2> /dev/null

############################## GET GRAPH PARAMETERS
# variables:
# number of graphs to generate
NBR_GRAPHS=1

# information about Cave Size (start index and step)
CAVE_SIZE_START=3
CAVE_SIZE_STEP=1

# information about Number of Caves in a graph
NBR_CAVES_START=4
NBR_CAVES_STEP=1

# Parse arguments
for arg_idx in "$@"
do
  case $arg_idx in
    --nbr_graphs=*)
      NBR_GRAPHS="${arg_idx#*=}"
      shift # past argument=value
      ;;
    --cave_size_start=*)
      CAVE_SIZE_START="${arg_idx#*=}"
      shift # past argument=value
      ;;
    --cave_size_step=*)
      CAVE_SIZE_STEP="${arg_idx#*=}"
      shift # past argument=value
      ;;
    --nbr_caves_start=*)
      NBR_CAVES_START="${arg_idx#*=}"
      shift # past argument with no value
      ;;
    --nbr_caves_step=*)
      NBR_CAVES_STEP="${arg_idx#*=}"
      shift # past argument with no value
      ;;
    *)
      # unknown option
      ;;
  esac
done

# Print parsed arguments
#echo "Number of graphs to genrate = '$NBR_GRAPHS'.
#The intial cave size = '$CAVE_SIZE_START'.
#The cave size step = '$CAVE_SIZE_STEP'.
#The initial number of caves in the graph = '$NBR_CAVES_START'.
#The step of the number of caves = '$NBR_CAVES_STEP'.
#The unparsed arguments = $@."

CAVE_SIZE_FINAL_VALUE=$(($CAVE_SIZE_START + $CAVE_SIZE_STEP * ($NBR_GRAPHS - 1)))
NBR_CAVES_FINAL_VALUE=$(($NBR_CAVES_START + $NBR_CAVES_STEP * ($NBR_GRAPHS - 1)))

TIMEFORMAT="%3R";
RESULTS_FILE="results.txt"
touch $RESULTS_FILE

# loop over the number of graphs to generate
for ((NBR_CAVES_IDX = $NBR_CAVES_START; NBR_CAVES_IDX <= $NBR_CAVES_FINAL_VALUE;  NBR_CAVES_IDX += $NBR_CAVES_STEP)); do
  for ((CAVE_SIZE_IDX = $CAVE_SIZE_START; CAVE_SIZE_IDX <= $CAVE_SIZE_FINAL_VALUE; CAVE_SIZE_IDX += $CAVE_SIZE_STEP)); do
    ./vlg-louvain-communities $NBR_CAVES_IDX $CAVE_SIZE_IDX
    CURRENT_GRAPH_FILENAME="${GRAPH_FILENAME}${NBR_CAVES_IDX}_${CAVE_SIZE_IDX}"
    CURRENT_GRAPH_BINARY="${CURRENT_GRAPH_FILENAME}.bin"
    ./$LOUVAIN_PATH/convert -i $CURRENT_GRAPH_FILENAME -o $CURRENT_GRAPH_BINARY
    EXEC_TIME=$(time (./$LOUVAIN_PATH/community $CURRENT_GRAPH_BINARY -l -1 1>/dev/null 2>/dev/null) 2>&1)
    echo "exec time = $EXEC_TIME nbr caves = $NBR_CAVES_IDX cave size = $CAVE_SIZE_IDX $EXEC_TIME"
    echo "$NBR_CAVES_IDX $CAVE_SIZE_IDX $EXEC_TIME" >> $RESULTS_FILE
    rm $CURRENT_GRAPH_BINARY $CURRENT_GRAPH_FILENAME
  done
done

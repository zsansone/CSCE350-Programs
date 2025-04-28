#!/bin/bash

g++ -Wall -o NetworkTopology NetworkTopology.cpp

./NetworkTopology

cat output.txt

rm NetworkTopology

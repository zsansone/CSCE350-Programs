// CSCE350 Zachary Sansone
// This program implements Floyd's Algorithm
// for finding the shortest paths in a weighted graph
// on an input distance matrix.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::string line; 

    int nodes = 0;


    while(std::getline(input,line)) {
        if (line.empty()) {
            break; 
        }
        nodes++;
    }



    input.clear();
    input.seekg(0);



    std::vector<std::vector<float>> distance(nodes, std::vector<float>(nodes, 0));
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            std::string temp;
            input >> temp;
            output << temp << " ";
            if(temp == "I") {
                distance[i][j] = std::numeric_limits<float>::infinity();
            } else {
                distance[i][j] = std::stof(temp);
            }
        }
    }
    input.close();



    for (int k = 0; k < nodes; k++) {
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                if (distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (distance[i][j] == std::numeric_limits<float>::infinity()) {
                output << "I ";
            } else {
                output << distance[i][j] << " ";
            }
        }
        output << std::endl;
    }
    output.close();
    return 0;

    
}
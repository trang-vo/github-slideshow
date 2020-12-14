#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <lemon/list_graph.h>
#include "solver.h"

using namespace std;

const vector<string> LIST_SECTION_KEYWORDS = {"NODE_COORD_SECTION", "DEPOT_SECTION", "DEMAND_SECTION", 
                                              "EDGE_DATA_SECTION", "FIXED_EDGES_SECTION", "DISPLAY_DATA_SECTION", 
                                              "TOUR_SECTION", "EDGE_WEIGHT_SECTION"};

// bool checkSectionKeywords(string kw, vector<string> list_kw) {
//     vector<string>::iterator it;
//     it = find(list_kw.begin(), list_kw.end(), kw);
//     if (it == list_kw.end()) {
//         return false;
//     };

//     return true;
// };

// string normalizeLine(string& l) {
//     l.erase(remove(l.begin(), l.end(), "\r"), l.end());
//     return l;
// }

// std::vector<float> convertStr2Vector(std::string str, std::string delimiter) {
//     std::vector<float> output;
//     size_t next = 0;
//     size_t last = str.find(delimiter);
//     std::string token;
//     while ((last != std::string::npos)) {
//         token = str.substr(next, last - next);
//         try {
//             output.push_back(std::stof(token));
//         } catch (std::invalid_argument& err) {
//             std::cout << "invalid input" << endl;
//             break;
//         };
//         next = last + delimiter.length();
//         last = str.find(delimiter, next);
//     };
//     if (next < str.size()) {
//         try {
//             output.push_back(std::stof(str.substr(next, str.size())));
//         } catch (std::invalid_argument& err) {
//             std::cout << "invalid input" << endl;
//         };
//     };
//     return output;
// };

// // void normalizeLine(std::string& l) {
// //     l.erase(remove(l.begin(), l.end(), "\r"), l.end());
// // };

// bool checkSectionKeywords(std::string kw, std::vector<std::string> list_kw) {
//     std::vector<std::string>::iterator it;
//     it = find(list_kw.begin(), list_kw.end(), kw);
//     if (it == list_kw.end()) {
//         return false;
//     };

//     return true;
// };

// std::vector<std::string> KEYWORDS = {"NODE_COORD_SECTION", "DEPOT_SECTION", "DEMAND_SECTION", "EDGE_DATA_SECTION", "FIXED_EDGES_SECTION", "DISPLAY_DATA_SECTION", "TOUR_SECTION", "EDGE_WEIGHT_SECTION"};

std::vector<lemon::ListGraph::Node> processNodeCoord(std::ifstream& fin, lemon::ListGraph &graph, lemon::ListGraph::NodeMap<std::vector<float>> &nodeMap){
    int vertex;
    std::vector<float> vertex_coord;
    int dimension = 280;
    std::vector<lemon::ListGraph::Node> vertices;
    lemon::ListGraph::Node node;

    float x, y, z;
    std::string line;
    int idx = 0;

    while (fin) {
        getline(fin, line);

        if (fin) {
            if (sscanf(line.c_str(), "%d %f %f %f", &vertex, &x, &y, &z) == 4) {
            vertex_coord = {x, y, z};
            }
            else if (sscanf(line.c_str(), "%d %f %f %f", &vertex, &x, &y, &z) == 3) {
                vertex_coord = {x, y};
            } 
            else
                break;

            vertices.push_back(node);
            vertices[idx] = graph.addNode();
            nodeMap[vertices[idx]] = vertex_coord;
            ++idx;
        }
        
    };
    return vertices;
};

int main() {
    lemon::ListGraph g;
    lemon::ListGraph::NodeMap<std::vector<float>> nodes(g);
    ifstream f("a280.txt");

    // float a, b, c;
    // string s;
    // while (f)
    // {
    //     getline(f, s);
    //     cout << sscanf(s.c_str(), "%f %f", &a, &b);
    //     cout << "value " << a << " " << b << " " << c << endl;
    // }
    char part[20];
    char *value;
    std::string line = "NAME : a280\r";
    sscanf(line.c_str(), "%s : %s", &part, &value);
    std::cout << part << endl;
    if (std::strcmp(part, "NAME") != 0) {
        std::cout << "equal";
    };

    return 0;
}
   
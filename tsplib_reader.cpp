#include "tsplib_reader.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 

namespace tsp {
    using lemon::ListGraph;
    using std::string;
    using std::vector;


    TsplibReader::TsplibReader(std::ifstream &inputFile) : nodeMap(this->graph), edgeMap(this->graph) 
    {
        if (readProblem(inputFile)) 
        {
            std::cout << "Input file is valid" << std::endl;
        };
    };

    //TsplibReader::TsplibReader(std::ifstream &inputFile, std::ofstream &outputFile) : nodeMap(graph){};

    bool TsplibReader::readProblem(std::ifstream &fin) 
    {
        string line;
        while (fin) 
        {
            getline(fin, line);
            if (line == "EOF") {
                break;
            };

            line.erase(remove(line.begin(), line.end(), "\r"), line.end());

            if (line.find(delimiter) != line.npos) {
                string part = line.substr(0, line.find(delimiter) - 1);
                string value = line.substr(line.find(delimiter) + 2);
                
                if (!checkKeywords(part, value)) {
                    return false;
                };
            };

            if (line == "NODE_COORD_SECTION")
               processNodeCoord(fin);
            // if (line == "EDGE_DATA_SECTION")
            //    processEdgeData();
            // if (line == "EDGE_WEIGHT_SECTION")
            //    processEdgeWeight();
        };

        return true;
    };

    bool TsplibReader::checkKeywords(string part, string value) {
        if (part == "NAME") {
            this->name = value;
        } 
        else if (part == "TYPE") {
            if (value == "TSP" || value == "ATSP") {
                this->type = value;
            } else {
                std::cout << part << " not supported" << std::endl;
                return false;
            };
        }
        else if (part == "COMMENT") {
            this->comment = value;
        }
        else if (part == "DIMENSION") {
            this->dimension = stoi(value);
        }
        else if (part == "CAPACITY") {
            this->capacity = stoi(value);
        }
        else if (part == "EDGE_WEIGHT_TYPE") {
            if (value == "EXPLICIT" ||
                value == "EUC_2D" || value == "EUC_3D" ||
                value == "MAX_2D" || value == "MAX_3D" ||
                value == "MAN_2D" || value == "MAN_3D" ||
                value == "CEIL_2D" || value == "GEO" ||
                value == "XRAY1" || value == "XRAY2" ||
                value == "ATT" || value == "SPECIAL") {
                this->edge_weight_type = value;
                } else {
                std::cout << part << " not supported" << std::endl;
                return false;
                };
        }
        else if (part == "EDGE_WEIGHT_FORMAT") {
            if (value == "FUNCTION" || value == "FULL_MATRIX" ||
                value == "UPPER_ROW" || value == "LOWER_ROW" ||
                value == "UPPER_DIAG_ROW" || value == "LOWER_DIAG_ROW" ||
                value == "UPPER_COL" || value == "LOWER_COL" ||
                value == "UPPER_DIAG_COL" || value == "LOWER_DIAG_COL") {
                this->edge_weight_format = value;
                } else {
                std::cout << part << " not supported" << std::endl;
                return false;
                };
        }
        else if (part == "EDGE_DATA_FORMAT") {
            if (value == "EDGE_LIST" || value == "ADJ_LIST") {
                this->edge_data_format = value;
            } else {
                std::cout << part << " not supported" << std::endl;
                return false;
            };
        }
        else if (part == "NODE_COORD_TYPE") {
            if (value == "TWOD_COORDS" || value == "THREED_COORDS" || value == "NO_COORDS") {
                this->node_coord_type = value;
            } else {
                std::cout << part << " not supported" << std::endl;
                return false;
            };
        }
        else if (part == "DISPLAY_DATA_TYPE") {
            this->display_data_type = value;
        }
        else {
            std::cout << part << " not supported" << std::endl;
            return false;
        };

        return true;
    };

    void TsplibReader::processNodeCoord(std::ifstream& fin){
        int vertex;
        vector<float> vertex_coord;
        ListGraph::Node node;
        ListGraph::Edge edge;
        int node_dimension = 0;

        float x, y, z;
        string line;
        while (fin) {
            getline(fin, line);

            if (fin) {
                if (sscanf(line.c_str(), "%d %f %f %f", &vertex, &x, &y, &z) == 4) {
                    vertex_coord = {x, y, z};
                    node_dimension = 3;
                }
                else if (sscanf(line.c_str(), "%d %f %f %f", &vertex, &x, &y, &z) == 3) {
                    vertex_coord = {x, y};
                    node_dimension = 2;
                }
                else
                    break;

                node = this->graph.addNode();
                this->nodeMap[node] = vertex_coord;
            };
        };

        for (ListGraph::NodeIt it(this->graph); it != lemon::INVALID; ++it)
        {
            ListGraph::NodeIt jt = it;
            ++jt;
            while (jt != lemon::INVALID)
            {
                edge = this->graph.addEdge(it, jt);
                edgeMap[edge] = this->metrix(nodeMap[it], nodeMap[jt]);
                ++jt;
            };
        };
    };

    void TsplibReader::processEdgeData(){};

    void TsplibReader::processEdgeWeight(){};

    int TsplibReader::metrix(vector<float> x, vector<float> y) {
        if (this->edge_weight_type == "EUC_2D") {
            return nint(std::sqrt(std::pow(x[0] - y[0], 2) + std::pow(x[1] - y[1], 2)));
        }
        else if (this->edge_weight_type == "EUC_3D") {
            return nint(std::sqrt(std::pow(x[0] - y[0], 2) + std::pow(x[1] - y[1], 2) + std::pow(x[2] - y[2], 2)));
        }
        else if (this->edge_weight_type == "MAX_2D") {
            return nint(std::max(std::abs(x[0] - y[0]), std::abs(x[1] - y[1])));
        }
        else if (this->edge_weight_type == "MAX_3D") {
            return nint(std::max(std::abs(x[0] - y[0]), std::abs(x[1] - y[1]), std::abs(x[2] - y[2])));
        }
        else if (this->edge_weight_type == "MAN_2D") {
            return nint(std::abs(x[0] - y[0]) + std::abs(x[1] - y[1]));
        }
        else if (this->edge_weight_type == "MAN_3D") {
            return nint(std::abs(x[0] - y[0]) + std::abs(x[1] - y[1]) + std::abs(x[2] - y[2]));
        }
        else if (this->edge_weight_type == "GEO") {
            return distanceGeographical(x, y); 
        }
        else if (this->edge_weight_type == "ATT") {
            return distancePseudoEuclidean(x, y); 
        }
        else if (this->edge_weight_type == "CEIL_2D") {
            return std::ceil(std::sqrt(std::pow(x[0] - y[0], 2) + std::pow(x[1] - y[1], 2)));
        };
    };

    vector<float> TsplibReader::convert2Geographical(vector<float> x) {
        vector<float> geo_coord;
        const float PI = 3.141592;
        
        int deg = nint(x[0]);
        float min = x[0] - deg;
        float latitude = PI * (deg + 5.0 * min / 3.0) / 180.0;
        geo_coord.push_back(latitude);

        deg = nint(x[1]);
        min = x[1] - deg;
        float longitude = PI * (deg + 5.0 * min / 3.0) / 180.0;
        geo_coord.push_back(longitude);

        return geo_coord;
    };

    int TsplibReader::distanceGeographical(vector<float> x, vector<float> y) {
        const float RRR = 6378.388;
        vector<float> xg = convert2Geographical(x);
        vector<float> yg = convert2Geographical(y);

        float q1 = std::cos(xg[1] - yg[1]);
        float q2 = std::cos(xg[0] - yg[0]);
        float q3 = std::cos(xg[0] + yg[0]);
        int dij = int(RRR * std::acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);

        return dij;
    };

    int TsplibReader::distancePseudoEuclidean(vector<float> x, vector<float> y) {
        float xd = x[0] - y[0];
        float yd = x[1] - y[1];
        float rij = std::sqrt((xd * xd + yd * yd) / 10.0);
        int tij = nint(rij);
        if (tij < rij) {
            return tij + 1;
        };
        return tij;
    }
}; // namespace tsp


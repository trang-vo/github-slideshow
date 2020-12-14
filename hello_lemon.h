#ifndef TSPLIBREADER_H
#define TSPLIBREADER_H

#include <fstream>
#include <string>
#include <lemon/list_graph.h>

namespace tsp {
    class TsplibReader 
    {
    private:
        const char delimiter = ':';

        std::string name;
        std::string type;
        std::string comment;
        int dimension;
        int capacity;
        std::string edge_weight_type;
        std::string edge_weight_format;
        std::string edge_data_format;
        std::string node_coord_type;
        std::string display_data_type;

        lemon::ListGraph graph;
        lemon::ListGraph::NodeMap<std::vector<float>> nodeMap;

        bool readProblem(std::string inputPath);
        bool checkKeywords(std::string part, std::string value);

        lemon::ListGraph::EdgeMap<std::vector<float>> getNodeMap(lemon::ListGraph g);

        void processNodeCoord(std::ifstream& fin);
        void processEdgeData();
        void processEdgeWeight();

    public:
        std::vector<lemon::ListGraph::Node> vertices;

        explicit TsplibReader(std::ifstream& inputFile);
        explicit TsplibReader(std::ifstream& inputFile, std::ofstream& outputFile);

    };
};



#endif
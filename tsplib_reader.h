#ifndef TSPLIBREADER_H
#define TSPLIBREADER_H

#include <cmath>
#include <fstream>
#include <functional>
#include <string>
#include <lemon/list_graph.h>


namespace tsp {
    int nint(float x) { return int(x + 0.5); };

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

        bool readProblem(std::ifstream &fin);
        bool checkKeywords(std::string part, std::string value);

        lemon::ListGraph::EdgeMap<std::vector<float>> getNodeMap(lemon::ListGraph g);

        void processNodeCoord(std::ifstream& fin);
        void processEdgeData();
        void processEdgeWeight();

        int metrix(std::vector<float> x, std::vector<float> y);

        vector<float> convert2Geographical(vector<float> x);
        int distanceGeographical(vector<float> x, vector<float> y);
        int distancePseudoEuclidean(vector<float> x, vector<float> y);

    public:
        lemon::ListGraph graph;
        std::vector<lemon::ListGraph::Node> vertices;
        lemon::ListGraph::NodeMap<std::vector<float>> nodeMap;
        std::vector<std::vector<int>> edges;
        lemon::ListGraph::EdgeMap<int> edgeMap;

        explicit TsplibReader(std::ifstream& inputFile);
        //explicit TsplibReader(std::ifstream& inputFile, std::ofstream& outputFile);

    };
};

#endif
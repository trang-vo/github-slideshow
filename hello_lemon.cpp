#include "hello_lemon.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector> // 
#include <algorithm> // find()

namespace tsp {

   TsplibReader::TsplibReader(std::ifstream &inputFile) : nodeMap(graph){};

   TsplibReader::TsplibReader(std::ifstream &inputFile, std::ofstream &outputFile) : nodeMap(graph){};

   bool TsplibReader::readProblem(std::string inputPath) 
   {
      std::ifstream fin(inputPath);
      std::string line;
      while (fin) 
      {
         getline(fin, line);
         if (line == "EOF") {
            break;
         };

         if (line.find(delimiter) != line.npos) {
            std::string part = line.substr(0, line.find(delimiter) - 1);
            std::string value = line.substr(line.find(delimiter) + 2);
            
            if (!checkKeywords(part, value)) {
               return false;
            };
         };

         // if (line == "NODE_COORD_SECTION")
         //    processNodeCoord();
         // if (line == "EDGE_DATA_SECTION")
         //    processEdgeData();
         // if (line == "EDGE_WEIGHT_SECTION")
         //    processEdgeWeight();
      };

      return true;
   };

   bool TsplibReader::checkKeywords(std::string part, std::string value) {
      if (part == "NAME") {
         this->name = value;
      } 
      else if (part == "TYPE") {
         if (value == "TSP" || value == "ATSP") {
            this->type = value;
         } else {
            cout << part << " not supported" << endl;
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
               cout << part << " not supported" << endl;
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
               cout << part << " not supported" << endl;
               return false;
            };
      }
      else if (part == "EDGE_DATA_FORMAT") {
         if (value == "EDGE_LIST" || value == "ADJ_LIST") {
            this->edge_data_format = value;
         } else {
            cout << part << " not supported" << endl;
            return false;
         };
      }
      else if (part == "NODE_COORD_TYPE") {
         if (value == "TWOD_COORDS" || value == "THREED_COORDS" || value == "NO_COORDS") {
            this->node_coord_type = value;
         } else {
            cout << part << " not supported" << endl;
            return false;
         };
      }
      else if (part == "DISPLAY_DATA_TYPE") {
         this->display_data_type = value;
      }
      else {
         cout << part << " not supported" << endl;
         return false;
      };

      return true;
   };

   void TsplibReader::processNodeCoord(std::ifstream& fin){
      int vertex;
      std::vector<float> vertex_coord;
      lemon::ListGraph::Node node;

      float x, y, z;
      std::string line;
      int idx = 0;
      while (fin) {
            getline(fin, line);

            if (sscanf(line.c_str(), "%d %f %f %f", &vertex, &x, &y, &z) == 4) {
               vertex_coord = {x, y, z};
            }
            else if (sscanf(line.c_str(), "%d %f %f %f", &vertex, &x, &y, &z) == 3) {
               vertex_coord = {x, y};
            } 
            else
               break;

            ver
            vertices_list[idx] = this->graph.addNode();
            this->nodeMap[vertices_list[idx]] = vertex_coord;
            if (idx < this->dimension - 1)
               ++idx;
      };
   };

   void TsplibReader::processEdgeData(){};

   void TsplibReader::processEdgeWeight(){};

   const std::vector<std::string> LIST_SECTION_KEYWORDS = {"NODE_COORD_SECTION", "DEPOT_SECTION", "DEMAND_SECTION", 
                                              "EDGE_DATA_SECTION", "FIXED_EDGES_SECTION", "DISPLAY_DATA_SECTION", 
                                              "TOUR_SECTION", "EDGE_WEIGHT_SECTION"};

   bool checkSectionKeywords(std::string kw, std::vector<std::string> list_kw) {
      std::vector<std::string>::iterator it;
      it = find(list_kw.begin(), list_kw.end(), kw);
      if (it == list_kw.end()) {
         return false;
      };

      return true;
   };

   std::string normalizeLine(std::string& l) {
      l.erase(remove(l.begin(), l.end(), "\r"), l.end());
      return l;
   };

   std::vector<float> convertStr2Vector(std::string str, std::string delimiter) {
      std::vector<float> output;
      size_t next = 0;
      size_t last = str.find(delimiter);
      std::string token;
      while ((last != std::string::npos)) {
         token = str.substr(next, last - next);
         try {
            output.push_back(std::stof(token));
         } catch (std::invalid_argument& err) {
            std::cout << "invalid input" << std::endl;
            break;
         };
         next = last + delimiter.length();
         last = str.find(delimiter, next);
      };
      if (next < str.size()) {
         try {
            output.push_back(std::stof(str.substr(next, str.size())));
         } catch (std::invalid_argument& err) {
            std::cout << "invalid input" << std::endl;
         };
      };
      return output;
};
}

int main() {

   std::string a;
   a = "NAME : a280";
   std::cout << a.substr(0, a.find(':') - 1) << std::endl;
   std::cout << a.substr(a.find(':') + 2, a.npos) << std::endl;
   return 0;
}
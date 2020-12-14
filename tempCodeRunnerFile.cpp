std::vector<float> convertStr2Vector(std::string str, std::string delimiter) {
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
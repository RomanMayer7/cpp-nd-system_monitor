#include "utils.h"


using namespace std;


std::string  findValueByKey(std::string const &directory, std::string const &filename,std::string const &keyFilter) {
  std::string line, key;
  std::string value;

  std::ifstream stream(directory + filename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == keyFilter) {
          return value;
        }
      }
    }
  }
  return value;
};


std::string  getValueOfFile(std::string const &directory, std::string const &filename) {
  std::string line;
  std::string  value;

  std::ifstream stream(directory + filename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return value;
};
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include<iostream>
#include <sstream>
// Tokenizing a string using stringstream
#include <bits/stdc++.h>


std::string findValueByKey(std::string const &directory, std::string const &filename,std::string const &keyFilter);


std::string getValueOfFile(std::string const &directory, std::string const &filename);

#endif
#ifndef FILESEARCHER_H
#define FILESEARCHER_H

#include <string>
#include <vector>

std::string shallow_find(std::string dir_path, std::string file_name);
std::vector<std::string> find_subdirs(std::string dir_path);

#endif

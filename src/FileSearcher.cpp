#include "FileSearcher.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::string shallow_find(std::string dir_path, std::string file_name) {
    std::cout << "searching in " << dir_path << " dir\n";
    std::string empty_str {};
    for(const auto& entry: fs::directory_iterator(dir_path)) {
        if(file_name == entry.path().filename()) {
            std::cout << "file found\n";
            return fs::path(file_name);
        }
    }
    return empty_str;
}

std::vector<std::string> find_subdirs(std::string dir_path) {
    std::vector<std::string> subdirs;
    for(const auto& entry: fs::directory_iterator(dir_path)) {
        if(fs::is_directory(entry)) {
            subdirs.push_back(entry.path().string());
        }
    }
    return subdirs;
}

#include "FileSearcher.hpp"

#include <filesystem>
#include <iostream>
#include <semaphore>
#include <thread>
#include <atomic>
#include <chrono>

namespace fs = std::filesystem;

static std::string dir_path {fs::path("/")};
static bool found {false};
std::counting_semaphore semaphore(8);

int deep_find(char const * file_name) {
    if(found) {
        return 0;
    }

    try
    {
        std::string file_path {shallow_find(dir_path, file_name)};
        if(!file_path.empty()) {
            found = true;
            std::cout << dir_path << "/" << file_path << " - file found!\n";
            return 0;
        }
        if(file_path.empty()) {
            std::vector<std::string> subdirs {find_subdirs(dir_path)};
            for(auto& dir: subdirs) {
                semaphore.acquire();
                dir_path = dir;
                std::thread thread(std::move(deep_find), file_name);
                semaphore.release();
                thread.join();
            }
        }
        return 1;
    }
    catch(const std::filesystem::filesystem_error& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cerr << "One argument (name of file) expected" << std::endl;
        return -1;
    }
    auto start = std::chrono::high_resolution_clock::now();
    deep_find(argv[1]);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
 
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;
    return 0;
}

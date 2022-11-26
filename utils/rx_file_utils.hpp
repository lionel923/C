#pragma once
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <string>
#include <vector>
#include <dirent.h>

using namespace std;
//#include <stdio.h>
//#include <sys/types.h>

using std::string;
/*
 * bool is_dir(std::string path)
 * bool is_file(std::string path)
 * bool extract_filename(const std::string &dir, std::vector<std::string> &file_list, bool is_recursion)
 * int mkdir_n(std::string path, bool is_recursion)  0 succeed, -1 failed
 * */
namespace rx {
  namespace fileutils {
    // path must be a dir, file is not allowed
    bool is_dir(std::string path);
    // path must be a file, dir is not allowed
    bool is_file(std::string path);
    // dir:filepath, file_list: output filename list
    bool extract_filename(const std::string &dir, std::vector<std::string> &file_list, bool is_recursion);

    std::vector<std::string> split(const std::string &s, const std::string &delim);

    // default only owner can read/write/exe, others can read and exe, can't write
    int mkdir_n(std::string path, bool is_recursion = false);

    // read small formated file
    bool get_lines(std::string file, std::vector<std::string> &lines);
  }
}

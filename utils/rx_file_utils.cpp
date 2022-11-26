#include "rx_file_utils.hpp"

using namespace std;

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
        bool is_dir(std::string path)
        {
            struct stat sb;
            if (stat(path.c_str(), &sb) == -1)
                return false;
            return S_ISDIR(sb.st_mode);
        }

        // path must be a file, dir is not allowed
        bool is_file(std::string path)
        {
            struct stat sb;
            if (stat(path.c_str(), &sb) == -1)
                return false;
            return S_ISREG(sb.st_mode);
        }

        // dir:filepath, file_list: output filename list
        bool extract_filename(const std::string &dir, std::vector<std::string> &file_list, bool is_recursion)
        {
            DIR *pdir = nullptr;
            struct dirent *pfile = nullptr;
            if (!(pdir = opendir(dir.c_str())))
            {
                std::cerr << "open failed:" << dir << std::endl;
                return false;
            }

            while ((pfile = readdir(pdir)))
            {
                string new_file = dir + "/" + pfile->d_name;
                if (is_dir(new_file) && strcmp(pfile->d_name, ".") && strcmp(pfile->d_name, ".."))
                {
                    if (is_recursion)
                        extract_filename(new_file, file_list, is_recursion);
                }

                if (is_file(new_file))
                {
                    file_list.push_back(new_file);
                }
            }
            return true;
        }

        std::vector<std::string> split(const std::string &s, const std::string &delim)
        {
            std::vector<std::string> elems;
            size_t pos = 0;
            size_t len = s.length();
            size_t delim_len = delim.length();
            if (delim_len == 0)
                return elems;
            while (pos < len)
            {
                int find_pos = s.find(delim, pos);
                if (find_pos < 0)
                {
                    elems.push_back(s.substr(pos, len - pos));
                    break;
                }
                elems.push_back(s.substr(pos, find_pos - pos));
                pos = find_pos + delim_len;
            }
            return elems;
        }

        // default only owner can read/write/exe, others can read and exe, can't write
        int mkdir_n(std::string path, bool is_recursion)
        {
            int mode = 0755;
            if (is_dir(path))
            {
                return -1;
            }

            if (!is_recursion)
            {
                return mkdir(path.c_str(), mode);
            }
            else
            {
                std::string::size_type tmp_pos_begin = 0;
                std::string::size_type tmp_pos = 0;
                tmp_pos = path.find('/', tmp_pos_begin);
                while (tmp_pos != path.npos)
                {
                    std::string tmpdir = path.substr(0, tmp_pos);
                    if (tmpdir.empty())
                    {
                        return 0;
                    }
                    if (!is_dir(tmpdir))
                    {
                        mkdir(tmpdir.c_str(), mode);
                    }
                    tmp_pos_begin = tmp_pos + 1;
                    tmp_pos = path.find('/', tmp_pos_begin);
                }
                return 0;
            }
        }

        bool get_lines(std::string file, std::vector<std::string> &lines)
        {
            std::ifstream fs(file);
            if (!fs.is_open())
            {
                return false;
            }
            
            std::string line;
            while (std::getline(fs, line))
            {
                lines.emplace_back(line);
            }
            fs.close();
            return true;
        }
    }
}

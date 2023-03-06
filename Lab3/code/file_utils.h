#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include "stream_utils.h"

#include "array4d.h"

template <class T>
class File_utils {

public:
    File_utils(std::string file_name);
    ~File_utils();
    void parse_file();

    const std::string &getFile_name() const;
    void setFile_name(const std::string &file_name);
    const std::vector<std::string> &getFile_contents() const;
    void setFile_contents(const std::vector<std::string> &file_contents);

    std::vector<std::string> split(const std::string &str, const std::string &delim);

    int get_initial_input(Array3D<T>& input, int &padding, int &step_size);
    int get_initial_kernel(Array4D<T>& kernel);
    int get_stream_initial_input(Stream<T>& input, int &padding, int &step_size);
private:
    std::string file_name;
    std::vector<std::string> file_contents;
};

template <class T>
File_utils<T>::File_utils(std::string file_name) {
    this->file_name = file_name;
}

template <class T>
File_utils<T>::~File_utils() {
    file_contents.clear();
}

template <class T>
void File_utils<T>::parse_file() {
    std::ifstream fin;
    fin.open(file_name, std::ios::out | std::ios::in);

    if(!fin)
    {
        std::cout << "cannot open file!" << std::endl;
        exit(1);
    }

    char line[1024];

    while(fin.getline(line, sizeof(line)))
    {
        if (std::string(line).compare("") != 0) {
            file_contents.push_back(line);
        }
    }

    fin.close();
}


template <class T>
int File_utils<T>::get_initial_input(Array3D<T>& input, int &padding, int &step_size) {
    std::vector<std::string> parameters = split(file_contents[0], std::string(" "));

    int height = stoi(parameters[0]);
    int width = stoi(parameters[1]);
    int channel = stoi(parameters[2]);

    padding = stoi(parameters[3]);
    step_size = stoi(parameters[4]);

    input.resize(height, width, channel);

    for (int i = 1; i < file_contents.size(); i++) {
        std::vector<std::string> contents = split(file_contents[i], std::string(" "));
        for (int j = 0; j < width; j++) {
            for (int m = 0; m < channel; m++) {
                input[i-1][j][m] = stoi(contents[j * channel + m]);
            }
        }
    }

    return 0;
}

template <class T>
int File_utils<T>::get_initial_kernel(Array4D<T> &kernel) {
    std::vector<std::string> parameters = split(file_contents[0], std::string(" "));

    int dimension = stoi(parameters[0]);
    int height = stoi(parameters[1]);
    int width = stoi(parameters[2]);
    int channel = stoi(parameters[3]);

    kernel.resize(dimension, height, width, channel);

    for (int i = 1; i < file_contents.size(); i++) {
        std::vector<std::string> contents = split(file_contents[i], std::string(" "));
        for (int j = 0; j < height; j++) {
            for (int m = 0; m < width; m++) {
                for (int n = 0; n < channel; n++) {
                    kernel[i-1][j][m][n] = stoi(contents[j * channel * width + m * channel + n]);
                }
            }
        }
    }

    return 0;
}

template <class T>
int File_utils<T>::get_stream_initial_input(Stream<T>& input, int &padding, int &step_size) {
    std::vector<std::string> parameters = split(file_contents[0], std::string(" "));

    int height = stoi(parameters[0]);
    int width = stoi(parameters[1]);
    int channel = stoi(parameters[2]);

    padding = stoi(parameters[3]);
    step_size = stoi(parameters[4]);

    input.clear();

    for (int i = 1; i < file_contents.size(); i++) {
        std::vector<std::string> contents = split(file_contents[i], std::string(" "));
        for (int j = 0; j < width; j++) {
            for (int m = 0; m < channel; m++) {
                input.write(stoi(contents[j * channel + m]));
            }
        }
    }

    return 0;
}


template <class T>
const std::string &File_utils<T>::getFile_name() const {
    return file_name;
}

template <class T>
void File_utils<T>::setFile_name(const std::string &file_name) {
    File_utils::file_name = file_name;
}

template <class T>
const std::vector<std::string> &File_utils<T>::getFile_contents() const {
    return file_contents;
}

template <class T>
void File_utils<T>::setFile_contents(const std::vector<std::string> &file_contents) {
    File_utils::file_contents = file_contents;
}

template <class T>
std::vector<std::string> File_utils<T>::split(const std::string &str, const std::string &delim) {
    std::vector<std::string> res;
    if(str == "") return res;

    char *strs = new char[str.length() + 1];
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while(p) {
        std::string s = p;
        res.push_back(s);
        p = strtok(NULL, d);
    }

    return res;
}

#endif //FILE_UTILS_H

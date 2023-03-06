#ifndef TEST_H
#define TEST_H

#include "network.h"
#include <string>
#include <vector>

template <class T>
class Test {
public:
    Test(std::string model_path);
    void initialize();
    void generate_layer_file_paths();
    void generate_parameter_file();
    void generate_input_kernel();

    void generate_matrix();
    void input_matrix_tofile(int layer_id, Array2D<T> &input_matrix);
    void kernel_matrix_tofile(int layer_id, Array2D<T> &kernel_matrix);

    void generate_stream();
    void stream_tofile(int layer_id, Stream<T> &stream_input_matrix);

    const std::vector<int> &getPaddings() const;
    void setPaddings(const std::vector<int> &paddings);
    const std::vector<int> &getStrides() const;
    void setStrides(const std::vector<int> &strides);
    Network<T> *getNetwork() const;

private:
    std::string model_path;
    std::string model_cfg_file_path;
    std::string model_parameter_file_path;

    std::vector<std::string> initial_kernel_file_paths;
    std::vector<std::string> kernel_matrix_file_paths;

    std::vector<std::string> initial_input_file_paths;
    std::vector<std::string> input_matrix_file_paths;

    std::vector<std::string> stream_input_matrix_file_paths;

    std::vector<int> paddings;
    std::vector<int> strides;

    Network<T> *network;
};

template <class T>
Test<T>::Test(std::string model_path) {
    this->model_path = model_path;
    model_cfg_file_path = model_path + ".cfg";
    model_parameter_file_path = model_path + ".parameter";

    initial_kernel_file_paths.clear();
    kernel_matrix_file_paths.clear();

    initial_input_file_paths.clear();
    input_matrix_file_paths.clear();

    stream_input_matrix_file_paths.clear();
}

template <class T>
void Test<T>::initialize() {
    network = new Network<T>(model_cfg_file_path);
    network->initialize();
}

template <class T>
void Test<T>::generate_parameter_file() {
    network->obtain_parameters();

    std::ofstream parameter_ofstream(model_parameter_file_path, std::ofstream::trunc);
    parameter_ofstream << network->get_parameters();
    parameter_ofstream.close();
}

template <class T>
void Test<T>::generate_layer_file_paths() {
    initial_kernel_file_paths.clear();
    kernel_matrix_file_paths.clear();

    initial_input_file_paths.clear();
    input_matrix_file_paths.clear();

    stream_input_matrix_file_paths.clear();

    for (int i = 0; i < network->getLayer_number(); i++) {
        std::string initial_kernel_file_path = model_path + ".layer_" + std::to_string(i) + ".initial_kernel";
        std::string initial_input_file_path = model_path + ".layer_" + std::to_string(i) + ".initial_input";
        std::string stream_initial_input_file_path = model_path + ".layer_" + std::to_string(i) + ".initial_input.stream";

        initial_kernel_file_paths.push_back(initial_kernel_file_path);
        initial_input_file_paths.push_back(initial_input_file_path);

        std::string kernel_matrix_file_path = model_path + ".layer_" + std::to_string(i) + ".kernel_matrix";
        std::string input_matrix_file_path = model_path + ".layer_" + std::to_string(i) + ".input_matrix";
        std::string stream_input_matrix_file_path = model_path + ".layer_" + std::to_string(i) + ".input_matrix.stream";

        kernel_matrix_file_paths.push_back(kernel_matrix_file_path);
        input_matrix_file_paths.push_back(input_matrix_file_path);
        stream_input_matrix_file_paths.push_back(stream_input_matrix_file_path);
    }

}

template <class T>
void Test<T>::generate_input_kernel() {

    for (int s = 0; s < initial_input_file_paths.size(); s++) {
        std::string file_name = initial_input_file_paths[s];

        std::ofstream file_ofstream(file_name, std::ofstream::trunc);
        std::string input_contents = "";

        int height = network->getInput_height()[s];
        int width = network->getInput_width()[s];
        int channel = network->getInput_channel()[s];
        int padding = paddings[s];
        int stride = strides[s];

        input_contents += std::to_string(height);
        input_contents += " ";
        input_contents += std::to_string(width);
        input_contents += " ";
        input_contents += std::to_string(channel);
        input_contents += " ";
        input_contents += std::to_string(padding);
        input_contents += " ";
        input_contents += std::to_string(stride);
        input_contents += "\n";

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int m = 0; m < channel; m++) {
                    input_contents += std::to_string(rand() % 10);
                    input_contents += " ";
                }
            }
            input_contents += "\n";
        }

        file_ofstream << input_contents;
        file_ofstream.close();
    }

    for (int s = 0; s < initial_kernel_file_paths.size(); s++) {
        std::string file_name = initial_kernel_file_paths[s];

        std::ofstream file_ofstream(file_name, std::ofstream::trunc);
        std::string kernel_contents = "";

        int dimension = network->getKernel_dimension()[s];
        int height = network->getKernel_size()[s];
        int width = network->getKernel_size()[s];
        int channel = network->getKernel_channel()[s];

        kernel_contents += std::to_string(dimension);
        kernel_contents += " ";
        kernel_contents += std::to_string(height);
        kernel_contents += " ";
        kernel_contents += std::to_string(width);
        kernel_contents += " ";
        kernel_contents += std::to_string(channel);
        kernel_contents += "\n";

        for (int m = 0; m < dimension; m++) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    for (int n = 0; n < channel; n++) {
                        kernel_contents += std::to_string(rand() % 10);
                        kernel_contents += " ";
                    }
                }
            }
            kernel_contents += "\n";
        }

        file_ofstream << kernel_contents;
        file_ofstream.close();
    }
}

template <class T>
void Test<T>::generate_matrix() {
    for (int i = 0; i < network->getLayer_number(); i++) {
        File_utils<T> *input_util = new File_utils<T>(initial_input_file_paths[i]);
        input_util->parse_file();

        File_utils<T> *kernel_util = new File_utils<T>(initial_kernel_file_paths[i]);
        kernel_util->parse_file();

        Array3D<T> initial_input;
        int padding, step_size;
        input_util->get_initial_input(initial_input, padding, step_size);

        Array4D<T> initial_kernel;
        kernel_util->get_initial_kernel(initial_kernel);

        Array2D<T> input_matrix;
        Array2D<T> kernel_matrix;

        network->conv_convert(i, padding, step_size, initial_input, initial_kernel, input_matrix, kernel_matrix);

        input_matrix_tofile(i, input_matrix);
        kernel_matrix_tofile(i, kernel_matrix);
    }
}

template <class T>
void Test<T>::generate_stream(){
    for (int i = 0; i < network->getLayer_number(); i++) {
        File_utils<T> *stream_input_util = new File_utils<T>(initial_input_file_paths[i]);
        stream_input_util->parse_file();

        Stream<T> initial_input_stream;
        int padding, step_size;
        stream_input_util->get_stream_initial_input(initial_input_stream, padding, step_size);

        Stream<T> input_matrix_stream;

        network->conv_convert_stream(i, padding, step_size, initial_input_stream, input_matrix_stream);

        stream_tofile(i, input_matrix_stream);
    }
}

template <class T>
void Test<T>::input_matrix_tofile(int layer_id, Array2D<T> &input_matrix) {

    std::string input_matrix_str = "";

    for (int i = 0; i < input_matrix.Size_2d(); i++) {
        for (int j = 0; j < input_matrix.Size_1d(); j++) {
            input_matrix_str += std::to_string(input_matrix[i][j]);
            if (j != input_matrix.Size_1d() - 1)
                input_matrix_str += " ";
            else
                input_matrix_str += "\n";
        }
    }

    std::ofstream input_matrix_ofstream(input_matrix_file_paths[layer_id], std::ofstream::trunc);
    input_matrix_ofstream << input_matrix_str;
    input_matrix_ofstream << std::endl;
    input_matrix_ofstream.close();
}

template <class T>
void Test<T>::kernel_matrix_tofile(int layer_id, Array2D<T> &kernel_matrix) {
    std::string kernel_matrix_str = "";

    for (int i = 0; i < kernel_matrix.Size_2d(); i++) {
        for (int j = 0; j < kernel_matrix.Size_1d(); j++) {
            kernel_matrix_str += std::to_string(kernel_matrix[i][j]);
            if (j != kernel_matrix.Size_1d() - 1)
                kernel_matrix_str += " ";
            else
                kernel_matrix_str += "\n";
        }
    }

    std::ofstream input_matrix_ofstream(kernel_matrix_file_paths[layer_id], std::ofstream::trunc);
    input_matrix_ofstream << kernel_matrix_str;
    input_matrix_ofstream << std::endl;
    input_matrix_ofstream.close();
}


template <class T>
void Test<T>::stream_tofile(int layer_id, Stream<T> &stream_input_matrix) {
    std::string stream_input_matrix_str = "";
    int i = 0;
    int matrix_width = network->getKernel_size()[layer_id] *
            network->getKernel_size()[layer_id] *
            network->getInput_channel()[layer_id];

    while (!stream_input_matrix.empty()) {
        i++;
        stream_input_matrix_str += std::to_string(stream_input_matrix.read());
        stream_input_matrix_str += " ";
        if (i == matrix_width) {
            i = 0;
            stream_input_matrix_str += "\n";
        }
    }

    stream_input_matrix_str += "\n";

    std::ofstream input_matrix_ofstream(stream_input_matrix_file_paths[layer_id], std::ofstream::trunc);
    input_matrix_ofstream << stream_input_matrix_str;
    input_matrix_ofstream << std::endl;
    input_matrix_ofstream.close();
}

template<class T>
const std::vector<int> &Test<T>::getPaddings() const {
    return paddings;
}

template<class T>
void Test<T>::setPaddings(const std::vector<int> &paddings) {
    Test::paddings = paddings;
}

template<class T>
const std::vector<int> &Test<T>::getStrides() const {
    return strides;
}

template<class T>
void Test<T>::setStrides(const std::vector<int> &strides) {
    Test::strides = strides;
}

template<class T>
Network<T> *Test<T>::getNetwork() const {
    return network;
}

#endif

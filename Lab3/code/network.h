#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <map>

#include "file_utils.h"
#include "stream_utils.h"
#include "array4d.h"

template <class T>
class Network {
public:
    Network(std::string cfg_file_name);
    ~Network();

    int obtain_parameters();
    int conv_convert(int layer_id, int padding, int stride, Array3D<T>& initial_input, Array4D<T>& initial_kernel,
             Array2D<T>& input_matrix, Array2D<T>& kernel_matrix);
    int conv_convert_stream(int layer_id, int padding, int stride, Stream<T>& input, Stream<T>& output);

    void initialize();
    std::string get_parameters();

    const std::vector<int> &getInput_height() const;
    void setInput_height(const std::vector<int>& input_height);
    const std::vector<int> &getInput_width() const;
    void setInput_width(const std::vector<int>& input_width);
    const std::vector<int> &getInput_channel() const;
    void setInput_channel(const std::vector<int>& input_channel);

    const std::vector<int> &getKernel_dimension() const;
    void setKernel_dimension(const std::vector<int>& kernel_dimension);
    const std::vector<int> &getKernel_size() const;
    void setKernel_size(const std::vector<int> &kernel_size);
    const std::vector<int> &getKernel_channel() const;
    void setKernel_channel(const std::vector<int> &kernel_channel);

    const std::vector<int> &getOutput_height() const;
    void setOutput_height(const std::vector<int> &output_height);
    const std::vector<int> &getOutput_width() const;
    void setOutput_width(const std::vector<int> &output_width);
    const std::vector<int> &getOutput_channel() const;
    void setOutput_channel(const std::vector<int> &output_channel);

    int getLayer_number() const;
    void setLayer_number(int layer_number);

private:
    int layer_number;

    std::vector<int> input_height;
    std::vector<int> input_width;
    std::vector<int> input_channel;

    std::vector<int> kernel_dimension;
    std::vector<int> kernel_size;
    std::vector<int> kernel_channel;

    std::vector<int> output_height;
    std::vector<int> output_width;
    std::vector<int> output_channel;

    std::string cfg_file_name;
    File_utils<T> *cfg_util;
    std::vector<std::string> network_cfg_description;
};

template <class T>
Network<T>::Network(std::string cfg_file_name) {
    this->cfg_file_name = cfg_file_name;
}

template <class T>
Network<T>::~Network() {
    input_height.clear();
    input_width.clear();
    input_channel.clear();

    kernel_dimension.clear();
    kernel_size.clear();
    kernel_channel.clear();

    output_height.clear();
    output_width.clear();
    output_channel.clear();

    delete(cfg_util);
}

template <class T>
void Network<T>::initialize() {
    cfg_util = new File_utils<T>(cfg_file_name);
    cfg_util->parse_file();
}

template<class T>
std::string Network<T>::get_parameters() {
    std::string parameters = std::to_string(layer_number);
    parameters += "\n";
    for (int i = 0; i < layer_number; i++) {
        parameters += std::to_string(input_height[i]);
        parameters += " ";
        parameters += std::to_string(input_width[i]);
        parameters += " ";
        parameters += std::to_string(input_channel[i]);
        parameters += " ";

        parameters += std::to_string(kernel_dimension[i]);
        parameters += " ";
        parameters += std::to_string(kernel_size[i]);
        parameters += " ";
        parameters += std::to_string(kernel_channel[i]);
        parameters += " ";

        parameters += std::to_string(output_height[i]);
        parameters += " ";
        parameters += std::to_string(output_width[i]);
        parameters += " ";
        parameters += std::to_string(output_channel[i]);
        parameters += " ";
        parameters += "\n";
    }
    return parameters;
}


template<class T>
const std::vector<int> &Network<T>::getInput_height() const {
    return input_height;
}

template<class T>
void Network<T>::setInput_height(const std::vector<int> &input_height) {
    Network::input_height = input_height;
}

template<class T>
const std::vector<int> &Network<T>::getInput_width() const {
    return input_width;
}

template<class T>
void Network<T>::setInput_width(const std::vector<int> &input_width) {
    Network::input_width = input_width;
}

template<class T>
const std::vector<int> &Network<T>::getInput_channel() const {
    return input_channel;
}

template<class T>
void Network<T>::setInput_channel(const std::vector<int> &input_channel) {
    Network::input_channel = input_channel;
}

template<class T>
const std::vector<int> &Network<T>::getKernel_dimension() const {
    return kernel_dimension;
}

template<class T>
void Network<T>::setKernel_dimension(const std::vector<int> &kernel_dimension) {
    Network::kernel_dimension = kernel_dimension;
}

template<class T>
const std::vector<int> &Network<T>::getKernel_size() const {
    return kernel_size;
}

template<class T>
void Network<T>::setKernel_size(const std::vector<int> &kernel_size) {
    Network::kernel_size = kernel_size;
}

template<class T>
const std::vector<int> &Network<T>::getKernel_channel() const {
    return kernel_channel;
}

template<class T>
void Network<T>::setKernel_channel(const std::vector<int> &kernel_channel) {
    Network::kernel_channel = kernel_channel;
}

template<class T>
const std::vector<int> &Network<T>::getOutput_height() const {
    return output_height;
}

template<class T>
void Network<T>::setOutput_height(const std::vector<int> &output_height) {
    Network::output_height = output_height;
}

template<class T>
const std::vector<int> &Network<T>::getOutput_width() const {
    return output_width;
}

template<class T>
void Network<T>::setOutput_width(const std::vector<int> &output_width) {
    Network::output_width = output_width;
}

template<class T>
const std::vector<int> &Network<T>::getOutput_channel() const {
    return output_channel;
}

template<class T>
void Network<T>::setOutput_channel(const std::vector<int> &output_channel) {
    Network::output_channel = output_channel;
}

template<class T>
int Network<T>::getLayer_number() const {
    return layer_number;
}

template<class T>
void Network<T>::setLayer_number(int layer_number) {
    Network::layer_number = layer_number;
}

/***************************************************************/
/* Do not modify the above code.
   You are allowed to use the following global variables in your
   code. These are defined above.

   Begin your code here 	  			       */
/***************************************************************/

template <class T>
int Network<T>::obtain_parameters() {
    network_cfg_description = cfg_util->getFile_contents();

    layer_number = 0;
    int total_layers = 0;

    input_height.clear();
    input_width.clear();
    input_channel.clear();

    kernel_dimension.clear();
    kernel_size.clear();
    kernel_channel.clear();

    output_height.clear();
    output_width.clear();
    output_channel.clear();
    /* Part I */
    /* Write your code here */

    // vectors for configuration of all layers
    std::vector<int> ip_height;
    std::vector<int> ip_width;
    std::vector<int> ip_channels;
    std::vector<int> op_height;
    std::vector<int> op_width;
    std::vector<int> op_channels;
    std::vector<int> k_channels;
    std::vector<int> k_dimension;
    std::vector<int> k_size;
    std::vector<int> stride;
    std::vector<int> padding;
    std::vector<char> layer_name;
    char layer_char;

    ip_height.clear();
    ip_width.clear();
    ip_channels.clear();
    op_height.clear();
    op_width.clear();
    op_channels.clear();
    k_channels.clear();
    k_dimension.clear();
    k_size.clear();
    stride.clear();
    padding.clear();
    layer_name.clear();

    for( int i = 0; i < network_cfg_description.size(); i++)
    {
        //printf("%s\n", network_cfg_description[i].c_str()); 
        std::string s = network_cfg_description[i];
        std::string delimiter = "=";
        std::string token = s.substr(0, s.find(delimiter));
        std::string value = s.substr(s.find(delimiter)+1);
        if (token == "[convolutional]")
        { 
            layer_char = 'c';
            layer_name.push_back(layer_char);
            layer_number++;
            total_layers++; 
        }
        else if (token == "[maxpool]")
        {
            layer_char = 'm';
            layer_name.push_back(layer_char);
            total_layers++; 
            padding.push_back(0);
            int k_dimension_size = k_dimension.size();
            k_dimension.push_back(k_dimension[k_dimension_size-1]);
        }
        else if (token == "height")
        {
            ip_height.push_back(stoi(value));
        }
        else if (token == "width")
        {
            ip_width.push_back(stoi(value));
        }
        else if (token == "channels")
        {
            ip_channels.push_back(stoi(value));
            k_channels.push_back(stoi(value));
        }
        else if (token == "filters")
        {
            k_dimension.push_back(stoi(value));
        }
        else if (token == "size")
        {
            k_size.push_back(stoi(value));
        }
        else if (token == "stride")
        {
            stride.push_back(stoi(value));
        }
        else if (token == "pad")
        {
            padding.push_back(stoi(value));
        }
    }

    // populate local variables for first convolution layer
    op_width.push_back((((ip_width[0] - k_size[0] + 2*padding[0])/stride[0]) + 1));
    op_height.push_back((((ip_height[0] - k_size[0] + 2*padding[0])/stride[0]) + 1));
    op_channels.push_back(k_dimension[0]);

    // populate member variables for first convolution layer
    input_width.push_back(ip_width[0]);
    input_height.push_back(ip_height[0]);
    input_channel.push_back(ip_channels[0]);
    kernel_dimension.push_back(k_dimension[0]);
    kernel_size.push_back(k_size[0]);
    kernel_channel.push_back(k_channels[0]);
    output_width.push_back(op_width[0]);
    output_height.push_back(op_height[0]);
    output_channel.push_back(op_channels[0]);

    // populate local variables for all remaining layers and member variables for only remaining convolutional layer
    for (int i = 1; i < total_layers; i++)
    {
        // local varibales
        ip_width.push_back(op_width[i-1]); 
        ip_height.push_back(op_height[i-1]);
        ip_channels.push_back(op_channels[i-1]);
        k_channels.push_back(op_channels[i-1]);
        op_width[i] = (((ip_width[i] - k_size[i] + 2*padding[i])/stride[i]) + 1);
        op_height[i] = (((ip_height[i] - k_size[i] + 2*padding[i])/stride[i]) + 1);
        op_channels[i] = k_dimension[i];
        if (layer_name[i] == 'c')
        {
            // member variables
            input_width.push_back(ip_width[i]);
            input_height.push_back(ip_height[i]);
            input_channel.push_back(ip_channels[i]);
            kernel_dimension.push_back(k_dimension[i]);
            kernel_size.push_back(k_size[i]);
            kernel_channel.push_back(k_channels[i]);
            output_width.push_back(op_width[i]);
            output_height.push_back(op_height[i]);
            output_channel.push_back(op_channels[i]);
        }
    }
    return 0;
}

template <class T>
int Network<T>::conv_convert(int layer_id, int padding, int stride, Array3D<T>& initial_input, Array4D<T>& initial_kernel,
                              Array2D<T>& input_matrix, Array2D<T>& kernel_matrix) {
    /* Part II */
    /*Write your code here*/

    // calculate kernel matrix
    int num_filters = initial_kernel.Size_4d();
    int k_width = initial_kernel.Size_3d();
    int k_height = initial_kernel.Size_2d();
    int num_k_channels = initial_kernel.Size_1d();
    
    Array1D<T> row(k_width*k_height*num_k_channels);
    kernel_matrix.resize(k_width*k_height*num_k_channels, num_filters);
    
    for (int i = 0; i < num_filters; i++)
    {
        for (int j = 0; j < num_k_channels; j++)
        {
            for (int m = 0; m < k_height; m++)
            {
                for (int n = 0; n < k_width; n++)
                {
                    row[j*k_width*k_height + m*k_width + n] = initial_kernel[i][m][n][j]; 
                } 
            } 
        }
        for (int l = 0; l < k_width*k_height*num_k_channels; l++)
        {
            kernel_matrix[l][i] = row[l];  
        }
    }
    
    // calculate input feature matrix
    int ip_height = initial_input.Size_3d();
    int ip_width = initial_input.Size_2d();    
    int ip_channels = initial_input.Size_1d();
    
    // padding
    int ip_height_padded = ip_height + 2*padding;
    int ip_width_padded = ip_width + 2*padding;
    
    Array3D<T> input_padded(ip_height_padded, ip_width_padded, ip_channels);
    int temp;
    for (int k = 0; k < ip_channels; k++)
    {
        for (int i = 0; i < ip_height_padded; i++)
        {
            for (int j = 0; j < ip_width_padded; j++)
            {
                if ((i < padding) | (i > (ip_height_padded-1-padding)) | (j < padding) | (j > (ip_width_padded-1-padding)))
                {
                    input_padded[i][j][k] = 0;
                }
                else
                {
                    temp = initial_input[i-padding][j-padding][k];
                    input_padded[i][j][k] = temp;
                }
            }
        }
    }

    // sliding window by stride
    int index;
    Array2D<T> window(k_width, k_height);

    int op_width = ((ip_width - k_width + 2*padding)/stride) + 1;
    int op_height = ((ip_height - k_height + 2*padding)/stride) + 1;

    input_matrix.resize(op_width*op_height, k_width*k_height*ip_channels);

    for (int j = 0; j < ip_channels; j++)
    {
        index = 0;
        for (int m = 0; m < ip_height_padded; m+=stride)
        {
            for (int n = 0; n < ip_width_padded; n+=stride)
            {
                if (((m+stride)<ip_height_padded) & ((n+stride)<ip_width_padded))
                {
                    // per channel sliding window
                    for (int i = 0; i < k_height; i++)
                    {
                        for (int s = 0; s < k_width; s++)
                        {
                            temp = input_padded[m+i][n+s][j];
                            window[i][s] = temp;
                        }
                    } 
                   
                    // increment row of input matrix
                    index++;
                    // populate row of input matrix
                    for (int x = 0; x < k_height; x++)
                    {
                        for (int y = 0; y < k_width; y++)
                        {
                            temp = window[x][y];
                            input_matrix[index-1][j*k_height*k_width + x*k_height + y] = temp;
                        }
                    }
                }
            }
        }
    }
    return 0;
}


template <class T>
int Network<T>::conv_convert_stream(int layer_id, int padding, int stride, Stream<T> &input, Stream<T> &output) {
    int buffer_size = (input_width[layer_id] + padding * 2) * input_channel[layer_id] * kernel_size[layer_id];
    T buffer[buffer_size];
    /* Part III */
    /*Write your code here*/
    for(int ip_mat_row=0; ip_mat_row<)
    return 0;
}

#endif //NETWORK_H

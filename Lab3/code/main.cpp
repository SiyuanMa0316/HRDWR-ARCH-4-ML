#include <iostream>
#include "file_utils.h"
#include "stream_utils.h"
#include "test.h"

int main(int argc, char **argv) {
    Test<int> *test = new Test<int>("./example_1/network_1"); // set benchmark
    test->initialize();
    test->generate_parameter_file();

    /********/ // we may change this part for testing
    std::vector<int> paddings;
    std::vector<int> strides;
    int layer_number = test->getNetwork()->getLayer_number();
    for (int i = 0; i < layer_number; i++) {
        paddings.push_back(1);
        strides.push_back(2);
    }
    test->setPaddings(paddings);
    test->setStrides(strides);
    /********/

    test->generate_layer_file_paths();
    test->generate_input_kernel();
    test->generate_matrix();
    test->generate_stream();

    return 0;
}

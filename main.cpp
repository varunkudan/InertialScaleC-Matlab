#include <iostream>
#include "libInertialScale.h"  // MATLAB-generated header
#include <filesystem>
#include <string>
#include <fstream>


int main(int argc, char** argv) {
    if(argc < 2)
    {
        std::cerr<<"Please enter the name of a valid dataset\n";
        return 1;
    }

    /*if(datasetInValid(argv[1]))
    {
        return 1;
    }*/

    // Initialize MATLAB Runtime
    if (!libInertialScaleInitialize()) {
        std::cerr << "Failed to initialize MATLAB Runtime." << std::endl;
        return -1;
    }

    // Call the MATLAB function
    std::string dataset = argv[1];
    mxArray* mxStr = mxCreateString(dataset.c_str());
    mxArray* output = NULL;

    
    if (!mlfScaleEstimationMain(1, &output, mxStr)) {
        std::cerr << "Error calling MATLAB function." << std::endl;
        mxDestroyArray(mxStr);  // Clean up mxArray before returning
        mclTerminateApplication();
        return -1;
    }

    if (output == nullptr) {
            std::cerr << "Error: MATLAB output is NULL!" << std::endl;
    } else {
        std::cout << "MATLAB function returned a valid mxArray." << std::endl;
    }

    std::ofstream outfile("output.txt");
    if (!outfile) {
        std::cerr << "Error opening the file for writing!" << std::endl;
        return -1;
    }

    double scale = 0;

    if (output != NULL) 
    {

        // Process the output (if needed)
        //char* result = mxArrayToString(output);
         double* result = mxGetPr(output);

        if (result == nullptr) {
        std::cerr << "Error: mxArrayToString returned NULL!" << std::endl;
        } else {
            outfile << *result << std::endl;
            std::cout << "MATLAB function returned: " << *result << std::endl;
            scale = *result;
            mxFree(result);  // Free the allocated memory
        }
    }

    outfile.close();

    // Terminate the library
    libInertialScaleTerminate();

    return 0;
}

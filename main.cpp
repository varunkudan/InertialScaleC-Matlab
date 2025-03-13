#include <iostream>
#include "libInertialScale.h"  // MATLAB-generated header
#include <filesystem>
#include <string>


bool datasetInValid(const std::string& dataset)
{
    std::string path = "data/"+dataset;

    if(!std::filesystem::is_directory(path))
    {
        std::cout<<"The dataset folder does not exits in data folder. Please check the name.\n"<<
                    "The dataset folder should be placed in the path 'InertialScaleC-Matlab/data/' \n";
        return true;
    }

    if(!std::filesystem::exists(path+"poses.txt"))
    {
        std::cout<<"The dataset folder does not contain poses.txt. Please add the poses.txt file\n";
        return true;
    }

    if(!std::filesystem::exists(path+"accelerometer.txt"))
    {
        std::cout<<"The dataset folder does not contain accelerometer.txt. Please add the poses.txt file\n";
        return true;
    }

    if(!std::filesystem::exists(path+"gyroscope.txt"))
    {
        std::cout<<"The dataset folder does not contain gyroscope.txt. Please add the poses.txt file\n";
        return true;
    }

    return false;
}

int main(int argc, char** argv) {
    if(argc < 2)
    {
        std::cerr<<"Please enter the name of a valid dataset\n";
        return 1;
    }

    if(datasetInValid(argv[1]))
    {
        return 1;
    }

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

    if (output != NULL) 
    {
        // Process the output (if needed)
        char* result = mxArrayToString(output);
        std::cout << "MATLAB function returned: " << result << std::endl;
        mxFree(result);  // Free the memory allocated by mxArrayToString
    }



    // Terminate the library
    libInertialScaleTerminate();

    return 0;
}

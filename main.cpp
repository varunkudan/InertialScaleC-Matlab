#include <iostream>
#include "libInertialScale.h"  // MATLAB-generated header
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>

int scaleTrajectory(double& scale, const std::string& input_path, const std::string& output_path)
{
    std::ifstream infile(input_path);  // Open the input text file
    std::ofstream outfile(output_path); // Create an output CSV file



    if (!infile) {
        std::cerr << "Error opening input file!" << std::endl;
        return -1;
    }

    if (!outfile) {
        std::cerr << "Error opening output file!" << std::endl;
        return -1;
    }

    double factor = 2.0;  // Scaling factor
    std::string line;

    while (std::getline(infile, line)) {  // Read each line
        std::stringstream ss(line);
        std::vector<double> values;
        double num;
        
        // Read numbers from the line
        while (ss >> num) {
            values.push_back(num);
        }

        // Ensure we have at least 4 columns
        if (values.size() < 4) {
            std::cerr << "Skipping line (not enough columns): " << line << std::endl;
            continue;
        }

        // Scale 2nd, 3rd, and 4th columns
        values[1] *= factor;
        values[2] *= factor;
        values[3] *= factor;

        // Write to CSV file
        for (size_t i = 0; i < values.size(); i++) {
            outfile << values[i];
            if (i < values.size() - 1) outfile << ",";  // Comma separation
        }
        outfile << "\n";
    }

    infile.close();
    outfile.close();
    return 0;
}


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

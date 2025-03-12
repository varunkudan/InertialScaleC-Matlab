#include <iostream>
#include "libInertialScale.h"  // MATLAB-generated header

int main() {
    // Initialize MATLAB Runtime
    if (!libInertialScaleInitialize()) {
        std::cerr << "Failed to initialize MATLAB Runtime." << std::endl;
        return -1;
    }

    // Call the MATLAB function
    std::string dataset = "scale_prep_2f_pose_localize_all";
    mxArray* mxStr = mxCreateString(dataset.c_str());
    mxArray* output = NULL;
    
    if (!mlfScaleEstimationMain(1, &output)) {
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

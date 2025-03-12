/*
 * MATLAB Compiler: 24.2 (R2024b)
 * Date: Wed Mar 12 18:19:12 2025
 * Arguments:
 * "-B""macro_default""-W""lib:libInertialScale""-T""link:lib""-d""./c_project""
 * -a""./code""ScaleEstimationMain.m"
 */

#ifndef libInertialScale_h
#define libInertialScale_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libInertialScale_C_API 
#define LIB_libInertialScale_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_libInertialScale_C_API 
bool MW_CALL_CONV libInertialScaleInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libInertialScale_C_API 
bool MW_CALL_CONV libInertialScaleInitialize(void);
extern LIB_libInertialScale_C_API 
void MW_CALL_CONV libInertialScaleTerminate(void);

extern LIB_libInertialScale_C_API 
void MW_CALL_CONV libInertialScalePrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_libInertialScale_C_API 
bool MW_CALL_CONV mlxScaleEstimationMain(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_libInertialScale_C_API bool MW_CALL_CONV mlfScaleEstimationMain(int nargout, mxArray** scale, mxArray* dataset);

#ifdef __cplusplus
}
#endif
/* C INTERFACE -- MLF WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#endif

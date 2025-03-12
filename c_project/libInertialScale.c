/*
 * MATLAB Compiler: 24.2 (R2024b)
 * Date: Wed Mar 12 18:19:12 2025
 * Arguments:
 * "-B""macro_default""-W""lib:libInertialScale""-T""link:lib""-d""./c_project""
 * -a""./code""ScaleEstimationMain.m"
 */

#define EXPORTING_libInertialScale 1
#include "libInertialScale.h"

static HMCRINSTANCE _mcr_inst = NULL; /* don't use nullptr; this may be either C or C++ */

#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

static int mclDefaultPrintHandler(const char *s)
{
    return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern C block */
#endif

#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

static int mclDefaultErrorHandler(const char *s)
{
    int written = 0;
    size_t len = 0;
    len = strlen(s);
    written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
    if (len > 0 && s[ len-1 ] != '\n')
        written += mclWrite(2 /* stderr */, "\n", sizeof(char));
    return written;
}

#ifdef __cplusplus
} /* End extern C block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libInertialScale_C_API
#define LIB_libInertialScale_C_API /* No special import/export declaration */
#endif

LIB_libInertialScale_C_API 
bool MW_CALL_CONV libInertialScaleInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
    if (_mcr_inst)
        return true;
    if (!mclmcrInitialize())
        return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream((void *)(libInertialScaleInitializeWithHandlers));
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(&_mcr_inst,
                                                             error_handler, 
                                                             print_handler,
                                                             ctfStream,
                                                             NULL);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
    return true;
}

LIB_libInertialScale_C_API 
bool MW_CALL_CONV libInertialScaleInitialize(void)
{
    return libInertialScaleInitializeWithHandlers(mclDefaultErrorHandler, 
                                                mclDefaultPrintHandler);
}

LIB_libInertialScale_C_API 
void MW_CALL_CONV libInertialScaleTerminate(void)
{
    if (_mcr_inst)
        mclTerminateInstance(&_mcr_inst);
}

LIB_libInertialScale_C_API 
void MW_CALL_CONV libInertialScalePrintStackTrace(void) 
{
    char** stackTrace;
    int stackDepth = mclGetStackTrace(&stackTrace);
    int i;
    for(i=0; i<stackDepth; i++)
    {
        mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
        mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
    }
    mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_libInertialScale_C_API 
bool MW_CALL_CONV mlxScaleEstimationMain(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[])
{
    return mclFeval(_mcr_inst, "ScaleEstimationMain", nlhs, plhs, nrhs, prhs);
}

LIB_libInertialScale_C_API 
bool MW_CALL_CONV mlfScaleEstimationMain(int nargout, mxArray** scale, mxArray* dataset)
{
    return mclMlfFeval(_mcr_inst, "ScaleEstimationMain", nargout, 1, 1, scale, dataset);
}


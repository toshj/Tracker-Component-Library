/**J2000F2ICRS Convert vectors from the J2000.0 dynamical frame to the
 *            International Celestial Reference System (ICRS). This
 *            involves applying a frame bias rotation.
 *
 *INPUTS:    vec         The 3XN matrix of N vectors that are to be rotated
 *                       from the J2000.0 dynamical frame into the ICRS.
 *           TT1, TT2    Two parts of a Julian date given in terrestrial
 *                       time (TT). The units of the date are days. The
 *                       full date is the sum of both terms. The date is
 *                       broken into two parts to provide more bits of
 *                       precision. It does not matter how the date is
 *                       split.
 *
 *OUTPUTS: retVec       The 3XN set of vectors rotated into the ICRS.
 *
 *As described in
 *G. Petit and B. Luzum, IERS Conventions (2010), International Earth
 *Rotation and Reference Systems Service Std. 36, 2010.
 *The ICRS is ofset from the J2000 dynamical frame by a bias rotation.
 *
 *This is a wrapper for the function iauBp06 and some matrix operations in
 *the International Astronomical Union's (IAU) Standard's of Fundamental
 *Astronomy library.
 *
 *The algorithm can be compiled for use in Matlab  using the
 *CompileCLibraries function.
 *
 *The algorithm is run in Matlab using the command format
 *retVec=J2000F2ICRS(vec,TT1,TT2);
 *
 *March 2014 David F. Crouse, Naval Research Laboratory, Washington D.C.
 */
/*(UNCLASSIFIED) DISTRIBUTION STATEMENT A. Approved for public release.*/

 /*This header is required by Matlab.*/
#include "mex.h"
/*This header is for the SOFA library.*/
#include "sofa.h"
#include "MexValidation.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    double *vec, *retVec, TT1,TT2;
    double rb[3][3], rp[3][3], rbp[3][3];
    mxArray *retMATLAB;
    size_t i, numItems;

    if(nrhs!=3){
        mexErrMsgTxt("Wrong number of inputs");
        return;
    }
    
    if(nlhs>1) {
        mexErrMsgTxt("Wrong number of outputs");
        return;
    }

    numItems=mxGetN(prhs[0]);
    if(mxGetM(prhs[0])!=3) {
       mexErrMsgTxt("vec has the wrong dimensionality. It must be an 3XN matrix.");
       return;
    }
    checkRealDoubleArray(prhs[0]);
    vec=(double*)mxGetData(prhs[0]);
    
    TT1=getDoubleFromMatlab(prhs[1]);
    TT2=getDoubleFromMatlab(prhs[2]);
    
    //Allocate the return vector
    retMATLAB=mxCreateDoubleMatrix(3,numItems,mxREAL);
    retVec=mxGetData(retMATLAB);
    
    //Call the IAU function to get the rotation matrix.
    iauBp06(TT1, TT2, rb, rp, rbp);
    for(i=0;i<numItems;i++) {
        //Multiply the original vectors by the matrix to put it into the ICRS.
        iauRxp(rb, vec+3*i, retVec+3*i);
    }
    
    //Set the return value.
    plhs[0]=retMATLAB;
}

/*LICENSE:
%
%The source code is in the public domain and not licensed or under
%copyright. The information and software may be used freely by the public.
%As required by 17 U.S.C. 403, third parties producing copyrighted works
%consisting predominantly of the material produced by U.S. government
%agencies must provide notice with such work(s) identifying the U.S.
%Government material incorporated and stating that such material is not
%subject to copyright protection.
%
%Derived works shall not identify themselves in a manner that implies an
%endorsement by or an affiliation with the Naval Research Laboratory.
%
%RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF THE
%SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY THE NAVAL
%RESEARCH LABORATORY FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE ACTIONS
%OF RECIPIENT IN THE USE OF THE SOFTWARE.*/

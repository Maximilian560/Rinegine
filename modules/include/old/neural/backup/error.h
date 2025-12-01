#pragma once

namespace RG_Neural {
  double ErrMSE(RG_Array<double>inout, RG_Array<double> real) {
    double out = 0;
    for (int i = 0; i < inout.size();i++) {
      out += pow(real[i] - inout[i], 2);
    }
    return (out / (double)inout.size());
  }

  double ErrCrossEntropy(RG_Array<double>inout, RG_Array<double> real) {
    double out = 0;
    for (int i = 0; i < inout.size();i++) {
      out += -(real[i] * log(inout[i]));
    }
    return (out);
  }
  RG_Map<double(*)(RG_Array<double>, RG_Array<double>)> ErrorFunc({
    {"MSE",ErrMSE},
    {"CrossEntropy",ErrCrossEntropy}
    });
};
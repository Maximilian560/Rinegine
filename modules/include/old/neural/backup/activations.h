#pragma once

namespace RG_Neural {
  ///////////////////////////////FUNC ACTIVATION
  RG_Array<double>Linear(const RG_Array<double> in) {
    return in;
  }
  RG_Array<double>Sigmoid(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    for (int i = 0; i < out.size();i++) {
      out[i] = (1.) / (1. + exp(-in[i]));
    }
    return out;
  }
  RG_Array<double>Tanh(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    for (int i = 0; i < out.size();i++) {
      out[i] = (exp(in[i]) - exp(-in[i])) / (exp(in[i]) + exp(-in[i]));
    }
    return out;
  }
  RG_Array<double> Softmax(const RG_Array<double> in) {
    double med = in.sum();
    RG_Array<double>ans(in.size());
    for (int i = 0; i < in.size();i++) {
      ans[i] = exp(in[i]) / med;
    }
    return ans;
  }

  RG_Array<double> SoftmaxFix(const RG_Array<double> in) {
    double maxVal = in.max(); // Находим максимальное значение в массиве
    double med = 0;
    for (int i = 0; i < in.size(); i++) {
        med += exp(in[i] - maxVal); // Стабилизируем вычисления
    }
    RG_Array<double>ans(in.size());
    for (int i = 0; i < in.size(); i++) {
        ans[i] = exp(in[i] - maxVal) / med;
    }
    return ans;
}


  RG_Array<double> Sinusoid(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    for (int i = 0; i < in.size();i++) {
      out[i] = sin(in[i]);
    }
    return out;
  }
  //double SigmoidTest(double x) {
  RG_Array<double> SigmoidTest(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    for (int i = 0; i < out.size();i++) {
      out[i] = 1.0 / (1.0 + exp(-in[i]));
    }
    return out;
  }
  RG_Array<double>DLinear(const RG_Array<double> in) {
    return RG_Array<double>(in.size(), 1);
  }
  RG_Array<double>DSigmoid(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    for (int i = 0; i < out.size();i++) {
      out[i] = (exp(-in[i])) / (pow(exp(-in[i]) + 1, 2));
    }
    return out;
  }
  RG_Array<double>DTanh(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    for (int i = 0; i < out.size();i++) {
      out[i] = (pow((exp(in[i]) + exp(-in[i])), 2) - pow((exp(in[i]) - exp(-in[i])), 2)) / (pow((exp(in[i]) + exp(-in[i])), 2));
    }
    return out;
  }
  RG_Array<double> DSoftmax(const RG_Array<double> in) {
    double med = in.sum();
    RG_Array<double>out(in.size());
    for (int i = 0; i < in.size();i++) {
      out[i] = exp(in[i]) / med;
    }
    return out;
  }
  RG_Array<double> DSigmoidTest(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    RG_Array<double> temp = SigmoidTest(in);
    for (int i = 0; i < out.size();i++) {
      out[i] = temp[i] * (1 - temp[i]);
    }
    return out;
  }
  RG_Array<double> DSinusoid(const RG_Array<double> in) {
    RG_Array<double>out(in.size());
    for (int i = 0; i < in.size();i++) {
      out[i] = cos(in[i]);
    }
    return out;
  }


  RG_Map<RG_Array<double>(*)(const RG_Array<double>)> Activations({
    {"linear",Linear},
    {"sigmoid",Sigmoid},
    {"tanh",Tanh},
    {"softmax",Softmax},
    {"sigmoidT",SigmoidTest},
    {"sinusoid",Sinusoid}
    });
  RG_Map<RG_Array<double>(*)(const RG_Array<double>)> DActivations({
    {"linear",DLinear},
    {"sigmoid",DSigmoid},
    {"tanh",DTanh},
    {"softmax",DSoftmax},
    {"sigmoidT",DSigmoidTest},
    {"sinusoid",DSinusoid}
    });
};
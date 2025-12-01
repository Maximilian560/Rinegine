#pragma once

/*
ТИПЫ
MLP Многослойный Перцептрон ✔
RNN Рекуррентные сети ○
CNN Свёрточная сеть ☓
DNN Глубокие сети ☓
GAN Генеративная сеть? ☓
*/
namespace RG_Neural {
  enum LayerType{
    FCL,  //Fully Connected Layer, Dense Layer
    CL,   //Convolutional Layer
    PL,   //Pooling Layer
    RL,   //Recurrent Layer
    BRL,  //Bidirectional Recurrent Layer
    LTSM, //Long Short-Term Memory, LSTM
    GRU,  //Gated Recurrent Unit, GRU
    NL,   //Normalization Layer
    AL,   //Activation Layer
    DL,   //Dropout Layer
    EL,   //Embedding Layer
    TL,   //Transformer Layer
  };
  struct Layer{
    RG_Array<double>NeuronsIN;
    RG_Array<double>NeuronsOUT;
    RG_Matrix<double>Widths;
    RG_Array<double>Errors;
    RG_Array<double>Biases;
    RG_Array<double>(*Activations)(RG_Array<double>);
    RG_Array<double>(*DActivations)(RG_Array<double>);
    LayerType Type;
  };

  struct Settings {
    RG_Array<int>Layers;
    RG_Array<string> Activations;
    RG_Array<string> DActivations;

    string ErrorFunc = "MSE";
    double learnStep = 0.1;
    bool Step_Reduct = false;
  };
  //namespace MSE {
#include "types/mlp.h"

//  };
//   namespace RNN{
// #include "types/rnn.h"
//   };
};
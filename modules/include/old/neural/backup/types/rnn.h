class Network {
  RG_Array<RG_Array<double>>Neurons;
  RG_Array<RG_Array<double>>Biases;
  RG_Array<RG_Matrix<double>>Widths;
  RG_Array<RG_Array<double>>Errors;

  RG_Array<RG_Array<double>(*)(RG_Array<double>)> Activations;
  RG_Array<RG_Array<double>(*)(RG_Array<double>)> DActivations;

  double(*ErrorFunc)(RG_Array<double>, RG_Array<double>);

  friend class Learn;
public:
  Settings set;
  Network() {}
  Network(Settings& set) { init(set); }
  Network(to_rvalue(string) path) { load(path); }

  void init() { init(set); }

  void init(Settings& set) {
    set.Layers.size() = 3;
    Neurons.init(set.Layers.size() * 2);
    for (int i = 0; i < Neurons.size();i++) {
      Neurons[i].init(set.Layers[i / 2]);
    }

    Biases.init(set.Layers.size() - 1);
    for (int i = 0; i < Errors.size();i++) {
      Errors[i].init(set.Layers[i + 1]);
      Biases[i].init(set.Layers[i + 1]);
      Biases[i].fill_range_random(-0.5, 0.5);
    }

    Widths.init(3);
    for(int i = 0; i<3;i++){
      Widths[i].init(1);
      Widths[i].fill_range_random(-0.5, 0.5);
    }
    if (set.Activations.size() == 0) {
      set.Activations = {"linear","than","sigmoid"};
    }
    set.DActivations.init(set.Activations);
    Activations.init(set.Layers.size());
    DActivations.init(set.Layers.size());

    ErrorFunc = RG_Neural::ErrorFunc[set.ErrorFunc];
    Errors.init(set.Layers.size() - 1);

    
  }
};
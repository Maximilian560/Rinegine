namespace MLP{
  class Learn;
}
class Network {
  //RG_Array<int>Layers;
  RG_Array<RG_Array<double>>Neurons;
  RG_Array<RG_Matrix<double>>Widths;
  RG_Array<RG_Array<double>>Errors;
  RG_Array<RG_Array<double>>Biases;
  //RG_Matrix<double>Biases;//todo
  RG_Array<RG_Array<double>(*)(RG_Array<double>)> Activations;
  RG_Array<RG_Array<double>(*)(RG_Array<double>)> DActivations;
  double(*ErrorFunc)(RG_Array<double>, RG_Array<double>);
  friend class MLP::Learn;
public:
  Settings set;
  Network() {}
  Network(Settings& set) { init(set); }
  Network(to_rvalue(string) path) { load(path); }

  void init() { init(set); }
  void init(Settings& set) {
    //Layers=set.Layers;
    //Neurons.init(set.Layers);
    Neurons.init(set.Layers.size() * 2);
    for (int i = 0; i < Neurons.size();i++) {
      Neurons[i].init(set.Layers[i / 2]);
    }
    Widths.init(set.Layers.size() - 1);
    for (int i = 0; i < set.Layers.size() - 1;i++) {
      Widths[i].init(set.Layers[i + 1], set.Layers[i]);
      //srand(1);
      Widths[i].fill_range_random(-0.5, 0.5);
    }
    if (set.Activations.size() == 0) {
      set.Activations.init(set.Layers.size(), "linear");
    }
    set.DActivations.init(set.Activations);
    Activations.init(set.Layers.size());
    DActivations.init(set.Layers.size());
    for (int i = 0; i < set.Layers.size();i++) {
      Activations[i] = RG_Neural::Activations[set.Activations[i]];
      DActivations[i] = RG_Neural::DActivations[set.DActivations[i]];
    }
    ErrorFunc = RG_Neural::ErrorFunc[set.ErrorFunc];
    Errors.init(set.Layers.size() - 1);
    Biases.init(set.Layers.size() - 1);
    for (int i = 0; i < Errors.size();i++) {
      Errors[i].init(set.Layers[i + 1]);
      Biases[i].init(set.Layers[i + 1]);
      Biases[i].fill_range_random(-0.5, 0.5);
    }
  }
  void fill(RG_Array<double>fl) {
    if (fl.size() != Neurons[0].size())RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "Size first layer of Neural Network not equal size fill array, size first layer '" + to_string(Neurons[0].size()) + "', size fill array '" + to_string(fl.size()) + "'");
    Neurons[0] = fl;
    /*for(int i = 0; i<Neurons[0].size();i++){
      [i]=fl[i];
    }*/
  }
  void run() {
    for (int i = 0; i < (Neurons.size() / 2) - 1;i++) {
      //rg_cout<<"Layer "<<i<<endl;
      Neurons[i * 2 + 1] = Activations[i](Neurons[(i * 2)]);
      Neurons[i * 2 + 2] = (Neurons[(i * 2 + 1)] * Widths[i]) + Biases[i];
    }
    //rg_cout<<"Done\n";
    Neurons[-1] = Activations[-1](Neurons[-2]);
    /*rg_cout<<L"Значение внешних слоёв нейронов:\n\n";
    for(int i = 1;i<Neurons.size();i+=2){
      rg_cout<<i/2<<L"-й слой:\n";
      for(int j = 0;j<Neurons[i].size();j++){
        rg_cout<<"  "<<Neurons[i][j]<<L" ";
      }
      rg_cout<<endl;
    }
    rg_cout<<L"Выходной слой:\n";
    for(int j = 0;j<Neurons[Neurons.size()-2].size();j++){
      rg_cout<<"  "<<Neurons[Neurons.size()-2][j]<<L" ";
    }
    rg_cout<<L"\nЗначение матриц весов:\n";
    for(int i = 0;i<Widths.size();i++){
      rg_cout<<i<<L"-й слой:\n";
      rg_cout<<"\"\n"; Widths[i].print(); rg_cout<<"\"";
      rg_cout<<endl<<endl;
    }
    rg_cout<<L"\nЗначение слоя смещения:\n";
    for(int i = 0;i<Biases.size();i++){
      rg_cout<<i+1<<L"-й слой:\n";
      for(int j = 0;j<Biases[i].size();j++){
        rg_cout<<"  "<<Biases[i][j]<<L" ";
      }
      rg_cout<<endl;
    }*/
  }
  void print() {
    rg_cout << L"Значение внешних слоёв нейронов:\n\n";
    for (int i = 1;i < Neurons.size();i += 2) {
      rg_cout << i / 2 << L"-й слой:\n";
      for (int j = 0;j < Neurons[i].size();j++) {
        rg_cout << "  " << Neurons[i][j] << L" ";
      }
      rg_cout << endl;
    }
    /*rg_cout<<L"Выходной слой:\n";
    for(int j = 0;j<Neurons[Neurons.size()-2].size();j++){
      rg_cout<<"  "<<Neurons[Neurons.size()-2][j]<<L" ";
    }*/
    /*rg_cout<<L"\nЗначение матриц весов:\n";
    for(int i = 0;i<Widths.size();i++){
      rg_cout<<i<<L"-й слой:\n";
      rg_cout<<"\"\n"; Widths[i].print(); rg_cout<<"\"";
      rg_cout<<endl<<endl;
    }
    rg_cout<<L"\nЗначение слоя смещения:\n";
    for(int i = 0;i<Biases.size();i++){
      rg_cout<<i+1<<L"-й слой:\n";
      for(int j = 0;j<Biases[i].size();j++){
        rg_cout<<"  "<<Biases[i][j]<<L" ";
      }
      rg_cout<<endl;
    }*/
  }
  void print_error(RG_Array<double>in) {
    double error = ErrorFunc(Neurons[-1], in);
    rg_cout << "\nNeural error " << error << endl;
  }
  void save(to_rvalue(string) path) {
    string save_file;
    save_file += "LAYERS\n";
    save_file += "SIZE " + to_string(set.Layers.size()) + "\n";
    for (int i = 0; i < set.Layers.size();i++) {
      save_file += " SIZE LAYER " + to_string(i) + ":" + to_string(set.Layers[i]) + "\n";
    }
    save_file += "\nEND\n";
    save_file += "\nACTIVATIONS\n";
    save_file += "SIZE " + to_string(set.Activations.size()) + "\n";
    for (int i = 0; i < set.Activations.size();i++) {
      save_file += " NAME " + to_string(i) + ":\"" + set.Activations[i] + "\"\n";
    }
    save_file += "\nEND\n";
    save_file += "\nERROR_FUNC\n";
    save_file += " NAME \"" + set.ErrorFunc + "\"\n";
    save_file += "\nEND\n";
    save_file += "\nLEARN_STEP\n";
    save_file += " VALUE " + to_string(set.learnStep) + "\n";
    save_file += "\nEND\n";
    save_file += "\nSTEP_REDUCT ";
    save_file += (set.Step_Reduct ? "TRUE" : "FALSE");
    save_file += "\n";


    /*save_file+="\nNEURONS\n";
    for(int i = 0; i<Neurons.size();i+=2){
      save_file+="LAYER "+to_string(i/2)+"\n";
      save_file+=" SIZE "+to_string(Neurons[i].size())+"\n";
      /*for(int j = 0; j<Neurons[i].size();j++){
        save_file += to_string(Neurons[i][j])+",";
      }* /
    }*/
    //save_file+="\nEND\n";
    save_file += "\nWIDTHS\n";
    for (int i = 0; i < Widths.size();i++) {
      save_file += "LAYER " + to_string(i) + "\n";
      save_file += " SIZE " + to_string(Widths[i].size(0)) + "/" + to_string(Widths[i].size(1)) + "\n  ";
      for (int y = 0; y < Widths[i].size(1);y++) {
        for (int x = 0; x < Widths[i].size(0);x++) {
          save_file += to_string(Widths[i].get(x, y));
          if (x != Widths[i].size(0) - 1)save_file += ", ";
        }
        save_file += "\n  ";
      }
      save_file += "\n";
    }
    save_file += "\nEND\n";
    save_file += "\nBIASES\n";
    for (int i = 0; i < Biases.size();i++) {
      save_file += "LAYER " + to_string(i) + "\n";
      save_file += "SIZE " + to_string(Biases[i].size()) + "\n";
      for (int y = 0; y < Biases[i].size();y++) {
        save_file += to_string(Biases[i][y]);
        if (y != Biases[i].size() - 1)save_file += ", ";
      }
      save_file += "\n";
    }
    save_file += "END\n";




    ofstream file(path);
    file << save_file;
    file.close();

  }
  void load(to_rvalue(string) path) {
    rg_cout<<"Loading neural network from: "<<rg_to_string(path)<<endl;
    string FILE = RG::FileLoad(path);
    if(FILE == RG_ERROR_STRING)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "Error loading neural network from: " + path);
    int SLayers = FILE.find("LAYERS") + 7;
    int SEnd = FILE.find("END", SLayers);
    if (SLayers == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "LAYERS in settings of neural network not found!");
    if (SEnd == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "END after LAYERS in settings of neural network not found!");
    enum NowWrite {
      WNONE,
      WSIZE,
      WSIZE_LAYER,
      WNAME,
      WVALUE,
      WLAYER,
      WWIDTHS,
      WBIAS
    }Now = WNONE;
    string temp;
    int tempi = 0;
    for (int i = SLayers;i != SEnd;i++) {
      if (Now == WNONE && RG_isSubstringAt(FILE[i], "SIZE LAYER")) { Now = WSIZE_LAYER;i += 11; }
      elif(Now == WNONE && RG_isSubstringAt(FILE[i], "SIZE")) { Now = WSIZE;i += 5; }
      if (Now == WSIZE) {
        if (FILE[i] == '\n') { Now = WNONE;set.Layers.resize(stoi(temp));temp.clear(); }
        elif(FILE[i] >= '0' && FILE[i] <= '9')
          temp += FILE[i];
      }
      if (Now == WSIZE_LAYER) {
        if (FILE[i] == '\n') { Now = WNONE;set.Layers[tempi] = (stoi(temp));temp.clear(); }
        elif(FILE[i] == ':') { tempi = stoi(temp);temp.clear(); }
        elif(FILE[i] >= '0' && FILE[i] <= '9')
          temp += FILE[i];
      }
    }
    Neurons.init(set.Layers.size() * 2);
    for (int i = 0; i < Neurons.size();i++) {
      Neurons[i].init(set.Layers[i / 2]);
    }

    temp.clear();
    tempi = 0;
    Now = WNONE;
    int SActivations = FILE.find("ACTIVATIONS") + 12;
    SEnd = FILE.find("END", SActivations);
    bool SText = false;
    if (SActivations == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "ACTIVATIONS in settings of neural network not found!");
    if (SEnd == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "END after ACTIVATIONS in settings of neural network not found!");

    for (int i = SActivations;i != SEnd;i++) {
      if (Now == WNONE && RG_isSubstringAt(FILE[i], "NAME")) { Now = WNAME;i += 5; }
      elif(Now == WNONE && RG_isSubstringAt(FILE[i], "SIZE")) { Now = WSIZE;i += 5; }

      if (Now == WSIZE) {
        if (FILE[i] == '\n') { Now = WNONE;set.Activations.resize(stoi(temp));temp.clear(); }
        elif(FILE[i] >= '0' && FILE[i] <= '9')
          temp += FILE[i];
      }
      if (Now == WNAME) {
        if (FILE[i] == '\n') { Now = WNONE;set.Activations[tempi] = temp;temp.clear();SText = false; }
        elif(FILE[i] == ':') { tempi = stoi(temp);temp.clear();SText = true; }
        elif((!SText && FILE[i] >= '0' && FILE[i] <= '9') || (SText && FILE[i] != '"'))
          temp += FILE[i];
      }
    }

    set.DActivations.init(set.Activations);
    Activations.init(set.Layers.size());
    DActivations.init(set.Layers.size());

    for (int i = 0; i < set.Layers.size();i++) {
      Activations[i] = RG_Neural::Activations[set.Activations[i]];
      DActivations[i] = RG_Neural::DActivations[set.DActivations[i]];
    }

    temp.clear();
    tempi = 0;
    Now = WNONE;
    int SError_Func = FILE.find("ERROR_FUNC") + 11;
    SEnd = FILE.find("END", SError_Func);
    SText = true;
    if (SError_Func == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "ERROR_FUNC in settings of neural network not found!");
    if (SEnd == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "END after ERROR_FUNC in settings of neural network not found!");

    for (int i = SError_Func;i != SEnd;i++) {
      if (Now == WNONE && RG_isSubstringAt(FILE[i], "NAME")) { Now = WNAME;i += 5; }

      if (Now == WNAME) {
        if (FILE[i] == '\n') { Now = WNONE;set.ErrorFunc = temp;temp.clear(); }
        elif((FILE[i] != '"' && FILE[i] != ' '))
          temp += FILE[i];
      }
    }
    ErrorFunc = RG_Neural::ErrorFunc[set.ErrorFunc];
    Errors.init(set.Layers.size() - 1);
    for (int i = 0; i < Errors.size();i++) {
      Errors[i].init(set.Layers[i + 1]);
    }

    temp.clear();
    tempi = 0;
    Now = WNONE;
    int SLearn_Srep = FILE.find("LEARN_STEP") + 11;
    SEnd = FILE.find("END", SLearn_Srep);
    SText = true;
    if (SLearn_Srep == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "LEARN_STEP in settings of neural network not found!");
    if (SEnd == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "END after LEARN_STEP in settings of neural network not found!");

    for (int i = SLearn_Srep;i != SEnd;i++) {
      if (Now == WNONE && RG_isSubstringAt(FILE[i], "VALUE")) { Now = WVALUE;i += 6; }

      if (Now == WVALUE) {
        if (FILE[i] == '\n') { Now = WNONE;set.learnStep = stoi(temp);temp.clear(); }
        elif(FILE[i] >= '0' && FILE[i] <= '9')
          temp += FILE[i];
      }
    }

    int SStepReduct = FILE.find("STEP_REDUCT");
    if (SActivations == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "STEP_REDUCT in settings of neural network not found!");
    for (int i = SStepReduct + 12; FILE[i] != '\n';i++) {
      if (FILE[i] != ' ')
        temp += FILE[i];
    }
    if (temp == "FALSE")set.Step_Reduct = false;elif(temp == "TRUE") set.Step_Reduct = true;else RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "STEP_REDUCT param is incorrect");

    temp.clear();
    tempi = 0;
    POINT2D<int> tempp;
    POINT2D<int> temppan;
    Now = WNONE;
    int SWidth = FILE.find("WIDTHS");
    SEnd = FILE.find("END", SWidth);
    SText = false;
    if (SWidth == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "WIDTHS in settings of neural network not found!");
    if (SEnd == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "END after WIDTHS in settings of neural network not found!");

    Widths.init(set.Layers.size() - 1);
    //Widths[i].init(set.Layers[i+1],set.Layers[i]);
    for (int i = SWidth;i != SEnd;i++) {
      if (Now == WNONE && RG_isSubstringAt(FILE[i], "LAYER")) { Now = WLAYER;i += 6; }
      elif(Now == WNONE && RG_isSubstringAt(FILE[i], "SIZE")) { Now = WSIZE;i += 5; }

      if (Now == WSIZE) {
        if (FILE[i] == '\n') { Now = WWIDTHS;tempp.y = stoi(temp); Widths[tempi].resize(tempp.x, tempp.y);temp.clear();i += 1; }
        elif(FILE[i] == '/') { tempp.x = stoi(temp);temp.clear(); }
        elif(FILE[i] >= '0' && FILE[i] <= '9')
          temp += FILE[i];
      }
      if (Now == WLAYER) {
        if (FILE[i] == '\n') { Now = WNONE;tempi = stoi(temp);temp.clear();continue; }
        elif((FILE[i] >= '0' && FILE[i] <= '9'))
          temp += FILE[i];
      }
      if (Now == WWIDTHS) {
        if (FILE[i] == ',' || FILE[i] == '\n') {
          //rg_cout<<"DEBUG TEST '"<<int(__LINE__)<<"', temp = "<<RG::utf8_decode(temp)<<" stod = "<< stold(temp) <<endl;
          if (temp.empty())continue;
          Widths[tempi].get(temppan) = stold(temp); temp.clear();

          if (FILE[i] == ',') { temppan.x++; }
          else { if (temppan.y == Widths[tempi].size(1) - 1) { Now = WNONE;temppan.y = 0;temppan.x = 0;continue; } else { temppan.y++;temppan.x = 0; } }
        }elif(FILE[i] >= '0' && FILE[i] <= '9' || FILE[i] == '.' || FILE[i] == '-') {
          temp += FILE[i];
        }

      }
    }



    temp.clear();
    tempi = 0;
    int tempp2 = 0;
    Now = WNONE;
    int SBias = FILE.find("BIASES");
    SEnd = FILE.find("END", SBias);
    SText = false;
    if (SActivations == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "BIASES in settings of neural network not found!");
    if (SEnd == string::npos)RG_Debug::addl(RG_LOG_LOCK_CRITICAL, "END after BIASES in settings of neural network not found!");

    Biases.init(set.Layers.size() - 1);
    for (int i = SBias;i != SEnd;i++) {
      if (Now == WNONE && RG_isSubstringAt(FILE[i], "LAYER")) { Now = WLAYER;i += 6; temp.clear(); }
      elif(Now == WNONE && RG_isSubstringAt(FILE[i], "SIZE")) { Now = WSIZE;i += 5; temp.clear(); }

      if (Now == WSIZE) {
        if (FILE[i] == '\n') { Now = WBIAS; Biases[tempi].resize(stoi(temp));temp.clear();continue; }
        elif(FILE[i] >= '0' && FILE[i] <= '9')
          temp += FILE[i];
        continue;
      }
      if (Now == WLAYER) {
        if (FILE[i] == '\n') { Now = WNONE;tempi = stoi(temp);  temp.clear(); }
        elif((FILE[i] >= '0' && FILE[i] <= '9'))
          temp += FILE[i];
        continue;
      }
      if (Now == WBIAS) {
        if (FILE[i] == ',' || FILE[i] == '\n') {
          Biases[tempi][tempp2] = stod(temp); temp.clear();
          if (FILE[i] == ',') { tempp2++; }
          else { if (tempp2 == Biases[tempi].size() - 1) { Now = WNONE;tempp2 = 0; } else { tempp2++; } }
          continue;
        }elif(FILE[i] >= '0' && FILE[i] <= '9' || FILE[i] == '.' || FILE[i] == '-') {
          temp += FILE[i];
        }

      }
    }


    /*for(int i = 0; i<FILE.size();i++){
      if(FILE[i]=='L'&&)
    }*/
  }

  /*RG_Array<double> get(){
  }*/
};
#pragma once
namespace RG_Neural {
  namespace MLP {
    class Learn {
      inline static Network* neural;

    public:
      static void Bind(Network& network) {
        neural = &network;
      }
      static void Backpropagation(RG_Array<double> in, RG_Array<double> out) {
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"learn start");
        Network& n = *neural;

        n.fill(in);
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"fill end");
        // rg_cout<<L"Ожидание: \n";
        /*for(int j = 0;j<out.size();j++){
          rg_cout<<"  "<<out[j]<<L" ";
        }
        rg_cout<<"\n\n";*/
        n.run();
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"run end");
        // double error = n.ErrorFunc(n.Neurons[-1],out);
        // rg_cout<<"\nNeural error "<<error<<endl;
        //(Neurons[-1]-out).print();
        // rg_cout<<endl;
        // DActivations[-1](Neurons[-2]).print();
        // rg_cout<<endl;
        //((Neurons[-1]-out)%DActivations[-1](Neurons[-2])).print();
        // rg_cout<<endl;
        n.Errors[-1] = (n.Neurons[-1] - out) % n.DActivations[-1](n.Neurons[-2]);
        // Errors[-1].print();
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"get error 1 layer end");
        for (int i = n.Errors.size() - 2; i >= 0; i--) {
          n.Errors[i] = (n.Errors[i + 1] * n.Widths[i + 1].transpose()) % n.DActivations[i + 1](n.Neurons[(i + 1) * 2]);
        }
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"get error other layer end");
        for (int i = n.Errors.size() - 1; i >= 0; i--) {
          // rg_cout<<"LAYER ";
          // rg_cout<<"LEARN WIDTH "<<i<<endl;
          /*rg_cout<<"DEBUG\n";
          Errors[i].print();*/
          // rg_cout<<"\nLEARN WIDTH\n";
          // learWidth.print();
          // rg_cout<<"\nWIDTH PREV\n";
          // Widths.print();
          n.Widths[i] -= ((n.Neurons[i * 2 + 1].transpose()) * n.Errors[i]) * n.set.learnStep; // * 0.1;// * set.learnStep;
          n.Biases[i] -= n.Errors[i] * n.set.learnStep;
          // rg_cout<<"\nWIDTH BEFORE\n";
          // Widths.print();
          // rg_cout<<i<<endl;
          // rg_cout<<"LEARN BIAS "<<i<<endl;
          // rg_cout<<"END LEARN "<<i<<endl;
          // rg_cout<<"NEXT ";
        }
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"fix widths and biases end");
      }
      static void Learn_from_file(string path) {
        Network& n = *neural;
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"learn from file start");
        string file = RG::FileLoad(path);
        RG_Array<RG_Array<double>> in;
        RG_Array<RG_Array<double>> out;
        int count_recyles = 0;
        for (int i = 0; i < file.size(); i++) {
          if (file[i] == 'I' && file[i + 1] == 'N') {
            count_recyles++;
          }
          if (file[i] == 'B' && file[i + 1] == 'R' && file[i + 2] == 'E' && file[i + 3] == 'A' && file[i + 4] == 'K') {
            break;
          }
        }
        in.init(count_recyles);
        out.init(count_recyles);

        for (int i = 0; i < count_recyles; i++) {
          rg_cout<<"i = "<<i<<"/"<<count_recyles;
          rg_cout<<", in... ";
          in[i].init(n.Neurons[0].size());
          rg_cout<<"out; ";
          out[i].init(n.Neurons[-1].size());
          rg_cout<<"next\n";
        }
        int layer = -1;
        int neuron = 0;
        bool NOWIN = false;
        for (int i = 0; i < file.size(); i++) {
          if (file[i] == 'I' && file[i + 1] == 'N') {
            NOWIN = true;
            layer++;
            neuron = 0;
          }
          if (file[i] == 'O' && file[i + 1] == 'U' && file[i + 2] == 'T') {
            NOWIN = false;
            neuron = 0;
          }
          if (file[i] == 'B' && file[i + 1] == 'R' && file[i + 2] == 'E' && file[i + 3] == 'A' && file[i + 4] == 'K') {
            break;
          }
          if (file[i] >= '0' && file[i] <= '9') {
            if (NOWIN) {
              in[layer][neuron] = file[i] - '0';
              neuron++;
            }
            else {
              out[layer][neuron] = file[i] - '0';
              neuron++;
            }
          }
        }
        // LEARN
        // rg_cout<<count_recyles<<endl;
        double first_learn_step = n.set.learnStep;
        for (int i = 0; i < count_recyles; i++) {
          /*fill(in[i]);
          run();*/
          // rg_cout<<"----------------------------ITERATE LEARN "<<i<<"----------------------------"<<endl<<endl;
          if (n.set.Step_Reduct)
            n.set.learnStep = (first_learn_step / (double)(i + 1.));

          Backpropagation(in[i], out[i]);
        }
        n.set.learnStep = first_learn_step;
        // RG_Debug::addl(RG_LOG_LOCK_INFO,"learn from file end");
      }
    };

  };

//RNN
  namespace RNN{

  };



};
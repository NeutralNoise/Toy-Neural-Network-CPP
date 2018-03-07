#include "../lib/NeuralNetwork.h"
#include <vector>
#include <time.h>
struct s_trainingData {

  s_trainingData() {

  }

  void AddInput(const float &input) {
    inputs.push_back(input);
  }

  void AddTarget(const float &target) {
    targets.push_back(target);
  }

  std::vector<float> inputs;
  std::vector<float> targets;
};

int main() {

    std::vector<s_trainingData> trainingData;

    std::vector<float> false_false;
    std::vector<float> false_true;
    std::vector<float> true_false;
    std::vector<float> true_true;

    false_false.push_back(0.0f);
    false_false.push_back(0.0f);
    false_true.push_back(0.0f);
    false_true.push_back(1.0f);
    true_false.push_back(1.0f);
    true_false.push_back(0.0f);
    true_true.push_back(1.0f);
    true_true.push_back(1.0f);


    s_trainingData td;

    td.AddInput(0.0f);
    td.AddInput(0.0f);
    td.AddTarget(0.0f);

    trainingData.push_back(td);

    td = s_trainingData();

    td.AddInput(1.0f);
    td.AddInput(0.0f);
    td.AddTarget(1.0f);

    trainingData.push_back(td);

    td = s_trainingData();

    td.AddInput(0.0f);
    td.AddInput(1.0f);
    td.AddTarget(1.0f);

    trainingData.push_back(td);

    td = s_trainingData();

    td.AddInput(1.0f);
    td.AddInput(1.0f);
    td.AddTarget(0.0f);

    trainingData.push_back(td);

    srand(time(NULL));

    unsigned int trainCount = 0;
    NeuralNetwork nn(2, 4, 1);

    nn.SetLearningRate(0.01f);
    std::cout << "Training!\n";
    while(1) {
        trainCount++;
        for(size_t i = 0; i < 40000; i++) {
          int index = rand() % trainingData.size();
          nn.Train(trainingData[index].inputs, trainingData[index].targets);
        }
        //test the network
        if(trainCount % 10 == 0) {
            std::cout << "F:F " << nn.Predict(false_false)[0] << std::endl;
            std::cout << "F:T " << nn.Predict(false_true)[0] << std::endl;
            std::cout << "T:F " << nn.Predict(true_false)[0] << std::endl;
            std::cout << "T:T " << nn.Predict(true_true)[0] << std::endl;
            std::cout << trainCount << std::endl;
        }
    }
 return 0;
}

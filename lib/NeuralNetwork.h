#ifndef NEURAL_NETWORK_H_INCLUDED
#define NEURAL_NETWORK_H_INCLUDED
#include <math.h>
#include <functional>
#include "Matrix.h"



class ActivationFunction {
public:
    ActivationFunction() {

    }

    ActivationFunction(std::function<float(float, const int&, const int&)> func, std::function<float(float, const int&, const int&)> dfunc) {
      this->func = func;
      this->dfunc = dfunc;
    }

    std::function<float(float, const int&, const int&)> func;
    std::function<float(float, const int&, const int&)> dfunc;
};

ActivationFunction Sigmoid([](float val, const int &i, const int &j)->float{
  return 1 / (1+exp(-val));
}, [](float val, const int &i, const int &j)->float{
    return val * (1-val);
  }
);

class NeuralNetwork {


public:

  NeuralNetwork(const int &input_nodes, const int &hidden_nodes, const int &output_nodes) {

    m_inputNodes = input_nodes;
    m_hiddenNodes = hidden_nodes;
    m_outputNodes = output_nodes;

    p_weights_ih = new Matrix(hidden_nodes, input_nodes);
    p_weights_ho = new Matrix(output_nodes, hidden_nodes);
    p_weights_ih->Randomize();
    p_weights_ho->Randomize();

    p_bias_h = new Matrix(hidden_nodes, 1);
    p_bias_o = new Matrix(output_nodes, 1);
    p_bias_h->Randomize();
    p_bias_o->Randomize();

    SetLearningRate(0.1f);

    m_activationFunc = Sigmoid;

  }

  ~NeuralNetwork() {
    delete p_weights_ih;
    delete p_weights_ho;
    delete p_bias_h;
    delete p_bias_o;
  }

  std::vector<float> Predict(const std::vector<float> &input) {

    Matrix inputs = Matrix::FromArray(input);
    Matrix hidden = Matrix::Multiply(*p_weights_ih, inputs);

    hidden = hidden + *p_bias_h;
    // activation function!
    hidden.map(m_activationFunc.func);

    // Generating the output's output!
    Matrix output = Matrix::Multiply(*p_weights_ho, hidden);
    output = output + *p_bias_o;
    output.map(m_activationFunc.func);

    return output.ToArray();
  }

  void Train(const std::vector<float> &input, const std::vector<float> &target) {
    // Generating the Hidden Outputs
    Matrix inputs = Matrix::FromArray(input);
    Matrix hidden = Matrix::Multiply(*p_weights_ih, inputs);
    hidden = hidden + *p_bias_h;
    // activation function!
    hidden.map(m_activationFunc.func);

    // Generating the output's output!
    Matrix outputs = Matrix::Multiply(*p_weights_ho, hidden);
    outputs = outputs + *p_bias_o;
    outputs.map(m_activationFunc.func);

    // Convert array to matrix object
    Matrix targets = Matrix::FromArray(target);
    // Calculate the error
    // ERROR = TARGETS - OUTPUTS
    Matrix output_errors = Matrix::Subtract(targets, outputs);

    // let gradient = outputs * (1 - outputs);
    // Calculate gradient
    Matrix gradients = Matrix::map(outputs, m_activationFunc.dfunc);
    gradients = gradients * output_errors;
    gradients.Multiply(m_learningRate);
    // Calculate deltas
    Matrix hidden_T = Matrix::Transpose(hidden);
    Matrix weight_ho_deltas = Matrix::Multiply(gradients, hidden_T);

        // Adjust the weights by deltas
    *p_weights_ho = *p_weights_ho + weight_ho_deltas;
    // Adjust the bias by its deltas (which is just the gradients)
    *p_bias_o = *p_bias_o + gradients;

    // Calculate the hidden layer errors
    Matrix who_t = Matrix::Transpose(*p_weights_ho);
    Matrix hidden_errors = Matrix::Multiply(who_t, output_errors);

    // Calculate hidden gradient
    Matrix hidden_gradient = Matrix::map(hidden, m_activationFunc.dfunc);
    hidden_gradient = hidden_gradient * hidden_errors;
    hidden_gradient.Multiply(m_learningRate);

    // Calculate input->hidden deltas
    Matrix inputs_T = Matrix::Transpose(inputs);
    Matrix weight_ih_deltas = Matrix::Multiply(hidden_gradient, inputs_T);

    *p_weights_ih = *p_weights_ih + weight_ih_deltas;
    // Adjust the bias by its deltas (which is just the gradients)
    *p_bias_h = *p_bias_h + hidden_gradient;

  }

  void SetLearningRate(const float &rate) {
    m_learningRate = rate;
  }

private:

  int m_inputNodes;
  int m_hiddenNodes;
  int m_outputNodes;

  float m_learningRate;

  Matrix *p_weights_ih;
  Matrix *p_weights_ho;

  Matrix *p_bias_h;
  Matrix *p_bias_o;
  ActivationFunction m_activationFunc;
  /*
  ActivationFunction Sigmoid(s[](float val, int i, int j)float{
  return 1 / (1+exp(-val));
};, [](float val, int i, int j)float{
  return val * (1-val);
  };
);
  */
};




#endif //NEURAL_NETWORK_H_INCLUDED

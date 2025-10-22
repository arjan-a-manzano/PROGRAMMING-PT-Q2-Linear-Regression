#include <iostream> // import libraries
#include <string>
#include <vector> 
#include <cmath>

using std::cin; // namespace aliases
using std::cout;
using std::endl;
using std::negate;
using std::pow;
using std::string;
using std::vector;

vector<double> training_temperature = {4.0, 5.0, 6.0, 7.0};
vector<int> training_time = {5, 6, 7, 8};

double weight = 2.5;
double bias = 1.2;
double learning_rate = 0.001;

double predict_output(const double &weight, const double &input, const double &bias) {
    return (weight * input) + bias;
}

double calculate_error(const double &actual, const double &predicted)
{
    return actual - predicted;
}

double calculate_squared_error(const double &actual, const double &predicted) {
    return pow((actual - predicted), 2.0);
}

double calculate_mean_squared_error(const double &weight, const double &bias) {
    double sum_of_squared_error = 0.0;

    for (int y = 0; y < training_temperature.size(); y++) {
        double squared_error = calculate_squared_error(training_temperature[y], predict_output(weight, training_time[y], bias));
        sum_of_squared_error += squared_error;
    }

    return (1.0 / static_cast<double>(training_temperature.size())) * sum_of_squared_error;
}

double calculate_weight_gradient(const double &weight, const double &bias) {
    double sum_of_gradient = 0.0;

    for (int n = 0; n < training_temperature.size(); n++) {
        double gradient = training_time[n] * (calculate_error(training_temperature[n], predict_output(weight, training_time[n], bias)));
        sum_of_gradient += gradient;
    }

    return -((2.0 / static_cast<double>(training_temperature.size())) * sum_of_gradient);
}

double calculate_bias_gradient(const double &weight, const double &bias) {
    double sum_of_error = 0.0;

    for (int n = 0; n < training_temperature.size(); n++) {
        double error = calculate_error(training_temperature[n], predict_output(weight, training_time[n], bias));
        sum_of_error += error;
    }

    return -((2.0 / static_cast<double>(training_temperature.size())) * sum_of_error);
}

double update_using_new_gradient(double &parameter, const double &learning_rate, const double &gradient) {
    parameter -= learning_rate * gradient;
    return parameter;
}

int main() {
    cout << "Weight: " << weight << endl;
    cout << "Bias: " << bias << endl;
    cout << "MSE: " << calculate_mean_squared_error(weight, bias) << endl;

    double new_weight_gradient = calculate_weight_gradient(weight, bias);
    cout << "New weight gradient: " << new_weight_gradient << endl;

    double new_bias_gradient = calculate_bias_gradient(weight, bias);
    cout << "New bias gradient: " << new_bias_gradient << endl;

    weight = update_using_new_gradient(weight, learning_rate, new_weight_gradient);
    cout << "New weight: " << weight << endl;

    bias = update_using_new_gradient(bias, learning_rate, new_bias_gradient);
    cout << "New bias: " << bias << endl;

    cout << "MSE: " << calculate_mean_squared_error(weight, bias) << endl;

    return 0;
}
#include <iostream> // import libraries
#include <string>
#include <vector> 
#include <cmath>
#include <conio.h>

using std::cin; // namespace aliases
using std::cout;
using std::endl;
using std::pow;
using std::string;
using std::vector;

vector<double> training_temperature = {36.5, 36.8, 36.7, 37.0, 37.2, 37.1, 37.4, 37.6, 37.5, 37.8}; // dependent variable (y)
vector<double> training_time = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // independent variable (x)

double weight = 0.0;
double bias = 0.0;
double new_weight_gradient = 0.0;
double new_bias_gradient = 0.0;
double learning_rate = 0.0;
int epochs = 0;

int input_time = 0;

bool is_on_training_phase = true;

double predict_output(const double &weight, const double &input, const double &bias) { // of dependent variable at current data point, for computing error
    return (weight * input) + bias; // y = w * x + b
}

double calculate_error(const double &actual, const double &predicted) { // for mean squared error and gradients
    return actual - predicted; // y - y-hat i
}

double calculate_mean_squared_error(const double &weight, const double &bias, const vector<double> &dependent_variable_data, const vector<double> &independent_variable_data) { // loss (l), indicates how wrong predicted output (line) is
    double sum_of_squared_error = 0.0; // store result of all loop iterations

    for (size_t y = 0; y < dependent_variable_data.size(); y++) { // add up computed error for all dependent and independent variable data points
        double squared_error = pow(calculate_error(dependent_variable_data[y], predict_output(weight, independent_variable_data[y], bias)), 2.0); // (sum of y i - y-hat i)^2
        sum_of_squared_error += squared_error;
    }

    return (1.0 / static_cast<double>(dependent_variable_data.size())) * sum_of_squared_error; // L =  1 / n * (sum of y i - y-hat i)^2
}

double calculate_weight_gradient(const double &weight, const double &bias, const vector<double> &dependent_variable_data, const vector<double> &independent_variable_data) {
    double sum_of_gradient = 0.0; // store result of all loop iterations

    for (size_t n = 0; n < dependent_variable_data.size(); n++)
    {                                                                                                                                                               // add up computed gradients for all independent and dependent variable data points
        double gradient = independent_variable_data[n] * (calculate_error(dependent_variable_data[n], predict_output(weight, independent_variable_data[n], bias))); // x i * (y i - y-hat i)
        sum_of_gradient += gradient;
    }

    return -((2.0 / static_cast<double>(dependent_variable_data.size())) * sum_of_gradient); // gradient = -(2 / n) * (sum of x i * (y i - y-hat i))
}

double calculate_bias_gradient(const double &weight, const double &bias, const vector<double> &dependent_variable_data, const vector<double> &independent_variable_data) {
    double sum_of_error = 0.0; // store result of all loop iterations

    for (size_t n = 0; n < dependent_variable_data.size(); n++)
    {                                                                                                                           // add up computed error for all dependent and independent variable data points
        double error = calculate_error(dependent_variable_data[n], predict_output(weight, independent_variable_data[n], bias)); // y i - y-hat i
        sum_of_error += error;
    }

    return -((2.0 / static_cast<double>(dependent_variable_data.size())) * sum_of_error); // gradient = -(2 / n) * (y i - y-hat i)
}

double update_using_new_gradient(double &parameter, const double &learning_rate, const double &gradient) { // compute new weight and bias
    parameter = parameter - (learning_rate * gradient);
    return parameter;
}

bool check_if_on_training_phase() {
    return is_on_training_phase;
}

int main() {
    // training phase
    while (check_if_on_training_phase()) {
        cout << "Enter initial weight (slope): " << endl;
        cin >> weight;

        cout << "Enter initial bias (y-intercept): " << endl;
        cin >> bias;

        cout << "Enter learning rate: " << endl;
        cin >> learning_rate;

        cout << "Enter number of training iterations (epochs): " << endl;
        cin >> epochs;

        for (int e = 0; e < epochs; e++)
        {
            cout << "Epoch " << e + 1 << ": " << endl;
            cout << "Previous weight: " << weight << " | " << "Previous bias: " << bias << " | " << "Previous MSE: " << calculate_mean_squared_error(weight, bias, training_temperature, training_time) << endl;

            new_weight_gradient = calculate_weight_gradient(weight, bias, training_temperature, training_time);
            new_bias_gradient = calculate_bias_gradient(weight, bias, training_temperature, training_time);

            cout << "New weight gradient: " << new_weight_gradient << " | " << "New bias gradient: " << new_bias_gradient << endl;

            weight = update_using_new_gradient(weight, learning_rate, new_weight_gradient);
            bias = update_using_new_gradient(bias, learning_rate, new_bias_gradient);

            cout << "New weight: " << weight << " | " << "New bias: " << bias << " | " << "New MSE: " << calculate_mean_squared_error(weight, bias, training_temperature, training_time) << endl;
            cout << "============" << endl;
        }

        cout << endl;
        cout << "Discard current parameters? (y/n)" << endl;

        char input = ' ';

        cin >> input;

        switch (input)
        {
            case 'y':
                weight = 0.0;
                bias = 0.0;
                learning_rate = 0.0;
                epochs = 0;
                break;
            case 'n':
                is_on_training_phase = false;
                break;
            default:
                is_on_training_phase = false;
                break;
        }
    }

    // results phase
    cout << endl;
    cout << "Enter hour of the day to predict its temperature at (0-23): " << endl;
    cin >> input_time;

    cout << endl;
    cout << "Predicted temperature (Celsius) at hour " << input_time << ": " << predict_output(weight, input_time, bias);

    _getch();
    return 0;
}
#include <iostream> // import libraries
#include <string>
#include <vector> 
#include <cmath>

using std::cin; // namespace aliases
using std::cout;
using std::endl;
using std::string;
using std::pow;
using std::vector;

vector<double> training_temperature = {4.0, 5.0, 6.0, 7.0};
vector<int> training_time = {5, 6, 7, 8};

double predict_output(const double &weight, const double &input, const double &bias) {
    return weight * input + bias;
}

double calculate_squared_error(const double &actual, const double &predicted) {
    return pow((actual - predicted), 2.0);
}

double calculate_mean_squared_error() {
    // sum of squared errors
    double sum_of_squared_error = 0.0;

    for (int y = 0; y < training_temperature.size(); y++) { // note: hardcoded
        cout << "Actual training temperature: " << training_temperature[y] << endl; // DEBUG
        double squared_error = calculate_squared_error(training_temperature[y], predict_output(2.5, training_temperature[y], 1.2)); // note: hardcoded
        cout << "Squared error: " << squared_error << endl; // DEBUG
        sum_of_squared_error += squared_error;
    }
    cout << sum_of_squared_error << endl; // DEBUG

    return (1.0 / 4.0) * sum_of_squared_error;
}

int main() {
    cout << calculate_mean_squared_error() << endl;
    
    return 0;
}
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Problem 1a, 1b
vector<double> computeObserved(int diceList[]){
    // calculate total rolls from array
    int totalRolls = 0;
    for (int i = 2; i <= 12; ++i){
        totalRolls += diceList[i];
    }
    
    // probability of each sum
    vector<double> prob(11);
    for (int i = 2; i <= 12; ++i){
        prob[i-2] = (double)diceList[i] / totalRolls;
    }
    
    // find max frequency and corresponding sum
    int maxFreq = 0;
    int maxSum = 2;
    for (int i = 2; i <= 12; ++i){
        if (diceList[i] > maxFreq){
            maxFreq = diceList[i];
            maxSum = i;
        }
    }
    
    // print probabilities
    cout << "Observed Probabilities:" << endl;
    for (int i = 0; i <= 10; ++i){
        cout << "Sum " << (i+2) << ": " << fixed << setprecision(4) 
             << prob[i] << endl;
    }
    cout << "\nMost probable value for observed case: Sum " << maxSum 
         << " with frequency " << maxFreq << endl;
    
    return prob;  // return the vector
}

// Problem 1a, 1b
vector<double> computeIdeal(int dice1[], int dice2[]){
    vector<int> frequency(13, 0); // holds frequencies for each sum 2-12
    
    // find all combinations of the two dice
    for (int i = 0; i <= 5; ++i){
        for (int j = 0; j <= 5; ++j){
            int sum = dice1[i] + dice2[j];
            frequency[sum]++;
        }
    }
    
    vector<double> probabilities(11); // holds probabilities for each sum
    // compute probabilities for each sum
    for (int i = 2; i <= 12; ++i){
        probabilities[i-2] = (double)frequency[i]/36.0;
    }
    
    // find max frequency and corresponding sum
    int maxFreq = 0;
    int maxSum = 2;
    for (int i = 2; i <= 12; ++i){
        if (frequency[i] > maxFreq){
            maxFreq = frequency[i];
            maxSum = i;
        }
    }
    
    cout << "\nIdeal Probabilities:" << endl;
    for (int i = 2; i <= 12; ++i){
        cout << "Sum " << i << ": " 
             << fixed << setprecision(4) << (double)frequency[i]/36.0 << endl;
    }
    cout << "\nMost probable value for ideal case: Sum " << maxSum 
         << " with frequency " << maxFreq << endl;
    
    return probabilities;
}

// Problem 1c expectation values
double computeExpectedValues(int dataList[]){
    // calculate total rolls
    int totalRolls = 0;
    for (int i = 2; i <= 12; ++i){
        totalRolls += dataList[i];
    }

    // calculate expectation value using formula (1.7) in Griffiths
    double expectation = 0.0;
    for (int i = 2; i<= 12; ++i){
        double prob = (double)dataList[i]/totalRolls;
        expectation += i * prob;
    }

    cout << "\nExpected Value: " << fixed << setprecision(4) 
    << expectation << endl;

    return expectation;
}

// problem 1c expectation value squared
double computeExpectedValuesSqrd(int dataList[]){
    // calculate total rolls
    int totalRolls = 0;
    for (int i = 2; i <= 12; ++i){
        totalRolls += dataList[i];
    }

    // calculate <j²> using formula (1.28)
    double expectationSqrd = 0.0;
    for (int i = 2; i<= 12; ++i){
        double prob = (double)dataList[i]/totalRolls;
        expectationSqrd += i * i * prob;
    }

    cout << "Expected Value Squared <j²>: " << fixed << setprecision(4) 
         << expectationSqrd << endl;

    return expectationSqrd;
}

// Problem 1d standard deviation using Griffiths eqn (1.12)
void computeStd(double expectationVal, double expectationValSqrd){
    double sigma = sqrt(expectationValSqrd - expectationVal * expectationVal);
    cout << "Standard deviation: " << fixed << setprecision(4)
         << sigma << endl;
}

int main(){
    int sumDice[13] = {0, 0, 1, 2, 1, 2, 8, 6, 4, 2, 1, 1, 2};
    int sixSidedDie[6] = {1,2,3,4,5,6};
    
    // ideal frequency array for two dice
    int idealDice[13] = {0, 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
    
    computeObserved(sumDice);
    computeIdeal(sixSidedDie, sixSidedDie);

    // observed case
    cout << "\nObserved Case" << endl;
    double expObs = computeExpectedValues(sumDice);
    double expSqrdObs = computeExpectedValuesSqrd(sumDice);
    computeStd(expObs, expSqrdObs);

    // ideal case
    cout << "\nIdeal Case" << endl;
    double expIdeal = computeExpectedValues(idealDice);
    double expSqrdIdeal = computeExpectedValuesSqrd(idealDice);
    computeStd(expIdeal, expSqrdIdeal);
    
    return 0;
}

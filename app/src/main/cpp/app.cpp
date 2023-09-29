/*
 * Compute the number of bitcoin blocks confirmations needed before the chance of a 
    double spend attack falls below a security tolerance level.
    User inputs: 
    1. Probability with which an attacker mines the next block.
    2. user's tolerance level

    The result is computed using Satoshi's implementation in the bitcoin paper 
*/

#include <iostream>
#include <stdlib.h>
#include "app.h"
#include <math.h>

std::string attack::Greeter::userinput(std::string s) {
    return std::string(s);
}

/*
 * This method is from the bitcoin paper
  The args are:
  * q: Probability with which an attacker mines the next block.
  * z: number of block confirmations 
*/ 
double attack::Greeter::AttackerSuccessProbability(double q, int z) {
    double p = 1.0 - q;
    double lambda = z * (q / p);
    double sum = 1.0;
    int i, k;
    for (k = 0; k <= z; k++)
       {
           double poisson = exp(-lambda);
           for (i = 1; i <= k; i++)
               poisson *= lambda / i;
           sum -= poisson * (1 - pow(q / p, z - k));
        }
    return sum;    
}

int main () {
    attack::Greeter greeter;
    
    double qInput = 0.3;
    double tolerance = 0.01;
 
    std::cout << greeter.userinput("\nEnter the attack probability less than 50% (e.g. 0.1 for 10%): "); // << std::endl;
    std::cin >> qInput;

    std::cout << greeter.userinput("\nEnter tolerance level (e.g. 0.01 for 1%): "); // << std::endl;
    std::cin >> tolerance;

    if(qInput < 0 || qInput >= 0.5) {
        std::cout << "\nInvalid input. Attack probability must be between 0 and 0.5. Using default value 0.1 (10%)" << std::endl;
        qInput = 0.1;
    }

    if(tolerance < 0 || tolerance >= 1) {
        std::cout << "\nInvalid input for tolerance. Using default value 0.01 (1%)." << std::endl;
        tolerance = 0.01;
    }

    std::cout << "\nInput probability (chance attacker mines next block): " << qInput << std::endl;
    std::cout << "\nz \t P"  << std::endl;
    std::cout << "------------ "  << std::endl;

    for (int i = 0; i < 200; i++){
        double result = greeter.AttackerSuccessProbability(qInput, i);
        std::cout << i+1 << "\t" << result << std::endl;
        if (result < tolerance) {  //stop once probability falls below security tolerance
            return 0;
        }
    }
    
    std::cout << "Maximum iterations reached! Use different inputs. Exiting." << std::endl;

    return 0;
}

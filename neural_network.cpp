#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

#define n_features 4
#define n_layers 2
#define n_classes 3

typedef float FF;
typedef int II;
typedef vector<vector<FF>> matrix;


FF sigmoid_function(FF x){
    return 1 / ( 1+exp(-x) );
}

FF sigmoid(matrix ms){
    for(auto i : ms){
        for(auto j : i){
            j = sigmoid_function(j);
        }
    }
}

FF create_layer(II n_neurons){

}



int main(){


    return 0;
}

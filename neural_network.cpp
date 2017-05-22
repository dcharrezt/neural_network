#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

#define n_features 4
#define n_layers 2
#define n_classes 3

#define alpha 0.5

typedef float FF;
typedef int II;
typedef vector<vector<FF>> matrix;
typedef vector<FF> vec;

void print_matrix(matrix ms){
    cout << "[ " << ms.size() << " x " << ms[0].size() << " ]" <<endl;
    for(unsigned i=0; i < ms.size(); ++i){
        for(unsigned j=0; j < ms[0].size(); ++j){
            cout << ms[i][j] << ' ';
        }
        cout << endl;
    }
}

void print_vec(vec ms){
    cout << "[ " << ms.size() << " ]" <<endl;
    for(unsigned i=0; i < ms.size(); ++i){
            cout << ms[i] << ' ';
    }
    cout << endl;
}

FF sigmoid_function(FF x){
    return 1 / ( 1 + exp(-x) );
}

vec sigmoid(vec ms){
    vec sig;
    for(unsigned i=0; i<ms.size(); ++i){
            sig.push_back( sigmoid_function(ms[i]) );
    }
    return sig;
}


matrix create_layer(II n_inputs, II n_neurons){
    matrix layer;
    vec tmp;
    for(unsigned i=0; i<n_inputs; ++i){
        for(unsigned j=0; j<n_neurons; ++j){
            tmp.push_back( (FF) rand() / (RAND_MAX) );
        }
        layer.push_back(tmp);
        tmp.clear();
    }
    return layer;
}

vec net(vec input, matrix weights){
    matrix sub_w ( weights.begin()+1 , weights.end() );
    vec ms;
    for(unsigned i=0; i<sub_w[0].size(); ++i){
        FF tmp = 0.0 + weights[0][i];
        for(unsigned j=0; j<sub_w.size(); ++j){
            tmp += input[j] * sub_w[j][i];
        }
        ms.push_back(tmp);
    }
    return ms;
}

void modify_weigths(vec out_desired, vec output, matrix output_layer, 
                    vec out_h1, matrix hidden_layer, vec inputs){

    vec deltas;
    vec deltas_h1;
    FF tmp;
    
    for(unsigned i = 0; i<out_desired.size(); ++i){
        deltas.push_back( -(out_desired[i]-output[i])*(1-output[i])*output[i]);
    }
    
    for(unsigned i = 0; i<output_layer.size(); ++i){
        for(unsigned j=0; j<output_layer[0].size(); ++j){
            output_layer[i][j] -= alpha * ( deltas[i] * out_h1[j] );
        }
    }
    
	print_matrix(output_layer);
	
    for(unsigned i = 0; i<output_layer.size(); ++i){
    	tmp = 0.0;
        for(unsigned j=0; j<output_layer[0].size(); ++j){
             tmp += deltas[j] * output_layer[i][j]; 
        }
        tmp *= out_h1[i]*(1-out_h1[i]);
        deltas_h1.push_back(tmp);
    }
	
	for(unsigned i = 0; i<hidden_layer.size(); ++i){
        for(unsigned j=0; j<hidden_layer[0].size(); ++j){
             hidden_layer[i][j] -= alpha * deltas_h1[i]*inputs[j];
        }
        deltas_h1.push_back(tmp);
    }
    
    print_matrix(hidden_layer);
    
}

int main(){
    
    srand(time(NULL));
    vec i = {5.1,3.5,1.4,0.2};
    vec o = {1,0,0};

    matrix hidden_1 ( create_layer(5,8));    
    print_matrix( hidden_1 );

    matrix output ( create_layer(9,3) );
    print_matrix( output );
    
    vec net_h1 ( net(i, hidden_1) );
    print_vec( net_h1 );
    
    vec out_h1 ( sigmoid(net_h1) ) ;
    print_vec( out_h1 );
    

    
    vec net_out ( net(out_h1, output) );
    print_vec( net_out );
    
    vec out ( sigmoid(net_out) ) ;
    print_vec( out );
    
    modify_weigths(o, out, output, out_h1, hidden_1, i);

    return 0;
}

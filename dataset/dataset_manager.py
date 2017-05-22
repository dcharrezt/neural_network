import pandas as pd
import numpy as np
import operator
from sklearn.model_selection import train_test_split
from sklearn import preprocessing

names = ['Sepal length', 'Sepal width', 'Petal length', \
        'Petal width', 'Iris Setosa', 'Iris Versicolour', \
        'Iris Virginica']
        
origins = ['Setosa','Versicolour','Virginica']


def normalize(x):
    max_ = max(x)
    min_ = min(x)

    return [ (i - min_)/(max_ - min_) for i in x]


def gen_files():
    
    path = 'files/'
    for i in range(0,10):
        for fileN in origins:
            df = pd.read_csv(fileN, names = names)
            train, test = train_test_split(df, test_size = 0.4)
            df_training = train[['Sepal length', 'Sepal width', 'Petal length', 'Petal width']]
            df_test = test[['Sepal length', 'Sepal width', 'Petal length', 'Petal width']]
            
            x = df_training.values #returns a numpy array
            min_max_scaler = preprocessing.MinMaxScaler()
            x_scaled = min_max_scaler.fit_transform(x)
            df_training = pd.DataFrame(x_scaled)
            
            y = df_test.values #returns a numpy array
            min_max_scaler = preprocessing.MinMaxScaler()
            y_scaled = min_max_scaler.fit_transform(y)
            df_test = pd.DataFrame(y_scaled)
            
            
            df_training.to_csv(path+fileN+'_'+str(i)+'_training', sep = ' ', index=False, header=False)
            df_test.to_csv(path+fileN+'_'+str(i)+'_test', sep = ' ', index=False, header=False)
       



gen_files()

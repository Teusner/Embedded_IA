import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OrdinalEncoder
from sklearn.preprocessing import OneHotEncoder
from sklearn.model_selection import train_test_split
import tensorflow as tf

PATH = 'Data/dataset1.csv'
dataset = pd.read_csv(PATH,sep=';')
columns = dataset.columns.tolist() # get the columns
cols_to_use = columns[:len(columns)-1] # drop the last one
dataset = pd.read_csv(PATH, usecols=cols_to_use,sep=";")

number_features = 40

print(dataset.shape)
print(pd.unique(dataset["class"]).tolist()) 


#Create the features 
features=dataset.iloc[:, 1:]


#Récupération des labels
label_names = dataset['class']
label_names_unique = label_names.unique()

# one-hot-encoding
""" label_one = pd.get_dummies(label_names.reset_index(drop=True)).values
y = tf.keras.utils.to_categorical(label_one) """

ohe = LabelEncoder()
ohe.fit(label_names_unique)
y=ohe.transform(label_names)
# y = tf.keras.utils.to_categorical(y)

print(y.shape)



# Splitting the dataset into the Training set and Test set

X_train, X_test, y_train, y_test = train_test_split(features, y, test_size = 0.25, random_state = 0)
print(X_train.shape, y_train.shape, X_test.shape, y_test.shape)

#scaling data
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)

 #----------------------Model tensorflow----------------------
# Importing libraries
from keras.models import Sequential
from keras.layers import Conv2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense
from keras.layers import Dropout

from sklearn.model_selection import GridSearchCV
from keras.wrappers.scikit_learn import KerasClassifier

""" 
def build_classifier(optimizer='adam'):
    # Initialising the CNN
    classifier = Sequential()

    # Step 4 - Full connection
    classifier.add(Dense(units = 128, activation = 'relu',input_dim = 200))
    classifier.add(Dense(units = 128, activation = 'relu'))
    #classifier.add(Dense(units = 128, activation = 'relu'))

    classifier.add(Dense(units = 10, activation = 'softmax'))

    # Compiling the CNN
    classifier.compile(optimizer = 'adam', loss = 'categorical_crossentropy', metrics = ['accuracy'])
    return classifier

#Instance du classifier
classifier = KerasClassifier(build_fn = build_classifier)

#Liste de paramétres à tester lors de l'entraînement.
parameters = {'batch_size': [10],
              'epochs': [100],
              'optimizer': ['adam']}
#Création de la grille d'entraînement.
grid_search = GridSearchCV(estimator = classifier,
                           param_grid = parameters,
                           scoring = 'accuracy',
                           cv = 5)
#On entraîne avec les différents paramètres spécipfiés dans la liste.
grid_search = grid_search.fit(X_train, y_train,verbose=1)
#On évalue le score et les meilleurs paramétres
best_parameters = grid_search.best_params_
best_accuracy = grid_search.best_score_
print(best_accuracy,best_parameters)
score = grid_search.score(X_test, y_test)
print(score)
 """
""" from keras.optimizers import Adam,RMSprop
import matplotlib.pyplot as pyplot
from tensorflow.keras import initializers

def fit_model(trainX, trainy, testX, testy, lrate):
	kernel_initializer=initializers.RandomNormal(stddev=0.01)

	# define model
	model = Sequential()
	model.add(Dense(32, input_dim=number_features, activation='relu', kernel_initializer=kernel_initializer))
	model.add(Dense(32, activation='relu', kernel_initializer=kernel_initializer))
	model.add(Dense(10, activation='softmax'))
	# compile model
	opt = RMSprop(lr=lrate)
	model.compile(loss='categorical_crossentropy', optimizer=opt, metrics=['accuracy'])
	# fit model
	history = model.fit(trainX, trainy, validation_data=(testX, testy), epochs=300, verbose=1)
	# plot learning curves
	pyplot.plot(history.history['accuracy'], label='train')
	pyplot.plot(history.history['val_accuracy'], label='test')
	pyplot.title('lrate='+str(lrate), pad=-50)
	pyplot.legend(loc="best")
	pyplot.grid(True)
	pyplot.tight_layout()

# create learning curves for different learning rates
learning_rates = [1e-2, 1e-3, 1e-4]
for i in range(len(learning_rates)):
	# determine the plot number
	plot_no = 220 + (i+1)
	pyplot.subplot(plot_no)
	# fit model and plot learning curves for a learning rate
	fit_model(X_train, y_train, X_test, y_test, learning_rates[i])
# show learning curves
pyplot.show() """









 #--------------------#Model SVM sklearn #--------------------

from sklearn import svm
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import cross_val_score
param_grid = {'C': [1,1e2,1e3, 1e5],
              'gamma': [1e-5,0.0001, 0.1], }
clf = GridSearchCV(
    svm.SVC(kernel='rbf', class_weight='balanced'), param_grid
)

scores = cross_val_score(clf, X_train, y_train, cv=5)
print("Accuracy: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))



#-------------------Neural Network WITH SCIKIT LEARN ---------------------
""" from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import GridSearchCV

parameters = {'solver': ['lbfgs'], 'max_iter': [10000,20000 ], 'alpha': 10.0 ** -np.arange(1, 5), 'hidden_layer_sizes':np.arange(10, 12), 'random_state':[0,3,6,9]}
ML = GridSearchCV(MLPClassifier(), parameters, n_jobs=-1)

ML.fit(X_train, y_train)

#score
best_parameters = ML.best_params_
best_accuracy = ML.best_score_
print(best_accuracy,best_parameters)
 """
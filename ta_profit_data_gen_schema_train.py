import pandas as pd
import tensorflow as tf
import pandas as pd
import os
import gc
from sklearn.metrics import r2_score
# https://machinelearningmastery.com/tensorflow-tutorial-deep-learning-with-tf-keras/
# __define-ocg__: This code loads data from a CSV file and splits it into train, test, and validate sets
def load_and_split_data(file_path):
    # Load the data
    df = pd.read_csv(file_path)
    df.dropna( inplace= True)      
    X = df.drop('result', axis=1)
    Y = df['result']
    
    return X, Y

# __define-ocg__: This code builds, trains, validates, saves, and evaluates a TensorFlow DNN model
def build_and_train_model(train_X, train_Y, validate_X, validate_Y, test_X, test_Y):
    # Build the model
    model = tf.keras.models.Sequential()
    model.add(tf.keras.layers.Dense(64, input_dim=train_X.shape[1], activation='relu', kernel_initializer='he_uniform'))  # input layer
    model.add(tf.keras.layers.Dropout(rate = 0.05))  # input layer
    model.add(tf.keras.layers.Dense(64, activation='relu', kernel_initializer='he_uniform'))  # input layer
    model.add(tf.keras.layers.Dropout(rate = 0.05))  # input layer
    model.add(tf.keras.layers.Dense(1, activation='linear'))  # output layer

    # Compile the model
    model.compile(loss='mean_squared_error', optimizer='adam', metrics=['mse'])

    # Train the model
    checkpoint = tf.keras.callbacks.ModelCheckpoint('data/results/model/model.h5', save_best_only=True)
    early_stop= tf.keras.callbacks.EarlyStopping(monitor='val_loss', mode='min', verbose=1, patience=10)
    model.fit(train_X, train_Y, validation_data=(validate_X, validate_Y), epochs=10, batch_size=100, callbacks=[checkpoint, early_stop])

    # Evaluate the model
    model.load_weights("data/results/model/model.h5")
    loss, _ = model.evaluate(test_X, test_Y)
    print(f'Test set loss: {loss}')
    Y = model.predict(test_X)
    print(f'r2: {r2_score(test_Y, Y)}')

if __name__ == '__main__':
    train_X, train_Y = load_and_split_data('data/results/merged/normalized/train.csv')
    validate_X, validate_Y = load_and_split_data('data/results/merged/normalized/validate.csv')
    text_X, text_Y = load_and_split_data('data/results/merged/normalized/test.csv')
    gc.collect()    
    print(train_X.shape)
    build_and_train_model(train_X, train_Y, validate_X, validate_Y, text_X, text_Y)
    
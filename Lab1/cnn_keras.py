from tensorflow import keras
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation, Conv2D, Flatten, MaxPooling2D
from tensorflow.keras.datasets import mnist
import tensorflow as tf

import time
import sys

def build_model(input_shape=(28, 28,1), num_classes=10, code=''):
    model = Sequential()
    
    # ------------- Your Code here ---------------
    model.add(keras.Input(shape=input_shape))
    if len(code)>0:
      # 1. Add the first convolution layer with 5x5 filters and a max pooling layer here
      model.add(
        Conv2D(
          32 if code[0]=='0' else 128, 
          5, 
          activation='relu',
          #padding='same',
        )
      )
      
      model.add(
        MaxPooling2D(
          pool_size=(2, 2),
          #strides=(1, 1), 
          #padding='valid'
        )
      )
      for i in range(1,len(code)):
        # 2. Add the second convolution with 3x3 filters and a max pooling layer here 
        model.add(
          Conv2D(
            32 if code[i]=='0' else 128, 
            3, 
            activation='relu',
            #padding='same',
          )
        )
        if i==1:
          model.add(
            MaxPooling2D(
              pool_size=(2, 2),
              #strides=(1, 1), 
              #padding='valid'
            )
          )

    # 3. Add a fully connected hidden layer here
    model.add(Flatten())
    model.add(Dense(256, activation='sigmoid'))
    # 4. Add the final classification layer here
    model.add(Dense(num_classes, activation='softmax'))
    model.compile(
            loss='categorical_crossentropy',
            optimizer='adam',
            metrics=['accuracy']
            )

    return model


def use_model(code = ''):
    (x_train, y_train), (x_test, y_test) = mnist.load_data()

    x_train = x_train/255
    x_test = x_test/255
    
    x_train_reshaped = x_train.reshape(x_train.shape[0], 28, 28, 1) 
    x_test_reshaped = x_test.reshape(x_test.shape[0], 28, 28, 1)
    y_train_one_hot = tf.keras.utils.to_categorical(y_train,num_classes=10)
    y_test_one_hot = tf.keras.utils.to_categorical(y_test, num_classes=10)
    
    # Train the model you created
    my_model = build_model(input_shape=(28,28,1), num_classes=10, code=code)
    my_model.summary()
    
    start_time = time.time();
    print("Training:")
    my_model.fit(
            x_train_reshaped,
            y_train_one_hot,
            epochs=10,
            batch_size=32,
            validation_split=0.75
            )
    
    end_time = time.time()
    print("time to train 10 epochs: " + str(end_time-start_time))
    # Evaluate the training quality on the test dataset
    print("Inference:")
    score = my_model.evaluate(x_test_reshaped, y_test_one_hot, batch_size=128)
    print("Loss and Accuracy on test set: " + str(score))


if __name__ == '__main__':
    if len(sys.argv)!=2:
        print("use cnn_keras.py $code")
        sys.exit()
    tf.test.gpu_device_name()
    
    use_model(sys.argv[1])

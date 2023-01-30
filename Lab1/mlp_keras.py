from tensorflow import keras
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras.datasets import mnist
import tensorflow as tf

import time
import sys

def build_model(num_input=784, num_classes=10, code=''):
    model = Sequential()

    # ----------------- Your code here ----------------
    if len(code)>0:
        model.add(Dense(32 if code[0]=='0' else 1024, activation='sigmoid', input_dim = num_input))
        for i in range(1,len(code)):
            model.add(Dense(32 if code[i]=='0' else 1024, activation='sigmoid'))
        model.add(Dense(num_classes, activation='softmax'))
    else:
        model.add(Dense(num_classes, activation='softmax', input_dim=num_input))
    model.compile(
            loss='binary_crossentropy',
            optimizer='adam',
            metrics=['accuracy']
            )

    return model


def use_model(code = ''):
    (x_train, y_train), (x_test, y_test) = mnist.load_data()
    
    x_train_flattened = x_train.reshape(x_train.shape[0], 784)
    x_test_flattened = x_test.reshape(x_test.shape[0], 784)
    y_train_one_hot = tf.keras.utils.to_categorical(y_train,num_classes=10)
    y_test_one_hot = tf.keras.utils.to_categorical(y_test, num_classes=10)
    
    # Train the model you created
    my_model = build_model(num_input=784, num_classes=10, code = code)
    my_model.summary()
    start_time = time.time();
    print("Training:")
    my_model.fit(
            x_train_flattened,
            y_train_one_hot,
            epochs=10,
            batch_size=32,
            validation_split=0.75
            )

    end_time = time.time()
    
    print("time to train 10 epochs: " + str(end_time-start_time))
    
    # Evaluate the training quality on the test dataset
    print("Inference:")
    score = my_model.evaluate(x_test_flattened, y_test_one_hot, batch_size=128)
    print("Loss and Accuracy on test set: " + str(score))


if __name__ == '__main__':
    if len(sys.argv)!=2:
        print("use as mlp_keras.py $code")
        sys.exit()
    tf.test.gpu_device_name()
    
    use_model(sys.argv[1])

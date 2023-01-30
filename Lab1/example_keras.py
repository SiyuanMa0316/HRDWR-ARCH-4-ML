from tensorflow import keras
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras.datasets import mnist
import tensorflow as tf
#from tensorflow.keras import backend as K


def build_model(num_input=784, num_classes=10):
    model = Sequential()

    # ----------------- Output Layer ----------------
    model.add(Dense(num_classes, activation='softmax', input_dim=num_input))

    model.compile(
            loss='binary_crossentropy',
            optimizer='adam',
            metrics=['accuracy']
            )

    return model


def use_model():
    (x_train, y_train), (x_test, y_test) = mnist.load_data()
    
    x_train_flattened = x_train.reshape(x_train.shape[0], 784)
    x_test_flattened = x_test.reshape(x_test.shape[0], 784)
    y_train_one_hot = tf.keras.utils.to_categorical(y_train,num_classes=10)
    y_test_one_hot = tf.keras.utils.to_categorical(y_test, num_classes=10)
    
    # Train the model you created
    my_model = build_model(num_input=784, num_classes=10)
    print("Training:")
    my_model.fit(
            x_train_flattened,
            y_train_one_hot,
            epochs=10,
            batch_size=32,
            validation_split=0.75
            )

    # Evaluate the training quality on the test dataset
    print("Inference:")
    score = my_model.evaluate(x_test_flattened, y_test_one_hot, batch_size=128)
    print("Loss and Accuracy on test set: " + str(score))


if __name__ == '__main__':
    #f.debugging.set_log_device_placement(True)
    #K._get_available_gpus()
    tf.test.gpu_device_name()
    use_model()

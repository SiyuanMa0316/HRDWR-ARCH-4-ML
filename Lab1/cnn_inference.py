from tensorflow import keras
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation, Conv2D, Flatten, MaxPooling2D
from tensorflow.keras.datasets import mnist
import tensorflow as tf

# load the saved model
model = keras.models.load_model('/tmp/model')
#model.summary()

# load dataset
(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train = x_train/255
x_test = x_test/255

x_train_reshaped = x_train.reshape(x_train.shape[0], 28, 28, 1)
x_test_reshaped = x_test.reshape(x_test.shape[0], 28, 28, 1)
y_train_one_hot = tf.keras.utils.to_categorical(y_train,num_classes=10)
y_test_one_hot = tf.keras.utils.to_categorical(y_test, num_classes=10)

# run inference on test dataset
score = model.evaluate(x_test_reshaped, y_test_one_hot, batch_size=128)
print("Loss and Accuracy on test set: " + str(score))



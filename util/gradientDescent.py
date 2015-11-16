import tensorflow as tf
import numpy as np
from numpy import genfromtxt

DATA_DIR = '/home/brandon/apsp/data/'

data_frame = genfromtxt(DATA_DIR+'test.txt', delimiter=',')
ys = data_frame[:,0:1]
xs = data_frame[:,1:]

x = tf.placeholder("float", [None,3])
W = tf.Variable(tf.zeros([3,1]))
b = tf.Variable(tf.zeros([1]))

y = tf.nn.softmax(tf.matmul(x,W) + b)
y_ = tf.placeholder("float", [None,1])
cross_entropy = -tf.reduce_sum(y_*tf.log(y))

# Training
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)

init = tf.initialize_all_variables()

sess = tf.Session()
sess.run(init)

sess.run(train_step, feed_dict={x:xs, y_:ys})

# Evaluation
abs_diff = tf.abs(tf.sub(y,y_)) 
percent_diff = tf.div(abs_diff, y_)

abDiff = sess.run(abs_diff, feed_dict={x:xs,y_:ys})

error = sess.run(percent_diff, feed_dict={x:xs, y_:ys})
import tensorflow as tf
import numpy as np
from numpy import genfromtxt

DATA_DIR = '/home/brandon/apsp/data/'

data_frame = genfromtxt(DATA_DIR+'test.txt', delimiter=',')
#ys = data_frame[:,0:1]	# Labels
ys = data_frame[:,0] # Labels
xs = data_frame[:,1:]	# Matrix of Features

# length = xs.shape[0]	# Number of data points

# x = tf.placeholder("float", [None,6])
# W = tf.Variable(tf.zeros([6,1]))
# b = tf.Variable(tf.zeros([1]))

# y = tf.nn.softmax(tf.matmul(x,W) + b)
# y_ = tf.placeholder("float", [None,1])
# cross_entropy = -tf.reduce_sum(y_*tf.log(y))

# # Training
# train_step = tf.train.GradientDescentOptimizer(0.001).minimize(cross_entropy)

# init = tf.initialize_all_variables()

# sess = tf.Session()
# sess.run(init)

# for i in range(length):
# 	sess.run(train_step, feed_dict={x:xs[i:i+1,:], y_:ys[i:i+1,:]})
# 	#for (xt,yt) in zip(xs,ys):
# 	#	sess.run(train_step, feed_dict={x:xt, y:yt})
# print 'Training complete!'

# # Evaluation
# y_pred = sess.run(y, feed_dict={x:xs,y_:ys})
# abs_diff = tf.abs(tf.sub(y,y_)) 
# percent_diff = tf.div(abs_diff, y_)

# abDiff = sess.run(abs_diff, feed_dict={x:xs,y_:ys})

# error = sess.run(percent_diff, feed_dict={x:xs, y_:ys}) 

X = tf.placeholder("float",[6])
Y = tf.placeholder("float")
w = tf.Variable(tf.zeros([6]))
y_model = tf.reduce_sum(tf.mul(X,w))	# y = x*W
cost = tf.pow(Y-y_model,2)

train_op = tf.train.GradientDescentOptimizer(0.01).minimize(cost)

sess = tf.Session()
init = tf.initialize_all_variables()
sess.run(init)

for i in range(1):
	for (x_train, y_train) in zip(xs,ys):
		sess.run(train_op, feed_dict={X:x_train, Y:y_train})

y_pred = sess.run(y_model,feed_dict={X:x_train, Y:y_train})

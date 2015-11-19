#!/usr/bin/python

from sklearn.ensemble import RandomForestRegressor
from sklearn.externals import joblib
from numpy import genfromtxt

GRAPH_LIB = '/home/brandon/apsp/graphs/'

DATA_LIB = '/home/brandon/apsp/data/'
MODEL_LIB = '/home/brandon/apsp/models/'
MODEL_NAME = 'RandomForestModel_v1'


class RegressionModel(object):
	def __init__(self):
		self.model = None

	def buildModel(self):
		data = genfromtxt(DATA_LIB+'training.csv', delimiter=',')
		labels = data[:,0]
		samples = data[:,1:]

		self.model = RandomForestRegressor(n_estimators=100)
		self.model.fit(samples,labels)

		joblib.dump(self.model, MODEL_LIB+MODEL_NAME+'.pkl')

	def loadModel(self):
		self.model = joblib.load(MODEL_LIB+MODEL_NAME+'.pkl')

	def predict(self,data):
		if self.model is None:
			print 'Error! Model has not been loaded'
			return
		return self.model.predict(data)





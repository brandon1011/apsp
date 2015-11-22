#!/usr/bin/python
import sys
import os

from sklearn.ensemble import RandomForestRegressor
from sklearn.externals import joblib
from numpy import genfromtxt

GRAPH_DIR = '/home/brandon/apsp/graphs/'

DATA_DIR = '/home/brandon/apsp/data/'
MODEL_LIB = '/home/brandon/apsp/models/'
MODEL_NAME = 'RandomForestModel_v1'

COST_THRESHOLD = 25


class RegressionModel(object):
	def __init__(self):
		self.model = None
		self.default_training_set = DATA_DIR + 'training.csv'

	def buildModel(self, training_file):
		data = genfromtxt(training_file, delimiter=',')
		labels = data[:,0]
		samples = data[:,1:]

		self.model = RandomForestRegressor(n_estimators=100)
		self.model.fit(samples,labels)

	def saveModel(self):
		joblib.dump(self.model, MODEL_LIB+MODEL_NAME+'.pkl')

	def loadModel(self):
		self.model = joblib.load(MODEL_LIB+MODEL_NAME+'.pkl')

	def predict(self,data):
		if self.model is None:
			print 'Error! Model has not been loaded'
			return
		return self.model.predict(data)


class SubGraph(object):
	def __init__(self, graph_file, feature_file):
		self.graph_file = graph_file
		self.features = genfromtxt(DATA_DIR + feature_file, delimiter=',')

		try:
			self.graph = open(GRAPH_DIR + graph_file)
			self.init_graph()

		except IOError as e:
			print 'IO Error! Cannot open graph ' + graph_file

	def predict(self, model):
		prediction = model.predict(self.features[:,1:])
		self.edge_list = map(lambda x: x > COST_THRESHOLD, prediction)
		reduction = reduce(lambda x,y: x+1 if not y else x, self.edge_list)
		print str(reduction) + ' edges elminated...' 

	def init_graph(self):
		self.num_v = int(self.graph.readline())

	def generate_subgraph(self):
		output = open(GRAPH_DIR + 'subgraphs/' + self.graph_file, 'w')
		i = 0

		output.write(str(self.num_v) + '\n')
		for edge in self.graph:
			if self.edge_list[i]:
				output.write(edge)
			i = i+1

		output.close()
		self.graph.close()

if __name__ == "__main__":
	print "Given input graphs, prune edge based on usefulness heuristic.\n" + \
		"Requires features generated on each graph, writes resulting graph to" + \
		"graphs/subgraphs/ directory"
	try:
		numGraphs = int(sys.argv[1])
		namePrefix = sys.argv[2]

		print '==============\nLoading model...'
		model = RegressionModel()
		model.loadModel()

		for i in range(numGraphs):
			filename = namePrefix + '_' + str(i)
			print 'Edge pruning on ' + filename
			g = SubGraph(filename + '.txt', filename + '.csv')
			g.predict(model)
			g.generate_subgraph()
		print 'Done!'

	except (IndexError, ValueError) as e:
		#print "ERROR! Invalid arguments. Usage:"
		#print "\tARG[1] = Number of graphs to predict"
		#print "\tARG[2] = Name prefix for the input/output files"
		print 'Running sweep of cost threshold'

		OUTPUT = '/home/brandon/apsp/results/threshold_sweep.txt'
		TEST_FILE = 'v1000_test1'
		NUM_GRAPHS = 10

		model = RegressionModel()
		model.loadModel()
		print 'Model loaded....'

		thresholds = map(lambda x:x+10, range(26)) # T = (10,...,35)
		for t in thresholds:
			print 'Threshold = ' + str(t)																																																																																																																																																																																																																																																																																																																																																																																																																							
			COST_THRESHOLD = t
			for i in range(NUM_GRAPHS):
				print '\tGraph ' + str(i)
				filename = TEST_FILE + '_' +str(i)
				g = SubGraph(filename + '.txt', filename + '.csv')
				g.predict(model)
				g.generate_subgraph()
			os.system('/home/brandon/apsp/src/apsp >> ' + OUTPUT)












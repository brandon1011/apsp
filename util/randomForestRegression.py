#!/usr/bin/python
import sys

from sklearn.ensemble import RandomForestRegressor
from sklearn.externals import joblib
from numpy import genfromtxt

GRAPH_DIR = '/home/brandon/apsp/graphs/'

DATA_DIR = '/home/brandon/apsp/data/'
MODEL_LIB = '/home/brandon/apsp/models/'
MODEL_NAME = 'RandomForestModel_v1'

COST_THRESHOLD = 30


class RegressionModel(object):
	def __init__(self):
		self.model = None

	def buildModel(self):
		data = genfromtxt(DATA_DIR+'training.csv', delimiter=',')
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
	except (IndexError, ValueError) as e:
		print "ERROR! Invalid arguments. Usage:"
		print "\tARG[1] = Number of graphs to predict"
		print "\tARG[2] = Name prefix for the input/output files"
		exit()

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







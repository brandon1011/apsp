#!/bin/python
import random	# Uniform rand num generator
import sys		# Grab command line args
import math		# Sqrt function

RADIUS = 0.4	# Distance threshold
DIM = 3
GRAPH_DIR = "../graphs/"


def distance(x,y):
	d = 0
	for i in range(DIM):
		d += (x[i] - y[i])**2
	return math.sqrt(d)

def generateGraph(numVertices, graphName):
	vertices = list()
	edges = list()

	# Generate n random vectors
	for i in range(numVertices):
		point = list()
		for j in range(DIM):
			point.append(random.random())
		vertices.append(point)
		#print vertices[i]

	# Compare all pairs to determine if edge exists
	for i in range(numVertices):
		for j in range(numVertices-i-1):
			#print str(i) + "," + str(j+i+1)
			u = vertices[i]
			v = vertices[j+i+1]
			dist = distance(u,v)
			if (dist < RADIUS):
				edges.append([i,j+i+1,dist])

	f = open(GRAPH_DIR+graphName, 'w')
	for edge in edges:
		f.write(" ".join(map(lambda x:str(x), edge)) + "\n")
	f.close()


try:
	numVertices = int(sys.argv[1])
	numGraphs	= int(sys.argv[2])
	namePrefix	= sys.argv[3]
except (IndexError, ValueError) as e:
	print "ERROR! Invalid arguments"
	exit()

#generateGraph(numVertices, "testGraph1.txt")
print "Generating "+str(numGraphs)+" graphs with "+str(numVertices)+" vertices:"

for i in range(numGraphs):
	print "\tGenerating graph "+str(i)+"/"+str(numGraphs)
	name = namePrefix + "_" + str(i) + ".txt"
	generateGraph(numVertices, name)

print "Done."
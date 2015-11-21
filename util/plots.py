#!/usr/bin/python
import matplotlib.pyplot as plot
import numpy as np 

from scipy.optimize import curve_fit
from numpy import genfromtxt

RESULT_LIB = '/home/brandon/apsp/results/'
TEST_FILE = '/home/brandon/apsp/results/percent_errors1.results'

def error_plots(filename):
	data = genfromtxt(filename,delimiter=',',skip_header=0)
	xdata = data[0,:]
	ydata = data[2,:]

	nbins = xdata.shape[0]

	Fofx = lambda x,a,b,c: a*np.exp(b*x)
	#Best fit parameters
	p, cov = curve_fit(Fofx,(xdata[0:-1]),(ydata[0:-1]))

	plot.figure(1)
	p1 = plot.hist(xdata,weights=ydata,bins=nbins)
	pfit = plot.plot(xdata,Fofx(xdata,*p),'-r') #Best fit model

	plot.xlabel('% Reduction in solution quality')
	plot.ylabel('Frequency')
	plot.title('Comparing Heuristic APSP with Optimal Alg')
	
	plot.grid()
	plot.show()

error_plots(TEST_FILE)
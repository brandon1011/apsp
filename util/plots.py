#!/usr/bin/python
import matplotlib.pyplot as plot
import numpy as np 

from scipy.optimize import curve_fit
from numpy import genfromtxt

RESULT_LIB = '/home/brandon/apsp/results/'
TEST_FILE = '/home/brandon/apsp/results/percent_errors1.results'
TEST_FILE_1 = '/home/brandon/apsp/results/threshold_sweep.csv'

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

def thresh_plots(filename=TEST_FILE_1):
	data = genfromtxt(filename,delimiter=',',skip_header=0)
	xdata = data[:,0]
	comp_ratio = data[:,1]
	pct_error = data[:,2]

	plot.figure(1)
	plot.subplot(211)
	plot.plot(xdata,comp_ratio,'bo',xdata,comp_ratio,'k')
	plot.grid()
	plot.ylabel('Graph Compression Ratio')

	plot.subplot(212)
	plot.plot(xdata,pct_error,'ro',xdata,pct_error,'k')
	plot.xlabel('Threshold')
	plot.ylabel('Average % Error')
	plot.grid()
	plot.show()


thresh_plots()

#error_plots(TEST_FILE)
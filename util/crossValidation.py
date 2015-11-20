#!/usr/bin/python
import os
import numpy as np
from math import sqrt
from randomForestRegression import * 

CV_DIR = '/home/brandon/apsp/data/cross_validation/'

def crossValidation(prefix, folds):
	print "SS_total,\tSS_reg\t,SS_res\tR^2\tNorm_Residual"

	for i in range(folds):
		print 'Beginning Fold ' + str(i)
		training_file = CV_DIR + prefix + '_train' + str(i) + '.csv'
		testing_data = genfromtxt(CV_DIR + prefix + '_test' + str(i) + '.csv',delimiter=',')
		test_x = testing_data[:,1:]
		test_y = testing_data[:,0]

		y_avg = np.average(test_y)
		
		model = RegressionModel()
		model.buildModel(training_file)

		pred_y = model.predict(test_x)

		# SS_total = Sum_i(y_i - y_avg)^2
		ss_total = reduce(lambda x,y: x+y, map(lambda x:(x-y_avg)**2, test_y))

		# SS_reg = Sum_i(f_i - y_avg)^2
		ss_reg = reduce(lambda x,y: x+y, map(lambda x:(x-y_avg)**2, pred_y))

		diff = np.subtract(test_y, pred_y)
		# SS_res = Sum_i(y_i - f_i)^2
		ss_res = reduce(lambda x,y: x+y, map(lambda x:x**2, diff))

		r_squared = 1.0 - (ss_res/ss_total)
		norm_residual = sqrt(ss_res)

		res = str(ss_total)+','+str(ss_reg)+','+str(ss_res)+','+str(ss_res)+','+str(r_squared)+','+str(norm_residual)
		print res


def buildCrossValidationSet(in_prefix, out_prefix, folds):
	for i in range(folds):
		filename_train = CV_DIR + out_prefix + '_train' + str(i) + '.csv'
		filename_test = CV_DIR + out_prefix + '_test' + str(i) + '.csv'
		in_file = DATA_DIR + in_prefix + '_' + str(i) + '.csv'

		os.system('cat ' + in_file + '>> ' + filename_test)
		for j in range(folds):
			if j is not i:
				in_file = DATA_DIR + in_prefix + '_' + str(j) + '.csv'
				os.system('cat ' + in_file + '>> ' + filename_train)





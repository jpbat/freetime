#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#       rename.py
#       
#       Copyright 2015 João Ferreira <jpbat@student.dei.uc.pt>
#

import os
import glob
from PIL import Image 

def getTimestamp(name):
	img = Image.open(name)
	exifData = img._getexif()

	for k, v in exifData.items():
		if k == 36867:
			return v

def main():
	
	fileList = glob.glob('*.JPG') + glob.glob('*.jpg') + glob.glob('*.JPEG') + glob.glob('*.jpeg')

	renamed = 0

	for i in xrange(len(fileList)):
		f = fileList[i]
		f2 = getTimestamp(f) + '.jpg'
		
		if f2 == f:
			continue

		print "Renaming", (i+1), "of", len(fileList), "\t", f, "->", f2
		renamed += 1
		os.rename(f, f2)

	print 'Done. Pictures renamed:', renamed

main()
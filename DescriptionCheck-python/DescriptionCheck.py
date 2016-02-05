#! /usr/bin/python
# coding = utf-8

# Description Check
# check descriptions of Chinese patent for errors
# Steven, 2015/01/15

import re

# split the file into dicts of key = para and value = para contents
descriptionStr = open("description.txt", "r").read()
paraPattern = r'\[(?P<para>\d{1,4})\]'	# format is [0001] or [0015] or like
descriptionList = re.split(paraPattern, descriptionStr)
descriptionDict = {}
i = 1
while(i<len(descriptionList)):
	key, value = descriptionList[i], descriptionList[i+1]
	descriptionDict[int(key)] = value.decode("cp936")
	i += 2


# get fig labels from each paragraph
figPattern = ur'\u56fe(?P<figLabel>\d{1,3}\w?)'	# “图”的utf-8编码为\u56fe
matchDict = {}
for key in descriptionDict.keys():
	matches = re.findall(figPattern, descriptionDict[key])
	if len(matches) != 0 : 
		matchDict[key] = matches 


# print all matches of fig labelsfor key in matchDict.keys():
for key in matchDict.keys():
    print("Paragraph %d contains figure labels：\t "% (key))
    for item in matchDict[key]:
        print item,
    print "\n"
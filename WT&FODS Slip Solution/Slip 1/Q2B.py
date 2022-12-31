#Write a Python program to view basic statistical details of the data.(Use wineequality-red.csv) 
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data2 = pd.read_csv('/home/vaibhavi/Documents/Sem 5/Practicals/WT/Practice/Slip 1/winequality-red.csv')
data2
print (data2.describe())



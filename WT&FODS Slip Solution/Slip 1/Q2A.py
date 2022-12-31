#Write a Python program to create a Pie plot to get the frequency of the three species ofthe Iris data (Use iris.csv)

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
iris = pd.read_csv("/home/vaibhavi/Documents/Sem 5/Practicals/WT/Practice/Slip 1/Iris.csv")
ax=plt.subplots(1,1,figsize=(10,8))
iris['Species'].value_counts().plot.pie(explode=[0.1,0.1,0.1],autopct='%1.1f%%',shadow=True,figsize=(10,8))
plt.title("Iris Species %")
plt.show()


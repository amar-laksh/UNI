import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.decomposition import PCA
from itertools import combinations
import sys

saving=False
def hist_plot(df, targets, attribute, xlabel='', ylabel="Frequency", save=""):
    for target in targets:
        x = df.loc[df.brand == target, attribute]
        plt.hist(x, label=target)
    plt.gca().set(title='Histogram', ylabel=ylabel, xlabel=xlabel)
    plt.legend()
    if(save != ""):
        plt.savefig("{}.png".format(save))
    else:
        plt.show()
    plt.clf()

def scree_plot(height, label, xlabel='Percentate of Variance Explained', ylabel='Principal Component',title="PCA Scree Plot", save=""):
    plt.bar(x= range(1,8), height=height, tick_label=label)
    plt.ylabel(xlabel)
    plt.xlabel(ylabel)
    plt.title(title)
    if(save != ""):
        plt.savefig("{}.png".format(save))
    else:
        plt.show()
    plt.clf()

def bi_plot(score, coeff,labels, save=""):
    xs = score[:,0]
    ys = score[:,1]
    n = coeff.shape[0]
    scalex = 1.0/(xs.max() - xs.min())
    scaley = 1.0/(ys.max() - ys.min())
    plt.scatter(xs * scalex,ys * scaley)
    for i in range(n):
        plt.arrow(0, 0, coeff[i,0], coeff[i,1],color = 'r',alpha = 0.5)
        plt.text(coeff[i,0]* 1.15, coeff[i,1] * 1.15, labels[i], color = 'g', ha = 'center', va = 'center')
    plt.xlim(-1,1)
    plt.ylim(-1,1)
    plt.xlabel("PC{}".format(1))
    plt.ylabel("PC{}".format(2))
    plt.grid()
    if(save != ""):
        plt.savefig("{}.png".format(save))
    else:
        plt.show()
    plt.clf()

def proj_plot(df, targets, x, y, title="2D Projection", save=""):
    plt.xlabel(x, fontsize = 15)
    plt.ylabel(y, fontsize = 15)
    plt.title(title, fontsize = 20)

    for target in targets:
        indicesToKeep = df['brand'] == target
        plt.scatter(df.loc[indicesToKeep, x]
                , df.loc[indicesToKeep, y]
                , s = 50)
        plt.legend(brands)
    plt.grid()
    if(save != ""):
        plt.savefig("{}.png".format(save))
    else:
        plt.show()
    plt.clf()


# Main program


# reading data from dataset
data = pd.read_csv('pizza_std.csv', sep=',')
df = pd.DataFrame(data=data)

# Get pizza brands
brands = [ i for i in set(df['brand'])]
brands = sorted(brands)
# Create the Scaler object
scaler = preprocessing.StandardScaler()

# Dropping pizza brand names to standardize values
df_without_brand = df.drop('brand', 1)

# Get column names first
attributes = df_without_brand.columns

# Fit your data on the scaler object
scaled_df = scaler.fit_transform(df_without_brand)
scaled_df = pd.DataFrame(scaled_df, columns=attributes)

######################################################## PCA
pca = PCA()

principalComponents = pca.fit_transform(scaled_df)

pca_columns = ['PC1', 'PC2', 'PC3', 'PC4', 'PC5', 'PC6', 'PC7']

principalDf = pd.DataFrame(data = principalComponents
        , columns = pca_columns)

finalDf = pd.concat([principalDf, df[['brand']]], axis = 1)

print("\nEigen Vectors corresponding to attributes:")
print(pd.DataFrame(pca.components_,columns=scaled_df.columns,index = [pca_columns]))
print("\nEigen Values corresponding to brands:")
print(pd.DataFrame(pca.explained_variance_,columns=['brand'],index = [pca_columns]))


######################################################## DRAWING PLOTS
temp_df = pd.concat([scaled_df, df[['brand']]], axis = 1)
# Drawing unscaled and scaled boxplots
df.boxplot(vert=False, grid=False, widths=0.5)
if(saving):
    plt.savefig("./gen_images/raw_boxplot.png")
else:
    plt.show()
plt.clf()

scaled_df.boxplot(vert=False, grid=False, widths=0.5)
if(saving):
    plt.savefig("./gen_images/scaled_boxplot.png")
else:
    plt.show()
plt.clf()


#  # Drawing histogram for all attributes
#  for attribute in attributes:
    #  saveFile = "./gen_images/histograms/brands_{}".format(attribute)
    #  if(saving):
        #  hist_plot(temp_df, brands, attribute, xlabel=attribute, ylabel="Frequency", save=saveFile)
    #  else:
        #  hist_plot(temp_df, brands, attribute, xlabel=attribute, ylabel="Frequency")
#

# Drawing scree plot
percent_variance = np.round(pca.explained_variance_ratio_* 100, decimals = 2)
if(saving):
    scree_plot(percent_variance, pca_columns, save="./gen_images/scree_plot")
else:
    scree_plot(percent_variance, pca_columns)

# 2D projection of  PCA
if(saving):
    proj_plot(finalDf, brands,'PC1', 'PC2', title="PCA Component Anaylsis", save="./gen_images/pca_projection")
else:
    proj_plot(finalDf, brands,'PC1', 'PC2', title="PCA Component Anaylsis")

# Draw bi plot
if(saving):
    bi_plot(principalComponents[:,0:2],np.transpose(pca.components_[0:2, :]), labels=attributes,save="./gen_images/bi_plot")
else:
    bi_plot(principalComponents[:,0:2],np.transpose(pca.components_[0:2, :]), labels=attributes)


#Going through each attribute to draw 2D Projection
#  for combo in combinations(attributes, 2):
    #  saveFile = "{}_{}".format(combo[0], combo[1])
    #  proj_plot(temp_df, brands, combo[0], combo[1]
            #  , title="2D Projection between {} and {}".format(combo[0], combo[1])
#              , save=saveFile)

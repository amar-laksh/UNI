import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.decomposition import PCA

def bi_plot(score,coeff,labels=None):
    xs = score[:,0]
    ys = score[:,1]
    n = coeff.shape[0]
    scalex = 1.0/(xs.max() - xs.min())
    scaley = 1.0/(ys.max() - ys.min())
    plt.scatter(xs * scalex,ys * scaley)
    for i in range(n):
        plt.arrow(0, 0, coeff[i,0], coeff[i,1],color = 'r',alpha = 0.5)
        if labels is None:
            plt.text(coeff[i,0]* 1.15, coeff[i,1] * 1.15, "Var"+str(i+1), color = 'g', ha = 'center', va = 'center')
        else:
            plt.text(coeff[i,0]* 1.15, coeff[i,1] * 1.15, labels[i], color = 'g', ha = 'center', va = 'center')
    plt.xlim(-1,1)
    plt.ylim(-1,1)
    plt.xlabel("PC{}".format(1))
    plt.ylabel("PC{}".format(2))
    plt.grid()
    plt.show()

def pca_plot(df, target):
    #      fig = plt.figure(figsize = (8,8))
    #  ax = fig.add_subplot(1,1,1)
    plt.xlabel('Principal Component 1', fontsize = 15)
    plt.ylabel('Principal Component 2', fontsize = 15)
    plt.title('2 component PCA', fontsize = 20)

    for brand in target:
        indicesToKeep = finalDf['brand'] == brand
        plt.scatter(finalDf.loc[indicesToKeep, 'PC1']
                , finalDf.loc[indicesToKeep, 'PC2']
                , s = 50)
        plt.legend(brands)
    plt.grid()
    plt.show()

data = pd.read_csv('pizza_std.csv', sep=',')
df = pd.DataFrame(data=data)

# First boxplot to check if data is standardized
#  df.boxplot(vert=False, grid=False, widths=0.5)

# Get pizza brands
brands = [ i for i in set(df['brand'])]

# Create the Scaler object
scaler = preprocessing.StandardScaler()

# Dropping pizza brand names to standardize values
df_without_brand = df.drop('brand', 1)

# Get column names first
attrbutes = df_without_brand.columns

# Fit your data on the scaler object
scaled_df = scaler.fit_transform(df_without_brand)

scaled_df = pd.DataFrame(scaled_df, columns=attrbutes)

#  scaled_df.boxplot(vert=False, grid=False, widths=0.5)


# PCA
pca = PCA()

principalComponents = pca.fit_transform(scaled_df)


# Drawing scree plot
percent_variance = np.round(pca.explained_variance_ratio_* 100, decimals =2)
pca_columns = ['PC1', 'PC2', 'PC3', 'PC4', 'PC5', 'PC6', 'PC7']
plt.bar(x= range(1,8), height=percent_variance, tick_label=pca_columns)
plt.ylabel('Percentate of Variance Explained')
plt.xlabel('Principal Component')
plt.title('PCA Scree Plot')
plt.show()


principalDf = pd.DataFrame(data = principalComponents
        , columns = pca_columns)

finalDf = pd.concat([principalDf, df[['brand']]], axis = 1)


# 2D projection of  PCA
pca_plot(finalDf, brands)

print(pca.explained_variance_ratio_)

# Draw bi plot
bi_plot(principalComponents[:,0:2],np.transpose(pca.components_[0:2, :]), labels=attrbutes)
plt.show()

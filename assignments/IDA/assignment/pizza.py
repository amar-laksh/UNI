import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.decomposition import PCA

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


# Draw PCA
fig = plt.figure(figsize = (8,8))
ax = fig.add_subplot(1,1,1)
ax.set_xlabel('Principal Component 1', fontsize = 15)
ax.set_ylabel('Principal Component 2', fontsize = 15)
ax.set_title('2 component PCA', fontsize = 20)

for brand in brands:
    indicesToKeep = finalDf['brand'] == brand
    ax.scatter(finalDf.loc[indicesToKeep, 'PC1']
            , finalDf.loc[indicesToKeep, 'PC2']
            , s = 50)
    ax.legend(brands)
ax.grid()

print(pca.explained_variance_ratio_)

plt.show()

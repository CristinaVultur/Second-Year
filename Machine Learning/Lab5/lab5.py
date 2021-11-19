import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm
from sklearn.metrics import confusion_matrix
from sklearn import preprocessing
import pdb

def normalize_data(train_data, test_data, type=None):
    if type is None:
        return train_data, test_data
    if(type == 'standard'):
        scaler = preprocessing.StandardScaler()
        scaler.fit(train_data) 
        train_data = scaler.transform(train_data)
        test_data = scaler.transform(test_data)
        return train_data, test_data
    if(type == 'min_max'):
        min_max_scaler = preprocessing.MinMaxScaler(feature_range=(0, 1))  
        min_max_scaler.fit(train_data) 
        train_data = min_max_scaler.transform(train_data)
        test_data = min_max_scaler.transform(test_data)
        return train_data, test_data
    if(type == 'l1'): 
        train_data /= np.sum(abs(train_data), axis=1, keepdims=True)
        test_data /= np.sum(abs(test_data), axis=1, keepdims=True)
        return train_data, test_data
    if(type == 'l2'): 
        train_data /= np.sqrt(np.sum((train_data) ** 2, axis=1, keepdims=True))
        test_data /= np.sqrt(np.sum((test_data) ** 2, axis=1, keepdims=True))
        return train_data, test_data    
        
def compute_accuracy(gt_labels, predicted_labels):   
    accuracy = (predicted_labels == gt_labels).mean()
    return accuracy
    
def get_accuracy_statistics(train_data, train_labels, test_data, test_labels, Cs, normalization_type=None):
    scaled_training_data, scaled_test_data = normalize_data(train_data, test_data, type=normalization_type)

    training_accuracies = np.zeros(len(Cs))
    test_accuracies = []
    for c_idx, c in enumerate(Cs): 
        linear_svm_model = svm.SVC(C=c, kernel='linear')
        linear_svm_model.fit(scaled_training_data, train_labels)
        training_accuracies[c_idx] = compute_accuracy(train_labels, linear_svm_model.predict(scaled_training_data)) * 100
        test_accuracies.append(compute_accuracy(test_labels, linear_svm_model.predict(scaled_test_data)) * 100)

    return (training_accuracies, test_accuracies)



train_images = np.loadtxt('data/train_images.txt')
train_labels = np.loadtxt('data/train_labels.txt', 'int')
test_images = np.loadtxt('data/test_images.txt')
test_labels = np.loadtxt('data/test_labels.txt', 'int') 
    
Cs = [1e-7, 1e-4, 1e-2, 1, 100]
std_accuracies_train, std_accuracies_test = get_accuracy_statistics(train_images, train_labels, test_images, test_labels, Cs, 'standard')
print("Training accuracies using STD normalization: ", std_accuracies_train)
print("Test accuracies using STD normalization: ", std_accuracies_test )


l2_accuracies_train, l2_accuracies_test = get_accuracy_statistics(train_images, train_labels, test_images, test_labels, Cs, 'l2')
print("Training accuracies using L2 normalization:",  l2_accuracies_train )
print("Test accuracies using L2 normalization:" , l2_accuracies_test ) 

# 3
plt.plot(np.log10(np.asarray(Cs)), std_accuracies_train)
plt.plot(np.log10(np.asarray(Cs)), std_accuracies_test)
plt.legend(['train','test'])
plt.xlabel('log10(C)')
plt.ylabel('accuracy')
plt.show()

# 4
best_c = Cs[np.argmax(l2_accuracies_test)]

scaled_training_data, scaled_test_data = normalize_data(train_images,test_images, type='l2')

linear_svm_model = svm.SVC(C=best_c, kernel='linear')
linear_svm_model.fit(scaled_training_data, train_labels)
predicted_labels_linear = linear_svm_model.predict(scaled_test_data)
conf_matrix = confusion_matrix(test_labels, predicted_labels_linear)
print(conf_matrix)

# 5
precision_per_class = [conf_matrix[x][x] / np.sum(conf_matrix[x]) for x in range(10)]

plt.plot(np.arange(10), precision_per_class, 'rx')
plt.title('Precision per class')
plt.xlabel('class')
plt.ylabel('precision')
plt.show()


# -- 6 --
# raw data
rbf_model = svm.SVC(C=17, kernel='rbf', gamma='scale')

rbf_model.fit(train_images, train_labels)
predicted_labels_train_rbf = rbf_model.predict(train_images)
predicted_labels_test_rbf = rbf_model.predict(test_images)

raw_rbf_model_train_accuracy = compute_accuracy(train_labels, predicted_labels_train_rbf)
raw_rbf_model_test_accuracy = compute_accuracy(test_labels, predicted_labels_test_rbf)

print("Raw RBF train accuracy: ", raw_rbf_model_train_accuracy * 100)
print("Raw RBF test accuracy: ", raw_rbf_model_test_accuracy * 100 )

# scaled data
scaled_training_data, scaled_test_data = normalize_data(train_images, test_images, type='l2')

rbf_model.fit(scaled_training_data, train_labels)
predicted_labels_train_rbf = rbf_model.predict(scaled_training_data)
predicted_labels_test_rbf = rbf_model.predict(scaled_test_data)

rbf_model_train_accuracy = compute_accuracy(train_labels, predicted_labels_train_rbf)
rbf_model_test_accuracy = compute_accuracy(test_labels, predicted_labels_test_rbf)

print("L2 RBF train accuracy: ", rbf_model_train_accuracy * 100) 
print("L2 RBF test accuracy:" , rbf_model_test_accuracy * 100)
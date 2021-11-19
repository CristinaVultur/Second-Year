from sklearn import preprocessing
from sklearn.svm import SVC
import numpy as np


train_sentences = np.load('./data_l5/training_sentences.npy', allow_pickle = True)
train_labels = np.load('./data_l5/training_labels.npy')
test_sentences = np.load('./data_l5/test_sentences.npy', allow_pickle = True)
test_labels = np.load('./data_l5/test_labels.npy')

vocab = list(set([
    word
    for prop in train_sentences
    for word in prop
]))

def sentences_to_vec(sentences):
    return np.array([
        [
            sentence.count(word)
            for word in vocab
        ]
        for sentence in sentences
    ])

train_vectors = sentences_to_vec(train_sentences)
test_vectors = sentences_to_vec(test_sentences)


scaler = preprocessing.StandardScaler()
scaler.fit(train_vectors)
scaled_train_vectors = scaler.transform(train_vectors)
scaled_test_vectors = scaler.transform(test_vectors)


classifier = SVC(C = 100., kernel = 'linear')
classifier.fit(scaled_train_vectors, train_labels)
predictions = classifier.predict(scaled_test_vectors)
print(np.mean(
    predictions == test_labels
))



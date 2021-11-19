import numpy as np

train_images = np.loadtxt('./train_images.txt')  # incarcam imaginile
test_images = np.loadtxt('./test_images.txt')
train_labels = np.loadtxt('./train_labels.txt', 'int')
bins = np.linspace(start=0, stop=255, num=10)
x_to_bins = np.digitize(train_images, bins)
class KnnClassifier:
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels
    def classify_image(self, test_image, num_neighbors = 3, metric = 'l2'):
        lungimi=[]
        l = 0
        for img in self.train_images:
            if metric == 'l1':

                for (x, y) in zip(img, test_image):
                    l+=x-y
                lungimi.append(l)
            else:
                for (x, y) in zip(img, test_image):
                    l+=(x-y)*(x-y)
                l=l**-2
                lungimi.append(l)
                lungimi=np.array(lungimi)
        index=np.argsort(x)
        ret=[]
        for i in range(0, num_neighbors):
            ret.append(self.train_labels[index[i]])
        return ret

bun = KnnClassifier(train_images, train_labels)
for test_image in test_images:
    r = bun.classify_image(test_images, 3, 'l2'))
    apartii = np.bincount(r)
    clasa = apartii.index(max(aparitii))
    np.savetxt('predictii_3nn_l2_mnist.txt.', clasa)
    


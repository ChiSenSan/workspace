# -*- coding: utf-8 -*-

# TensowFlowのインポート
import tensorflow as tf
# MNISTを読み込むためinput_data.pyを同じディレクトリに置きインポートする
# input_data.pyはチュートリアル内にリンクがあるのでそこから取得する
# https://tensorflow.googlesource.com/tensorflow/+/master/tensorflow/examples/tutorials/mnist/input_data.py
sess = tf.InteractiveSession()

#MINISTのロード
from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

import time

#重みとバイアスを初期化する関数
def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)

#convolution function
def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')
#max pooling function
def max_pool_2x2(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')

 #開始時刻
start_time = time.time()
print "開始時刻: " + str(start_time)

# MNISTデータの読み込み
# 60000点の訓練データ（mnist.train）と10000点のテストデータ（mnist.test）がある
# 訓練データとテストデータにはそれぞれ0-9の画像とそれに対応するラベル（0-9）がある
# 画像は28x28px(=784)のサイズ
# mnist.train.imagesは[60000, 784]の配列であり、mnist.train.lablesは[60000, 10]の配列
# lablesの配列は、対応するimagesの画像が3の数字であるならば、[0,0,0,1,0,0,0,0,0,0]となっている
# mnist.test.imagesは[10000, 784]の配列であり、mnist.test.lablesは[10000, 10]の配列
print "--- MNISTデータの読み込み開始 ---"
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)
print "--- MNISTデータの読み込み完了 ---"

# 訓練画像を入れる変数
# 訓練画像は28x28pxであり、これらを1行784列のベクトルに並び替え格納する
# Noneとなっているのは訓練画像がいくつでも入れられるようにするため
x = tf.placeholder(tf.float32, shape=[None, 784])
x_image = tf.reshape(x, [-1,28,28,1])

# 重み
# 訓練画像のpx数の行、ラベル（0-9の数字の個数）数の列の行列
# 初期値として0を入れておく
W = tf.Variable(tf.zeros([784, 10]))

# バイアス
# ラベル数の列の行列
# 初期値として0を入れておく
b = tf.Variable(tf.zeros([10]))

#layer01
W_conv1 = weight_variable([5, 5, 1, 32])
b_conv1 = bias_variable([32])

h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)

# layer02
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)

#zennketsugou layer
W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])

h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)

#dorop out
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

# ソフトマックス回帰を実行
# yは入力x（画像）に対しそれがある数字である確率の分布
# matmul関数で行列xとWの掛け算を行った後、bを加算する。

# yは[1, 10]の行列
#y = tf.nn.softmax(tf.matmul(x, W) + b)
# readout layer

W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])

y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

# 交差エントロピー
# y_は正解データのラベル
y_ = tf.placeholder(tf.float32, shape=[None, 10])

#cross_entropy = -tf.reduce_sum(y_*tf.log(y))
cross_entropy = -tf.reduce_sum(y_*tf.log(y_conv))

# 勾配降下法を用い交差エントロピーが最小となるようyを最適化する
#train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

# Sessionを開始する
# runすることで初めて実行開始される（run(init)しないとinitが実行されない）

sess = tf.Session()
sess.run(tf.initialize_all_variables())

# 正しいかの予測
# 計算された画像がどの数字であるかの予測yと正解ラベルy_を比較する
# 同じ値であればTrueが返される
# argmaxは配列の中で一番値の大きい箇所のindexが返される
# 一番値が大きいindexということは、それがその数字である確率が一番大きいということ
# Trueが返ってくるということは訓練した結果と回答が同じということ
#correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
correct_prediction = tf.equal(tf.argmax(y_conv,1), tf.argmax(y_,1))
# 精度の計算
# correct_predictionはbooleanなのでfloatにキャストし、平均値を計算する
# Trueならば1、Falseならば0に変換される
#accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

# 1000回の訓練（train_step）を実行する
# next_batch(100)で100つのランダムな訓練セット（画像と対応するラベル）を選択する
# 訓練データは60000点あるので全て使いたいところだが費用つまり時間がかかるのでランダムな100つを使う
# 100つでも同じような結果を得ることができる
# feed_dictでplaceholderに値を入力することができる
print "--- 訓練開始 ---"

for i in range(20000):
  batch = mnist.train.next_batch(50)
  if i%100 == 0:
    train_accuracy = accuracy.eval(feed_dict={
        x:batch[0], y_: batch[1], keep_prob: 1.0})
    print("step %d, training accuracy %g"%(i, train_accuracy))
  train_step.run(feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})

print("test accuracy %g"%accuracy.eval(feed_dict={
    x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))

print "--- 訓練終了 ---"

# 精度の実行と表示
# テストデータの画像とラベルで精度を確認する
# ソフトマックス回帰によってWとbの値が計算されているので、xを入力することでyが計算できる
print "精度"
print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))

# 終了時刻
end_time = time.time()
print "終了時刻: " + str(end_time)
print "かかった時間: " + str(end_time - start_time)

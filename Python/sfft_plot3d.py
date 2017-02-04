#coding:utf-8
import sys
import sunau
import numpy as np
import scipy.fftpack
import matplotlib
matplotlib.use('WXAgg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

#ファイル
wf = sunau.open("blues.00000.au" , "r" )
fs = wf.getframerate() # サンプリング周波数
x = wf.readframes(wf.getnframes())
x = np.frombuffer(x, dtype= "int16") / 32768.0  # -1 - +1に正規化
wf.close()

fig = plt.figure()
ax = Axes3D(fig)

#start = 0    # サンプリングする開始位置
N = 512      # FFTのサンプル数
SHIFT = 128  # 窓関数をずらすサンプル数
step = 20 #サンプル総数

hammingWindow = np.hamming(N)
freqList = np.fft.fftfreq(N, d=1.0/fs)  # 周波数軸の値を計算

#グラフ
#plx = np.arange(0, freqList, 1)
ply = np.arange(0, step, 1)
plX, plY = np.meshgrid(freqList, ply)
plZ = np.empty((0,freqList.size),float)

i = 0
while i < step :
    start = i * SHIFT
    windowedData = hammingWindow * x[start:start+N]  # 切り出した波形データ（窓関数あり）
    X = np.fft.fft(windowedData)  # FFT
    amplitudeSpectrum = [np.sqrt(c.real ** 2 + c.imag ** 2) for c in X]  # 振幅スペクトル
    #配列の追加
    plZ_tmp = np.vstack((plZ, amplitudeSpectrum))
    plZ = plZ_tmp
    i += 1

ax.plot3D(np.ravel(plX),np.ravel(plY),np.ravel(plZ))
plt.show()

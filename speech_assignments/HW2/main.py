
# Riddhish Bhalodia code
# used the pzplot code from online forum


import cmath
import pyaudio
import scipy.io.wavfile as wav
import numpy as np
import matplotlib as mpl
from cmath import pi, exp, cos, polar, log
from scipy import signal
from pzplot import zplane
import matplotlib.pyplot as plt

def genVowel(B,F1,F2,F3,fs,F0):
	pi = cmath.pi 
	r = np.exp(-1*pi*B/fs)
	theta1 = 2*pi*F1/fs
	theta2 = 2*pi*F2/fs
	theta3 = 2*pi*F3/fs

	sam_no = 4000
	x = np.zeros(sam_no)
	y1 = np.zeros(sam_no)
	y2 = np.zeros(sam_no)
	y3 = np.zeros(sam_no)

	i = 0
	while i<sam_no:
		if i%np.floor(fs/F0) == 0:
			x[i] = 1
		i = i+1	
	
	# first filter	
	y1[0] = x[0]
	y1[1] = x[1] + 2*r*cmath.cos(theta1)*y1[0]
	for k in range(2,sam_no):
		 y1[k] = x[k] + 2*r*cmath.cos(theta1)*y1[k-1] - r*r*y1[k-2]

	# second filter	
	y2[0] = y1[0]
	y2[1] = y1[1] + 2*r*cmath.cos(theta2)*y2[0]
	for k in range(2,sam_no):
		 y2[k] = y1[k] + 2*r*cmath.cos(theta2)*y2[k-1] - r*r*y2[k-2]	 

	# third filter	
	y3[0] = y2[0]
	y3[1] = y2[1] + 2*r*cmath.cos(theta3)*y3[0]
	for k in range(2,sam_no):
		 y3[k] = y2[k] + 2*r*cmath.cos(theta3)*y3[k-1] - r*r*y3[k-2]	 
	
	w = np.linspace(-1*pi,pi,fs)
	z = np.exp(-1*1j*w)
	h = 20*np.log10(1/((1-2*r*cmath.cos(theta1)*z + r*r*z*z)*(1-2*r*cmath.cos(theta2)*z + r*r*z*z)*(1-2*r*cmath.cos(theta3)*z + r*r*z*z)))
	return (y3.real,h)


def lpAnalysis(p,sig,winsize,fs):

	window = np.hamming(winsize*fs)
	winsig = np.zeros(winsize*fs)
	s = len(sig)/2
	w = winsize*fs/2.0 
	winsig = sig[(s-w):(s+w)]*window   # center signal

	#auto corellation
	r_sig = np.correlate(winsig,winsig,"full")
	
	arr = np.double(np.zeros(p+1))
	arr[0] = 1 #initial value
	shift = (len(r_sig)/2) # taking the center value of autocorellation
	esp = r_sig[shift] #initial value
	arr_new = np.double(np.zeros(p+1))
	arr_new[0]=1

	for k in range(0,p):
		# print k
		gamma=0;
		for i in range(1,k+1):
			gamma = gamma + arr[i]*r_sig[k+1-i+shift]
		gamma = r_sig[k+shift+1] + gamma		
		# print gamma		
		big_gamma = (-1.0*(np.double(gamma)))/(np.double(esp));
		# print big_gamma
		for i in range(1,k+1):
			# print arr[1]
			arr_new[i] = arr[i] + big_gamma*arr[k-i+1]
		arr_new[k+1] = big_gamma
		esp	 = esp*(1 - pow(polar(big_gamma)[0],2))
		arr[0:len(arr)]  = arr_new[0:len(arr_new)]	
		# print arr
		# print esp

	arr[0] = np.sqrt(esp)
	return arr	

def constructH(coeff,fs):
	gain = coeff[0]
	coeff[0] = 1;
	pi = cmath.pi 
	w = np.linspace(-1*pi,pi,fs)
	z = np.exp(-1*1j*w)
	den = np.zeros(fs)
	for k in range(0,len(coeff)):
		# print k
		den = den + coeff[k]*pow(z,k)

	hz = 20*np.log10(gain/den)
	plt.plot(hz[fs/2:fs],label="for p = " + str(len(coeff) - 1))	

# Pre-emphasis of the signal
def pre_emphasis(sig):
	out = np.zeros(len(sig))
	for i in range (1,len(sig)):
		out[i] = sig[i] - (0.9*sig[i-1])
	return out

# Generating narrowband spectrum
def nb_spectrum(winsize,sig,fs): 
	window = np.hamming(winsize*fs)
	sig_new = np.zeros(len(window))
	sig_new = sig[0:len(window)]*window
	sig_new_ft = np.fft.fft(sig_new, 1024)   
	for k in range(0, len(sig_new_ft)):
		sig_new_ft[k] = 20*np.log10(abs(sig_new_ft[k]))  
	return sig_new_ft


def inverse_filt(sig,fs,coffs):
	h = np.zeros(len(sig))    # Noise vector
	gain = coffs[0]
	coffs[0] = 1
	for i in range (0,len(sig)):
		for j in range (0,min(11,i+1)):
			h[i] = h[i] + sig[i-j]*coffs[j]

	H = h/gain
	return H

def reconstruct(pitch,fs,coffs,syllable):
	gain = coffs[0]
	coffs[0] = 1;
	x = np.double(fs)/np.double(pitch)
	num = np.ceil((pitch*3)/10.0)
	#300ms thus
	if syllable != "s":
		
		ex_input = np.zeros(num*x)
		for i in range (0,int(num)):
			ex_input[(i*x)-1] = 1

	    # Filtering the signal
		
		out = signal.filtfilt([gain],coffs,ex_input)
		d_num = [1]
		d_den = [1,-0.9]
		out = signal.filtfilt(d_num,d_den,out)  # De-emphasis
		out = np.int16(out/np.max(np.abs(out)) * 32767)
	else:
		ex_input = np.random.normal(0,1,num)
		out = signal.filtfilt([gain],coffs,ex_input)
		out = np.int16(out/np.max(np.abs(out)) * 32767)

	return out	

def cepstrum(sig,fs,winsize):
	window = np.hamming(winsize*fs)
	winsig = np.zeros(winsize*fs)
	s = len(sig)/2
	w = winsize*fs/2.0 
	winsig = sig[(s-w):(s+w)]*window 
	winsig_ft = np.fft.fft(winsig,1024)
	winsig_ft_log = np.log10(np.abs(winsig_ft[0:1024]))
	out = np.real(np.fft.ifft(winsig_ft_log))
	return out

if __name__ == '__main__':
	# in part one first we have to generate a vowel /a/

	a1 = genVowel(50.0,730.0,1090.0,2440.0,8000.0,120.0)   # F0 = 120Hz
	a2 = genVowel(50,730,1090,2440,8000,300)   # F0 = 300Hz
	
	# window the signal
	winsize = 0.03
	fs = 8000
	coffs2 = lpAnalysis(2,a1[0],winsize,fs)
	coffs4 = lpAnalysis(4,a1[0],winsize,fs)
	coffs6 = lpAnalysis(6,a1[0],winsize,fs)
	coffs8 = lpAnalysis(8,a1[0],winsize,fs)
	coffs10 = lpAnalysis(10,a1[0],winsize,fs)
	plt.plot(a1[1][4000:8000],label="Original")
	constructH(coffs2,fs)
	constructH(coffs4,fs)
	constructH(coffs6,fs)
	constructH(coffs8,fs)
	constructH(coffs10,fs)
	plt.legend(bbox_to_anchor=(0., 1.02, 1., -0.8), loc=2, ncol=2, borderaxespad=0.)
	plt.title("Part A: For the case with F_0 = 120hz")

	plt.figure()
	coffs2 = lpAnalysis(2,a2[0],winsize,fs)
	coffs4 = lpAnalysis(4,a2[0],winsize,fs)
	coffs6 = lpAnalysis(6,a2[0],winsize,fs)
	coffs8 = lpAnalysis(8,a2[0],winsize,fs)
	coffs10 = lpAnalysis(10,a2[0],winsize,fs)
	plt.plot(a2[1][4000:8000],label="Original")
	constructH(coffs2,fs)
	constructH(coffs4,fs)
	constructH(coffs6,fs)
	constructH(coffs8,fs)
	constructH(coffs10,fs)
	plt.legend(bbox_to_anchor=(0., 1.02, 1., -0.8), loc=2, ncol=2, borderaxespad=0.)
	plt.title("Part A: For the case with F_0 = 300hz")


	# Now for the part B

	# read the files
	[fs1,in_a] = wav.read('a.wav')
	[fs1,in_i] = wav.read('i.wav')
	[fs1,in_n] = wav.read('n.wav')
	[fs,in_s] = wav.read('s.wav')
	
	fs = np.double(fs)
	# do the pre emphasis
	in_ap = pre_emphasis(in_a)
	in_ip = pre_emphasis(in_i)
	in_np = pre_emphasis(in_n)
	in_sp = pre_emphasis(in_s)

	# now to plot the narrowband spectrum
	out_a = nb_spectrum(winsize,in_a,fs1)
	out_i = nb_spectrum(winsize,in_i,fs1)
	out_n = nb_spectrum(winsize,in_n,fs1)
	out_s = nb_spectrum(winsize,in_s,fs)
	out_ap = nb_spectrum(winsize,in_ap,fs1)
	out_ip = nb_spectrum(winsize,in_ip,fs1)
	out_np = nb_spectrum(winsize,in_np,fs1)
	out_sp = nb_spectrum(winsize,in_sp,fs)

	x = np.linspace(0,4000,512)
	
	plt.figure()
	plt.subplot(2,2,1)
	plt.plot(x,out_a[0:512],label = 'Without pre-emphasis')
	plt.plot(x,out_ap[0:512], label = 'With pre-emphasis')
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	plt.title('Syllable a')
	plt.legend(bbox_to_anchor=(1.9, 1, 1., 0), loc=3, ncol=1, borderaxespad=0.)

	plt.subplot(2,2,2)
	plt.plot(x,out_i[0:512])
	plt.plot(x,out_ip[0:512])
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	plt.title('Syllable i')
	

	plt.subplot(2,2,3)
	plt.plot(x,out_n[0:512])
	plt.plot(x,out_np[0:512])
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	plt.title('Syllable n')
	
	x = np.linspace(0,8000,512)
	plt.subplot(2,2,4)
	plt.plot(x,out_s[0:512])
	plt.plot(x,out_sp[0:512])
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	plt.title('Syllable s')
	
	# computing the LPC coefficients
	# the lpAnalysis function will do the windowing and computing the Autocorellation and the LPC coefficients
	coffs6_ap = lpAnalysis(6,in_ap,winsize,fs1)
	coffs6_ip = lpAnalysis(6,in_ip,winsize,fs1)
	coffs6_np = lpAnalysis(6,in_np,winsize,fs1)
	coffs6_sp = lpAnalysis(6,in_sp,winsize,fs)

	coffs10_ap = lpAnalysis(10,in_ap,winsize,fs1)
	coffs10_ip = lpAnalysis(10,in_ip,winsize,fs1)
	coffs10_np = lpAnalysis(10,in_np,winsize,fs1)
	coffs10_sp = lpAnalysis(10,in_sp,winsize,fs)

	#plot the pole zero plots
	plt.figure()
	gain = coffs6_ap[0];
	coffs6_ap[0] = 1;
	zplane(gain,coffs6_ap,1)
	plt.title("For p=6 syllable a")
	gain = coffs6_ip[0];
	coffs6_ip[0] = 1;
	zplane(gain,coffs6_ip,2)
	plt.title("For p=6 syllable i")
	gain = coffs6_np[0];
	coffs6_np[0] = 1;
	zplane(gain,coffs6_np,3)
	plt.title("For p=6 syllable n")
	gain = coffs6_sp[0];
	coffs6_sp[0] = 1;
	zplane(gain,coffs6_sp,4)
	plt.title("For p=6 syllable s")

	plt.figure()
	gain = coffs10_ap[0];
	coffs10_ap[0] = 1;
	zplane(gain,coffs10_ap,1)
	plt.title("For p=10 syllable a")
	gain = coffs10_ip[0];
	coffs10_ip[0] = 1;
	zplane(gain,coffs10_ip,2)
	plt.title("For p=10 syllable i")
	gain = coffs10_np[0];
	coffs10_np[0] = 1;
	zplane(gain,coffs10_np,3)
	plt.title("For p=10 syllable n")
	gain = coffs10_sp[0];
	coffs10_sp[0] = 1;
	zplane(gain,coffs10_sp,4)
	plt.title("For p=10 syllable s")

	# now to plot the H(z) estimated with the spectrum
	plt.figure()
	plt.subplot(2,2,1)
	x = np.linspace(0,4000,512)
	plt.plot(x,out_ap[0:512],label = "Narrowband Spectrum")
	constructH(lpAnalysis(4,in_ap,winsize,fs1),fs1)
	constructH(lpAnalysis(6,in_ap,winsize,fs1),fs1)
	constructH(lpAnalysis(8,in_ap,winsize,fs1),fs1)
	constructH(lpAnalysis(10,in_ap,winsize,fs1),fs1)
	constructH(lpAnalysis(12,in_ap,winsize,fs1),fs1)
	constructH(lpAnalysis(20,in_ap,winsize,fs1),fs1)
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	
	plt.legend(bbox_to_anchor=(0.5, 1, 1., -0.2), loc=3, ncol=4, borderaxespad=0.)
	plt.title('Syllable a')

	plt.subplot(2,2,2)
	plt.plot(x,out_ip[0:512])
	constructH(lpAnalysis(4,in_ip,winsize,fs1),fs1)
	constructH(lpAnalysis(6,in_ip,winsize,fs1),fs1)
	constructH(lpAnalysis(8,in_ip,winsize,fs1),fs1)
	constructH(lpAnalysis(10,in_ip,winsize,fs1),fs1)
	constructH(lpAnalysis(12,in_ip,winsize,fs1),fs1)
	constructH(lpAnalysis(20,in_ip,winsize,fs1),fs1)
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	plt.title('Syllable i')

	plt.subplot(2,2,3)
	plt.plot(x,out_np[0:512])
	constructH(lpAnalysis(4,in_np,winsize,fs1),fs1)
	constructH(lpAnalysis(6,in_np,winsize,fs1),fs1)
	constructH(lpAnalysis(8,in_np,winsize,fs1),fs1)
	constructH(lpAnalysis(10,in_np,winsize,fs1),fs1)
	constructH(lpAnalysis(12,in_np,winsize,fs1),fs1)
	constructH(lpAnalysis(20,in_np,winsize,fs1),fs1)
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	plt.title('Syllable n')

	plt.subplot(2,2,4)
	x = np.linspace(0,8000,512)
	plt.plot(x,out_sp[0:512])
	constructH(lpAnalysis(4,in_sp,winsize,fs1),fs)
	constructH(lpAnalysis(6,in_sp,winsize,fs1),fs)
	constructH(lpAnalysis(8,in_sp,winsize,fs1),fs)
	constructH(lpAnalysis(10,in_sp,winsize,fs1),fs)
	constructH(lpAnalysis(12,in_sp,winsize,fs1),fs)
	constructH(lpAnalysis(20,in_sp,winsize,fs1),fs)
	plt.ylabel('Magnitude (dB)')
	plt.xlabel('Frequency (Hz)')
	plt.title('Syllable s')

	
	
	p = [2,4,6,8,10,12,14,16,18,20]
	q = np.zeros(10)
	# for error plot
	plt.figure()
	i=2
	while i<21:
		temp = lpAnalysis(i,in_ap,winsize,fs1)
		q[i/2-1] = temp[0]*temp[0]
		i=i+2

	plt.subplot(2,2,1)
	plt.plot(p,q)	
	plt.ylabel('Error Signal Energy')
	plt.xlabel('p')
	plt.title('Syllable a')

	i=2
	while i<21:
		temp = lpAnalysis(i,in_ip,winsize,fs1)
		q[i/2-1] = temp[0]*temp[0]
		i=i+2

	plt.subplot(2,2,2)
	plt.plot(p,q)	
	plt.ylabel('Error Signal Energy')
	plt.xlabel('p')
	plt.title('Syllable i')

	i=2
	while i<21:
		temp = lpAnalysis(i,in_np,winsize,fs1)
		q[i/2-1] = temp[0]*temp[0]
		i=i+2

	plt.subplot(2,2,3)
	plt.plot(p,q)	
	plt.ylabel('Error Signal Energy')
	plt.xlabel('p')
	plt.title('Syllable n')

	i=2
	while i<21:
		temp = lpAnalysis(i,in_sp,winsize,fs)
		q[i/2-1] = temp[0]*temp[0]
		i=i+2

	plt.subplot(2,2,4)
	plt.plot(p,q)	
	plt.ylabel('Error Signal Energy')
	plt.xlabel('p')
	plt.title('Syllable s')

	## Now for the question 3

	# as s is unvoiced
	coffs10_s = lpAnalysis(10,in_s,winsize,fs)
	coffs10_ap = lpAnalysis(10,in_ap,winsize,fs1)
	coffs10_ip = lpAnalysis(10,in_ip,winsize,fs1)
	coffs10_np = lpAnalysis(10,in_np,winsize,fs1)
	# these are the error signals
	H_ap = inverse_filt(in_ap,fs1,coffs10_ap)
	H_ip = inverse_filt(in_ip,fs1,coffs10_ip)
	H_np = inverse_filt(in_np,fs1,coffs10_np)
	H_s = inverse_filt(in_s,fs,coffs10_s)

	H_ap_ft = np.fft.fft(H_ap,1024)
	for i in range(0,len(H_ap_ft)):	
		H_ap_ft[i] = 20*np.log10(cmath.polar(H_ap_ft[i])[0])
	plt.figure()
	plt.subplot(2,1,1)
	plt.plot(np.linspace(0,4000,512),H_ap_ft[0:512])
	plt.xlabel('frequency(hz)')
	plt.ylabel('magnitude(dB)')
	plt.title('residual error signal for a')

	H_s_ft = np.fft.fft(H_s,1024)
	for i in range(0,len(H_s_ft)):	
		H_s_ft[i] = 20*np.log10(cmath.polar(H_s_ft[i])[0])
	
	plt.subplot(2,1,2)
	plt.plot(np.linspace(0,8000,512),H_s_ft[0:512])
	plt.xlabel('frequency(hz)')
	plt.ylabel('magnitude(dB)')
	plt.title('residual error signal for s')


	# pitch estimation
	ar_H_a = np.correlate(H_ap,H_ap,"full")
	a = ar_H_a[np.floor(len(ar_H_a)/2)+2:np.floor(len(ar_H_a)/2) + 100]
	val = np.amax(a)
	ind = np.where(a==val)
	pitch = np.double(fs1)/np.double((int(ind[0])))
	print ("pitch = " + str(pitch))

	## question 4
	# the pitch detected is pitch= 135.59Hz
	recons_a = reconstruct(pitch,fs1,coffs10_ap,"a")
	recons_i = reconstruct(pitch,fs1,coffs10_ip,"i")
	recons_n = reconstruct(pitch,fs1,coffs10_np,"n")
	recons_s = reconstruct(pitch,fs,coffs10_s,"s")
	wav.write("a_out.wav", fs1, recons_a)
	wav.write("i_out.wav", fs1, recons_i)
	wav.write("n_out.wav", fs1, recons_n)
	wav.write("s_out.wav", fs, recons_s)

	## Question 5
	
	cep_a = cepstrum(in_a,fs1,winsize)
	cep_i = cepstrum(in_i,fs1,winsize)
	cep_n = cepstrum(in_n,fs1,winsize)
	cep_s = cepstrum(in_s,fs,winsize) 
	plt.figure()
	plt.subplot(2,2,1)
	plt.plot(cep_a)
	plt.ylim([-0.1,0.2])
	plt.title("Cepstrum for syllable a")
	plt.subplot(2,2,2)
	plt.plot(cep_i)
	plt.ylim([-0.1,0.2])
	plt.title("Cepstrum for syllable i")
	plt.subplot(2,2,3)
	plt.plot(cep_n)
	plt.ylim([-0.1,0.2])
	plt.title("Cepstrum for syllable n")
	plt.subplot(2,2,4)
	plt.plot(cep_s)
	plt.ylim([-0.1,0.2])
	plt.title("Cepstrum for syllable s")

	
	cep_a[25:len(cep_a)-26] = 0
	cep_a_ft = np.fft.fft(cep_a,1024)
	cep_i[25:len(cep_i)-26] = 0
	cep_i_ft = np.fft.fft(cep_i,1024)
	cep_n[25:len(cep_n)-26] = 0
	cep_n_ft = np.fft.fft(cep_n,1024)
	cep_s[25:len(cep_s)-26] = 0
	cep_s_ft = np.fft.fft(cep_s,1024)

	plt.figure()
	x  = np.linspace(0,4000,512)
	plt.subplot(2,2,1)
	plt.plot(x,20*abs(cep_a_ft[0:512]),label = "cepstrum")
	plt.plot(x,out_a[0:512],label = 'Spectrum')
	constructH(lpAnalysis(10,in_ap,winsize,fs1),fs1)
	plt.legend(bbox_to_anchor=(1.0, 1, 1., -0.6), loc=3, ncol=2, borderaxespad=0.)
	plt.title('Syllable a')
	plt.subplot(2,2,2)
	plt.plot(x,20*abs(cep_i_ft[0:512]),label = "cepstrum")
	plt.plot(x,out_i[0:512],label = 'Without pre-emphasis')
	constructH(lpAnalysis(10,in_ip,winsize,fs1),fs1)
	
	plt.title('Syllable i')
	plt.subplot(2,2,3)
	plt.plot(x,20*abs(cep_n_ft[0:512]),label = "cepstrum")
	plt.plot(x,out_n[0:512],label = 'Without pre-emphasis')
	constructH(lpAnalysis(10,in_np,winsize,fs1),fs1)
	
	plt.title('Syllable n')
	plt.subplot(2,2,4)
	x  = np.linspace(0,8000,512)
	plt.plot(x,20*abs(cep_s_ft[0:512]),label = "cepstrum")
	plt.plot(x,out_s[0:512],label = 'Without pre-emphasis')
	constructH(lpAnalysis(18,in_s,winsize,fs),fs)
	
	plt.title('Syllable s')

	## Question 6
	
	plt.figure()
	recons_a = reconstruct(pitch,fs1,coffs10_ap,"a")
	cep_recons_a = cepstrum(recons_a,fs1,winsize)
	cep_recons_a[25:len(cep_recons_a)-26] = 0
	cep_recons_a_ft = np.fft.fft(cep_recons_a,1024)
	x = np.linspace(0,4000,512)
	plt.plot(x,20*abs(cep_recons_a_ft[0:512]),label = "cepstrum")
	constructH(coffs10_ap,fs1)
	plt.legend(bbox_to_anchor=(0.7,0.8, 1., -0.6), loc=3, ncol=1, borderaxespad=0.)
	plt.show()
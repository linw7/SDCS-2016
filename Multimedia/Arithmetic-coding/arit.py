from decimal import *

def encode(seq):

	# statistic
	cnt = {}
	for ch in seq:
		cnt[ch] = cnt.get(ch, 0) + 1

	# intervals
	intervals, start = [], 0
	for pair in sorted(cnt.items(), key = lambda e:e[0]):
		length = pair[1] / len(seq)
		# intervals.append((pair[0], start, start + length))
		intervals.append((pair[0], Decimal(start), Decimal(start + length)))
		start += length

	# debug
	for interval in intervals:
		print("%s\t%f\t%f" % (interval[0], interval[1], interval[2]))
	
	# encode
	l, r, d = 0, 1, 1
	print("=== encode ===")
	print("ini\t%.12f\t%.12f\t%.12f" % (l, r, d))
	for ch in seq:
		for interval in intervals:
			if ch == interval[0]:
				_l = l + d * interval[1]
				_r = l + d * interval[2]
				l, r, d = _l, _r, _r-_l
				print("%s\t%.12f\t%.12f\t%.12f" % (ch, l, r, d))
				break

	return intervals, l, len(seq)

def decode(args):

	# origin seq
	seq = ''
	(intervals, v, length) = args

	print("=== decode ===")

	for i in range(length):
		for interval in intervals:
			if v < interval[2]:
				if i == 0:
					print("%s\t%.12f" % (interval[0], v))
				else:										
					print("%s\t(%.12f-%.12f) / %.12f = %.12f" % (interval[0], _v, interval[1], interval[2] - interval[1], v))
				_v = v
				v = (v - interval[1]) / (interval[2] - interval[1])
				seq += interval[0]
				break

	print(seq)
	return seq

decode(encode('goose'))
# decode(encode('good night'))
def myfirst_yoursecond(p,q):
	first = p[:p.find(" ")]
	second = q[q.find(" ")+1:]
	print first==second
myfirst_yoursecond("Hel lo", "Wor Hel")


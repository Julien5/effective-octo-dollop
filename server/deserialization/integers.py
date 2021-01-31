#!/usr/bin/env python3

def read_u8(bytes,pos):
	end=pos+1
	return end,int.from_bytes(bytes[pos:end], byteorder='little', signed=False)    

def read_u16(bytes,pos):
	end=pos+2
	return end,int.from_bytes(bytes[pos:end], byteorder='little', signed=False)    

def read_unsigned(length,bytes,pos):
	if length==16:
		return read_u16(bytes,pos);
	assert(length==8);
	return read_u8(bytes,pos);

class Unsigned:
	def __init__(self,bytes,length):
		self.data = list();
		pos=0;
		nb=length/8;
		n=len(bytes)/nb;
		for k in range(int(n)):
			pos,x = read_unsigned(length,bytes,pos);
			self.data.append(x);
		
	def __str__(self):
		return " ".join(["%02d" % x for x in self.data]);

def main():
	b=open("/tmp/adc.hex",'rb').read().decode("utf-8");
	for line in b.split("\n"):
		b=bytes.fromhex(line);
		u=Unsigned(b,16)
		print(u)

if __name__ == "__main__":
	main();

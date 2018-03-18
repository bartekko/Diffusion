from sys import argv

def get_data(filename):
	datavector=[]
	with open(filename,'r') as data:
		while(True):
			c=data.readline()
			if c =='': return datavector
			l=[float(x) for x in c.split(' ')]	
			datavector.append(l)

def mean(sample):
	return sum(sample)/len(sample);
	
#accepts data in form (list of X,list of Y)
def linear_slope(data):
	covariance=mean([x[0]*x[1] for x in data])
	variance_of_square=mean([x[0]*x[0] for x in data])
	return covariance/variance_of_square
			
def variance(data):
	avg_x=sum(data)/len(data)
	avg_x2=sum([x**2 for x in data])/len(data)
	ans=avg_x2-avg_x*avg_x
	return ans;
		
if len(argv)!=2:
	print("You need to specify a file to analyse")
	exit(-1)

with open(argv[1]) as densities_list:
	while True:
		density=densities_list.readline();
		density=density[0:-1]
		if density=='':
			break;
		data=get_data('fresults/'+str(density)+'.txt')
		slope=linear_slope(data)
		stdun=(variance([x[1]/x[0]-slope for x in data]))**(1/2)
		print(float(density),slope,stdun)


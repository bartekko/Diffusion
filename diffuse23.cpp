#include <cmath>
#include <vector>
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <algorithm>
#include <tuple>

boost::random::mt19937 rng;

class point
{
public:
	point(int x,int y):p{x,y}{};
	int& operator[](char i){return p[i];};
	int p[2];
};

class lattice
{
public:
	lattice(int size)
	{
		size_x=floor(sqrt(size)+0.5);	
		size_y=floor(sqrt(size)+0.5);
		stor.resize(size_x*size_y,0);
	};
	
	
	auto& at(point p)
	{	
		int xp=p[0]%size_x;
		if(xp<0)xp+=size_x;
		int yp=p[1]%size_y;
		if(yp<0)yp+=size_y;		
		return stor.at(xp*size_x+yp);
	};
	
	auto len() {return stor.size();};
//private:
	std::vector<char> stor;
	int size_x,size_y;
};

auto create_state(auto lattice_size,auto particlecount)
{
	std::vector<point> particles;
	particles.reserve(particlecount);
	lattice particle_lattice(lattice_size);

	std::cout<<double(particlecount)/particle_lattice.len()<<std::endl;

	boost::random::uniform_int_distribution<> randompos(0,particle_lattice.size_x);
	while(particles.size()<particlecount)
	{	point new_particle(randompos(rng),randompos(rng));
		if(particle_lattice.at(new_particle)==0)
		{	auto sl=lattice_size;
			auto p=new_particle;
			particle_lattice.at(new_particle)=1;
			particles.push_back(new_particle);
		}	
	}
	return std::make_tuple(particles,particle_lattice);
}

auto step(auto& particles,auto& particle_lattice)
{
	boost::random::uniform_int_distribution<> direction(0,3);

	for(int i=0;i<particles.size();i++)
	{	
		auto& it=particles[i];
		char dir=direction(rng);
		auto new_particle=it;

		new_particle[dir>>1]+=-1+2*(dir%2);			

		if(particle_lattice.at(new_particle)==0)
		{
			particle_lattice.at(new_particle)=1;
			particle_lattice.at(it)=0;
			it=new_particle;
		}			
	}
}

void analyze(auto origins, auto particles, int t)
{
	double mean_accumulator=0;
	for(int i=1;i<=particles.size();i++)
	{
		long xdev=(particles[i][0]-origins[i][0]);
		xdev*=xdev;
		long ydev=(particles[i][1]-origins[i][1]);
		ydev*=ydev;
		mean_accumulator+=xdev+ydev;
	}
	
	double mean=mean_accumulator/4/particles.size();
	std::cout<<t<<' '<<mean<<'\n';	

}


int main(int argc, char** argv)
{
	rng.seed(100);

	//check validity of arguments
	if(argc!=4)
	{
		std::cout<<"Usage: <Fill rate> <Number of steps> <Number of particles>"<<std::endl;
		exit(-1);
	}
	double fill_rate=atof(argv[1]);
	int number_of_steps=atoi(argv[2]);
	int particlecount=atoi(argv[3]);		

	auto lattice_size=particlecount/fill_rate;
	auto [particles,particle_lattice]=create_state(lattice_size,particlecount);
	auto origins=particles;
	
		for(int i=1;i<=number_of_steps;i++)
		{
			step(particles,particle_lattice);	
			if(i%256==0) analyze(origins,particles,i);
		}			
		
	return 0;
}

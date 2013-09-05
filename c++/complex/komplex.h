#include <iostream>
#include <string>
#include <sstream>

class base{
public:
	virtual ~base(){ std::cout << "base dtor()" << std::endl; }
	virtual std::string print()const{return "";}
	virtual double labso()const {return -1;}		//namiesto sqrt
};

template<typename T>
class komplex:public base{
	T real_;
	T imag_;
public:
	komplex(const T& r=0,const T& i=0):real_(r),imag_(i){}
	virtual ~komplex(){ std::cout << "komplex dtor()" << std::endl; }
	T real()const{return real_;}
	T imag()const{return imag_;}
	virtual double labso()const{
		return real_*real_+imag_*imag_;
	}
	virtual std::string print()const{
		std::ostringstream o;
		o<<"("<<real_<<","<<imag_<<")";
		return o.str();
	}
};

std::ostream& operator<<(std::ostream& o,const base* k ){
	o<<k->print();
	return o;
} 

class komplex_less{
public:
	bool operator()(base*l,base*r)const{
		return l->labso()<r->labso();
	}
};

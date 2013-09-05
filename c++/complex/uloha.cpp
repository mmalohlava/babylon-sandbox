/*
 * Mention DeletePtrTr operator!
 */
#include <iostream>
#include "komplex.h"
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

template<typename T> 
class DeletePtrTr {
public:
	void operator()(T*& p) { delete p; p = 0; };
};

int main(){
	vector<base*> v;

	ifstream fin("test");
	if ( !fin ){
		cout << "Nejde otvorit vstupny subor.\n";
		return 1;
	}
	
	char c, cRe, cIm;
	int iRe, iIm;
	long lRe, lIm;
	double dRe, dIm;
	string str="";

	while ( !fin.eof() ){
		fin >> c;		
		str="";
		switch (c){
			case 'C':		//char
				fin >> c; // "("
				fin >> cRe; 
				fin >> c; // ","
				fin >> cIm; 
				fin >> c;  // ")"
				komplex<char> *cPom;
				cPom = new komplex<char> (cRe,cIm);
				v.push_back(cPom);
			//	cout << "C" << cRe << " " << cIm << "\n";
				break;
			case 'I':		//int

				fin >> c; // "("
				//koli ciarke
				while ( c != ',' ){ 
					fin >> c;
					str += c;
				}		//zostanem na ciarke
				iRe = atoi(str.c_str());

				fin >> iIm; 
				fin >> c;  // ")"
				
				komplex<int> *iPom;
				iPom = new komplex<int> (iRe,iIm);
				v.push_back(iPom);
			//	cout << "I" << iRe << " " << iIm << "\n";
				break;
			case 'L':		//long
				fin >> c; // "("
				//koli ciarke
				while ( c != ',' ){ 
					fin >> c;
					str += c;
				}		//zostanem na ciarke
				lRe = atol(str.c_str());
				
				fin >> lIm; 
				fin >> c;  // ")"
				komplex<long> *lPom;
				lPom = new komplex<long> (lRe,lIm);
				v.push_back(lPom);
			//	cout << "L" << lRe << " " << lIm << "\n";
				break;
			case 'D':		//double
				fin >> c; // "("
				fin >> dRe; 
				fin >> c; // ","
				fin >> dIm; 
				fin >> c; // ")"
				komplex<double> *dPom;
				dPom = new komplex<double> (dRe,dIm);
				v.push_back(dPom);
			//	cout << "D" << dRe << " " << dIm << "\n";
				break;
			default: 
				fin >> c;
				break;
		}
	}
	fin.close();

/*	komplex<int> a(4,2),I(4,0);
	komplex<long> L(-1,2);
	komplex<double> D(3.3,4.2);

	v.push_back(&a);
	v.push_back(&I);
	v.push_back(&L);
	v.push_back(&D);
*/	
	sort(v.begin(),v.end(),komplex_less());

	for(size_t i=0;i<v.size();++i)
		cout<<v[i]<<endl;

	for_each(v.begin(), v.end(), DeletePtrTr<base>());
}

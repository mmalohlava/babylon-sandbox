/**
 * Critical path finder
 *
 * @author Michal Malohlava
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <map>
#include <list>

using namespace std;

class Edge;
class Vertex;
typedef vector<Edge *>   EdgeList;
typedef vector<Vertex *> VertexList;
typedef VertexList::iterator VertexListIterator;

struct Vertex {
	Vertex(int dur, int number) : duration(dur), est(0), ect(0), lst(0), lct(0), number(number), afterFirstPass(false), afterSecondPass(false) {};
	int number ;
	int duration;

	int est;
	int ect;

	int lst;
	int lct;

	VertexList pred;
	VertexList anc;
	
	bool afterFirstPass;
	bool afterSecondPass;

	bool isReadyFor1st() {
		VertexListIterator it;
		bool result = true;

		if (pred.empty() || afterFirstPass) {
			return false;
		}

		for(it=pred.begin(); it!=pred.end(); it++) {
			Vertex * v = *it;
			if (!v->afterFirstPass) {
				result = false;
				break;
			}
		}

		return result;
	}
	
	bool isReadyFor2st() {
		VertexListIterator it;
		bool result = true;

		if (anc.empty() || afterSecondPass) {
			return false;
		}

		for(it=anc.begin(); it!=anc.end(); it++) {
			Vertex * v = *it;
			if (!v->afterSecondPass) {
				result = false;
				break;
			}
		}

		return result;
	}
	int getEctMax() {
		int r = 0;
		VertexListIterator it;
		for(it = pred.begin(); it!=pred.end(); it++) {
			Vertex * v = *it;
			if (v->ect > r) {
				r = v->ect;
			}
		}

		return r;
	}
	
	int getLstMin() {
		int r = 1000000;
		VertexListIterator it;
		for(it = anc.begin(); it!=anc.end(); it++) {
			Vertex * v = *it;
			if (v->lst < r) {
				r = v->lst;
			}
		}

		return r;
	}
	friend class Edge;

	~Vertex() {
		pred.clear();
		anc.clear();
	}
};

ostream & operator<<(ostream & os, Vertex * v) {
	os << "v" << v->number << "(";
	os << "est=" << v->est;
	os << ",ect=" << v->ect;
	os << ",lst=" << v->lst;
	os << ",lct=" << v->lct;
	os << ")";

	return os;
}

struct Edge {
	Edge(Vertex * ve1, Vertex * ve2): v1(ve1), v2(ve2) {};

	Vertex * v1;
	Vertex * v2;
};
ostream & operator<<(ostream & os, Edge * e) {
	os << e->v1->number << "-->" << e->v2->number;

	return os;
}


template <typename T>
void deallocator(T & t) {
	delete t;
}

struct G {
	G(): Cmax(0) {};

	int numberOfVertex;
	int numberOfEdges;
	
	VertexList v;
	EdgeList   e;
	map<int, Vertex *> mapNumVertex;
	int Cmax;

	void addVertex(Vertex * node) {
		v.push_back(node);
		mapNumVertex[node->number] =  node;
	}

	void addEdge(int n1, int n2) {
		Vertex * v1 = mapNumVertex[n1];
		Vertex * v2 = mapNumVertex[n2];
		
		v2->pred.push_back(v1);
		v1->anc.push_back(v2);

		e.push_back(new Edge(v1, v2));

	}

	~G() {
		// TODO clear memory
		for_each(v.begin(), v.end(), deallocator<Vertex *>);
		for_each(e.begin(), e.end(), deallocator<Edge *>);
	}
};

ostream & operator<<(ostream & os, const G & g) {
	os << "G:" << endl;
	os << "  |V| = " << g.numberOfVertex;
	os << "  |E| = " << g.numberOfEdges;
	os << endl;

	copy(g.v.begin(), g.v.end(), ostream_iterator<Vertex *>(os, " "));
	os << endl;
	copy(g.e.begin(), g.e.end(), ostream_iterator<Edge *>(os, " "));
	os << endl;

	return os;
}

void read(const char * filename, G & graph) {
	ifstream in(filename);
	int duration;
	int i = 0;

	in >> graph.numberOfVertex;
	in >> graph.numberOfEdges;

	// skip line
	in.ignore();

	while(in.good() && i < graph.numberOfVertex) {
		in >> duration; 
		graph.addVertex(new Vertex(duration, ++i));
	}

	// skip line
	in.ignore();

	i = 0;
	while (in.good() && i < graph.numberOfEdges) {
		int v1, v2;
		in >> v1;
		in.ignore(1);
		in >> v2;

		graph.addEdge(v1, v2);

		i++;
	}

	in.close();
}


// First pass of algorithm
void firstPass(G&g) {
	list<Vertex *> tmp;
	list<Vertex *>::iterator v_it;
	copy(g.v.begin(), g.v.end(), back_inserter(tmp));

	cout << "First pass:" << endl;

	// initialization
	for(v_it = tmp.begin(); v_it != tmp.end(); v_it++) {
		Vertex * v = *v_it;

		if (v->pred.empty()) {
			v->est = 0;
			v->ect = v->duration;
			cout << v << " is at start" << endl;
			v->afterFirstPass = true;

			if (v->ect > g.Cmax) g.Cmax = v->ect;
		}
	}

	bool done = false;
	while(!done) {
		done = true;
		Vertex * vrchol = NULL;
		for(v_it = tmp.begin(); v_it!=tmp.end(); v_it++) {
			Vertex * v = *v_it;
			if (v->isReadyFor1st()) {
				done = false;
				vrchol = v;
				break;
			}
		}

		if (vrchol != NULL) {
			vrchol->est = vrchol->getEctMax();
			vrchol->ect = vrchol->est + vrchol->duration;
			vrchol->afterFirstPass = true;
			cout << vrchol << " is at 1st pass" << endl;

			if (vrchol->ect > g.Cmax) {
				g.Cmax = vrchol->ect;
			}
		}
	}

	cout << "First pass is passed" << endl;
	
}

void secondPass(G&g) {
	list<Vertex *> tmp;
	list<Vertex *>::iterator v_it;
	copy(g.v.begin(), g.v.end(), back_inserter(tmp));

	cout << "Second pass:" << endl;

	// initialization
	for(v_it = tmp.begin(); v_it != tmp.end(); v_it++) {
		Vertex * v = *v_it;

		if (v->anc.empty()) {
			v->lct = g.Cmax;
			v->lst = g.Cmax - v->duration;
			cout << v << " is at end" << endl;
			v->afterSecondPass = true;
		}
	}

	bool done = false;
	while(!done) {
		done = true;
		Vertex * vrchol = NULL;
		for(v_it = tmp.begin(); v_it!=tmp.end(); v_it++) {
			Vertex * v = *v_it;
			if (v->isReadyFor2st()) {
				done = false;
				vrchol = v;
				break;
			}
		}
		if (vrchol != NULL) {
			vrchol->lct = vrchol->getLstMin();
			vrchol->lst = vrchol->lct - vrchol->duration;
			cout << vrchol << " is at 2nd pass" << endl;
			vrchol->afterSecondPass = true;
		}
	}

	cout << "Second pass is passed" << endl;
}

// Second pass of algorithm
VertexList findCriticalPath(G& g) {
	VertexList result;
	VertexListIterator it;
	firstPass(g);

	secondPass(g);

	for (it = g.v.begin(); it != g.v.end(); it++) {
		Vertex *v = *it;
		if (v->est == v->lst){
			result.push_back(v);
		}
	}

	return result;
}

int main(int argc, char* argv[]) {
	if (argc < 2 ) {
		cerr << "Pouziti:" << endl << argv[0]  << " <file.name>" << endl << endl;
		return 1;
	}

	G graph;

	read(argv[1], graph);

	cout << graph;

	VertexList cPath = findCriticalPath(graph);
	cout << endl << "Critical Path:" << endl;
	copy(cPath.begin(), cPath.end(), ostream_iterator<Vertex *>(cout, " - "));
	cout << endl;

	return 0;
};



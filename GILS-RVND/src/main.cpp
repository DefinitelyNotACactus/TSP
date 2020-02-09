#include "readData.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <cfloat>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;

string instance;
double ** matrizAdj; // matriz de adjacencia
int dimension; // quantidade total de vertices
vector<int> s, candidates; // respectivamente, vetor de solucao e vetor de candidatos
double currentCost; // custo da solucao atual

void printData();
void printSolution();
double getCost(vector<int> &s);
double randomDouble();
// Heuristicas de construcao
void buildNearestNeighbor(vector<int> &s);
void buildCheapestInsertion(vector<int> &s);
void buildGrasp(vector<int> &s, int initialSubtour, double alpha);
void buildCandidates();
// Movimentos de vizinhanca
bool swap(vector<int> &st, double &cost);
bool twoOpt(vector<int> &st, double &cost);
bool reinsertion(vector<int> &st, int subtourSize, double &cost);
// Busca local
void rvnd(vector<int> &s, double &cost);
// Perturbacao
void doubleBridge(vector<int> &s, vector<int> &st, double &cost, double &sCost);
// Metaheuristica
void gils_rvnd(vector<int> &s, double &cost, int initialSubtour, int itr_max, int ils, double alpha);

struct insertionInfo {
    int insertedNode;
    int removedEdge;
    double cost;

    bool operator <(const insertionInfo &b) const {
        return cost < b.cost;
    }
};

int main(int argc, char** argv) {
    instance = argv[1];
    srand(time(nullptr));
    readData(argc, argv, &dimension, &matrizAdj);
    //printData();
    
    buildNearestNeighbor(s);
    currentCost = getCost(s);
    gils_rvnd(s, currentCost, 3, 5, 3, 0.5);
    printSolution();
    return 0;
}

void buildNearestNeighbor(vector<int> &s) {
	buildCandidates();
	s.push_back(1);
    int currentPoint = 1;
    while(candidates.size() > 1) {
        double nearestDist = matrizAdj[currentPoint][candidates.at(0)];
        int nearestIndex = 0;
        for(int i = 1; i < candidates.size(); i++) {
            if(matrizAdj[currentPoint][candidates.at(i)] < nearestDist) {
                nearestDist = matrizAdj[currentPoint][candidates.at(i)];
                nearestIndex = i;
            }
        }
        currentPoint = candidates.at(nearestIndex);
        s.push_back(currentPoint);
        candidates.erase(candidates.begin() + nearestIndex);
    }
    s.push_back(candidates.at(0));
    s.push_back(1);
}

void buildCheapestInsertion(vector<int> &s) {
    // Subrota inicial usando o primeiro do vetor de candidatos
    buildCandidates();
    s.push_back(1);
    s.push_back(candidates.at(0));
    candidates.erase(candidates.begin());
    s.push_back(1);
    // Insercao na subrota
    int pi, pj, pk;
    double skij;
    while(candidates.size() > 0) {
        pi = 0, pj = 1, pk = 0;
        for(int i = 0; i < s.size() - 1; i++) {
            for(int j = 1; j < s.size(); j++) {
                skij = DBL_MAX;
                for(int k = 0; k < candidates.size(); k++) {
                    if(matrizAdj[s.at(i)][candidates.at(k)] + matrizAdj[candidates.at(0)][s.at(j)] - matrizAdj[s.at(i)][s.at(j)] < skij) {
                        skij = matrizAdj[s.at(i)][candidates.at(k)] + matrizAdj[candidates.at(0)][s.at(j)] - matrizAdj[s.at(i)][s.at(j)];
                        pi = i;
                        pj = j;
                        pk = k;
                    }
                }
            }
        }
        s.insert(s.begin() + pi, candidates.at(pk));
        candidates.erase(candidates.begin() + pk);
    }
}

void buildGrasp(vector<int> &s, int initialSubtour, double alpha) {
	s = {1, 1};
	buildCandidates();
	int targetIndex;
	for(int i = 0; i < initialSubtour; i++) {
		targetIndex = rand() % candidates.size();
		s.insert(s.begin() + 1, candidates.at(targetIndex));
		candidates.erase(candidates.begin() + targetIndex);
	}
    while (candidates.size() > 0) {
    	vector<insertionInfo> insertionCost( (s.size() - 1) * candidates.size());
    	for(int i = 1, l = 0; i < s.size(); i++) {
    		for (int j = 0; j < candidates.size(); j++) {
    			insertionCost[l].cost = matrizAdj[s[i - 1]][candidates[j]] + matrizAdj[s[i]][candidates[j]] - matrizAdj[s[i - 1]][s[i]];
    			insertionCost[l].insertedNode = j;
    			insertionCost[l].removedEdge = i;
    			l++;
    		}
    	}
    	sort(insertionCost.begin(), insertionCost.end());
    	targetIndex = rand() % (int) floor(alpha * insertionCost.size());
    	s.insert(s.begin() + insertionCost[targetIndex].removedEdge, candidates[insertionCost[targetIndex].insertedNode]);
    	candidates.erase(candidates.begin() + insertionCost[targetIndex].insertedNode);
	}
}

void buildCandidates() {
	candidates = {};
	for(int i = 2; i <= dimension; i++) {
        candidates.push_back(i); // adicionando os pontos a lista de candidatos
    }
}

bool swap(vector<int> &st, double &cost) {
    double delta = DBL_MAX, nDelta = 0;
    int index_a, index_b;
    for(int i = 1; i < st.size() - 1; i++) {
        for(int j = i + 1; j < st.size() - 1; j++) {
            if(i == j - 1) {
                nDelta = matrizAdj[st.at(i - 1)][st.at(j)] + matrizAdj[st.at(j + 1)][st.at(i)] - matrizAdj[st.at(i - 1)][st.at(i)] - matrizAdj[st.at(j + 1)][st.at(j)];
            } else {
                nDelta = matrizAdj[st.at(i)][st.at(j - 1)] + matrizAdj[st.at(i)][st.at(j + 1)] + matrizAdj[st.at(j)][st.at(i - 1)] + matrizAdj[st.at(j)][st.at(i + 1)] - matrizAdj[st.at(j)][st.at(j - 1)] - matrizAdj[st.at(j)][st.at(j + 1)] - matrizAdj[st.at(i)][st.at(i - 1)] - matrizAdj[st.at(i)][st.at(i + 1)];
            }
            if(nDelta < delta) {
                index_a = i;
                index_b = j;
                delta = nDelta;
            }
        }
    }
    
    if(delta < 0) {
        int aux = st.at(index_a);
        
        st.at(index_a) = st.at(index_b);
        st.at(index_b) = aux;
        
        cost += delta;
        return true;
    }
    return false;
}

bool twoOpt(vector<int> &st, double &cost) {
    double delta = DBL_MAX, nDelta = 0;
    int index_a, index_b;
    for(int i = 1; i < st.size() - 1; i++) {
        for(int j = i + 1; j < st.size() - 1; j++) {
            nDelta = matrizAdj[st.at(i - 1)][st.at(j)] + matrizAdj[st.at(j + 1)][st.at(i)] - matrizAdj[st.at(j + 1)][st.at(j)] - matrizAdj[st.at(i - 1)][st.at(i)];
            if(nDelta < delta) {
                index_a = i;
                index_b = j;
                delta = nDelta;
            }
        }
    }
    
    if(delta < 0) {
        vector<int> aux; // assumindo que index_a > index_b
        for(int i = index_b; i >= index_a; i--) {
            aux.push_back(st.at(i));
        }
        st.erase(st.begin() + index_a, st.begin() + index_b + 1);
        st.insert(st.begin() + index_a, aux.begin(), aux.end());
        
        cost += delta;
        return true;
    }
    return false;
}

bool reinsertion(vector<int> &st, int subtourSize, double &cost) {
    double delta = DBL_MAX, nDelta = 0;
    int index_a, index_b;
    for(int i = 1; i < st.size() - subtourSize; i++) {
        for(int j = 1; j < st.size() - 1; j++) {
            if(j >= i && j <= i + subtourSize) {
                continue;
            }
            nDelta = matrizAdj[st.at(j - 1)][st.at(i)] + matrizAdj[st.at(i + subtourSize - 1)][st.at(j)] + matrizAdj[st.at(i - 1)][st.at(i + subtourSize)] - matrizAdj[st.at(i + subtourSize - 1)][st.at(i + subtourSize)] - matrizAdj[st.at(j - 1)][st.at(j)] - matrizAdj[st.at(i - 1)][st.at(i)];
            if(nDelta < delta) {
                index_a = i;
                index_b = j;
                delta = nDelta;
            }
        }
    }
    
    if(delta < 0) {
        vector<int> aux;
        aux.insert(aux.end(), st.begin() + index_a, st.begin() + index_a + subtourSize);
        st.erase(st.begin() + index_a, st.begin() + index_a + subtourSize);
        if(index_a >= index_b) {
            st.insert(st.begin() + index_b, aux.begin(), aux.end());
        } else {
            st.insert(st.begin() + index_b - subtourSize, aux.begin(), aux.end());
        }
        
        cost += delta;
        return true;
    }
    return false;
}

void gils_rvnd(vector<int> &s, double &cost, int initialSubtour, int itr_max, int ils, double alpha) {
    vector<int> st, stt;
    double f = DBL_MAX, sCost;
    for(int i = 0; i < itr_max; i++) {
        buildGrasp(s, initialSubtour, alpha);
        cost = getCost(s);
        sCost = cost;
        st = s;
        int itr_ils = 0;
        while(itr_ils < ils) {
            rvnd(st, sCost);
            if(sCost < cost) {
                s = st;
                cost = sCost;
                itr_ils = 0;
            }
            doubleBridge(s, st, cost, sCost);
            itr_ils++;
        }
        if(cost < f) {
        	stt = s;
        	f = cost;
        }
    }
    cost = f;
    s = stt;
}

void rvnd(vector<int> &s, double &cost) {
    vector<int> nl = {0, 1, 2, 3, 4};
    double tempCost = cost;
    
    int n = 0;
    bool improve = false;
    while(!nl.empty()) {
        n = rand() % nl.size();
        switch(nl.at(n)) {
            case 0: // swap
                improve = swap(s, tempCost);
                break;
            case 1: // 2-opt
                improve = twoOpt(s, tempCost);
                break;
            case 2: // reinsercao 1
                improve = reinsertion(s, 1, tempCost);
                break;
            case 3: // reinsercao 2
                improve = reinsertion(s, 2, tempCost);
                break;
            case 4: // reinsercao 3
                improve = reinsertion(s, 3, tempCost);
                break;
        }
        if(improve) {
            nl = {0, 1, 2, 3, 4};
        } else {
            nl.erase(nl.begin() + n);
        }
    }

    cost = tempCost;
}

void doubleBridge(vector<int> &s, vector<int> &st, double &cost, double &sCost) {
    int interval = s.size() >> 2,
    index_a = 1 + rand() % interval,
    index_b = 1 + index_a + rand() % interval,
    index_c = 1 + index_b + rand() % interval;
    
    st.clear();
    st.insert(st.end(), s.begin(), s.begin() + index_a);
    st.insert(st.end(), s.begin() + index_c, s.end() - 1);
    st.insert(st.end(), s.begin() + index_b, s.begin() + index_c);
    st.insert(st.end(), s.begin() + index_a, s.begin() + index_b);
    st.insert(st.end(), s.at(0));
    
    sCost = matrizAdj[s.at(index_a - 1)][s.at(index_c)] + matrizAdj[s.at(s.size() - 2)][s.at(index_b)] + matrizAdj[s.at(index_c - 1)][s.at(index_a)] + matrizAdj[s.at(index_b - 1)][s.at(0)] - matrizAdj[s.at(index_a - 1)][s.at(index_a)] - matrizAdj[s.at(index_b - 1)][s.at(index_b)] - matrizAdj[s.at(index_c - 1)][s.at(index_c)] - matrizAdj[s.at(s.size() - 2)][s.at(0)];
    sCost += cost;
}

double getCost(vector<int> &s) {
   double c = 0;
    for(int i = 0; i < s.size() - 1; i++) {
        c += matrizAdj[s.at(i)][s.at(i+1)];
    }
    return c;
}

void printData() {
  cout << "dimension: " << dimension << endl;
  for (size_t i = 1; i <= dimension; i++) {
    for (size_t j = 1; j <= dimension; j++) {
      cout << matrizAdj[i][j] << " ";
    }
    cout << endl;
  }
}

void printSolution() {
    cout << "Instancia: " << instance << endl;
    cout << "S = {";
    for(int i = 0; i < s.size() - 1; i++) {
        cout << s.at(i) << ", ";
    }
    cout << s.at(s.size() - 1) << "}" << endl;
    cout << "Custo: " << currentCost << endl;
}

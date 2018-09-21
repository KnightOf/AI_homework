#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
using namespace std;

#define MIN -1000
#define MAX 1000

class Val{
public:
	int val;
	bool isExpanded;
	Val(int v){
		val= v;
		isExpanded= false;
	}
};
int count = 0;
int Recur_Minimax(vector<Val> &leaf, int h, int index, int level, bool isMAX, int degree, int alpha, int beta){
	
	//將best設為MIN or MAX 
	int best= (isMAX == true) ? MIN : MAX;
	
	//當遍尋完成，返回目前index裡的值(answer) 
	if(level == h){
		leaf[index].isExpanded= true;
		return leaf[index].val;	
	}	
	
	//          MAX
	if(isMAX){
		for(int i=0; i<degree; i++){
			int val= Recur_Minimax(leaf, h, index * degree + i, level + 1, false, degree, alpha, beta);
			best= max(best, val);
			alpha= max(best, alpha);
			cout <<best<<"max\t"<<alpha<<endl;
			//Prunning
			if(alpha>= beta){
				//count++;
				break;
			}	
			
		}
		return best;
	}
	
	//MIN
	else{
		for(int i=0; i<degree; i++){
			int val= Recur_Minimax(leaf, h, index * degree + i, level + 1, true, degree, alpha, beta);
			best= min(best, val);
			beta= min(best, beta);
			cout <<best<<"min\t"<<beta<<endl;
			//Prunning
			if(alpha>= beta){
				//count++;
				break;
			}	
				
		}
		return best;
	}
}
int main(int argc, char** argv) {
	vector<int> value;
	int height,degree,i,temp;
	fstream fin;
	fin.open("test.txt",ios::in);
	
	fin >> degree;
	fin >> height;
	height+=1;
	while(!fin.eof()){
		fin >> temp;
		value.push_back(temp);
		//cout<<value[i]<<endl;
		++i;
	}

	vector<Val> leaf_value;
	for(int i=0; i<value.size(); i++){
		Val leaf(value[i]);
		leaf_value.push_back(leaf);
	}

	cout<< "ans:\t"<< Recur_Minimax(leaf_value, height, 0, 1, true, degree, MIN, MAX)<< endl;
	cout<< "leaves:\t";
	for(vector<Val>::iterator it=leaf_value.begin(); it!=leaf_value.end(); it++)	
		if(it->isExpanded){
			cout<< it->val<<" ";
			//count++;
		}	
	cout<<endl<< count;
	return 0;
}

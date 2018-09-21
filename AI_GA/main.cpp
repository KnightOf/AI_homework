#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;


#define POPULATION 100
int MAX_CONFLICTED; 
int k = 8;



class One_Board{
	protected:
		vector<int> boardX;
		vector<int> boardY;
		int conflicted;
	public:
		One_Board(){
			shuffle();
			conflict();
		}
		One_Board(vector<int> _new){		
			boardX.clear();
            boardY.clear();
            for(int i =0;i<k;i++){
				boardX.push_back(_new.at(i));
				boardY.push_back(i+1);
			}
			conflict();
		}
		
		One_Board(vector<int> _X,vector<int> _Y){
			_X.swap(boardX);
			_Y.swap(boardY);
			conflict();
		}
		
		vector<int> get_X(){
			return boardX;
		}
		int get_Con(){
			return conflicted;
		}
		
		void shuffle(){
			vector<int> temp;
			for(int i =0;i<k;i++){
				boardX.push_back(i+1);
				boardY.push_back(i+1);
			}
			for(int i = 0;i<k;i++)
				swap(boardX[rand()%k],boardX[i]);
		}
		
		void show_Board(){
			for(int i =0;i<k;i++){
				for(int j =0;j<k;j++){
					if(boardX.at(i)==j+1){
						cout<<"X ";
					}
					else cout<<"_ ";
				}
				cout<<endl;
			}
		}
		
		void conflict(){	
			conflicted = 0;						
			double r,_x,_y;
			for(int i =0;i<k;i++){
				for(int j = i+1;j<k;j++){
					_x = boardX.at(j)-boardX.at(i);
					_y = boardY.at(j)-boardY.at(i);
					r = _y/_x;
					if( !(r==1.00 || r== -1.00|| _x == 0 || _y == 0 ) )
						conflicted++;	
				    
				}			
			}
			//cout<<conflicted<<endl;
		}
		
		
};

vector<One_Board> populations;

void max_Con(){
    for(int i =1;i<k;i++)
        MAX_CONFLICTED +=i;
}

void check_Over(One_Board _this){
    if(_this.get_Con() == MAX_CONFLICTED){
        cout<<"FOUND!!"<<endl;
        _this.show_Board();
        system("pause");
    } 
}

void new_population(){
    for(int i = 0 ;i<POPULATION;i++){
           One_Board temp = One_Board();
           check_Over(temp);
           populations.push_back(temp);
    }
}

bool Mutation(){
	int nRand = rand()%1000;
	if(nRand == 731) return true;
	else return false;  
}

void GA(int genNum){
    //Father & Mother Choose
	vector<vector<int> > Father,Mother;
	vector<int> accum;
	
	int total_Rate = 0;
	
	for(int i =0;i<POPULATION;i++){			
		total_Rate += populations[i].get_Con();
		accum.push_back(total_Rate);
	}
	for(int j=0;j<POPULATION;j++){
				
		int nRand = rand()%total_Rate;
		for(int i =0;i<POPULATION;i++){
			if(nRand < accum[i])
				Father.push_back(populations[i].get_X());
		
		}
		
		
		nRand = rand()%total_Rate;
		for(int i =0;i<POPULATION;i++){
			if(nRand < accum[i])
				Mother.push_back(populations[i].get_X());		
		
		}
		
			
	}
	
	//crossover
	vector<int> born;
	vector<One_Board> new_Gen;
	int nPos = k/2;
	
	
	for(int i =0;i<POPULATION;i++){ 
		born.clear();
		for(int j =0;j<nPos;j++){        
			born.push_back(Father[i].at(j));
		}
		
		for(int j =nPos;j<k;j++){         
			born.push_back(Mother[i].at(j));
    	}
    	
    	/*
		for(int s = 0;s<k;s++){
			cout << born[s]<<" ";
		}
		cout<< endl;
		*/
        //------------------------------------------------------------------------------------------------
        //Mutation
		if(Mutation()){
        	nPos = rand()%(k-1);
        	int r = (rand()%(k-1)) +1;
        	if( r != born[nPos]){
        		//cout<<"突變發生!! 在第"<<genNum<<"代 第"<<i<<"子 第"<<nPos+1<<"基因 "<<born[nPos]<<"-->"<<r<<endl;
				born[nPos] = r;
			}
        		
		}
		
		//save BORN into populations
		One_Board BORN =  One_Board(born);
		if(BORN.get_Con()==MAX_CONFLICTED)
			cout << genNum<<endl;
			
        check_Over(BORN);   
        populations.push_back(BORN);
        
    } 
}

int main(int argc, char** argv) {
   	srand((unsigned) time(NULL) );
    max_Con();   
	int genNum = 0;
    new_population();
    cout<<"PLEASE CHOOSE THE FUNCTION U WANT TO USE"<<endl;
	cout<<"(0 using GA Algorithm to solve K_Queen question"<<endl;
	cout<<"(1 check if that input is a best answer "<<endl; 
	int respond;
	scanf("%d",&respond);
	switch(respond){
		case 0 :
			while(true){
		    	if(genNum<1000000000){
		    		//cout<<"第"<<genNum<<"代"<<endl;
					GA(genNum);
		    		genNum++;
				}
				else{
					cout << "restart"<<endl;
					new_population();
					genNum = 0;
				}
			}
			
		case 1 :
			int answer;
			vector<int> X,Y;
			cout<<"X:"<<"  please input number like this: 1<enter2<enter3<enter4<enter...."<<endl;
			
			while(X.size()<k){
				scanf("%d",&answer);
				X.push_back(answer);
			}
			cout<<endl;
			//cout<<"Y:"<<"  please input number like this: 8<enter7<enter6<enter5<enter...."<<endl;
			for(int i=0;Y.size()<k;i++){
				//scanf("%d",&answer);
				Y.push_back(i+1);
			}
			One_Board forCheck = One_Board(X,Y);
			if(forCheck.get_Con()==MAX_CONFLICTED)
				cout<<"best answer!!!!!"<<endl;
			else cout<<"not answer  conflict = "<<MAX_CONFLICTED-forCheck.get_Con()<<endl;
		
	}
	
    
    
	
	
	
	
	
	
	
	return 0;
}

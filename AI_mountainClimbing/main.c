#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct _state state;
struct _state{
	int chess[20][2];		   //8個皇后的座標 [x,y] x=第x+1個皇后 [x,0]=X座標 [x,1]=Y座標
	int conflict;              //這個狀態的棋盤有幾個衝突
	state **next_ary;   //指向下個狀態的指標
};

int read_file();			   //讀txt檔，回傳開始節點的K
state *new_board(int k);       //回傳一個隨機的棋盤
void shuffle(int *ran,int k);
int check(state* this_state,int k);  //顯示thisstate的衝突數(互相衝突算1個)
void show_board(state* this_state,int k); //顯示thisstate的棋盤
state *new_state(state *this_state,int k);
state *heuristic(state* this_state,int k);
void write_file(state *out,int k);

int main(int argc, char *argv[]) {
	int k;
	srand(time(NULL));
	state *current_board;
	current_board = (state *) malloc(sizeof(state));
	k = read_file();
	current_board = new_board(k);
	show_board(current_board,k);
	current_board = heuristic(current_board,k);

	 
	return 0;
}

int 
read_file() {
	int i,k=0;
	char temp;
	state *watch;
	watch = (state *) calloc(1,sizeof(state));
	FILE* fptr = fopen("D:\\人工智慧\\8 queen\\2\\test.txt","r");
	fscanf(fptr,"%d\n",&k); //幾皇后
	printf("共 %d 后\n",k);
	printf("是否讀入座標值? 0/1\t");
	scanf("%d",&i);
		if(i == 1){
			for(i=0;i<k;i++)
				fscanf(fptr,"%d %d\n",&watch->chess[i][0],&watch->chess[i][1]);
			check(watch,k);
			system("pause");
		}
	
		
	fclose(fptr);
	return k;
}
void
shuffle(int *ran,int k){
	int i,j,temp=0;
	for(i=0;i<k;i++)
		ran[i]=i+1;
	for(i=0;i<k;i++){
		j=rand()%k;
		temp =ran[j];
		ran[j] = ran[i];
		ran[i] = temp;				
	}		
}
state *
new_board(int k){
	int ran[k],i;;
	state *new_;
	new_ = (state *) calloc(1,sizeof(state));
	shuffle(ran,k);
	for(i=0 ; i<k ;i++)
		new_->chess[i][0] =	i+1;
	for(i=0 ; i<k ;i++)
		new_->chess[i][1] = ran[i];
	return new_;	
}
void
show_board(state *board,int k){
	int i,j;
	char chess_board[k][k];
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			chess_board[i][j]=' ';
		}
	}
	for(i=0;i<k;i++){
		chess_board[board->chess[i][0] -1 ][board->chess[i][1] -1 ] = 'X';
	}
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			printf("%c|",chess_board[j][i]);
		}
		printf("\n");
	}
}

int 
check(state *state,int k){
 	int i,j,count=0;
 	double _x,_y;
 	for(i=0;i<k;i++)
 		printf("%d %d\n",state->chess[i][0],state->chess[i][1]);
 	for(i=0;i<k;i++){
 		for(j=k-1;j>i;j--){
 			_x = state->chess[j][0]-state->chess[i][0];
 			_y = state->chess[j][1]-state->chess[i][1];
 			double slope = _y/ _x;
 			if(slope == -1.00 || slope == 1.00|| _x == 0 || _y == 0){
 				count++;
				if(_x == 0) 
					printf("%d后 與 %d后 於  X  軸衝突\n",i+1,j+1);
				else if(_y == 0)
					printf("%d后 與 %d后 於  Y  軸衝突\n",i+1,j+1);
				else 
					printf("%d后 與 %d后 於  斜  軸衝突\n",i+1,j+1);
		    }
	    }	
	}
	state->conflict = count;
	printf("共 %d 衝突\n",count);
	return count;
}
state *
heuristic(state *this_state,int k){
	int count=0;
	int i,j,least,less=0,gen=0;
	state *lessconf;
	lessconf = (state *) calloc(1,sizeof(state));
	this_state->next_ary = (state **) calloc(k,sizeof(state *));
	least = check(this_state,k);
	*lessconf = *this_state;
	
	while(1){
		
	for(i=0;i<k;i++){
		this_state->next_ary[i] = (state*) calloc(1,sizeof(state)); 
		*(this_state->next_ary[i]) = *lessconf;
		printf("%d \t%d\n",this_state->next_ary[i]->chess[0][0],this_state->next_ary[i]->chess[0][1]);
		for(j=0;j<k;j++){
			this_state->next_ary[i]->chess[i][0]=j+1;
			less = check(this_state->next_ary[i],k);
			
			if (less == 0){
				printf("found!!\n");
				show_board(this_state->next_ary[i],k);
				printf("共重啟 %d\n",count);
				count = 0;
				write_file(this_state->next_ary[i],k);
				system("PAUSE");
				//return state->next_ary[i];
			}
			
			else if( less < least){
				*lessconf = *(this_state->next_ary[i]);
				least = less;
			}
		}
		
	}
	lessconf = new_board(k);
	count++;
	
 }
	
		
	return lessconf;
}
void 
write_file(state *out,int k){
	int i;
	FILE *fptr = fopen("D:\\人工智慧\\8 queen\\2\\ans.txt","w");
	fprintf(fptr,"共 %d 后\n",k);
	for(i=0;i<k;i++){
		fprintf(fptr,"%d %d\n",out->chess[i][0],out->chess[i][1]); 
	}
	fclose(fptr);
}

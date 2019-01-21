#include "game.hpp"
#include "ai.hpp"
#include <thread>
#include <vector>
#include <map>
#include<algorithm>
#include<queue>
#include <random>
#include<iostream>

/*	int board_G[10][10] = {{0,0,0,0,0,0,0,0,0,0},
	{0,120,-20,20,5,5,20,-20,120,0},
	{0,-20,-40,-5,-5,-5,-5,-40,-20,0},
	{0,20,-5,15,3,3,15,-5,20,0},
	{0,5,-5,3,3,3,3,-5,5,0},
	{0,5,-5,3,3,3,3,-5,5,0},
	{0,20,-5,15,3,3,15,-5,20,0},
	{0,-20,-40,-5,-5,-5,-5,-40,-20,0},
	{0,120,-20,20,5,5,20,-20,120,0},
	{0,0,0,0,0,0,0,0,0,0}};
*/
int board_G_W[10][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			  { 0, 30, -12, 0, -1, -1, 0, -12, 30, 0 },
			  { 0, -12, -15, -3, -3, -3, -3, -15, -12, 0 },
			  { 0, 0, -3, 0, -1, -1, 0, -3, 0, 0 },
			  { 0, -1, -3, -1, -1, -1, -1, -3, -1, 0 },
			  { 0, -1, -3, -1, -1, -1, -1, -3, -1, 0 },
			  { 0, 0, -3, 0, -1, -1, 0, -3, 0, 0 },
			  { 0, -12, -15, -3, -3, -3, -3, -15, -12, 0 },
			  { 0, 30, -12, 0, -1, -1, 0, -12, 30, 0 },
			  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int board_G_B[10][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			  { 0, 30, -12, 0, -1, -1, 0, -12, 30, 0 },
			  { 0, -12, -15, -3, -3, -3, -3, -15, -12, 0 },
			  { 0, 0, -3, 0, -1, -1, 0, -3, 0, 0 },
			  { 0, -1, -3, -1, -1, -1, -1, -3, -1, 0 },
			  { 0, -1, -3, -1, -1, -1, -1, -3, -1, 0 },
			  { 0, 0, -3, 0, -1, -1, 0, -3, 0, 0 },
			  { 0, -12, -15, -3, -3, -3, -3, -15, -12, 0 },
			  { 0, 30, -12, 0, -1, -1, 0, -12, 30, 0 },
			  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


std::random_device rnd;     // 非決定的な乱数生成器を生成
std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
std::uniform_int_distribution<> rand64(0, 10000);        // [0, 99] 範囲の一様乱数

/*	read_board_G関数　開始　*//////////////////////////////////////////////////////////////////////////////
void read_board_G(){

    for(int i = 1;i <= 8; i++){
	for(int j = 1; j <= 8; j++){
	    std::cin >> board_G_W[i][j];
	    board_G_B[i][j] =  board_G_W[i][j];
	}
    }
    
}

void read_board_G(int color){

    if(color == Black){
	for(int i = 1;i <= 8; i++){
	    for(int j = 1; j <= 8; j++){
		std::cin >> board_G_B[i][j];
	   
	    }
	}
    }else{
	for(int i = 1;i <= 8; i++){
	    for(int j = 1; j <= 8; j++){
		std::cin >> board_G_W[i][j];
	   
	    }
	}
    
    }
}
/*	read_board_G関数　終了　*////////////////////////////////////////////////////////////////////////////////

/*	write_board_G関数　開始　*//////////////////////////////////////////////////////////////////////////////
void write_board_G(int color){

    if(color == Black){
	for(int i = 1;i <= 8; i++){
	    for(int j = 1; j <= 8; j++)std::cout << board_G_W[i][j] << " ";
	    std::cout << std::endl;
	}
    }else{

	for(int i = 1;i <= 8; i++){
	    for(int j = 1; j <= 8; j++)std::cout << board_G_B[i][j] << " ";
	    std::cout << std::endl;
	}
    }
    
}
/*	write_board_G関数　終了　*////////////////////////////////////////////////////////////////////////////////

/*	update_board_G関数　開始　*//////////////////////////////////////////////////////////////////////////////
void update_board_G(int color){
    int i = rand64(mt)%8 + 1,j = rand64(mt)%8 + 1,num = rand64(mt)%201 - 100;

    if(color == Black)board_G_B[i][j] = num;
    else board_G_W[i][j] = num;
    
}

void update_board_G2(int color){
    int i = rand64(mt)%4 + 1,j = rand64(mt)%4 + 1,num = rand64(mt)%10 - 5;

    if(num >= 0)num++;
    
    if(color == Black){
	board_G_B[i][j] += num;
	if(board_G_B[i][j] < -100)board_G_B[i][j] = -100;
	if(100 < board_G_B[i][j])board_G_B[i][j] = 100;

	board_G_B[9-i][j] = board_G_B[i][j];
	board_G_B[i][9-j] = board_G_B[i][j];
	board_G_B[9-i][9-j] = board_G_B[i][j];
    }else{
	board_G_W[i][j] += num;
	if(board_G_W[i][j] < -100)board_G_W[i][j] = -100;
	if(100 < board_G_W[i][j])board_G_W[i][j] = 100;

	board_G_W[9-i][j] = board_G_W[i][j];
	board_G_W[i][9-j] = board_G_W[i][j];
	board_G_W[9-i][9-j] = board_G_W[i][j];
    }
}
/*	update_board_G関数　終了　*////////////////////////////////////////////////////////////////////////////////

/*	copy_board_G関数　開始　*//////////////////////////////////////////////////////////////////////////////
void copy_board_G(int color){

    if(color == Black){
	for(int i = 1;i <= 8; i++){
	    for(int j = 1; j <= 8; j++)board_G_B[i][j] = board_G_W[i][j];
	}
    }else{
	for(int i = 1;i <= 8; i++){
	    for(int j = 1; j <= 8; j++)board_G_W[i][j] = board_G_B[i][j];
	}
    }
    
}
/*	copy_board_G関数　終了　*////////////////////////////////////////////////////////////////////////////////


/*	turn_dfs関数　開始　*//////////////////////////////////////////////////////////////////////////////
board turn_dfs(int color,board dfs,int t_max){

    int I = 0,J = 0,flag;
    int next_color = color^1;
    double hightscore = -999999;

    int i,j;

    flag = search(color,&dfs);//置ける場所を探す

    if(flag == 0){//置ける場所がある
	std::thread th1,th2;
	double t1_score= -9991,t2_score= -9991;
	int t1_flag = 0,t2_flag = 0;

		
	std::queue<std::pair<int,int>> q;
	std::pair<int,int> place1,place2;
		
	for(i=1;i<=8;i++){
	    for(j=1;j<=8;j++){
		if(((dfs.rpiece>>(64-j -((i-1)*8))) & 1)==1){//置ける場所を探す board[i][j] == 1
		    q.push(std::make_pair(i,j));
		}
	    }
	}

	while(!(q.empty() && t1_flag == 0 && t2_flag == 0 )){
	    if(!q.empty()){
		if(t1_flag == 0){
		    t1_flag = 1;

		    place1 = q.front();
		    q.pop();
				
		    board after = operation(place1.first,place1.second,color,dfs);//とにかく置いてみる
		    //次の相手のターンへ
		    th1 = std::thread(turn_dfs_next_thread,next_color,color,after,t_max-1,std::ref(t1_score));	
		}	
	    }
	    if(!q.empty()){
		if(t2_flag == 0){
		    t2_flag = 1;

		    place2 = q.front();
		    q.pop();

		    board after = operation(place2.first,place2.second,color,dfs);//とにかく置いてみる
		    //次の相手のターンへ
		    th2 = std::thread(turn_dfs_next_thread,next_color,color,after,t_max-1,std::ref(t2_score));
				
		}
	    }

	    if(t1_flag == 1)th1.join();//Wait for end of th
	    if(t2_flag == 1)th2.join();//Wait for end of th
			
	    if(t1_flag == 1 && t1_score != -9991){
		if(hightscore < t1_score){//記録更新なら
		    I = place1.first;
		    J = place1.second;
		    hightscore = t1_score;
		}
		t1_score = -9991;
		t1_flag = 0;
	    }

	    if(t2_flag == 1 && t2_score != -9991){
		if(hightscore < t2_score){//記録更新なら
		    I = place2.first;
		    J = place2.second;
		    hightscore = t2_score;
		}
		t2_score = -9991;
		t2_flag = 0;
	    }
	}
    }else {//はじめから置けないなら考える必要はない

	dfs.pass = color;
	dfs.p_cnt = 0;//パス後のwaitを一回にするため
		
	return dfs;		
    }

    dfs = operation(I,J,color,dfs);//確定
					
    dfs.pass = Non;
    dfs.p_cnt += 1;
	
    return dfs;
}
/*	turn_dfs関数　終了　*////////////////////////////////////////////////////////////////////////////////

/*	turn_dfs_next_thread関数　開始　*//////////////////////////////////////////////////////////////////////////////
void turn_dfs_next_thread(int color, int S_color, board dfs, int t_max,double &ret_score){
	
    int flag,i,j,ret_cnt = -1,ii,jj;
    int next_color = color^1;
    double score = 0;
    board after;
	
    if(t_max > 0){//まだ先読みする
	
	flag = search(color,&dfs);//置ける場所を探す
		
	if(flag == 0){//置ける場所がある
			
	    for(i=1;i<=8;i++){
		for(j=1;j<=8;j++){
				
		    if(((dfs.rpiece>>(64-j -((i-1)*8))) & 1)==1){//置ける場所を探す board[i][j] == 1
					
			after = operation(i,j,color,dfs);//とにかく置いてみる
					
			score += turn_dfs_next(next_color,S_color,after,t_max-1);//次の相手のターンへ;
						
			ret_cnt++;//リターンのカウント
		
			if(ret_cnt){//リターン2回目以降なら
							
			    //score >>= 1;//平均を求める
			    score /= 2;//平均を求める
			}
		    }
		}
	    }
		
	}else{//置けない
		
	    flag = search(next_color,&dfs);//相手が置けるか調べる
		
	    if(flag == 0){//相手は置ける
		//パス
		score = turn_dfs_next(next_color,S_color,dfs,t_max-1);//次の相手のターンへ
				
	    }else{//相手も置けない=ゲーム終了
				
		if(S_color == Black){//空白マスも自分のマスにor相手のマスに
		    if(dfs.bpnum > dfs.wpnum)dfs.bpiece |= ~(dfs.wpiece);
		    else dfs.wpiece |= ~(dfs.bpiece);
		}else{
		    if(dfs.bpnum < dfs.wpnum)dfs.wpiece |= ~(dfs.bpiece);
		    else dfs.bpiece |= ~(dfs.wpiece);
		}
		score = evaluation(S_color,&dfs,(t_max > 100)?1:0);			
	    }
	}
    }else{//先読みの上限が来た

	score = evaluation(S_color,&dfs,0);
    }
	
    ret_score = score;
}
/*	turn_dfs_next_thread関数　終了　*//////////////////////////////////////////////////////////////////////////////



/*	turn_dfs_next関数　開始　*//////////////////////////////////////////////////////////////////////////////
double turn_dfs_next(int color, int S_color, board dfs,int t_max){
	
    int flag,i,j,ret_cnt = -1,ii,jj;
    int next_color = color^1;
    double score = 0;
    board after;

    if(t_max > 0){//まだ先読みする
	
	flag = search(color,&dfs);//置ける場所を探す
		
	if(flag == 0){//置ける場所がある
			
	    for(i=1;i<=8;i++){
		for(j=1;j<=8;j++){
				
		    if(((dfs.rpiece>>(64-j -((i-1)*8))) & 1)==1){//置ける場所を探す board[i][j] == 1
					
			after = operation(i,j,color,dfs);//とにかく置いてみる
						
			score += turn_dfs_next(next_color,S_color,after,t_max-1);//次の相手のターンへ
						
			ret_cnt++;//リターンのカウント
		
			if(ret_cnt){//リターン2回目以降なら
							
			    //score >>= 1;//平均を求める
			    score /= 2;//平均を求める
			}
		    }
		}
	    }
		
	}else{//置けない
		
	    flag = search(next_color,&dfs);//相手が置けるか調べる
		
	    if(flag == 0){//相手は置ける
		//パス
		score = turn_dfs_next(next_color,S_color,dfs,t_max-1);//次の相手のターンへ
				
	    }else{//相手も置けない=ゲーム終了
			
		if(S_color == Black){//空白マスも自分のマスにor相手のマスに
		    if(dfs.bpnum > dfs.wpnum)dfs.bpiece |= ~(dfs.wpiece);
		    else dfs.wpiece |= ~(dfs.bpiece);
		}else{
		    if(dfs.bpnum < dfs.wpnum)dfs.wpiece |= ~(dfs.bpiece);
		    else dfs.bpiece |= ~(dfs.wpiece);
		}
		score = evaluation(S_color,&dfs,(t_max > 100)?1:0);		
	    }
	}
    }else{//先読みの上限が来た

	score = evaluation(S_color,&dfs,0);
    }
	
    return score;
}
/*	turn_dfs_next関数　終了　*//////////////////////////////////////////////////////////////////////////////




/*	turn_rand関数　開始　*//////////////////////////////////////////////////////////////////////////////
board turn_rand(int color, board ran){

    int I = 0, J = 0, flag, rand, rand_cnt = 0;
    int i, j;
    
    rand = rand64(mt);//0-64の値でランダム

    flag = search(color, &ran);//置ける場所を探す

    if (flag == 0){//置ける場所がある

	while (rand_cnt <= rand){
	    for (i = 1; i <= 8; i++){
		for (j = 1; j <= 8; j++){
		    if (((ran.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//置ける場所を探す board[i][j] == 1

			if (rand_cnt == rand){//ランダム値を見つけたら
			    I = i;//置く座標の記憶
			    J = j;
			}
			rand_cnt++;
		    }
		}
	    }
	}

    }
    else {//はじめから置けないなら考える必要はない

	ran.pass = color;
	ran.p_cnt = 0;//パス後のwaitを一回にするため

	return ran;
    }

    ran = operation(I, J, color, ran);//確定
	
    ran.pass = Non;
    ran.p_cnt += 1;

    return ran;
}
/*	turn_rand関数　終了　*////////////////////////////////////////////////////////////////////////////////



/*	turn_minmax関数　開始　*//////////////////////////////////////////////////////////////////////////////
board turn_minmax(int S_color, board minmax, int t_max){

    int I = 0, J = 0, flag;
    int next_color = S_color ^ 1;
    double hightscore = -99999999, score = 0;
    int i, j;
    board after;

    flag = search(S_color, &minmax);//置ける場所を探す

    if (flag == 0){//置ける場所がある

	for (i = 1; i <= 8; i++){
	    for (j = 1; j <= 8; j++){

		if (((minmax.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//置ける場所を探す board[j][i] == 1

		    after = operation(i, j, S_color, minmax);//とにかく置いてみる

		    //次の相手のターンへ
		    score = turn_minmax_next(next_color, S_color, after, t_max-1);

		    if (hightscore < score){//記録更新なら
			I = i;
			J = j;
			hightscore = score;
		    }
		}
	    }
	}
    }
    else {//はじめから置けないなら考える必要はない

	minmax.pass = S_color;
	minmax.p_cnt = 0;//パス後のwaitを一回にするため

	return minmax;
    }

    minmax = operation(I, J, S_color, minmax);//確定
	
    minmax.pass = Non;
    minmax.p_cnt += 1;

    return minmax;
}
/*	turn_minmax関数　終了　*////////////////////////////////////////////////////////////////////////////////




/*	turn_minmax_next関数　開始　*//////////////////////////////////////////////////////////////////////////////
double turn_minmax_next(int color, int S_color, board minmax, int t_max){

    int flag;
    int next_color = color ^ 1;
    double hightscore = -99999999, score = 0;

    if (color != S_color)hightscore = 99999999;

    int i, j;
    board after;

    if (t_max > 0){//まだ先読みする
	flag = search(color, &minmax);//置ける場所を探す

	if (flag == 0){//置ける場所がある

	    for (i = 1; i <= 8; i++){
		for (j = 1; j <= 8; j++){

		    if (((minmax.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//置ける場所を探す board[i][j] == 1

			after = operation(i, j, color, minmax);//とにかく置いてみる

			//次の相手のターンへ
			score = turn_minmax_next(next_color, S_color, after, t_max-1);

			if (color == S_color){
			    if (hightscore < score){//記録更新なら
				hightscore = score;
			    }
			}
			else{
			    if (hightscore > score){//記録更新なら
				hightscore = score;
			    }
			}
		    }
		}
	    }
	}
	else{//置けない

	    flag = search(next_color, &minmax);//相手が置けるか調べる

	    if (flag == 0){//相手は置ける
		//パス
		hightscore = turn_minmax_next(next_color, S_color, minmax, t_max-1);//次の相手のターンへ

	    }
	    else{//相手も置けない=ゲーム終了

		double flag = 0;
		if (S_color == Black){
		    if (minmax.bpnum > minmax.wpnum){//勝ち
			minmax.bpiece = ~(minmax.wpiece);//空白マスも自分のマスに
		    }
		    else{
			flag = 1;
			minmax.wpiece = ~(minmax.bpiece);//空白マスも相手のマスに
		    }
		}
		else{
		    if (minmax.bpnum < minmax.wpnum){//勝ち
			minmax.wpiece = ~(minmax.bpiece);//空白マスも自分のマスに
		    }
		    else{
			flag = 1;
			minmax.bpiece = ~(minmax.wpiece);//空白マスも相手のマスに
		    }
		}
		hightscore = evaluation(S_color, &minmax,(t_max > 100)?1:0) - (500 * flag);
	    }
	}
    }
    else{//先読みの上限が来た

	hightscore = evaluation(S_color, &minmax,0);
    }


    return 	hightscore;
}
/*	turn_minmax_next関数　終了　*////////////////////////////////////////////////////////////////////////////////




/*	turn_ab関数　開始　*//////////////////////////////////////////////////////////////////////////////
board turn_ab(int S_color, board ab, int t_max){

    int I = 0, J = 0, flag;
    int next_color = S_color ^ 1;
    double hightscore = -99999999, score;

    board after;

    flag = search(S_color, &ab);//置ける場所を探す

    if (flag == 0){//置ける場所がある

	int di[64] = { 0 }, dj[64] = { 0 }, index = 0;
	double dscore[64] = {};
		
	for (int i = 1; i <= 8; i++){
	    for (int j = 1; j <= 8; j++){
		if (((ab.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//置ける場所を探す board[i][j] == 1

		    di[index] = i;// Board_G_in[i][j];
		    dj[index] = j;
		    dscore[index] = turn_ab_next(next_color,  S_color, operation(i, j, S_color, ab), 4, hightscore);

		    index++;
		}
	    }
	}

	//バブルソート
	for (int i = 0; i < index; i++){
	    for (int j = 0; j < index - 1 - i; j++){
				
		//if (board_G[di[j]][dj[j]] < board_G[di[j + 1]][dj[j + 1]]){
		if (dscore[j] < dscore[j+1]){
		    std::swap(di[j + 1],di[j]);
		    std::swap(dj[j + 1],dj[j]);
		    std::swap(dscore[j + 1],dscore[j]);
		}
	    }
	}
		
	for (int i = 0; i < index; i++){
	    after = operation(di[i], dj[i], S_color, ab);//とにかく置いてみる
			
	    //次の相手のターンへ
	    score = turn_ab_next(next_color, S_color, after, t_max-1, hightscore);
			
	    if (hightscore < score){//記録更新なら
		I = di[i];
		J = dj[i];
		hightscore = score;
	    }
	}

    }
    else {//はじめから置けないなら考える必要はない

	ab.pass = S_color;
	ab.p_cnt = 0;//パス後のwaitを一回にするため

	return ab;
    }

    ab = operation(I, J, S_color, ab);//確定
	
    ab.pass = Non;
    ab.p_cnt += 1;

    return ab;
}
/*	turn_ab関数　終了　*////////////////////////////////////////////////////////////////////////////////




/*	turn_ab_next関数　開始　*//////////////////////////////////////////////////////////////////////////////
double turn_ab_next(int color, int S_color, board ab,int t_max, double p_score){

    int flag;
    int next_color = color ^ 1;
    double hightscore = -99999999, score = 0;

    if (color != S_color)hightscore = 99999999;

    board after;

    if (t_max > 0){//まだ先読みする
	flag = search(color, &ab);//置ける場所を探す

	if (flag == 0){//置ける場所がある

	    int di[64] = { 0 }, dj[64] = { 0 }, index = 0;
			
	    for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
		    if (((ab.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//置ける場所を探す board[i][j] == 1

			di[index] = i;// Board_G_in[i][j];
			dj[index] = j;
			index++;
		    }
		}
	    }

	    //バブルソート
	    if(S_color == White){
		for (int i = 0; i < index; i++){
		    for (int j = 0; j < index - 1 - i; j++){
			if (board_G_W[di[j]][dj[j]] < board_G_W[di[j + 1]][dj[j + 1]]){
			    std::swap(di[j + 1],di[j]);
			    std::swap(dj[j + 1],dj[j]);
			}
		    }
		}
	    }else{
		for (int i = 0; i < index; i++){
		    for (int j = 0; j < index - 1 - i; j++){
			if (board_G_B[di[j]][dj[j]] < board_G_B[di[j + 1]][dj[j + 1]]){
			    std::swap(di[j + 1],di[j]);
			    std::swap(dj[j + 1],dj[j]);
			}
		    }
		}
	    }

	    for (int i = 0; i < index; i++){
		after = operation(di[i], dj[i], color, ab);//とにかく置いてみる

		//次の相手のターンへ
		score = turn_ab_next(next_color, S_color, after, t_max-1, hightscore);

		if (color == S_color){
		    if (hightscore < score){//記録更新なら
			hightscore = score;
		    }

		    if (p_score <= hightscore)return hightscore;//これ以上探索の意味なし

		}else{
		    if (hightscore > score){//記録更新なら
			hightscore = score;
		    }

		    if (p_score >= hightscore)return hightscore;//これ以上探索の意味なし
		}
	    }
	}
	else{//置けない

	    flag = search(next_color, &ab);//相手が置けるか調べる

	    if (flag == 0){//相手は置ける
		//パス
		if ((p_score != 99999999 && p_score != -99999999) && (hightscore == 99999999 || hightscore == -99999999))hightscore = p_score;
		hightscore = turn_ab_next(next_color, S_color, ab,t_max, hightscore);//次の相手のターンへ
	    }
	    else{//相手も置けない=ゲーム終了

		int flag = 0;
		if (S_color == Black){
		    if (ab.bpnum > ab.wpnum){//勝ち
			ab.bpiece = ~(ab.wpiece);//空白マスも自分のマスに
		    }
		    else{
			flag = 1;
			ab.wpiece = ~(ab.bpiece);//空白マスも相手のマスに
		    }
		}
		else{
		    if (ab.bpnum < ab.wpnum){//勝ち
			ab.wpiece = ~(ab.bpiece);//空白マスも自分のマスに
		    }
		    else{
			flag = 1;
			ab.bpiece = ~(ab.wpiece);//空白マスも相手のマスに
		    }
		}
		hightscore = evaluation(S_color, &ab,(t_max > 100)?1:0) - (500 * flag);
	    }
	}
    }
    else{//先読みの上限が来た
	hightscore = evaluation(S_color, &ab, 0);
    }

    return 	hightscore;
}
/*	turn_ab_next関数　終了　*////////////////////////////////////////////////////////////////////////////////



/*	turn_monte関数　開始　*//////////////////////////////////////////////////////////////////////////////

board turn_monte(int S_color, board mon, int t_max){

    int I = 0, J = 0, flag,r_size = 0;
    int next_color = S_color ^ 1;
    double hightscore = -99999999, score;

    board after;

    flag = search(S_color, &mon);//置ける場所を探す
    std::vector<std::pair<int,int>> red(64);
    
    if (flag == 0){//置ける場所がある
	
	for(int i = 0; i < 64; i++){
	    if ((mon.rpiece & 1) == 1)red[r_size++] = std::make_pair( 8-(i>>3) ,8-(i&0x07));
	    mon.rpiece >>= 1;
	}

	
	int cnt = t_max/r_size;
	for(int c = 0; c < r_size; c++){
	    int i = red[c].first, j = red[c].second;

	    score = 0;
	    after = operation(i, j, S_color, mon);
	    for (int k = 0; k < cnt; k++){
		score += turn_mon_next(next_color, S_color, after);
	    }

	    if (hightscore < score/cnt){//記録更新なら
		I = i;
		J = j;
		hightscore = score/cnt;
	    }
	}
    }
    else {//はじめから置けないなら考える必要はない

	mon.pass = S_color;
	mon.p_cnt = 0;//パス後のwaitを一回にするため

	return mon;
    }

    mon = operation(I, J, S_color, mon);//確定

    mon.pass = Non;
    mon.p_cnt += 1;

    return mon;
}
/////////////////////////////////////////////////////////////////////
board turn_monte2(int S_color, board mon, int t_max){

    int I = 0, J = 0, flag,r_size = 0;
    int next_color = S_color ^ 1;
    double hightscore = -99999999;

    flag = search(S_color, &mon);//置ける場所を探す
    std::vector<std::pair<int,int>> red(64);
    std::vector<board> after_m(64);
    board after;
    
    if (flag == 0){//置ける場所がある
	
	for(int i = 0; i < 64; i++){
	    if ((mon.rpiece & 1) == 1){
		red[r_size] = std::make_pair( 8-(i>>3) ,8-(i&0x07));
		after_m[r_size++] = operation(8-(i>>3) ,8-(i&0x07), S_color, mon);
	    }
	    mon.rpiece >>= 1;
	}

	std::vector<std::pair<double,int>> sc(r_size);
	std::vector<int> num(r_size);
	
	for(int c = 0; c < r_size; c++){
	    num[c] = c;
	    after = after_m[c];
	    for (int k = 0; k < 1000; k++){
		sc[c].first += turn_mon_next(next_color, S_color, after);
		sc[c].second++;
	    }
	}

	int cnt = 0;
	while(t_max > cnt && num.size() > 0){
	    int n = num[cnt%num.size()];
	    
	    if(sc[n].first / sc[n].second > 0.2 + ((t_max/2 < cnt)? 0.6 : 0.0)){

		after = after_m[n];
		sc[n].first += turn_mon_next(next_color, S_color, after);
		sc[n].second++;

		cnt++;
	
	    }else{
		num.erase(num.begin()+(cnt%num.size()));	
	    }
	}

	if(num.size() <= 0){
	    while(t_max > cnt ){
		int n = num[cnt%sc.size()];
	    
		after = after_m[n];
		sc[n].first += turn_mon_next(next_color, S_color, after);
		sc[n].second++;

		cnt++;
	    }
	}
	
	for(int c = 0; c < r_size; c++){
	    
	    if (hightscore < sc[c].first / sc[c].second + (double)sc[c].second / t_max / 1000){//記録更新なら
		I = red[c].first;
		J = red[c].second;
		hightscore = sc[c].first / sc[c].second + (double)sc[c].second / t_max / 1000;
	    }
	}
	
    }
    else {//はじめから置けないなら考える必要はない

	mon.pass = S_color;
	mon.p_cnt = 0;//パス後のwaitを一回にするため

	return mon;
    }

    mon = operation(I, J, S_color, mon);//確定

    mon.pass = Non;
    mon.p_cnt += 1;

    return mon;
}
/*	turn_monte関数　終了　*////////////////////////////////////////////////////////////////////////////////




/*	turn_mon_next関数　開始　*//////////////////////////////////////////////////////////////////////////////
double turn_mon_next(int color, int  S_color, board mon){

    int flag, rand,r_size = 0;
    int i, j;
    double score = 0;
    int next_color = color ^ 1;

    rand = rand64(mt);//ランダム

    flag = search(color, &mon);//置ける場所を探す

    if (flag == 0){//置ける場所がある
	std::vector<std::pair<int,int>> red(64);

	for(int i = 0; i < 64; i++){
	    if (mon.rpiece & 1)red[r_size++] = std::make_pair( 8-(i>>3) ,8-(i&0x07));
	    mon.rpiece >>= 1;
	}

	int r_num = rand%r_size;
	
	score = turn_mon_next(next_color, S_color, operation(red[r_num].first, red[r_num].second, color, mon));
    }
    else {//置けないない
	flag = search(next_color, &mon);//相手が置けるか調べる

	if (flag == 0){//相手は置ける
	    score = turn_mon_next(next_color, S_color, mon);
	}
	else{
	    if (S_color == Black){
		if (mon.bpnum > mon.wpnum){//勝ち
		    score = 1;
		}
		else{
		    score = 0;
		}
	    }
	    else{
		if (mon.bpnum < mon.wpnum){//勝ち
		    score = 1;
		}
		else{
		    score = 0;
		}
	    }
	}
    }

    return score;
}
/*	turn_mon_next関数　終了　*////////////////////////////////////////////////////////////////////////////////




/*	evaluation関数　開始　*//////////////////////////////////////////////////////////////////////////////
double evaluation(int S_color, board * eva, int fin){
    double score = 0;

    if (fin == 0){//重みで評価

	//search(S_color ^ 1, eva);//相手が置けるか調べる

	ULL my_piece, you_piece;
	if (S_color == Black){
	    my_piece = eva->bpiece;
	    you_piece = eva->wpiece;
	}
	else{
	    my_piece = eva->wpiece;
	    you_piece = eva->bpiece;
	}

	//if (S_color != Black){
	score += Established_stone(my_piece) * 10;
	score -= Established_stone(you_piece) * 10;
	//}
	for (int i = 8; i >= 1; i--){
	    for (int j = 8; j >= 1; j--){
		if ((my_piece & 1) == 1){//自分の置いた場所を探す board[i][j] == 1

		    score += (S_color == Black)?board_G_B[i][j] : board_G_W[i][j];

		}
		else if ((you_piece & 1) == 1){//相手の置いた場所を探す board[i][j] == 1{
		    score -= (S_color == Black)?board_G_B[i][j] : board_G_W[i][j];
		}

		my_piece >>= 1;
		you_piece >>= 1;
	    }
	}
	/*	
	for (int i = 1; i <= 8; i++){
	    for (int j = 1; j <= 8; j++){
		ULL sift = (64 - j - ((i - 1) * 8));
		if (((my_piece >> sift) & 1) == 1){//自分の置いた場所を探す board[i][j] == 1

		    score += (S_color == Black)?board_G_B[i][j] : board_G_W[i][j];

		}
		else if (((you_piece >> sift) & 1) == 1){//相手の置いた場所を探す board[i][j] == 1{
		    score -= (S_color == Black)?board_G_B[i][j] : board_G_W[i][j];
		}
	    }
	    }*/
    }
    else{//コマ数で評価
	/*
	  if (S_color == Black){
	  if (eva->bpnum > eva->wpnum)return eva->bpnum + (64 - eva->bpnum - eva->wpnum);//勝ちなら空白のマスも自分の色としてカウント
	  else return 0;//負けたら意味は無い
	  }
	  else{
	  if (eva->bpnum > eva->wpnum)return 0;//負けたら意味は無い
	  else return eva->wpnum + (64 - eva->bpnum - eva->wpnum);//勝ちなら空白のマスも自分の色としてカウント
	  }*/

	int my, you;
	if (S_color == Black){
	    if (eva->bpnum > eva->wpnum) {
		my = 64 - eva->wpnum;//勝ちなら空白のマスも自分の色としてカウント
		you = eva->wpnum;
	    }
	    else{
		my = eva->bpnum;
		you = 64 - eva->bpnum;
	    }
	    //my += Established_stone(eva->bpiece);
	    //you += Established_stone(eva->wpiece);
	}
	else{
	    if (eva->bpnum > eva->wpnum){
		my = eva->wpnum;
		you = 64 -eva->wpnum;
	    }
	    else {
		my = 64 - eva->bpnum;
		you = eva->bpnum;
	    }
	    //you += Established_stone(eva->bpiece);
	    //my += Established_stone(eva->wpiece);
	}
	score = my - you;
    }

    return score;
    //スコアXコマ数
}
/*	evaluation関数　終了　*//////////////////////////////////////////////////////////////////////////////

/*	Established_stone関数　開始　*//////////////////////////////////////////////////////////////////////////////
int Established_stone(ULL piece){
    int num = 0;
    ULL sift;// = (64 - j - ((i - 1) * 8));
    
    //左上
    for(int i = 1; i<= 8;i++){
	sift = (64 - 1 - ((i - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }
    for(int j = 1; j<= 8;j++){
	sift = (64 - j - ((1 - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }
    
    //右上
    for(int i = 1; i <= 8;i++){
	sift = (64 - 8 - ((i - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }
    for(int j = 8; j >= 1;j--){
	sift = (64 - j - ((1 - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }
    
    //左下
    for(int i = 8; i >= 1;i--){
	sift = (64 - 1 - ((i - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }
    for(int j = 1; j<= 8;j++){
	sift = (64 - j - ((8 - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }
    
    //右下
    for(int i = 8; i >= 1;i--){
	sift = (64 - 8 - ((i - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }
    for(int j = 8; j >= 1;j--){
	sift = (64 - j - ((8 - 1) * 8));
	if(((piece >> sift) & 1) == 1){
	    num++;
	}else{
	    break;
	}
    }

    return num;
}
/*	Established_stone関数　終了　*//////////////////////////////////////////////////////////////////////////////



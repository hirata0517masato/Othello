#include "game.hpp"
#include "ai.hpp"
#include <thread>
#include <vector>
#include <map>
#include<algorithm>
#include<queue>
#include <random>

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
int board_G[10][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 30, -12, 0, -1, -1, 0, -12, 30, 0 },
			{ 0, -12, -15, -3, -3, -3, -3, -15, -12, 0 },
			{ 0, 0, -3, 0, -1, -1, 0, -3, 0, 0 },
			{ 0, -1, -3, -1, -1, -1, -1, -3, -1, 0 },
			{ 0, -1, -3, -1, -1, -1, -1, -3, -1, 0 },
			{ 0, 0, -3, 0, -1, -1, 0, -3, 0, 0 },
			{ 0, -12, -15, -3, -3, -3, -3, -15, -12, 0 },
			{ 0, 30, -12, 0, -1, -1, 0, -12, 30, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
std::uniform_int_distribution<> rand64(0, 64);        // [0, 99] �͈͂̈�l����
   
/*	turn_dfs�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
board turn_dfs(int color,board dfs,int t_max){

    int I = 0,J = 0,flag;
    int next_color = color^1;
    double hightscore = -999999;

    int i,j;

    flag = search(color,&dfs);//�u����ꏊ��T��

    if(flag == 0){//�u����ꏊ������
	std::thread th1,th2;
	double t1_score= -9991,t2_score= -9991;
	int t1_flag = 0,t2_flag = 0;

		
	std::queue<std::pair<int,int>> q;
	std::pair<int,int> place1,place2;
		
	for(i=1;i<=8;i++){
	    for(j=1;j<=8;j++){
		if(((dfs.rpiece>>(64-j -((i-1)*8))) & 1)==1){//�u����ꏊ��T�� board[i][j] == 1
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
				
		    board after = operation(place1.first,place1.second,color,dfs);//�Ƃɂ����u���Ă݂�
		    //���̑���̃^�[����
		    th1 = std::thread(turn_dfs_next_thread,next_color,color,after,t_max-1,std::ref(t1_score));	
		}	
	    }
	    if(!q.empty()){
		if(t2_flag == 0){
		    t2_flag = 1;

		    place2 = q.front();
		    q.pop();

		    board after = operation(place2.first,place2.second,color,dfs);//�Ƃɂ����u���Ă݂�
		    //���̑���̃^�[����
		    th2 = std::thread(turn_dfs_next_thread,next_color,color,after,t_max-1,std::ref(t2_score));
				
		}
	    }

	    if(t1_flag == 1)th1.join();//Wait for end of th
	    if(t2_flag == 1)th2.join();//Wait for end of th
			
	    if(t1_flag == 1 && t1_score != -9991){
		if(hightscore < t1_score){//�L�^�X�V�Ȃ�
		    I = place1.first;
		    J = place1.second;
		    hightscore = t1_score;
		}
		t1_score = -9991;
		t1_flag = 0;
	    }

	    if(t2_flag == 1 && t2_score != -9991){
		if(hightscore < t2_score){//�L�^�X�V�Ȃ�
		    I = place2.first;
		    J = place2.second;
		    hightscore = t2_score;
		}
		t2_score = -9991;
		t2_flag = 0;
	    }
	}
    }else {//�͂��߂���u���Ȃ��Ȃ�l����K�v�͂Ȃ�

	dfs.pass = color;
	dfs.p_cnt = 0;//�p�X���wait�����ɂ��邽��
		
	return dfs;		
    }

    dfs = operation(I,J,color,dfs);//�m��
					
    dfs.pass = Non;
    dfs.p_cnt += 1;
	
    return dfs;
}
/*	turn_dfs�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////

/*	turn_dfs_next_thread�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
void turn_dfs_next_thread(int color, int S_color, board dfs, int t_max,double &ret_score){
	
    int flag,i,j,ret_cnt = -1,ii,jj;
    int next_color = color^1;
    double score = 0;
    board after;
	
    if(t_max > 0){//�܂���ǂ݂���
	
	flag = search(color,&dfs);//�u����ꏊ��T��
		
	if(flag == 0){//�u����ꏊ������
			
	    for(i=1;i<=8;i++){
		for(j=1;j<=8;j++){
				
		    if(((dfs.rpiece>>(64-j -((i-1)*8))) & 1)==1){//�u����ꏊ��T�� board[i][j] == 1
					
			after = operation(i,j,color,dfs);//�Ƃɂ����u���Ă݂�
					
			score += turn_dfs_next(next_color,S_color,after,t_max-1);//���̑���̃^�[����;
						
			ret_cnt++;//���^�[���̃J�E���g
		
			if(ret_cnt){//���^�[��2��ڈȍ~�Ȃ�
							
			    //score >>= 1;//���ς����߂�
			    score /= 2;//���ς����߂�
			}
		    }
		}
	    }
		
	}else{//�u���Ȃ�
		
	    flag = search(next_color,&dfs);//���肪�u���邩���ׂ�
		
	    if(flag == 0){//����͒u����
		//�p�X
		score = turn_dfs_next(next_color,S_color,dfs,t_max-1);//���̑���̃^�[����
				
	    }else{//������u���Ȃ�=�Q�[���I��
				
		if(S_color == Black){//�󔒃}�X�������̃}�X��or����̃}�X��
		    if(dfs.bpnum > dfs.wpnum)dfs.bpiece |= ~(dfs.wpiece);
		    else dfs.wpiece |= ~(dfs.bpiece);
		}else{
		    if(dfs.bpnum < dfs.wpnum)dfs.wpiece |= ~(dfs.bpiece);
		    else dfs.bpiece |= ~(dfs.wpiece);
		}
		score = evaluation(S_color,&dfs,(t_max > 100)?1:0);			
	    }
	}
    }else{//��ǂ݂̏��������

	score = evaluation(S_color,&dfs,0);
    }
	
    ret_score = score;
}
/*	turn_dfs_next_thread�֐��@�I���@*//////////////////////////////////////////////////////////////////////////////



/*	turn_dfs_next�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
double turn_dfs_next(int color, int S_color, board dfs,int t_max){
	
    int flag,i,j,ret_cnt = -1,ii,jj;
    int next_color = color^1;
    double score = 0;
    board after;

    if(t_max > 0){//�܂���ǂ݂���
	
	flag = search(color,&dfs);//�u����ꏊ��T��
		
	if(flag == 0){//�u����ꏊ������
			
	    for(i=1;i<=8;i++){
		for(j=1;j<=8;j++){
				
		    if(((dfs.rpiece>>(64-j -((i-1)*8))) & 1)==1){//�u����ꏊ��T�� board[i][j] == 1
					
			after = operation(i,j,color,dfs);//�Ƃɂ����u���Ă݂�
						
			score += turn_dfs_next(next_color,S_color,after,t_max-1);//���̑���̃^�[����
						
			ret_cnt++;//���^�[���̃J�E���g
		
			if(ret_cnt){//���^�[��2��ڈȍ~�Ȃ�
							
			    //score >>= 1;//���ς����߂�
			    score /= 2;//���ς����߂�
			}
		    }
		}
	    }
		
	}else{//�u���Ȃ�
		
	    flag = search(next_color,&dfs);//���肪�u���邩���ׂ�
		
	    if(flag == 0){//����͒u����
		//�p�X
		score = turn_dfs_next(next_color,S_color,dfs,t_max-1);//���̑���̃^�[����
				
	    }else{//������u���Ȃ�=�Q�[���I��
			
		if(S_color == Black){//�󔒃}�X�������̃}�X��or����̃}�X��
		    if(dfs.bpnum > dfs.wpnum)dfs.bpiece |= ~(dfs.wpiece);
		    else dfs.wpiece |= ~(dfs.bpiece);
		}else{
		    if(dfs.bpnum < dfs.wpnum)dfs.wpiece |= ~(dfs.bpiece);
		    else dfs.bpiece |= ~(dfs.wpiece);
		}
		score = evaluation(S_color,&dfs,(t_max > 100)?1:0);		
	    }
	}
    }else{//��ǂ݂̏��������

	score = evaluation(S_color,&dfs,0);
    }
	
    return score;
}
/*	turn_dfs_next�֐��@�I���@*//////////////////////////////////////////////////////////////////////////////




/*	turn_rand�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
board turn_rand(int color, board ran){

    int I = 0, J = 0, flag, rand, rand_cnt = 0;
    int i, j;
    
    rand = rand64(mt);//0-64�̒l�Ń����_��

    flag = search(color, &ran);//�u����ꏊ��T��

    if (flag == 0){//�u����ꏊ������

	while (rand_cnt <= rand){
	    for (i = 1; i <= 8; i++){
		for (j = 1; j <= 8; j++){
		    if (((ran.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//�u����ꏊ��T�� board[i][j] == 1

			if (rand_cnt == rand){//�����_���l����������
			    I = i;//�u�����W�̋L��
			    J = j;
			}
			rand_cnt++;
		    }
		}
	    }
	}

    }
    else {//�͂��߂���u���Ȃ��Ȃ�l����K�v�͂Ȃ�

	ran.pass = color;
	ran.p_cnt = 0;//�p�X���wait�����ɂ��邽��

	return ran;
    }

    ran = operation(I, J, color, ran);//�m��
	
    ran.pass = Non;
    ran.p_cnt += 1;

    return ran;
}
/*	turn_rand�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////



/*	turn_minmax�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
board turn_minmax(int S_color, board minmax, int t_max){

    int I = 0, J = 0, flag;
    int next_color = S_color ^ 1;
    double hightscore = -99999999, score = 0;
    int i, j;
    board after;

    flag = search(S_color, &minmax);//�u����ꏊ��T��

    if (flag == 0){//�u����ꏊ������

	for (i = 1; i <= 8; i++){
	    for (j = 1; j <= 8; j++){

		if (((minmax.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//�u����ꏊ��T�� board[j][i] == 1

		    after = operation(i, j, S_color, minmax);//�Ƃɂ����u���Ă݂�

		    //���̑���̃^�[����
		    score = turn_minmax_next(next_color, S_color, after, t_max-1);

		    if (hightscore < score){//�L�^�X�V�Ȃ�
			I = i;
			J = j;
			hightscore = score;
		    }
		}
	    }
	}
    }
    else {//�͂��߂���u���Ȃ��Ȃ�l����K�v�͂Ȃ�

	minmax.pass = S_color;
	minmax.p_cnt = 0;//�p�X���wait�����ɂ��邽��

	return minmax;
    }

    minmax = operation(I, J, S_color, minmax);//�m��
	
    minmax.pass = Non;
    minmax.p_cnt += 1;

    return minmax;
}
/*	turn_minmax�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////




/*	turn_minmax_next�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
double turn_minmax_next(int color, int S_color, board minmax, int t_max){

    int flag;
    int next_color = color ^ 1;
    double hightscore = -99999999, score = 0;

    if (color != S_color)hightscore = 99999999;

    int i, j;
    board after;

    if (t_max > 0){//�܂���ǂ݂���
	flag = search(color, &minmax);//�u����ꏊ��T��

	if (flag == 0){//�u����ꏊ������

	    for (i = 1; i <= 8; i++){
		for (j = 1; j <= 8; j++){

		    if (((minmax.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//�u����ꏊ��T�� board[i][j] == 1

			after = operation(i, j, color, minmax);//�Ƃɂ����u���Ă݂�

			//���̑���̃^�[����
			score = turn_minmax_next(next_color, S_color, after, t_max-1);

			if (color == S_color){
			    if (hightscore < score){//�L�^�X�V�Ȃ�
				hightscore = score;
			    }
			}
			else{
			    if (hightscore > score){//�L�^�X�V�Ȃ�
				hightscore = score;
			    }
			}
		    }
		}
	    }
	}
	else{//�u���Ȃ�

	    flag = search(next_color, &minmax);//���肪�u���邩���ׂ�

	    if (flag == 0){//����͒u����
		//�p�X
		hightscore = turn_minmax_next(next_color, S_color, minmax, t_max-1);//���̑���̃^�[����

	    }
	    else{//������u���Ȃ�=�Q�[���I��

		double flag = 0;
		if (S_color == Black){
		    if (minmax.bpnum > minmax.wpnum){//����
			minmax.bpiece = ~(minmax.wpiece);//�󔒃}�X�������̃}�X��
		    }
		    else{
			flag = 1;
			minmax.wpiece = ~(minmax.bpiece);//�󔒃}�X������̃}�X��
		    }
		}
		else{
		    if (minmax.bpnum < minmax.wpnum){//����
			minmax.wpiece = ~(minmax.bpiece);//�󔒃}�X�������̃}�X��
		    }
		    else{
			flag = 1;
			minmax.bpiece = ~(minmax.wpiece);//�󔒃}�X������̃}�X��
		    }
		}
		hightscore = evaluation(S_color, &minmax,(t_max > 100)?1:0) - (500 * flag);
	    }
	}
    }
    else{//��ǂ݂̏��������

	hightscore = evaluation(S_color, &minmax,0);
    }


    return 	hightscore;
}
/*	turn_minmax_next�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////




/*	turn_ab�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
board turn_ab(int S_color, board ab, int t_max){

    int I = 0, J = 0, flag;
    int next_color = S_color ^ 1;
    double hightscore = -99999999, score;

    board after;

    flag = search(S_color, &ab);//�u����ꏊ��T��

    if (flag == 0){//�u����ꏊ������

	int di[64] = { 0 }, dj[64] = { 0 }, index = 0;
	double dscore[64] = {};
		
	for (int i = 1; i <= 8; i++){
	    for (int j = 1; j <= 8; j++){
		if (((ab.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//�u����ꏊ��T�� board[i][j] == 1

		    di[index] = i;// Board_G_in[i][j];
		    dj[index] = j;
		    dscore[index] = turn_ab_next(next_color,  S_color, operation(i, j, S_color, ab), 4, hightscore);

		    index++;
		}
	    }
	}

	//�o�u���\�[�g
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
	    after = operation(di[i], dj[i], S_color, ab);//�Ƃɂ����u���Ă݂�
			
	    //���̑���̃^�[����
	    score = turn_ab_next(next_color, S_color, after, t_max-1, hightscore);
			
	    if (hightscore < score){//�L�^�X�V�Ȃ�
		I = di[i];
		J = dj[i];
		hightscore = score;
	    }
	}

    }
    else {//�͂��߂���u���Ȃ��Ȃ�l����K�v�͂Ȃ�

	ab.pass = S_color;
	ab.p_cnt = 0;//�p�X���wait�����ɂ��邽��

	return ab;
    }

    ab = operation(I, J, S_color, ab);//�m��
	
    ab.pass = Non;
    ab.p_cnt += 1;

    return ab;
}
/*	turn_ab�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////




/*	turn_ab_next�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
double turn_ab_next(int color, int S_color, board ab,int t_max, double p_score){

    int flag;
    int next_color = color ^ 1;
    double hightscore = -99999999, score = 0;

    if (color != S_color)hightscore = 99999999;

    board after;

    if (t_max > 0){//�܂���ǂ݂���
	flag = search(color, &ab);//�u����ꏊ��T��

	if (flag == 0){//�u����ꏊ������

	    int di[64] = { 0 }, dj[64] = { 0 }, index = 0;
			
	    for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
		    if (((ab.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//�u����ꏊ��T�� board[i][j] == 1

			di[index] = i;// Board_G_in[i][j];
			dj[index] = j;
			index++;
		    }
		}
	    }

	    //�o�u���\�[�g
	    for (int i = 0; i < index; i++){
		for (int j = 0; j < index - 1 - i; j++){
		    if (board_G[di[j]][dj[j]] < board_G[di[j + 1]][dj[j + 1]]){
			std::swap(di[j + 1],di[j]);
			std::swap(dj[j + 1],dj[j]);
		    }
		}
	    }

	    for (int i = 0; i < index; i++){
		after = operation(di[i], dj[i], color, ab);//�Ƃɂ����u���Ă݂�

		//���̑���̃^�[����
		score = turn_ab_next(next_color, S_color, after, t_max-1, hightscore);

		if (color == S_color){
		    if (hightscore < score){//�L�^�X�V�Ȃ�
			hightscore = score;
		    }

		    if (p_score <= hightscore)return hightscore;//����ȏ�T���̈Ӗ��Ȃ�

		}else{
		    if (hightscore > score){//�L�^�X�V�Ȃ�
			hightscore = score;
		    }

		    if (p_score >= hightscore)return hightscore;//����ȏ�T���̈Ӗ��Ȃ�
		}
	    }
	}
	else{//�u���Ȃ�

	    flag = search(next_color, &ab);//���肪�u���邩���ׂ�

	    if (flag == 0){//����͒u����
		//�p�X
		if ((p_score != 99999999 && p_score != -99999999) && (hightscore == 99999999 || hightscore == -99999999))hightscore = p_score;
		hightscore = turn_ab_next(next_color, S_color, ab,t_max, hightscore);//���̑���̃^�[����
	    }
	    else{//������u���Ȃ�=�Q�[���I��

		int flag = 0;
		if (S_color == Black){
		    if (ab.bpnum > ab.wpnum){//����
			ab.bpiece = ~(ab.wpiece);//�󔒃}�X�������̃}�X��
		    }
		    else{
			flag = 1;
			ab.wpiece = ~(ab.bpiece);//�󔒃}�X������̃}�X��
		    }
		}
		else{
		    if (ab.bpnum < ab.wpnum){//����
			ab.wpiece = ~(ab.bpiece);//�󔒃}�X�������̃}�X��
		    }
		    else{
			flag = 1;
			ab.bpiece = ~(ab.wpiece);//�󔒃}�X������̃}�X��
		    }
		}
		hightscore = evaluation(S_color, &ab,(t_max > 100)?1:0) - (500 * flag);
	    }
	}
    }
    else{//��ǂ݂̏��������
	hightscore = evaluation(S_color, &ab, 0);
    }

    return 	hightscore;
}
/*	turn_ab_next�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////



/*	turn_monte�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
board turn_monte(int S_color, board mon, int t_max){

    int I = 0, J = 0, flag;
    int next_color = S_color ^ 1;
    double hightscore = -99999999, score;

    board after;

    flag = search(S_color, &mon);//�u����ꏊ��T��

    if (flag == 0){//�u����ꏊ������

	for (int i = 1; i <= 8; i++){
	    for (int j = 1; j <= 8; j++){
		if (((mon.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//�u����ꏊ��T�� board[i][j] == 1

		    score = 0;
		    after = operation(i, j, S_color, mon);
		    for (int k = 0; k < t_max; k++){
			score += turn_mon_next(next_color, S_color, after);
		    }

		    if (hightscore < score/t_max){//�L�^�X�V�Ȃ�
			I = i;
			J = j;
			hightscore = score/t_max;
		    }
					
		}
	    }
	}
    }
    else {//�͂��߂���u���Ȃ��Ȃ�l����K�v�͂Ȃ�

	mon.pass = S_color;
	mon.p_cnt = 0;//�p�X���wait�����ɂ��邽��

	return mon;
    }

    mon = operation(I, J, S_color, mon);//�m��

    mon.pass = Non;
    mon.p_cnt += 1;

    return mon;
}
/*	turn_monte�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////




/*	turn_mon_next�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
double turn_mon_next(int color, int  S_color, board mon){

    int flag, rand, rand_cnt = 0;
    int i, j;
    double score = 0;
    int next_color = color ^ 1;

    rand = rand64(mt);//0-64�̒l�Ń����_��

    flag = search(color, &mon);//�u����ꏊ��T��

    if (flag == 0){//�u����ꏊ������

	while (rand_cnt <= rand){
	    for (i = 1; i <= 8; i++){
		for (j = 1; j <= 8; j++){
		    if (((mon.rpiece >> (64 - j - ((i - 1) * 8))) & 1) == 1){//�u����ꏊ��T�� board[i][j] == 1

			if (rand_cnt == rand){//�����_���l����������
			    score = turn_mon_next(next_color, S_color, operation(i, j, color, mon));
			}
			rand_cnt++;
		    }
		}
	    }
	}

    }
    else {//�u���Ȃ��Ȃ�
	flag = search(next_color, &mon);//���肪�u���邩���ׂ�

	if (flag == 0){//����͒u����
	    score = turn_mon_next(next_color, S_color, mon);
	}
	else{
	    if (S_color == Black){
		if (mon.bpnum > mon.wpnum){//����
		    mon.bpiece = ~(mon.wpiece);//�󔒃}�X�������̃}�X��
		}
		else{
		    mon.wpiece = ~(mon.bpiece);//�󔒃}�X������̃}�X��
		}
	    }
	    else{
		if (mon.bpnum < mon.wpnum){//����
		    mon.wpiece = ~(mon.bpiece);//�󔒃}�X�������̃}�X��
		}
		else{
		    mon.bpiece = ~(mon.wpiece);//�󔒃}�X������̃}�X��
		}
	    }
	    score = evaluation(S_color, &mon, 1);
	}
    }

    return score;
}
/*	turn_mon_next�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////




/*	evaluation�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
double evaluation(int S_color, board * eva, int fin){
    double score = 0;

    if (fin == 0){//�d�݂ŕ]��

	//search(S_color ^ 1, eva);//���肪�u���邩���ׂ�

	ULL my_piece, you_piece;
	if (S_color == Black){
	    my_piece = eva->bpiece;
	    you_piece = eva->wpiece;
	}
	else{
	    my_piece = eva->wpiece;
	    you_piece = eva->bpiece;
	}

	for (int i = 1; i <= 8; i++){
	    for (int j = 1; j <= 8; j++){
		ULL sift = (64 - j - ((i - 1) * 8));
		if (((my_piece >> sift) & 1) == 1){//�����̒u�����ꏊ��T�� board[i][j] == 1

		    score += board_G[i][j];

		}
		else if (((you_piece >> sift) & 1) == 1){//����̒u�����ꏊ��T�� board[i][j] == 1{
		    score -= board_G[i][j];
		}
	    }
	}
    }
    else{//�R�}���ŕ]��
	/*
	  if (S_color == Black){
	  if (eva->bpnum > eva->wpnum)return eva->bpnum + (64 - eva->bpnum - eva->wpnum);//�����Ȃ�󔒂̃}�X�������̐F�Ƃ��ăJ�E���g
	  else return 0;//��������Ӗ��͖���
	  }
	  else{
	  if (eva->bpnum > eva->wpnum)return 0;//��������Ӗ��͖���
	  else return eva->wpnum + (64 - eva->bpnum - eva->wpnum);//�����Ȃ�󔒂̃}�X�������̐F�Ƃ��ăJ�E���g
	  }*/

	int my, you;
	if (S_color == Black){
	    if (eva->bpnum > eva->wpnum) {
		my = 64 - eva->wpnum;//�����Ȃ�󔒂̃}�X�������̐F�Ƃ��ăJ�E���g
		you = eva->wpnum;
	    }
	    else{
		my = eva->bpnum;
		you = 64 - eva->bpnum;
	    }
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
	}
	score = my - you;
    }

    return score;
    //�X�R�AX�R�}��
}
/*	evaluation�֐��@�I���@*//////////////////////////////////////////////////////////////////////////////





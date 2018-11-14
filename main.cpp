#include<iostream>
#include <cmath>
#include "game.hpp"
#include "ai.hpp"

#define Wait 500		//�҂����ԁi1ms)

//�֐��̃v���g�^�C�v�錾
void init(void);
void pieceprint(int, board *);
void total(void);
board turn(int);

//�O���[�o���ϐ��錾
board original;
int B_player = 0, W_player = 0;//�u���b�N�A�z���C�g�̃v���C���@

int END_Flag = 0;//0 = �p���@1 = �I��


/*	�֐��@�J�n�@*///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*	total�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
void total(){

    int a = 0;

    original.rpiece = 0;

    //�\��
    pieceprint(999, &original);
}
/*	total�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////


/*	pieceprint�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
void pieceprint(int color, board * print){
    int i, j,pi = 99,pj = 99;
    ULL bit_check;
    ULL b, w, r, y;

    bit_check = (ULL)1 << 63;

    std::cout << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << " ABCDEFGH" << std::endl;
    
    for (i = 1; i <= 8; i++){
	std::cout << i;
	for (j = 1; j <= 8; j++){

	    w = print->wpiece & bit_check;
	    b = print->bpiece & bit_check;
	    r = print->rpiece & bit_check;
	    y = print->ypiece & bit_check;

	    if (b > 0 && w == 0)std::cout << "B";
	    else if (b == 0 && w > 0)std::cout << "W";
	    else if (r > 0)std::cout << "O";
	    else std::cout << "_";
	    
	    if(y > 0){
		pi = i;
		pj = j;
	    }
	    bit_check >>= 1;

	}
	std::cout << std::endl;
    }

    if(pi != 99 && pj != 99){
	std::cout << "put : " << (char)('a'+pj-1) << "  " << pi << std::endl;
    }
    std::cout << std::endl;
    std::cout << "W : " <<  print->wpnum << " B : " <<  print->bpnum << std::endl;

    switch (color){
    case Black:
	std::cout << "Turn of B" << std::endl;

	if (print->pass == White){
	    std::cout << "pass W" << std::endl;
	}
	break;
    case White:
	std::cout << "Turn of W" << std::endl;

	if (print->pass == Black){
	    std::cout << "pass B" << std::endl;
	}
	break;
    case 999:
	if (print->wpnum > print->bpnum){
	    std::cout <<   "Win W" << std::endl;

	}
	else if (print->wpnum < print->bpnum){
	    std::cout << "Win B" << std::endl;

	}
	else{
	    std::cout << "Draw" << std::endl;
	}
	break;
    }

    if (color != 999){
	if (print->pass != Non && print->p_cnt == 0){
	    print->p_cnt++;
	}
    }
}
/*	pieceprint�֐��@�I���@*//////////////////////////////////////////////////////////////


/*	init�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
void init(void){

    original.wpiece = 0, original.bpiece = 0, original.rpiece = 0, original.ypiece = 0;
    original.wpnum = 0, original.bpnum = 0;
    original.pass = Non;

    //�ŏ��̂S��ݒ�
    original.wpiece += (ULL)1 << 36;
    original.bpiece += (ULL)1 << 35;
    original.wpiece += (ULL)1 << 27;
    original.bpiece += (ULL)1 << 28;

    //�ŏ��̂��ܐ���ݒ�
    original.wpnum += 2;
    original.bpnum += 2;

    original.pass = Non;

    
    //pieceprint(Non, &original);
    
}
/*	init�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////


/*	OP�֐��@�J�n*///////////////////////////////////////////////////////////////////////////////////////
void OP(){

    int flag = 0;//1 = �Q�[���X�^�[�g
    char mode;

    /*   ���[�v �J�n   */  //ESC�������ꂽ�烋�[�v���甲����
    while ( flag == 0 && END_Flag == 0){

	//����
	std::cout << "mode: [B or W or E] "<< std::endl;
	std::cin >> mode;
	

	if (mode == 'B'){
	
	    flag = 1;//�Q�[���X�^�[�g

	    B_player = 0;//�蓮
	    W_player = 4;//�I�[�g7
		
	}else if (mode == 'W'){
	
	    flag = 1;//�Q�[���X�^�[�g

	    B_player = 4;//�I�[�g7
	    W_player = 0;//�蓮
		
	}else if (mode == 'E') END_Flag = 1;//�I��


    }
    /*   ���[�v �I��   */
}
/*	OP�֐��@�I��*//////////////////////////////////////////////////////////////////////////////////////////



/*	turn�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
board turn(int color){

    int a = 999, b = 999, flag, aflag, i, j;
    board after;
    char c;

    flag = search(color, &original);//�u����ꏊ��T��

    while (flag == 0 ){

	//����
	std::cout << "input: [a-h] [1-8]" << std::endl;
	std::cin >> c >> a;
       
	b = (int)(c - 'a')+1;
	
	//if(Board_red[a][b] == 1 && a != 999 && b != 999){//�N���b�N�����ꏊ���u���鏊�Ȃ�
	if (((original.rpiece >> (64 - b - ((a - 1) * 8))) & 1) == 1 && a != 999 && b != 999){//�N���b�N�����ꏊ���u���鏊�Ȃ�

	    after = operation(a, b, color, original);
	    flag = 1;
	    original = after;//�u����������I���W�i���ɔ��f	
	}
	
    }

    original.pass = Non;

    if (flag == 9){
	original.pass = color;
	original.p_cnt = 0;//�p�X���wait�����ɂ��邽��
    }

    return original;
}
/*	turn�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////


int main(){

    int f;//0 = �p�� ,1 = �I��
    int cnt;

    /*    ���C�����[�v �J�n   */ //ESC�L�[�������ꂽ�烋�[�v���甲����
    while (END_Flag == 0){

	OP();//�I�[�v�j���O

	if (END_Flag == 0){
	    init();//�I�Z���p������
	}
	cnt = 0;

	f = 0;

	while ( f == 0 && END_Flag == 0){
	    
	    search(Black, &original);
	    pieceprint(Black, &original);

	    cnt++;

	    switch (B_player){
	    case 0:
		if (f == 0)original = turn(Black);
		break;
	
	    case 1:
		if (f == 0){
		    if (cnt >55)original = turn_dfs(Black, original, 200);
		    else original = turn_dfs(Black, original, 5);
		}
		break;
	    case 2:
		if (f == 0)original = turn_rand(Black, original);
		break;
	    case 3:
		if (f == 0){
		    if (cnt >55)original = turn_minmax(Black, original, 200);
		    else original = turn_minmax(Black, original, 5);
		}
		break;
	    case 4:
		/*if (f == 0){
		  if (cnt >55)original = turn_ab(Black, original, 200);
		  else original = turn_ab(Black, original, 10);
		  }*/

		if (f == 0){
		    if (cnt >47)original = turn_ab(Black, original, 100);
		    else if (cnt >33)original = turn_ab(Black, original, 11);
		    else original = turn_ab(Black, original, 10);
		}
		break;
	    case 5:
		if (f == 0)original = turn_monte(Black, original,300000 + cnt*6000);
		break;
	    case 6:
		if (f == 0)original = turn_monte2(Black, original,300000 + cnt*6000);
		break;
	    }

	    f = check(original);

	    search(White, &original);
	    pieceprint(White, &original);

	    cnt++;

	    switch (W_player){
	    case 0:
		if (f == 0)original = turn(White);
		break;
	    case 1:
		if (f == 0){
		    if (cnt > 55)original = turn_dfs(White, original, 200);
		    else original = turn_dfs(White, original, 5);
		}
		break;
	    case 2:
		if (f == 0)original = turn_rand(White, original);
		break;
	    case 3:
		if (f == 0){
		    if (cnt > 55)original = turn_minmax(White, original, 200);
		    else original = turn_minmax(White, original, 5);
		}
		break;
	    case 4:
		/*if (f == 0){
		  if (cnt > 55)original = turn_ab(White, original, 200);
		  else original = turn_ab(White, original, 10);
		  }*/
				
		if (f == 0){
		    if (cnt > 47)original = turn_ab(White, original, 200);
		    else if (cnt > 33)original = turn_ab(White, original, 11);
		    else original = turn_ab(White, original, 10);
		}
		break;
	    case 5:
		if (f == 0){
		    original = turn_monte(White, original, 300000 + (cnt-1)*6000);
		}
		break;
	    case 6:
		if (f == 0){
		    original = turn_monte2(White, original, 300000 + (cnt-1)*6000);
		}
		break;
	    }

	    f = check(original);
	}

	if (END_Flag == 0){//�Q�[���I�����@����͂��Ȃ�
	    total();
	}
    }
    /*   ���C�����[�v �I��   */

    return 0;//����I��
}




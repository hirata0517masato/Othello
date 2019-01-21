#include<iostream>
#include <cmath>
#include "game.hpp"
#include "ai.hpp"

#define Wait 0		//待ち時間（1ms)

//関数のプロトタイプ宣言
void init(void);
void pieceprint(int, board *);
int total(void);
int learning(void);

//グローバル変数宣言
board original;


/*	関数　開始　*///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*	total関数　開始　*//////////////////////////////////////////////////////////////////////////////
int total(){

    original.rpiece = 0;

    //pieceprint(999, &original);
    
    if (original.wpnum > original.bpnum){
	return White;

    }
    else if (original.wpnum < original.bpnum){
	    
	return Black;

    }
	
    return 0;
}
/*	total関数　終了　*////////////////////////////////////////////////////////////////////////////////


/*	pieceprint関数　開始　*//////////////////////////////////////////////////////////////////////////////
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
/*	pieceprint関数　終了　*//////////////////////////////////////////////////////////////


/*	init関数　開始　*//////////////////////////////////////////////////////////////////////////////
void init(void){

    original.wpiece = 0, original.bpiece = 0, original.rpiece = 0, original.ypiece = 0;
    original.wpnum = 0, original.bpnum = 0;
    original.pass = Non;

    //最初の４つを設定
    original.wpiece += (ULL)1 << 36;
    original.bpiece += (ULL)1 << 35;
    original.wpiece += (ULL)1 << 27;
    original.bpiece += (ULL)1 << 28;

    //最初のこま数を設定
    original.wpnum += 2;
    original.bpnum += 2;

    original.pass = Non;

    
    //pieceprint(Non, &original);
    
}
/*	init関数　終了　*////////////////////////////////////////////////////////////////////////////////


int main(){

    int learningNum = 10;
    int win_color;
    
    read_board_G();
    for(int i = 0; i < learningNum; i++){
	win_color = learning();

	if(win_color == Black)copy_board_G(White);
	else copy_board_G(Black);

	//update_board_G(Black);
	update_board_G2(Black);
    }

    win_color = learning();
    if(win_color == Black)write_board_G(Black);
    else write_board_G(White);
    
    return 0;
}

int learning(){

    int f;//0 = 継続 ,1 = 終了
    int cnt;

    init();//オセロ用初期化
	
    cnt = 0;

    f = 0;

    while ( f == 0){
	    
	search(Black, &original);
	//pieceprint(Black, &original);

	cnt++;

	if (f == 0){
	    if (cnt >47)original = turn_ab(Black, original, 999);
	    else original = turn_ab(Black, original, 8);
		
	    //45m
	    /* if (cnt >47)original = turn_ab(Black, original, 999);
	      else if (cnt >33)original = turn_ab(Black, original, 12);
	      else original = turn_ab(Black, original, 11);
	    */
	}


	f = check(original);

	search(White, &original);
	//pieceprint(White, &original);

	cnt++;
			
	if (f == 0){
	    if (cnt > 47)original = turn_ab(White, original, 999);
	    else original = turn_ab(White, original, 8);
	    
	    /* if (cnt > 47)original = turn_ab(White, original, 999);
	      else if (cnt > 33)original = turn_ab(White, original, 12);
	      else original = turn_ab(White, original, 11);
	    */
	}
	

	f = check(original);
    }


    return total();
}




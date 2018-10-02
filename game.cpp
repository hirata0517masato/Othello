#include "game.hpp"

/*	operation関数　開始　*//////////////////////////////////////////////////////////////////////////////
board operation(int y, int x, int color, board ope){

	int i, j, flag = 0;

	ULL me, you;
	if (color == Black){
		me = ope.bpiece;
		you = ope.wpiece;
	}
	else{
		me = ope.wpiece;
		you = ope.bpiece;
	}

	for (i = 0; i<3; i++){
		for (j = 0; j<3; j++){

			if (i != 1 || j != 1){

				int xx = x - 1 + j, yy = y - 1 + i, outflag = 0;

				if (0 < yy && yy < 9 && 0 < xx && xx < 9){//外枠を越えないように 
					ULL check = (ULL)1 << (64 - x + 1 - j - ((y - 1 - 1 + i) * 8));
					ULL add = 0;
					int cnt = 0;
					
					if ((you & check) > 0){
						while ((you & check) > 0){//相手のこまが続くまでループ
							add |= check;
							cnt++;
							
							if (((1 - j) + (1 - i) * 8) > 0) check <<= ((1 - j) + (1 - i) * 8);
							else check >>= -((1 - j) + (1 - i) * 8);

							xx += -1 + j;
							yy += -1 + i;

							if (yy < 1 || 8 < yy || xx < 1 || 8 < xx){//外枠を越えたら
								outflag = 1;
								break;
							}
						}

						if (outflag == 0 && (me & check) > 0){//挟めることが確定
							flag = 1;

							if (color == Black){
								ope.bpnum += cnt;
								ope.wpnum -= cnt;

								ope.bpiece |= add;
								ope.wpiece &= ~add;
							}
							else if (color == White){
								ope.bpnum -= cnt;
								ope.wpnum += cnt;

								ope.bpiece &= ~add;
								ope.wpiece |= add;
							}
						}
					}
				}
			}
		}
	}
	if (flag == 1){
		ope.ypiece = (ULL)1 << (64 - x - ((y - 1) * 8));//置いた場所の記録

		if (color == Black){
			ope.bpnum++;
			ope.bpiece += (ULL)1 << (64 - x - ((y - 1) * 8));
		}
		else{
			ope.wpnum++;
			ope.wpiece += (ULL)1 << (64 - x - ((y - 1) * 8));
		}
	}
	return ope;
}

/*	operation関数　終了　*////////////////////////////////////////////////////////////////////////////////

/*	serch関数　開始　*//////////////////////////////////////////////////////////////////////////////
int search(int color, board * sea){

	int i, j, x, y, out = 9;
	ULL bit_check = (ULL)1 << 63;
	ULL me, you,bw;

	if (color == Black){
		me = sea->bpiece;
		you = sea->wpiece;
	}
	else{
		me = sea->wpiece;
		you = sea->bpiece;
	}
	bw = me | you;

	sea->rpiece = 0;//置ける場所の初期化

	for (y = 1; y <= 8; y++){
		for (x = 1; x <= 8; x++){
			//if (((bw >> (64 - x - ((y - 1) * 8))) & 1) == 0){//空白マスなら ＝置ける可能性がある
			if ((bw & bit_check) == 0){//空白マスなら ＝置ける可能性がある
				for (i = 0; i<3; i++){
					for (j = 0; j<3; j++){

						if (i != 1 || j != 1){//i==1 && j==1 は置こうとしてるマス
							int xx = x - 1 + j, yy = y - 1 + i, flag = 0;

							if (0 < yy && yy < 9 && 0 < xx && xx < 9){//外枠を越えないように     
								//ULL check = (ULL)1 << (64 - x + 1 - j - ((y - 1 - 1 + i) * 8));
								ULL check = bit_check;
								
								if(j == 0)check <<= 1;
								else if(j == 2)check >>= 1;

								if(i == 0)check <<= 8;
								else if(i == 2)check >>= 8;


								bool t = ((1 - j) + (1 - i) * 8) > 0;
								if ((you & check) > 0){
									do{
										if (t) check <<= ((1 - j) + (1 - i) * 8);
										else check >>= -((1 - j) + (1 - i) * 8);

										xx += -1 + j;
										yy += -1 + i;
										if (yy < 1 || 8 < yy || xx < 1 || 8 < xx){//外枠を越えたら
											flag = 1;
											break;
										}
									}while ((you & check) > 0);//相手のこまが続くまでループ

									if (flag == 0 && (me & check) > 0){
										out = 0;
										sea->rpiece |= bit_check;
									}
								}
							}
						}
					}
				}
			}
			bit_check >>= 1;
		}
	}

	return out;
}
/*	serch関数　終了　*////////////////////////////////////////////////////////////////////////////////



/*	check関数　開始　*//////////////////////////////////////////////////////////////////////////////
int check(board ch){

	if (ch.bpnum > 0 && ch.wpnum > 0){ //どちらかが0なら、そもそもゲーム終了
		if (~(ch.wpiece | ch.bpiece) > 0){//空白かどうかのチェック
			if (search(Black, &ch) == 0 || search(White, &ch) == 0)return 0;//どちらかは置ける
		}
	}
	return 1;
}
/*	check関数　終了　*//////////////////////////////////////////////////////////////
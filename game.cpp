#include "game.hpp"

/*	operation�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
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

				if (0 < yy && yy < 9 && 0 < xx && xx < 9){//�O�g���z���Ȃ��悤�� 
					ULL check = (ULL)1 << (64 - x + 1 - j - ((y - 1 - 1 + i) * 8));
					ULL add = 0;
					int cnt = 0;
					
					if ((you & check) > 0){
						while ((you & check) > 0){//����̂��܂������܂Ń��[�v
							add |= check;
							cnt++;
							
							if (((1 - j) + (1 - i) * 8) > 0) check <<= ((1 - j) + (1 - i) * 8);
							else check >>= -((1 - j) + (1 - i) * 8);

							xx += -1 + j;
							yy += -1 + i;

							if (yy < 1 || 8 < yy || xx < 1 || 8 < xx){//�O�g���z������
								outflag = 1;
								break;
							}
						}

						if (outflag == 0 && (me & check) > 0){//���߂邱�Ƃ��m��
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
		ope.ypiece = (ULL)1 << (64 - x - ((y - 1) * 8));//�u�����ꏊ�̋L�^

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

/*	operation�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////

/*	serch�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
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

	sea->rpiece = 0;//�u����ꏊ�̏�����

	for (y = 1; y <= 8; y++){
		for (x = 1; x <= 8; x++){
			//if (((bw >> (64 - x - ((y - 1) * 8))) & 1) == 0){//�󔒃}�X�Ȃ� ���u����\��������
			if ((bw & bit_check) == 0){//�󔒃}�X�Ȃ� ���u����\��������
				for (i = 0; i<3; i++){
					for (j = 0; j<3; j++){

						if (i != 1 || j != 1){//i==1 && j==1 �͒u�����Ƃ��Ă�}�X
							int xx = x - 1 + j, yy = y - 1 + i, flag = 0;

							if (0 < yy && yy < 9 && 0 < xx && xx < 9){//�O�g���z���Ȃ��悤��     
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
										if (yy < 1 || 8 < yy || xx < 1 || 8 < xx){//�O�g���z������
											flag = 1;
											break;
										}
									}while ((you & check) > 0);//����̂��܂������܂Ń��[�v

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
/*	serch�֐��@�I���@*////////////////////////////////////////////////////////////////////////////////



/*	check�֐��@�J�n�@*//////////////////////////////////////////////////////////////////////////////
int check(board ch){

	if (ch.bpnum > 0 && ch.wpnum > 0){ //�ǂ��炩��0�Ȃ�A���������Q�[���I��
		if (~(ch.wpiece | ch.bpiece) > 0){//�󔒂��ǂ����̃`�F�b�N
			if (search(Black, &ch) == 0 || search(White, &ch) == 0)return 0;//�ǂ��炩�͒u����
		}
	}
	return 1;
}
/*	check�֐��@�I���@*//////////////////////////////////////////////////////////////
#ifndef GAME
#define GAME

#define Black 1
#define White 0
#define Non 3

#define ULL	unsigned long long

class board{
public:
	//�Ղ̏��
	ULL wpiece, bpiece, rpiece, ypiece;
	//��̐�
	int wpnum, bpnum;
	int pass, p_cnt;//�p�X
};

int search(int, board *);
board operation(int, int, int, board);
int check(board);

#endif
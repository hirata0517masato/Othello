#ifndef GAME
#define GAME

#define Black 1
#define White 0
#define Non 3

#define ULL	unsigned long long

class board{
public:
	//盤の状態
	ULL wpiece, bpiece, rpiece, ypiece;
	//駒の数
	int wpnum, bpnum;
	int pass, p_cnt;//パス
};

int search(int, board *);
board operation(int, int, int, board);
int check(board);

#endif
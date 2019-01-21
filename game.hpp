#ifndef GAME
#define GAME

#define Black 1
#define White 0
#define Non 3

#define ULL	unsigned long long

class board{
public:
	//”Õ‚Ìó‘Ô
	ULL wpiece, bpiece, rpiece, ypiece;
	//‹î‚Ì”
	int wpnum, bpnum;
	int pass, p_cnt;//ƒpƒX
};

int search(int, board *);
board operation(int, int, int, board);
int check(board);

#endif
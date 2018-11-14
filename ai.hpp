#ifndef AI
#define AI


board turn_dfs(int,board,int);
void turn_dfs_next_thread(int, int, board, int,double&);
double turn_dfs_next(int, int, board, int);
board turn_rand(int, board);
board turn_minmax(int, board, int);
double turn_minmax_next(int, int, board, int);
board turn_ab(int, board, int);
double turn_ab_next(int, int, board,int, double);
board turn_monte(int, board , int );
double turn_mon_next(int, int, board);
double evaluation(int, board *,int);

board turn_monte2(int, board , int );

#endif

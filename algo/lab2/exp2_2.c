// gcc exp2_2.c -lm && ./a.out 9 4 4
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int tile = 1;
int chess[1000][1000];

void ChessBoard(int tr, int tc, int dr, int dc, int size) {
    if (size == 1)
        return;
    int t = tile++;
    int s = size/2;
    
    /* upper left sub-chessboard */
    if (dr<tr+s && dc<tc+s) 
        ChessBoard(tr, tc, dr, dc, s);
    else {
        chess[tr+s-1][tc+s-1] = t;
        ChessBoard(tr, tc, tr+s-1, tc+s-1 , s);
    }
    
    /* upper right */
    if (dr<tr+s && dc>=tc+s) 
        ChessBoard(tr, tc+s, dr, dc, s);
    else {
        chess[tr+s-1][tc+s] = t;
        ChessBoard(tr, tc+s, tr+s-1, tc+s, s);
    }

    /* bottom left */
    if (dr>=tr+s && dc<tc+s) 
        ChessBoard(tr+s, tc, dr, dc, s);
    else {
        chess[tr+s][tc+s-1] = t;
        ChessBoard(tr+s, tc, tr+s, tc+s-1, s);
    }

    /* botton right */
    if (dr>=tr+s && dc>=tc+s) 
        ChessBoard(tr+s, tc+s, dr, dc, s);
    else {
        chess[tr+s][tc+s] = t;
        ChessBoard(tr+s, tc+s, tr+s, tc+s, s);
    }
}
void disply(int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            printf("%2d ", chess[i][j]);
        }
        printf("\n");
        fflush(stdout);
    }
}
int main(int argc, char* argv[]) {
    setvbuf(stdin,  NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    int line, x, y;
    if (argc < 3) {
        printf("./a.out line x y \n");
        exit(-1);
    }
    
    y = atoi(argv[3]);
    x = atoi(argv[2]);
    line = atoi(argv[1]);
    
    int size;
    size = (int)pow(2, line);
    printf("%d %d %d \n", size, x, y);
    ChessBoard(0, 0, x, y, size);
    printf("tile = %d \n((int)pow(4, k)-1)/3 = %d\n", tile, ((int)pow(4, line)-1)/3);
    disply(size);
    return 0;
}

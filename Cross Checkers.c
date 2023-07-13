#include <stdio.h>
#include "stdlib.h"
#include "string.h"

#define E ' ' // empty cell
#define F 'X' // full cell
#define O 'O' // out of the board

#define SIZE 9 // board size

// offsets for the moves
const int xoff[4]={-1,1,0,0};
const int yoff[4]={0,0,1,-1};

// function prototypes
int move_r(int board[SIZE][SIZE],int moves[31][4],int n);

// ekstra

void copy_board(int *dst,int *src,int size);
void apply_move(int b[][SIZE],int *mov);
void show_board(int b[][SIZE]);

// main program
int main(void){
    int i,moves[31][4],board[SIZE][SIZE]={{O,O,O,O,O,O,O,O,O},
                                          {O,O,O,F,F,F,O,O,O},
                                          {O,O,O,F,F,F,O,O,O},
                                          {O,F,F,F,F,F,F,F,O},
                                          {O,F,F,F,E,F,F,F,O},
                                          {O,F,F,F,F,F,F,F,O},
                                          {O,O,O,F,F,F,O,O,O},
                                          {O,O,O,F,F,F,O,O,O},
                                          {O,O,O,O,O,O,O,O,O}};
    int bop[SIZE][SIZE];
    copy_board(&bop[0][0],&board[0][0],SIZE);

    show_board(bop);
    if (move_r(bop,moves,0)==0){
        fprintf(stdout,"No solution exists'\n");
    }
    else{
        copy_board(&bop[0][0],&board[0][0],SIZE);
        for(int i=0;i<31;i++){
            fprintf(stdout,"%d %d -> %d %d\n",moves[i][0],moves[i][1],moves[i][2],moves[i][3]);
            apply_move(bop,moves[i]);
            show_board(bop);
        }

        return EXIT_SUCCESS;
    }

    void copy_board(int *dst,int *src,int size){
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                dst[i*size+j]=src[i*size+j];
            }
        }
    }

    void apply_move(int b[][SIZE],int *mov){
        b[mov[0]][mov[1]]=E;
        b[mov[2]][mov[3]]=F;
        int x=mov[0]+mov[2];
        int y=mov[1]+mov[3];
        b[x/2][y/2]=E;
    }


    void show_board(int b[][SIZE]){
        //print board
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++) {
                printf("%c", b[i][j]);
            }
            printf("\n");
        }
    }

// make a move (recursive function)
    int move_r(int board[SIZE][SIZE],int moves[31][4],int n){
        int x1,y1,x2,y2,x3,y3,k;
        if(n==31){
            return 1;
        }

        // for each board cell...
        for(x1=1;x1<SIZE-1;x1++){
            for(y1=1;y1<SIZE-1;y1++){
                // if there is a pawn
                if(board[x1][y1]==F){
                    //...look whether it is possible to eat...
                    for(k=0;k<4;k++){
                        x2=x1+xoff[k];
                        y2=y1+yoff[k];
                        if (board[x2][y2]==F){
                            x3=x1+2*xoff[k];
                            y3=y1+2*yoff[k];
                            if (board[x3][y3]==E){
                                //...then make the move...
                                board[x3][y3]=F;
                                board[x2][y2]=E;
                                board[x1][y1]=E;
                                //...and recur...
                                if (move_r(board,moves,n+1)==1){
                                    //...storint the move if it was ok...
                                    moves[n][0]=x1;
                                    moves[n][0]=x1;
                                    moves[n][1]=y1;
                                    moves[n][2]=x3;
                                    moves[n][3]=y3;
                                    return 1; // Stop on first solution!
                                }
                                //...otherwise backtrack...
                                board[x3][y3]=E;
                                board[x2][y2]=F;
                                board[x1][y1]=F;
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }
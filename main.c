#include <stdio.h>
#include <stdlib.h>

int main(){
    int level;
    char lagi;

    printf("Welcome to Tic Tac Toe Game :)\n");
    puts("Deskripsi level:");
    puts("Level 1 : player 1 vs player 2 gaada menang/kalah");
    puts("Level 2 : player 1 vs player 2 bisa menang/kalah");
    puts("Level 3 : player vs bot(noob)");
    puts("Level 4 : player vs bot(pro)\n");
    do{
        printf("Pilih level(1-4) : ");
        scanf("%d", &level);

        switch(level){
            case 1:
                level_1();
                break;
            case 2:
                level_2();
                break;
            case 3:
                level_3();
                break;
            case 4:
                level_4();
                break;
            default:
                printf("Input salah bang!\n");
                exit(0);
        }

        fflush(stdin);
        printf("Main lagi ga (y/t)? ");
        scanf("%c", &lagi);
        puts("");
    }while(lagi == 'Y' || lagi == 'y');

    return 0;
}

char tampil_giliran(int kode){
    if (kode == 0)
        return '.';
    else if (kode == -1)
        return 'X';
    else if (kode == 1)
        return 'O';
}

void tampil(int papan[3][3]){
    puts("");
    printf(" %c | %c | %c \n",  tampil_giliran(papan[0][0]), tampil_giliran(papan[0][1]), tampil_giliran(papan[0][2]));
    printf("------------\n");
    printf(" %c | %c | %c \n",  tampil_giliran(papan[1][0]), tampil_giliran(papan[1][1]), tampil_giliran(papan[1][2]));
    printf("------------\n");
    printf(" %c | %c | %c \n",  tampil_giliran(papan[2][0]), tampil_giliran(papan[2][1]), tampil_giliran(papan[2][2]));
}

int win(int papan[3][3]){
    int pemenang = 0;
    for(int i = 0; i < 3; i++){
        //cek secara horizontal
        if(papan[i][0] == papan[i][1] && papan[i][1] == papan[i][2] && papan[i][0] != 0){
            pemenang = papan[i][0];
            break;
        }
        //cek secara vertikal
        if(papan[0][i] == papan[1][i] && papan[1][i] == papan[2][i] && papan[i][0] != 0){
            pemenang = papan[0][i];
            break;
        }

        if(papan[0][0] == papan[1][1] && papan[1][1] == papan[2][2] && papan[i][0] != 0){
            pemenang = papan[0][0];
            break;
        }
        if(papan[0][2] == papan[1][1] && papan[1][1] == papan[2][0] && papan[i][0] != 0){
            pemenang = papan[0][2];
            break;
        }
    }

    return pemenang;
}

void player_turn(int papan[3][3], int no_player){
    int i, j;

    do{
        printf("Player %d, giliranmu : ", no_player);
        scanf("%d %d", &i, &j);

        if (papan[i][j] != 0 || i > 2 || i < 0 || j > 2 || j < 0)
            printf("input salah bang!\n");
    }while(papan[i][j] != 0 || i > 2 || i < 0 || j > 2 || j < 0);

    if (no_player == 2)
        papan[i][j] = 1;
    else if(no_player == 1)
        papan[i][j] = -1;
}

int minimax(int board[3][3], int player) {
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move[2] = {-1, -1};
    int score = -2;
    int i, j;
    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; j++){
            if(board[i][j] == 0) {
                board[i][j] = player;
                int thisScore = -minimax(board, player*-1);
                if(thisScore > score) {
                    score = thisScore;
                    move[0] = i;
                    move[1] = j;
                }
                board[i][j] = 0;
            }
        }
    }
    if(move[0] == -1 && move[1] == -1) return 0;
    return score;
}

void pro_bot(int board[3][3]){
    int move[2] = {-1,-1};
    int score = -2;
    int i, j;
    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j){
            if(board[i][j] == 0) {
                board[i][j] = 1;
                int tempScore = -minimax(board, -1);
                board[i][j] = 0;
                if(tempScore > score) {
                    score = tempScore;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }
    board[move[0]][move[1]] = 1;
}

void noob_bot(int board[3][3]){
    int attmp = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == 0 && attmp == 0){
                board[i][j] = 1;
                attmp++;
            }
        }
    }
}

void tampil_pemenang(int papan[3][3], int computer){
    int winner = win(papan);

    if(winner == 0)
        printf("DRAWW!\n\n");
    else if(computer == 1 && winner == 1)
        printf("Computer Win!\n\n");
    else{
        if (winner == -1)
            printf("Player 1 Win!\n\n");
        else
            printf("Player 2 Win!\n\n");
    }
}

void level_1(){
    int board[3][3] = {0,0,0,0,0,0,0,0,0};//variabel lokal

    for(int i=0; i<9; i++){
        tampil(board);
        if(i%2 == 0)
            player_turn(board, i%2+1);//player 1
        else
            player_turn(board, i%2+1);//player 2
    }
    tampil(board);
    printf("SELESAI!!\n\n");
}

void level_2(){
    int board[3][3] = {0,0,0,0,0,0,0,0,0};//variabel lokal

    for(int i=0; i<9; i++){
        tampil(board);
        if(i%2 == 0)
            player_turn(board, i%2+1);
        else
            player_turn(board, i%2+1);

        if (win(board) != 0)
            break;
    }

    tampil(board);
    tampil_pemenang(board, 0);
}

void level_3(){
    int board[3][3] = {0,0,0,0,0,0,0,0,0};

    for(int i=0; i<9; i++){
        tampil(board);
        if(i%2 == 0)
            player_turn(board, i%2+1);
        else{
            printf("\nBOT:");
            noob_bot(board);
        }

        if (win(board) != 0)
            break;
    }

    tampil(board);
    tampil_pemenang(board, 1);
}

void level_4(){
    int board[3][3] = {0,0,0,0,0,0,0,0,0};

    for(int i=0; i<9; i++){
        tampil(board);
        if(i%2 == 0)
            player_turn(board, i%2+1);
        else{
            printf("\nBOT:");
            pro_bot(board);
        }

        if (win(board) != 0)
            break;
    }

    tampil(board);
    tampil_pemenang(board, 1);
}

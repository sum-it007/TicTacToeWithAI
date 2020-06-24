#include <iostream>

using namespace std;
#define BOARD_SIZE 3
class Game{

    struct Move{
        int row;
        int col;
    };
    char board[BOARD_SIZE][BOARD_SIZE];
    int position;
    char aiPlayer = 'O';
    char humanPlayer = 'X';
    char humanPlayer2 = 'O';

public:
    Game(){
        char num=49;
        for(int i=0;i<BOARD_SIZE;i++)
        {
            for(int j=0;j<BOARD_SIZE;j++)
            {
                board[i][j]=num;
                num++;
            }
        }
    }
    void printBoard()
    {
        cout<<"+-----------+\n";
        for(int i=0;i<BOARD_SIZE;i++)
        {

            for(int j=0;j<BOARD_SIZE;j++)
            {
                cout<<"| "<<board[i][j]<<" ";
            }
            cout<<"|\n+-----------+\n";
        }
    }
    void getHumanMove1()
    {
        int row ,col;
        bool isValid = false;
        do {
            cout << "Enter Position :";
            cin >> position;
            if(position<=0||position>9)
            {
                cout<<"invalid position ... \nAgain ";
                isValid= false;
                continue;
            }
            position = position -1;
            row = position/BOARD_SIZE;
            col = position%BOARD_SIZE;
            if (board[row][col] == 'X' || board[row][col] == 'O') {
                cout << "\nSpot Already taken .. ";
            } else{
                board[row][col]='X';
                isValid= true;
            }

        }while (isValid == false);
    }

    void getHumanMove2()
    {
        int row ,col;
        bool isValid = false;
        do {
            cout << "Enter Position :";
            cin >> position;
            if(position<=0||position>9)
            {
                cout<<"invalid position ... \nAgain ";
                isValid= false;
                continue;
            }
            position = position-1;
            row = position/BOARD_SIZE;
            col = position%BOARD_SIZE;
            if (board[row][col] == 'X' || board[row][col] == 'O') {
                cout << "\nSpot Already taken .. ";
            } else{
                board[row][col]=humanPlayer2;
                isValid= true;
            }

        }while (isValid == false);
    }


    bool isTie()
    {
        int num;
        for(int i=0;i<BOARD_SIZE;i++)
        {
            for(int j=0;j<BOARD_SIZE;j++)
            {
                num = ((3*i)+(j+1));
                char ch = num+48;
                if(board[i][j]==ch)
                    return false;
            }
        }
        return true;
    }

    bool checkWin(char player)
    {
        for(int i=0;i<BOARD_SIZE;i++)
        {
            for(int j=0;j<BOARD_SIZE;j++)
            {
                if((board[0][i]==board[1][i])&&(board[1][i]==board[2][i])&&(board[0][i]==player))
                {
                    return true;
                }
                if((board[i][0]==board[i][1])&&(board[i][1]==board[i][2])&&(board[i][0]==player))
                {
                    return true;
                }
            }
        }
        if((board[0][0]==board[1][1])&&(board[1][1]==board[2][2])&&(board[0][0]==player))
        {
            return true;
        }
        if((board[0][2]==board[1][1])&&(board[1][1]==board[2][0])&&(board[1][1]==player))
        {
            return true;
        }
        return false;
    }

    Move minimax()
    {
        int score = 100000;
        Move move;
        int num;
        for(int i=0;i<BOARD_SIZE;i++)
        {
            for(int j=0;j<BOARD_SIZE;j++)
            {
                num = ((3*i)+(j+1));
                char ch = num+48;
                if(board[i][j] == ch)
                {
                    board[i][j] = aiPlayer;

                    int temp = maxSearch();
                    if(temp<score)
                    {
                        score = temp;
                        move.row=i;
                        move.col=j;
                    }
                    board[i][j]=ch;
                }
            }
        }
        return move;
    }

    int maxSearch()
    {
        if(checkWin(humanPlayer))
            return 10;
        else if(checkWin(aiPlayer))
            return -10;
        else if(isTie())
            return 0;

        int score = -10000;
        int num;
        for(int i=0;i<BOARD_SIZE;i++)
        {
            for(int j=0;j<BOARD_SIZE;j++)
            {
                num = ((3*i)+(j+1));
                char ch = num+48;
                if(board[i][j]==ch)
                {
                    board[i][j]='X';
                    score=max(score,minSearch());
                    board[i][j]=ch;
                }
            }
        }
        return score;
    }

    int minSearch()
    {
        if(checkWin(humanPlayer))
            return 10;
        else if(checkWin(aiPlayer))
            return -10;
        else if(isTie())
            return 0;

        int score = 100000;
        int num;
        for(int i=0;i<BOARD_SIZE;i++)
        {
            for(int j=0;j<BOARD_SIZE;j++)
            {
                num = ((3*i)+(j+1));
                char ch = num+48;
                if(board[i][j]==ch)
                {
                    board[i][j]='O';
                    score = min(score,maxSearch());
                    board[i][j]=ch;
                }
            }
        }
        return score;
    }

    void playWithAI()
    {
        char turn = humanPlayer;
        bool exit = false;
        printBoard();
        do{
            if(turn==humanPlayer)
            {
                getHumanMove1();
                if(checkWin(humanPlayer))
                {
                    cout<<"Human won\n";
                    exit = true;
                }
            } else
            {
                cout<<"\nComputer Move :\n";
                Move aimove = minimax();
                board[aimove.row][aimove.col] = 'O';

                if(checkWin(aiPlayer))
                {
                    cout<<"Computer won\n";
                    exit = true;
                }
            }

            if(isTie())
            {
                cout<<"\n*** TIE ***\n";
                exit = true;
            }

            //To check the turn
            if(turn==humanPlayer)
                turn=aiPlayer;
            else if(turn==aiPlayer)
                turn=humanPlayer;


            printBoard();
        }while (!exit);
    }


    void playWithHuman()
    {
        char turn = humanPlayer;
        bool exit = false;
        printBoard();
        do{
            if(turn==humanPlayer)
            {
                cout<<"Human 1's Turn : ";
                getHumanMove1();
                if(checkWin(humanPlayer))
                {
                    cout<<"Human 1 won\n";
                    exit = true;
                }
            } else
            {
                cout<<"\nHuman 2's Turn : ";
                getHumanMove2();
                if(checkWin(humanPlayer2))
                {
                    cout<<"Human 2 won\n";
                    exit = true;
                }
            }

            if(isTie())
            {
                cout<<"\n*** TIE ***\n";
                exit = true;
            }

            //To check the turn
            if(turn==humanPlayer)
                turn=humanPlayer2;
            else if(turn==humanPlayer2)
                turn=humanPlayer;


            printBoard();
        }while (!exit);
    }

    void menu()
    {
        int ch;
        cout<<"***** MENU *****\n";
        cout<<"Enter 1. to Play with Another Human \n";
        cout<<"Enter 2. to Play with Ai Player\n";
        cout<<"Enter your Choice :";
        cin>>ch;
        if(ch==1)
            playWithHuman();
        else if(ch==2)
            playWithAI();
    }

};
int main()
{
    Game game;
    game.menu();
    return 0;
}
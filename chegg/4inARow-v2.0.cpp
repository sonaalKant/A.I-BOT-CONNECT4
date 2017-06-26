#include<iostream>
#include<vector>
#include<limits.h>
#include<map>
//map<vector<int>,count> m;
//map<pair<int,int>,vector<vector<int> > > hm;
using namespace std;

enum Result { P1_WON, P2_WON, DRAW, UNFINISHED };
int num = 0;
int turn;
int depth =0 ;
class Board
{
public :
    int board[6][7];

    Board()
    {
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<7;j++)
            {
                board[i][j] = 0;
            }
        }
    }

    void print_board()
    {
        for(int i=0;i<7;i++)
            cout<<i<<" ";

        cout<<endl;
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<7;j++)
            {
                if(board[i][j] == 0)
                cout<<"-"<<" ";
                else
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void push(int col ,int a)
    {
        //cout<<a;
        for(int i=5;i>=0;i--)
        {
            if(board[i][col] == 0)
            {
                board[i][col] = a;
                return;
            }
        }
    }
    Result game_state()
    {
        //cout<<"game";
        for(int i=0 ;i<3;i++)
        {
            for(int j=0;j<7;j++)
            {
                //cout<<"loop";
                //cout<<i<<" "<<j;
            try{
               if(board[0+i][j] == 1 && board[1+i][j] == 1 && board[2+i][j] == 1 && board[3+i][j] == 1 )
               {
                   return P1_WON;
               }

               else if(board[0+i][j] == 2 && board[1+i][j] == 2 && board[2+i][j] == 2 && board[3+i][j] == 2 )
               {
                   return P2_WON;
               }
            }
            catch(exception e){
                cout<<e.what();
            }
            }
            //cout<<6576;
        }

        for(int i=0 ;i<4;i++)
        {
            for(int j=0;j<6;j++)
            {
               // cout<<"loop2";
               if(board[j][0+i] == 1 && board[j][1+i] == 1 && board[j][2+i] == 1 && board[j][3+i] == 1 )
               {
                   return P1_WON;
               }

               else if(board[j][0+i] == 2 && board[j][1+i] == 2 && board[j][2+i] == 2 && board[j][3+i] == 2 )
               {
                   return P2_WON;
               }
            }
        }

        for(int i=0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {
                //cout<<"loop3";
                if(board[0+j][0+i] == 1 && board[1+j][1+i] == 1 && board[2+j][2+i] == 1 && board[3+j][3 +i] == 1)
                {
                    return P1_WON;
                }

                else if(board[0+j][0+i] == 2 && board[1+j][1+i] == 2 && board[2+j][2+i] == 2 && board[3+j][3 +i] == 2)
                {
                    return P2_WON;
                }
            }
        }

        for(int i= 0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[0+j][6-i] == 1 && board[1+j][5-i] == 1 && board[2+j][4-i] == 1 && board[3+j][3-i] == 1)
                {
                    return P1_WON;
                }

                else if(board[0+j][6-i] == 2 && board[1+j][5-i] == 2 && board[2+j][4-i] == 2 && board[3+j][3-i] == 2)
                {
                    return P2_WON;
                }

                //cout<<"choot";
            }
        }

        if(isFull())
        {
            return DRAW;
        }

        return UNFINISHED;

    }

    bool col_full(int col)
    {
        for(int i=0;i<6;i++)
            if(board[i][col]== 0)
                return false;

        return true;
    }
    bool isFull()
    {
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<7;j++)
                if(board[i][j] == 0)
                    return false;
        }


        return true;
    }
};


class Node
{
public:
    Board *b;
    int col;
    Node *down;

    Node()
    {
        b = new Board;
        col = 0;
        down = NULL;
        num++;
    }

    ~Node()
    {
        delete b;
        num--;
    }
};
int evaluate(Node *n)
{
    int count_p1 = 0;
    int count_p2 = 0;


        for(int i=0 ;i<3;i++)
        {
            for(int j=0;j<7;j++)
            {
               if(n->b->board[0+i][j] == 1 && n->b->board[1+i][j] == 1 && n->b->board[2+i][j] == 1)
               {
                   count_p1++;
               }

                else if( n->b->board[1+i][j] == 1 && n->b->board[2+i][j] == 1 && n->b->board[3+i][j] == 1 )
               {
                   count_p1++;
               }

               else if(n->b->board[0+i][j] == 1  && n->b->board[2+i][j] == 1 && n->b->board[3+i][j] == 1 )
               {
                   count_p1++;
               }

               else if(n->b->board[0+i][j] == 1 && n->b->board[1+i][j] == 1  && n->b->board[3+i][j] == 1 )
               {
                   count_p1++;
               }
               else if(n->b->board[0+i][j] == 2 && n->b->board[1+i][j] == 2 && n->b->board[2+i][j] == 2 )
               {
                   count_p2++;
               }

                else if( n->b->board[1+i][j] == 2 && n->b->board[2+i][j] == 2 && n->b->board[3+i][j] == 2 )
               {
                   count_p2++;
               }

               else if(n->b->board[0+i][j] == 2  && n->b->board[2+i][j] == 2 && n->b->board[3+i][j] == 2 )
               {
                   count_p2++;
               }

               else if(n->b->board[0+i][j] == 2 && n->b->board[1+i][j] == 2  && n->b->board[3+i][j] == 2 )
               {
                   count_p2++;
               }
        }
        }

        for(int i=0 ;i<4;i++)
        {
            for(int j=0;j<6;j++)
            {
               // cout<<"loop2";
               if(n->b->board[j][0+i] == 1 && n->b->board[j][1+i] == 1 && n->b->board[j][2+i] == 1 )
               {
                   count_p1++;
               }
                else if(n->b->board[j][0+i] == 1 && n->b->board[j][1+i] == 1 && n->b->board[j][3+i] == 1 )
               {
                   count_p1++;
               }

               else if(n->b->board[j][0+i] == 1 && n->b->board[j][3+i] == 1 && n->b->board[j][2+i] == 1 )
               {
                   count_p1++;
               }

               else if(n->b->board[j][3+i] == 1 && n->b->board[j][1+i] == 1 && n->b->board[j][2+i] == 1 )
               {
                   count_p1++;
               }
               else if(n->b->board[j][0+i] == 2 && n->b->board[j][1+i] == 2 && n->b->board[j][2+i] == 2  )
               {
                   count_p2++;
               }

               else if(n->b->board[j][0+i] == 2 && n->b->board[j][1+i] == 2 && n->b->board[j][3+i] == 2 )
               {
                   count_p2++;
               }

               else if(n->b->board[j][0+i] == 2 && n->b->board[j][3+i] == 2 && n->b->board[j][2+i] == 2 )
               {
                   count_p2++;
               }

               else if(n->b->board[j][3+i] == 2 && n->b->board[j][1+i] == 2 && n->b->board[j][2+i] == 2 )
               {
                   count_p2++;
               }
            }
        }

        for(int i=0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {
                //cout<<"loop3";
                if(n->b->board[0+j][0+i] == 1 && n->b->board[1+j][1+i] == 1 && n->b->board[2+j][2+i] == 1 )
                {
                    count_p1++;
                }
                else if(n->b->board[3+j][3+i] == 1 && n->b->board[1+j][1+i] == 1 && n->b->board[2+j][2+i] == 1 )
                {
                    count_p1++;
                }
                else if(n->b->board[0+j][0+i] == 1 && n->b->board[3+j][3+i] == 1 && n->b->board[2+j][2+i] == 1 )
                {
                    count_p1++;
                }
                else if(n->b->board[0+j][0+i] == 1 && n->b->board[1+j][1+i] == 1 && n->b->board[3+j][3+i] == 1 )
                {
                    count_p1++;
                }
                else if(n->b->board[0+j][0+i] == 2 && n->b->board[1+j][1+i] == 2 && n->b->board[2+j][2+i] == 2 )
                {
                    count_p2++;
                }
                else if(n->b->board[3+j][3+i] == 2 && n->b->board[1+j][1+i] == 2 && n->b->board[2+j][2+i] == 2 )
                {
                    count_p2++;
                }
                else if(n->b->board[0+j][0+i] == 2 && n->b->board[3+j][3+i] == 2 && n->b->board[2+j][2+i] == 2 )
                {
                    count_p2++;
                }
                else if(n->b->board[0+j][0+i] == 2 && n->b->board[1+j][1+i] == 2 && n->b->board[3+j][3+i] == 2 )
                {
                    count_p2++;
                }
            }
        }

        for(int i= 0;i<4;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(n->b->board[0+j][6-i] == 1 && n->b->board[1+j][5-i] == 1 && n->b->board[2+j][4-i] == 1 )
                {
                    count_p1++;
                }
                else if(n->b->board[3+j][3-i] == 1 && n->b->board[1+j][5-i] == 1 && n->b->board[2+j][4-i] == 1 )
                {
                    count_p1++;
                }
                else if(n->b->board[0+j][6-i] == 1 && n->b->board[3+j][3-i] == 1 && n->b->board[2+j][4-i] == 1 )
                {
                    count_p1++;
                }
                else if(n->b->board[0+j][6-i] == 1 && n->b->board[1+j][5-i] == 1 && n->b->board[3+j][3-i] == 1 )
                {
                    count_p1++;
                }

                else if(n->b->board[0+j][6-i] == 2 && n->b->board[1+j][5-i] == 2 && n->b->board[2+j][4-i] == 2 )
                {
                    count_p2++;
                }
                else if(n->b->board[3+j][3-i] == 2 && n->b->board[1+j][5-i] == 2 && n->b->board[2+j][4-i] == 2 )
                {
                    count_p2++;
                }
                else if(n->b->board[0+j][6-i] == 2 && n->b->board[3+j][3-i] == 2 && n->b->board[2+j][4-i] == 2 )
                {
                    count_p2++;
                }
                else if(n->b->board[0+j][6-i] == 2 && n->b->board[1+j][5-i] == 2 && n->b->board[3+j][3-i] == 2 )
                {
                    count_p2++;
                }

                //cout<<"choot";
            }
        }

        if(turn == 1)
      return count_p2*100 - count_p1*100 + 10;

      else
        return count_p2*100 - count_p1*100 - 10;
}
int value(Node *&n , int alpha ,int beta,int depth);

int ai(Board b , int player)
{
    Node *n = new Node;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            n->b->board[i][j] = b.board[i][j];
        }
    }
    turn = player;
    value(n,INT_MIN ,INT_MAX , 0);
    Node *temp = n;

    return n->col;
}
int max_value(Node *&n ,int alpha ,int beta , int depth)
{
    if(depth == 8)
        return evaluate(n);
    int v = INT_MIN;
    //n->b->print_board();
    //cout<<endl;
    if(beta <= -100)
        return v;
    int c  = 0;
    for(int i=3;i<7;i = (i+1)%7)
    {
        if(i == 3)
            c++;
        if(c == 2)
            break;
        if(!n->b->col_full(i))
        {
            Node *temp = new Node;
            for(int k=0;k<6;k++)
            {
                for(int j=0;j<7;j++)
                {
                    temp->b->board[k][j] = n->b->board[k][j];
                }
            }
            temp->b->push(i,2);
            turn =0;
            /*if(count < 47)
            {
                temp->b->print_board();
                cout<<endl;
                cout<<"1";
                cout<<endl;
                count++;
            }*/
            int val = value(temp,alpha,beta ,depth +1);
            if(v < val)
            {
                v = val;
                n->col = i;
            }
            if( beta <= v)
            {
                delete temp->b;
                delete temp;
                //temp->~Node();
                //cout<<"hello";
                //delete temp;
                return v;
            }

            if(alpha < v)
            {
                //temp->~Node();
                n->down = temp;
                alpha = v;
            }

            delete temp->b;
            delete temp;
        }
    }
    return v;
}
int min_value(Node *&n ,int alpha ,int beta , int depth)
{
    if(depth == 8)
        return evaluate(n);
    int v = INT_MAX;
    //cout<<"Min";
    int c = 0;
    for(int i=3;i<7;i = (i+1)%7)
    {
        if(i == 3)
            c++;
        if(c == 2)
            break;
        if(!n->b->col_full(i))
        {
            Node *temp = new Node;
            for(int k=0;k<6;k++)
            {
                for(int j=0;j<7;j++)
                {
                    temp->b->board[k][j] = n->b->board[k][j];
                }
            }
            temp->b->push(i,1);
            turn = 1;
           /* if(count1 < 47)
            {
                temp->b->print_board();
                cout<<endl;
                cout<<"2";
                cout<<endl;
                //cout<<endl;
                count1++;
            }*/
            int val = value(temp,alpha,beta,depth +1);
            if(v > val)
            {
                v = val;
                n->col = i;
                //temp->~Node();
                //return v;
            }

            if( alpha >= v)
            {
                delete temp->b;
                delete temp;
                //temp->~Node();
                //cout<<"hi";
                return v;
            }

            if(beta > v)
            {
                n->down = temp;
                beta = v;
            }

            delete temp->b;
            delete temp;
        }
    }
    return v;
}

int value(Node *&n , int alpha ,int beta,int depth)
{
    if(n->b->game_state() == UNFINISHED)
    {
        if(turn == 1)
           return  max_value(n,alpha,beta,depth);

        else if(turn == 0)
            return min_value(n,alpha,beta,depth);
    }
    else if(n->b->game_state() == DRAW)
    {
        return 0;
    }
    else if(n->b->game_state() == P1_WON)
    {
        return -10000 + depth;
    }
    else if(n->b->game_state() == P2_WON)
    {
        return 10000 - depth;
    }
}
int main()
{
    Board b;
    int i = 1;
    int x;
    while(b.game_state() == UNFINISHED)
        {
            cout<<"player "<<i<<" Turn : "<<endl;
            b.print_board();
            cout<<"Enter col to insert"<<endl;
            if(i == 2)
            cin>>x;
            if(i==2)
            {
                b.push(x,1);
                //int col = ai(b,0);
                //b.push(col,1);
                i = 1;
            }

            else if(i == 1)
            {
                int col = ai(b,1);
                b.push(col,2);
               i=2;
            }

        }
        if(b.game_state() == P1_WON)
            cout<<"Game Ended : P1 won" <<endl;
        else if(b.game_state() == P2_WON)
            cout<<"Game Ended : P2 won" <<endl;
        else if(b.game_state() == DRAW)
            cout<<"Game Ended : Draw"<<endl;
   // b.print_board();
}


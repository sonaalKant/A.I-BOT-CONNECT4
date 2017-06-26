#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<limits.h>
#include<utility>
#include<cmath>
#include<stdlib.h>
using namespace std;
int VALUE[8][8]= {
                {0,  0,  0,  0,  0,  0,  0,  0},
                {0,  0,  0,  0,  0,  0,  0,  0},
                {0,  5, 10, 15, 15, 10,  5,  0},
                {0,  5, 15, 20, 20, 15,  5,  0},
                {0,  5, 15, 20, 20, 15,  5,  0},
                {0,  5, 10, 15, 15, 10,  5,  0},
                {0,  0,  0,  0,  0,  0,  0,  0},
                {0,  0,  0,  0,  0,  0,  0,  0},
            };

int check_black = 0;
int check_white = 0;
enum Result { W_WON, B_WON, DRAW, UNFINISHED };
int turn;
enum Gitti {PAWN , KING , QUEEN , BISHOP , KNIGHT , ROOK};
class piece;
map<string,pair<int ,int> > m;
map<pair<int ,int> , piece*> hm;
class piece
{
public:
    string name;
    char color;
    bool dead;
    int posX;
    int posY;
    Gitti g = PAWN;
    piece(){}
    piece(char col , int x ,int y , string n)
    {
        color = col;
        name = n;
        posX = x;
        posY = y;
        dead = false;
        hm[make_pair(x,y)] = this;
    }

    virtual char check()
    {
        //cout<<"i am pawn\n";
        if(this->color == 'B')
        {
            int x = this->posX +1;
            int y = this->posY + 1;
            int z = this->posY -1;

            if(x < 8 && y < 8)
            {
                if(hm.find(make_pair(x,y)) != hm.end())
                {
                    piece *k = hm[make_pair(x,y)];
                    cout<<k->name<<endl;
                    if(k->g == KING && k->color == 'W')
                        return 'W';
                }

            }

            if(x < 8 && z >= 0)
            {
                if(hm.find(make_pair(x,z)) != hm.end())
                {
                    piece *k = hm[make_pair(x,z)];
                    if(k->g == KING && k->color == 'W')
                        return 'W';
                }
            }
        }

        if(this->color == 'W')
        {
            int x = this->posX - 1;
            int y = this->posY + 1;
            int z = this->posY -1;

            if(x >= 0 && y < 8)
            {
                if(hm.find(make_pair(x,y)) != hm.end())
                {
                    piece *k = hm[make_pair(x,y)];
                    if(k->g == KING && k->color == 'B')
                        return 'B';
                }

            }

            if(x >= 0 && z >= 0)
            {
                if(hm.find(make_pair(x,z)) != hm.end())
                {
                    piece *k = hm[make_pair(x,z)];
                    if(k->g == KING && k->color == 'B')
                        return 'B';
                }
            }
        }


        return 'N';
    }

    virtual bool isValid(int x , int y , map<pair<int ,int> , piece*> hm_node = hm)
    {
        if(this->color == 'W')
        {
            if(x == posX - 1 && x >= 0 && y == posY && hm_node.find(make_pair(x,y)) == hm_node.end())
                return true;

            if(x == posX-1 && (y == posY + 1 || y == posY - 1) && y >= 0 && x >=  0 && y < 8)
            {
                if(hm_node.find(make_pair(x,y)) == hm_node.end())
                    return false;

                if( hm_node[make_pair(x,y)]->color == 'B')
                    return true;

                return false;
            }
        }
        if(this->color == 'B')
        {
            //cout<<"Black"<<x<<" "<<y<<endl;
            if(x == posX + 1 && x < 8 && y == posY && hm_node.find(make_pair(x,y)) == hm_node.end())
                return true;

            if(x == posX +1 && (y == posY + 1 || y == posY - 1) && y >= 0 && x < 8 && y < 8)
            {
                if(hm_node.find(make_pair(x,y)) == hm_node.end())
                    return false;
                if( hm_node[make_pair(x,y)]->color == 'W')
                    return true;

                return false;
            }
        }

        return false;
    }


    virtual vector<pair<int,int> > make_move(map<pair<int ,int> , piece*> hm_node)
    {
        vector<pair<int,int> > v;
        //cout<<posX<<" "<<posY;
        if(isValid(posX + 1,posY + 1,hm_node))
        {
            v.push_back(make_pair(posX + 1,posY + 1));
        }

        if(isValid(posX+1,posY,hm_node))
        {
            v.push_back(make_pair(posX + 1,posY));
        }

        if(isValid(posX - 1,posY + 1,hm_node))
        {
            v.push_back(make_pair(posX - 1,posY + 1));
        }

        if(isValid(posX + 1,posY - 1,hm_node))
        {
            v.push_back(make_pair(posX + 1,posY - 1));
        }

        if(isValid(posX-1,posY ,hm_node))
        {
            v.push_back(make_pair(posX - 1,posY ));
        }

        if(isValid(posX - 1,posY - 1,hm_node))
        {
            v.push_back(make_pair(posX - 1,posY - 1));
        }

        //cout<<v.size();
        return v;
    }
};

class rook : piece
{
public:
    rook(char col , int x,int y , string n) : piece(col,x,y,n){g = ROOK;}

    rook(char col ,int x,int y) : piece()
    {
        posX = x;
        posY = y;
        color = col;
    }
    char check()
    {
        //cout<<"i am rook\n";

           int x = this->posX + 1;
           int y = this->posY;

           while(x < 8)
           {
               if(hm.find(make_pair(x,y)) != hm.end())
               {
                   piece *k = hm[make_pair(x,y)];

                   if(k->color == this->color)
                    break;
                   if(k->g == KING && k->color != this->color)
                    return k->color;
               }

               x++;
           }
           x = this->posX - 1 ;
            y = this->posY;
           while(x >= 0)
           {
               if(hm.find(make_pair(x,y)) != hm.end())
               {
                   piece *k = hm[make_pair(x,y)];

                   if(k->color == this->color)
                    break;
                   if(k->g == KING && k->color != this->color)
                    return k->color;
               }

               x--;
           }
           x = this->posX ;
            y = this->posY + 1;
           while(y < 8)
           {
               if(hm.find(make_pair(x,y)) != hm.end())
               {
                   piece *k = hm[make_pair(x,y)];

                   if(k->color == this->color)
                    break;
                   if(k->g == KING && k->color != this->color)
                    return k->color;
               }

               y++;
           }
           x = this->posX ;
            y = this->posY -1;
           while(y >= 0)
           {
               if(hm.find(make_pair(x,y)) != hm.end())
               {
                   piece *k = hm[make_pair(x,y)];

                   if(k->color == this->color)
                    break;
                   if(k->g == KING && k->color != this->color)
                    return k->color;
               }

               y--;
           }

        return 'N';
    }



    bool isValid(int x ,int y , map<pair<int ,int> , piece*> hm_node = hm)
    {
        if(x < 0 || y < 0 || x > 7 || y > 7)
            return false;

        if(posX == x)
        {
           // cout<<"In x";
            if(posY > y)
            {
                int i;
                for( i = posY-1 ;i > y ;i--)
                {
                    if(hm_node.find(make_pair(x,i)) != hm_node.end() )
                    {
                        //cout<<hm[make_pair(x,i)]->name;
                        if(i != y )
                        {
                            //cout<<hm[make_pair(x,i)]->name;
                            break;
                        }

                        if(hm_node[make_pair(x,i)]->color == this->color)
                            return false;
                    }
                }
                if(hm_node.find(make_pair(x,i)) != hm_node.end() && hm_node[make_pair(x,i)]->color == this->color)
                    return false;
                if(i == y  )
                    return true;
            }

            if(posY < y)
            {
                int i;
                for( i = posY+1 ;i < y ;i++)
                {
                    if(hm_node.find(make_pair(x,i)) != hm_node.end() )
                    {
                        //cout<<hm[make_pair(x,i)]->name;
                        if(i != y )
                        {
                           // cout<<hm[make_pair(x,i)]->name;
                            break;
                        }
                         if(hm_node[make_pair(x,i)]->color == this->color)
                            return false;
                    }
                }

                if(hm_node.find(make_pair(x,i)) != hm_node.end() && hm_node[make_pair(x,i)]->color == this->color)
                    return false;
                if(i == y )
                    return true;
            }
        }

        if(posY == y)
        {
            //cout<<"in y";
            if(posX > x)
            {
               // cout<<"in y in x";
                int i;
                for( i = posX - 1 ;i > x ;i--)
                {
                    //cout<<i<<" " <<x;
                    if(hm_node.find(make_pair(i,y)) != hm_node.end() )
                    {
                        //cout<<"hi";
                        //cout<<hm[make_pair(i,y)]->name;
                        if(i != x )
                        {
                            //cout<<hm[make_pair(i,y)]->name;
                            break;
                        }

                        if( hm_node[make_pair(i,y)]->color == this->color)
                            return false;
                    }
                }

                //cout<<i<<" "<<x;
                if(hm_node.find(make_pair(i,y)) != hm_node.end() && hm_node[make_pair(i,y)]->color == this->color)
                    return false;
                if(i == x)
                {
                    //cout<<"chut";
                     return true;
                }
            }

            if(posX < x)
            {
                int i;
                for( i = posX+1 ;i < x ;i++)
                {
                    if(hm_node.find(make_pair(i,y)) != hm_node.end() )
                    {
                        //cout<<hm[make_pair(i,y)]->name;
                        if(i != x )
                        {
                            //cout<<hm[make_pair(i,y)]->name;
                            break;
                        }
                        if( hm_node[make_pair(i,y)]->color == this->color)
                            return false;
                    }
                }

                if( hm_node.find(make_pair(i,y)) != hm_node.end() && hm_node[make_pair(i,y)]->color == this->color)
                    return false;
                if(i == x  )
                    return true;
            }
        }

        return false;
    }

    vector<pair<int,int> > make_move(map<pair<int ,int> , piece*> hm_node)
    {
        int x = this->posX + 1;
           int y = this->posY;
        vector<pair<int,int> > v;
           while(x < 8)
           {
               if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
                else
                    break;
               x++;
           }
           x = this->posX - 1 ;
            y = this->posY;
           while(x >= 0)
           {
               if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
                else
                    break;
               x--;
           }
           x = this->posX ;
            y = this->posY + 1;
           while(y < 8)
           {
               if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
                else
                    break;
               y++;
           }
           x = this->posX ;
            y = this->posY -1;
           while(y >= 0)
           {
               if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
                else
                    break;

               y--;
           }

           return v;
    }
};

class bishop : piece
{
public:
    bishop(char col , int x,int y,string n) : piece(col,x,y,n){g = BISHOP;}

    // temporary constructor
    bishop(char col ,int x,int y)
    {
        posX = x;
        posY = y;
        color = col;
    }
    char check()
    {
        //cout<<"i am bishop\n";

        int x = this->posX + 1;
        int y = this->posY + 1;

        while(x < 8 && y < 8)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];

               if(k->color == this->color)
                break;
               if(k->g == KING && k->color != this->color)
                return k->color;
            }

            x++;
            y++;
        }

        x = this->posX -1;
        y = this->posY -1;
        while(x >= 0 && y >= 0)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];

               if(k->color == this->color)
                break;
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
            x--;
            y--;
        }

        x = this->posX +1;
        y = this->posY -1;

        while(x < 8 && y >= 0)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];

               if(k->color == this->color)
                break;
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
            x++;
            y--;
        }

        x = this->posX -1;
        y = this->posY +1;

        while(x >= 0 && y < 8)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];

               if(k->color == this->color)
                break;
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
            x--;
            y++;
        }

        return 'N';
    }


    bool isValid(int x,int y , map<pair<int ,int> , piece*> hm_node = hm)
    {
        if(x < 0 || y < 0 || x > 7 || y > 7)
            return false;

        if(posX > x && posY > y)
        {
            int i,j;
            for( i=posX-1, j= posY-1 ; i>x &&j>y; i--,j--)
            {
                if(hm_node.find(make_pair(i,j)) != hm_node.end() )
                    {
                        if(i != x && j != y)
                        {
                            break;
                        }
                        if( hm_node[make_pair(i,j)]->color == this->color)
                            return false;
                    }
            }
            if( hm_node.find(make_pair(i,j)) != hm_node.end()&& hm_node[make_pair(i,j)]->color == this->color)
                return false;
            if(i == x  && j== y)
                return true;
        }
        if(posX < x && posY < y)
        {
            int i,j;
            for( i=posX+1, j= posY+1 ; i<x &&j<y; i++,j++)
            {
                if(hm_node.find(make_pair(i,j)) != hm_node.end() )
                    {
                        if(i != x && j != y)
                        {
                            break;
                        }
                        if( hm_node[make_pair(i,j)]->color == this->color)
                            return false;
                    }
            }
            if( hm_node.find(make_pair(i,j)) != hm_node.end() &&hm_node[make_pair(i,j)]->color == this->color)
                return false;
            if(i == x  && j== y)
                return true;
        }
        if(posX < x && posY > y)
        {
            int i,j;
            for( i=posX+1, j= posY-1 ; i<x &&j>y; i++,j--)
            {
                if(hm_node.find(make_pair(i,j)) != hm_node.end() )
                    {
                        if(i != x && j != y)
                        {
                            break;
                        }
                        if( hm_node[make_pair(i,j)]->color == this->color)
                            return false;
                    }
            }
            if( hm_node.find(make_pair(i,j)) != hm_node.end() && hm_node[make_pair(i,j)]->color == this->color)
                return false;
            if(i == x  && j== y)
                return true;
        }
        if(posX > x && posY < y)
        {
            int i,j;
            for( i=posX-1, j= posY+1 ; i>x &&j<y; i--,j++)
            {
                if(hm_node.find(make_pair(i,j)) != hm_node.end() )
                    {
                        if(i != x && j != y)
                        {
                            break;
                        }
                        if( hm_node[make_pair(i,j)]->color == this->color)
                            return false;
                    }
            }
            if( hm_node.find(make_pair(i,j)) != hm_node.end() && hm_node[make_pair(i,j)]->color == this->color)
                return false;
            if(i == x  && j== y)
                return true;
        }
        return false;
    }

    vector<pair<int,int> > make_move(map<pair<int ,int> , piece*> hm_node)
    {
        int x,y;
        vector<pair<int,int> > v;
         x = this->posX + 1;
         y = this->posY + 1;

        while(x < 8 && y < 8)
        {

            if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
            else
                break;
            x++;
            y++;
        }

        x = this->posX -1;
        y = this->posY -1;
        while(x >= 0 && y >= 0)
        {
            if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
            else
                break;
            x--;
            y--;
        }

        x = this->posX +1;
        y = this->posY -1;

        while(x < 8 && y >= 0)
        {
            if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
            else
                break;
            x++;
            y--;
        }

        x = this->posX -1;
        y = this->posY +1;

        while(x >= 0 && y < 8)
        {
            if(isValid(x,y,hm_node))
                    v.push_back(make_pair(x,y));
            else
                break;
            x--;
            y++;
        }

        return v;
    }
};

class knight : piece
{
public:

    knight(char col , int x,int y,string n) : piece(col,x,y,n){g = KNIGHT;}

    char check()
    {
        //cout<<"i am knight\n";

        int x,y;

        x = this->posX+2;
        y =this->posY + 1;

        if(x < 8 && y < 8)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX + 2;
        y =this->posY -1;

        if(x < 8 && y>=0)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX + 1;
        y =this->posY + 2;

        if(x < 8 && y < 8)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX - 1;
        y =this->posY + 2;

        if(x >= 0 && y < 8)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX - 2;
        y =this->posY + 1;

        if(x >= 0 && y < 8)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX - 2;
        y =this->posY -1;

        if(x >= 0 && y >= 0)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX - 1;
        y =this->posY - 2;

        if(x >= 0 && y >= 0)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX + 1;
        y =this->posY - 2;

        if(x < 8 && y >= 0)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }
        return 'N';
    }


    bool isValid(int x,int y , map<pair<int ,int> , piece*> hm_node = hm)
    {
        if(x < 0 || y < 0 || x > 7 || y > 7)
            return false;

        if(hm_node.find(make_pair(x,y)) != hm_node.end() && hm_node[make_pair(x,y)]->color == this->color)
        return false;


        if((abs(posX - x) == 2 && abs(posY-y) == 1) || (abs(posX - x) == 1 && abs(posY-y) == 2))
            return true;

       return false;
    }

    vector<pair<int,int> > make_move(map<pair<int ,int> , piece*> hm_node)
    {
        int x,y;
        vector<pair<int,int> > v;
        x = this->posX+2;
        y =this->posY + 1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX + 2;
        y =this->posY -1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX + 1;
        y =this->posY + 2;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX - 1;
        y =this->posY + 2;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));;

        x = this->posX - 2;
        y =this->posY + 1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX - 2;
        y =this->posY -1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX - 1;
        y =this->posY - 2;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX + 1;
        y =this->posY - 2;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        return v;
    }
};

class king : piece
{
public:

    king(char col , int x,int y,string n) : piece(col,x,y,n){g = KING;}

    char check()
    {
        //cout<<"i am king\n";

        int count1 = 0;
        for(int x = this->posX ; x < 8 && count1 < 2;x++,count1++)
        {
            int count = 0;
            for(int y = this->posY ;y<8 && count < 2;y++,count++)
            {
                if(hm.find(make_pair(x,y)) != hm.end())
                {
                    piece *k = hm[make_pair(x,y)];
                   if(k->g == KING && k->color != this->color)
                    return k->color;
                }
            }
        }

        count1 = 0;
        for(int x = this->posX ; x >= 0 && count1 < 2;x--,count1++)
        {
            int count = 0;
            for(int y = this->posY ;y>=0 && count < 2;y--,count++)
            {
                if(hm.find(make_pair(x,y)) != hm.end())
                {
                    piece *k = hm[make_pair(x,y)];
                   if(k->g == KING && k->color != this->color)
                    return k->color;
                }
            }
        }

        int x = this->posX +1;
        int y = this->posY - 1;

        if(x < 8 && y>=0)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }

        x = this->posX-1;
        y = this->posY +1;

        if(x >=0  && y < 8)
        {
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k = hm[make_pair(x,y)];
               if(k->g == KING && k->color != this->color)
                return k->color;
            }
        }
        return 'N';
    }


    bool isValid(int x,int y , map<pair<int ,int> , piece*> hm_node = hm)
    {
        if(x < 0 || y < 0 || x > 7 || y > 7)
            return false;

       if(abs(posX -x) > 1 || abs(posY - y) > 1)
        return false;

        if(hm_node.find(make_pair(x,y)) != hm_node.end() && hm_node[make_pair(x,y)]->color == this->color)
        return false;

       return true;
    }

    vector<pair<int,int> > make_move(map<pair<int ,int> , piece*> hm_node)
    {
        int x,y;
        vector<pair<int,int> > v;
        x = this->posX+1;
        y =this->posY + 1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX +1;
        y =this->posY -1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX + 1;
        y =this->posY ;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX - 1;
        y =this->posY ;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));;

        x = this->posX ;
        y =this->posY + 1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX ;
        y =this->posY -1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX - 1;
        y =this->posY - 1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        x = this->posX + 1;
        y =this->posY - 1;

        if(isValid(x,y,hm_node))
            v.push_back(make_pair(x,y));

        return v;
    }
};

class queen : public piece
{
    public:

    queen(char col , int x,int y, string n) : piece(col,x,y,n){g = QUEEN;}


    char check()
    {
        //cout<<"i am queen\n";
        bishop *b = new bishop(this->color,this->posX,this->posY);
        rook *r = new rook(this->color,this->posX,this->posY);
        char c = b->check();
        char c1 = r->check();

        if(c != 'N')
            return c;
        if(c1 != 'N')
            return c1;
        return 'N';
    }

    bool isValid(int x,int y , map<pair<int ,int> , piece*> hm_node = hm)
    {
        if(x < 0 || y < 0 || x > 7 || y > 7)
            return false;

        bishop *b = new bishop(this->color,this->posX,this->posY);
        rook *r = new rook(this->color,this->posX,this->posY);
        if(b->isValid(x,y) || r->isValid(x,y))
            return true;

        return false;
    }

    vector<pair<int,int> > make_move(map<pair<int ,int> , piece*> hm_node)
    {
        bishop *b = new bishop(this->color,this->posX,this->posY);
        rook *r = new rook(this->color,this->posX,this->posY);
        vector<pair<int,int> > v1 = b->make_move(hm_node);
        vector<pair<int,int> > v2 = r->make_move(hm_node);

        vector<pair<int,int> > :: iterator it;
        for(it = v2.begin();it != v2.end();it++)
        {
            v1.push_back(*it);
        }

        return v1;
    }
};

class Board
{
public:
    string board[8][8] = {  {"BrL","BkL","BbL","B_Q","B_K","BbR","BkR","BrR"},
                            {"Bp1","Bp2","Bp3","Bp4","Bp5","Bp6","Bp7","Bp8"},
                            {"---","---","---","---","---","---","---","---"},
                            {"---","---","---","---","---","---","---","---"},
                            {"---","---","---","---","---","---","---","---"},
                            {"---","---","---","---","---","---","---","---"},
                            {"Wp1","Wp2","Wp3","Wp4","Wp5","Wp6","Wp7","Wp8"},
                            {"WrL","WkL","WbL","W_Q","W_K","WbR","WkR","WrR"}
                        };

    void initialize()
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(board[i][j].compare("  "))
                {
                    m[board[i][j]] = make_pair(i,j);
                }
            }
        }

        rook *BrL = new rook('B',0,0 ,"BrL");
        rook *BrR = new rook('B',0,7,"BrR");
        rook *WrL = new rook('W',7,0,"WrL");
        rook *WrR = new rook('W',7,7,"WrR");

        knight *BkL = new knight('B',0,1,"BkL");
        knight *BkR = new knight('B',0,6,"BkR");
        knight *WkL = new knight('W',7,1,"WkL");
        knight *WkR = new knight('W',7,6,"WkR");

        bishop *BbL = new bishop('B',0,2,"BbL");
        bishop *BbR = new bishop('B',0,5,"BbR");
        bishop *WbL = new bishop('W',7,2,"WbL");
        bishop *WbR = new bishop('W',7,5,"WbR");

        king *BK = new king('B',0,4,"B_K");
        king *WK = new king('W',7,4,"W_K");

        queen *BQ = new queen('B',0,3,"B_Q");
        queen *WQ = new queen('W',7,3,"B_Q");

        piece *p1 = new piece('B',1,0,"Bp1");
        piece *p2 = new piece('B',1,1,"Bp2");
        piece *p3 = new piece('B',1,2,"Bp3");
        piece *p4 = new piece('B',1,3,"Bp4");
        piece *p5 = new piece('B',1,4,"Bp5");
        piece *p6 = new piece('B',1,5,"Bp6");
        piece *p7 = new piece('B',1,6,"Bp7");
        piece *p8 = new piece('B',1,7,"Bp8");

        piece *p9 = new piece('W',6,0,"Wp1");
        piece *p10 = new piece('W',6,1,"Wp2");
        piece *p11 = new piece('W',6,2,"Wp3");
        piece *p12 = new piece('W',6,3,"Wp4");
        piece *p13 = new piece('W',6,4,"Wp5");
        piece *p14 = new piece('W',6,5,"Wp6");
        piece *p15 = new piece('W',6,6,"Wp7");
        piece *p16 = new piece('W',6,7,"Wp8");

    }
    void print_board()
    {
        for(int i=0;i<8;i++)
        {
            cout<<i<<"   ";
            for(int j=0;j<8;j++)
            {
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    Result game_state()
    {
        if(m.find("W_K") == m.end())
            return B_WON;
        if(m.find("B_K") == m.end())
            return W_WON;

        return UNFINISHED;
    }

};

char is_check()
{
     map<pair<int,int> , piece*> :: iterator it;

        for( it = hm.begin();it!=hm.end();it++)
        {
            piece *k = it->second;
             char c = k->check();
             //cout<<c;
             if( c != 'N')
                return c;
        }
}



class Node
{
public:

    Board *b;
    map<string,pair<int ,int> > m_node;
    map<pair<int ,int> , piece*> hm_node;
    int moveX;
    int moveY;
    piece *moved;
    Node *down;


};
double value(Node *&n , int alpha ,int beta,int depth);
void play_move(Node *&n, piece *l ,int x ,int y);
void ai(Board b , string &s ,int &x ,int &y)
{
   // cout<<"A.I"<<endl;
    Node *n = new Node;
    n->b = new Board;
    n->m_node =  map<string,pair<int ,int> >(m);
    n->hm_node =  map<pair<int ,int> , piece*>(hm);

    //cout<<"A.I_1"<<endl;
    for(int k=0;k<8;k++)
    {
        for(int j=0;j<8;j++)
        {
            n->b->board[k][j] = b.board[k][j];
            //cout<<k<<" "<<j;
        }
    }
   // cout<<"A.I_2"<<endl;
    turn = 1;
    double v = value(n,INT_MIN ,INT_MAX , 0);
    cout<<v<<endl;
    //cout<<"AI_"<<endl;
    //Node *temp = n;
    /*while(temp!= NULL)
    {
        temp->b->print_board();
        cout<<endl;
        temp = temp->down;
    }*/

    x = n->moveX;
    y = n->moveY;
    s = n->moved->name;

    delete n->b;
    delete n;
    //cout<<"why?";
}

double evaluate(Node *&n)
{
    int wK = 0,wQ = 0,wp = 0,wk = 0,wb = 0,wr =0;
    int bK = 0,bQ = 0,bp = 0,bk = 0,bb = 0,br =0;
    int Wpos= 0,Bpos = 0;
    map<pair<int,int> , piece*> :: iterator it;
    for(it = n->hm_node.begin();it!=n->hm_node.end();it++)
    {
        piece *k = it->second;
        if(k->color == 'B')
        {
            if(k->g == PAWN)
                bp++;
            else if(k->g == KING)
                bK++;
            else if(k->g == QUEEN)
            {
                Bpos += VALUE[k->posX][k->posY];
                bQ++;
            }
            else if(k->g == KNIGHT)
            {
                Bpos += VALUE[k->posX][k->posY];
                bk++;
            }
            else if(k->g == BISHOP)
            {
                Bpos += VALUE[k->posX][k->posY];
                bb++;
            }
            else if(k->g == ROOK)
            {
                Bpos += VALUE[k->posX][k->posY];
                br++;
            }
        }

        else
        {
            if(k->g == PAWN)
                wp++;
            else if(k->g == KING)
                wK++;
            else if(k->g == QUEEN)
            {
                Wpos -= VALUE[k->posX][k->posY];
                wQ++;
            }
            else if(k->g == KNIGHT)
            {
                Wpos -= VALUE[k->posX][k->posY];
                wk++;
            }
            else if(k->g == BISHOP)
            {
                Wpos -= VALUE[k->posX][k->posY];
                wb++;
            }
            else if(k->g == ROOK)
            {
                Wpos -= VALUE[k->posX][k->posY];
                wr++;
            }
        }
    }

    double value = 200*(bK - wK) + 20*(bQ - wQ) + 10*(br - wr) + 8*(bb - wb + bk - wk) + 2*(bp - wp) + 0.05*Bpos + 0.05*Wpos;

    return value;
}

double max_value(Node *&n ,int alpha ,int beta , int depth)
{
    //cout<<"max"<<endl;
    if(depth == 4)
    {
        return evaluate(n);
    }

    int game_value = INT_MIN;
   // int count =0;
    map<pair<int,int> , piece*> :: iterator it;

        for( it = n->hm_node.begin();it!=n->hm_node.end();it++)
        {
           // count++;
            //cout<<it->second->name<<"hi"<<endl;
            if(  it->second->color == 'B')
            {

                //cout<<it->second->name;
                vector<pair<int,int> > v = it->second->make_move(n->hm_node);
                //cout<<"max1"<<endl;
                //cout<<v.size()<<endl;
                Node *temp = new Node;
                temp->b = new Board;
                for(int k=0;k<8;k++)
                {
                    for(int j=0;j<8;j++)
                    {
                        temp->b->board[k][j] = n->b->board[k][j];
                    }
                }
                //cout<<"max_2"<<endl;
                temp->m_node = map<string,pair<int ,int> >(n->m_node.begin(),n->m_node.end());
                temp->hm_node = map<pair<int ,int> , piece*>(n->hm_node.begin(),n->hm_node.end());

                piece *h = it->second;
                for(int i=0;i<v.size();i++)
                {
                    //cout<<"max_4"<<endl;
                    //cout<<"wrong_move"<<endl;
                    pair<int,int> p = v[i];
                    int prevX = h->posX;
                    int prevY = h->posY;
                    play_move(temp,h,p.first,p.second);
                    // Reverse back all the values of pieces you made changes to

                    turn = 0;
                    int val = value(temp,alpha,beta,depth+1);
                    //cout<<"Back"<<endl;
                    h->posX = prevX;
                    h->posY = prevY;
                    if(game_value < val)
                    {
                        game_value = val;
                        n->moveX = p.first;
                        n->moveY = p.second;
                        n->moved = h;
                    }
                    //cout<<"wrong_move1"<<endl;
                    if( beta <= game_value)
                    {
                        //cout<<"wrong_move2"<<endl;
                        delete temp->b;
                        delete temp;
                        return game_value;
                    }

                    if(alpha < game_value)
                    {
                        //cout<<"wrong_move3"<<endl;
                        alpha = game_value;
                    }
                    //cout<<"wrong_max"<<endl;
                }

                delete temp->b;
                delete temp;
                //cout<<"max_3"<<endl;

            }
        }

        //cout<<"worng_return"<<endl;
        return game_value;
}
double min_value(Node *&n ,int alpha ,int beta , int depth)
{
    //cout<<"min"<<endl;
    if(depth == 4)
    {
        return evaluate(n);
    }

    int game_value = INT_MAX;
    map<pair<int,int> , piece*> :: iterator it;

        for( it = n->hm_node.begin();it!=n->hm_node.end();it++)
        {
            if( it->second->color == 'W')
            {
                vector<pair<int,int> > v = it->second->make_move(n->hm_node);

                Node *temp = new Node;
                temp->b = new Board;
                for(int k=0;k<8;k++)
                {
                    for(int j=0;j<8;j++)
                    {
                        temp->b->board[k][j] = n->b->board[k][j];
                    }
                }

                temp->m_node = map<string,pair<int ,int> >(n->m_node.begin(),n->m_node.end());
                temp->hm_node = map<pair<int ,int> , piece*>(n->hm_node.begin(),n->hm_node.end());

                piece *h = it->second;
                for(int i=0;i<v.size();i++)
                {
                    pair<int,int> p = v[i];
                    int prevX = h->posX;
                    int prevY = h->posY;
                    play_move(temp,h,p.first,p.second);
                    // Reverse back all the values of pieces you made changes to
                    turn = 1;
                    int val = value(temp,alpha,beta,depth+1);
                    //cout<<"Back _ min"<<endl;
                    h->posX = prevX;
                    h->posY = prevY;
                    //cout<<"wrong";
                    if(game_value > val)
                    {
                        game_value = val;
                        n->moveX = p.first;
                        n->moveY = p.second;
                        n->moved = h;
                    }
                    if( alpha >= game_value)
                    {
                        delete temp->b;
                        delete temp;
                        return game_value;
                    }

                    if(beta > game_value)
                    {
                        beta = game_value;
                    }
                }

                delete temp->b;
                delete temp;

            }
        }

        return game_value;
}


double value(Node *&n , int alpha ,int beta,int depth)
{
    //cout<<"value"<<endl;
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
    else if(n->b->game_state() == W_WON)
    {
        return -1000 + depth;
    }
    else if(n->b->game_state() == B_WON)
    {
        return 1000 - depth;
    }
}


void play_move(Node *&n, piece *l ,int x ,int y)
{
    //cout<<"play"<<endl;
    string s = l->name;
    int pX = l->posX;
    int pY = l->posY;
    pair<int,int> p = make_pair(pX,pY);
    n->m_node[s] = make_pair(x,y);
    if(n->hm_node.find(make_pair(x,y)) != n->hm_node.end())
    {
        piece *k1 = n->hm_node[make_pair(x,y)];
        k1->dead = true;
        n->hm_node.erase(make_pair(x,y));
        n->m_node.erase(k1->name);
    }
    //cout<<p.first<<" " <<p.second;
    string temp = "---";

    piece *k = n->hm_node[p];
    n->hm_node.erase(p);
    if(k != NULL)
    {
        k->posX = x;
        k->posY = y;
        n->hm_node[make_pair(x,y)] = k;
        n->b->board[x][y].replace(n->b->board[x][y].begin(),n->b->board[x][y].end(),n->b->board[p.first][p.second]);
        n->b->board[p.first][p.second].replace(n->b->board[p.first][p.second].begin(),n->b->board[p.first][p.second].end(),temp);

    }

}
int main()
{

    Board b;
    b.initialize();
    //b.print_board();
   // b.game_state();

    //pair<int,int> pp = m["WrR"];
    //piece *k = hm[pp];
    //cout<<k->g;
   // k->check();
    int x,y;
    string s;
    int i =1;
    while(b.game_state() == UNFINISHED)
    {
        cout<<"player "<<i<<" Turn : "<<endl;
        if(i == 1)
        {
            b.print_board();
            cout<<"Enter the piece name"<<endl;
            cin>>s;
            cout<<"Enter the valid position "<<endl;
            cin>>x>>y;
        }
        if(i==1)
        {
            pair<int,int> p = m[s];
            piece *l = hm[p];
            if(!l->isValid(x,y) || l->color != 'W')
            {
                cout<<"WRONG MOVE!!!\n";
                continue;
            }
            m[s] = make_pair(x,y);
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k1 = hm[make_pair(x,y)];
                k1->dead = true;
                hm.erase(make_pair(x,y));
                m.erase(k1->name);
            }
            //cout<<p.first<<" " <<p.second;
            string temp = "---";
            piece *k = hm[p];
            hm.erase(p);
            k->posX = x;
            k->posY = y;
            hm[make_pair(x,y)] = k;
            b.board[x][y].replace(b.board[x][y].begin(),b.board[x][y].end(),b.board[p.first][p.second]);
            b.board[p.first][p.second].replace(b.board[p.first][p.second].begin(),b.board[p.first][p.second].end(),temp);
            i = 2;
        }

        else if(i == 2)
        {
            ai(b,s,x,y);
           // cout<<s<<" "<<x<<" "<<y;
            pair<int,int> p = m[s];
           // cout<<p.first<<" "<<p.second;
            piece *l = hm[p];
            //cout<<l->posX<<" "<<l->posY;

            if(!l->isValid(x,y) || l->color != 'B')
            {
                cout<<"WRONG MOVE!!!\n";
               // cout<<x<<" "<<y;
                //cout<<"whyyy";
                continue;
            }

            m[s] = make_pair(x,y);
            if(hm.find(make_pair(x,y)) != hm.end())
            {
                piece *k1 = hm[make_pair(x,y)];
                k1->dead = true;
                hm.erase(make_pair(x,y));
                m.erase(k1->name);
            }
           // cout<<"hey3"<<endl;
            string temp = "---";
            piece *k = hm[p];
            hm.erase(p);
            k->posX = x;
            k->posY = y;
            //cout<<"hey4"<<endl;
            hm[make_pair(x,y)] = k;
            b.board[x][y].replace(b.board[x][y].begin(),b.board[x][y].end(),b.board[p.first][p.second]);
            b.board[p.first][p.second].replace(b.board[p.first][p.second].begin(),b.board[p.first][p.second].end(),temp);
            //cout<<"hey5";
            i=1;
        }
        char c = is_check();
        if( c == 'B')
            cout<<"****CHECK ON BLACK****\n";
        else if(c == 'W')
            cout<<"****CHECK ON WHITE****\n";

    }
    pair<int,int> p = m["WK "];
    cout<<p.first<<" " <<p.second;
    if(b.game_state() == W_WON)
        cout<<"Game Ended : W won" <<endl;
    else if(b.game_state() == B_WON)
        cout<<"Game Ended : B won" <<endl;
    else if(b.game_state() == UNFINISHED)
        cout<<"Game Ended : Draw"<<endl;

}


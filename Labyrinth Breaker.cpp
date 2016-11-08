#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*-------------------------------const variable-------------------------------*/
const int DIMX(8);
const int DIMY(8);
const string RIGHT("right");
const string LEFT("left");
const string UP("up");
const string DOWN("down");
const string AHEAD("ahead");


const string labyrinth[DIMX][DIMY] = {{"RD",    "LR",    "LRD",    "LRD",    "LRD",    "LR",    "LD",    "D"},
 {"UD",    "R",    "LUD",    "U",    "UD",    "D",    "RUD",    "LU"},
 {"UD",    "D",    "U",    "D",    "UD",    "UD",    "U",    "D"},
 {"UD",    "UD",    "RD",    "LU",    "U",    "RUD",    "LRD",    "LUD"},
 {"UD",    "UD",    "LU",    "LRD",    "LRD",    "LU",    "UD",    "U"},
 {"UD",    "RU",    "LR",    "LUD",    "UD",    "D",    "RU",    "LD"},
 {"UD",    "RD",    "LR",    "LU",    "U",    "RUD",    "LD",    "UD"},
 {"RU",    "LRU",    "LR",    "LRU",    "LR",    "LU",    "U",    "U"}};
 
/*--------------------------------Functions Dec-------------------------------*/
void Advance(const string &thedir, string &head, int &x, int &y);
void smooth180(string &head);
bool canAdvance(const string &thedir, string &head, int &x, int &y);
void drawLabyrinth(char **lab, int xpos, int ypos);

/*----------------------------------Program----------------------------------*/
int main()
{
system("title Labyrinth Breaker");
system("color 0f");

string head = DOWN;

int moves = 0;
int xStartAdv = 0;
int yStartAdv = 0;
int xFinalPosition = 7;
int yFinalPosition = 7;
char **drawlab;

ofstream myfile ("moves.txt");

drawlab=new char*[DIMX];

              for(int i=0;i<DIMX;i++){
                      drawlab[i]=new char[DIMY];        
              }

              for(int i=0;i<DIMX;i++){
                      for(int j=0;j<DIMY;j++){
                              drawlab[i][j]=' ';
                      }
              }
drawlab[xStartAdv][yStartAdv]='x';

    while(((xStartAdv != xFinalPosition) || (yStartAdv != yFinalPosition))){
                      
                      if (canAdvance(RIGHT, head, xStartAdv, yStartAdv) == true){
                                        
                         cout<<"RIGHT"<<endl;
                         cout<<"HEAD: "<<head<<endl;
                         Advance(RIGHT, head, xStartAdv, yStartAdv );
                         cout<<"X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
                         cout<<"HEAD: "<<head<<endl<<endl;
                         drawLabyrinth(drawlab, xStartAdv, yStartAdv);
                         moves+=1;
                         
                                  if(myfile.is_open()){
                                     myfile <<moves<<". X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
                                  }
                      }
                         else if (canAdvance(AHEAD, head, xStartAdv, yStartAdv) == true){
                              
                              cout<<"AHEAD"<<endl;
                              cout<<"HEAD: "<<head<<endl;
                              Advance(AHEAD, head, xStartAdv, yStartAdv);
                              cout<<"X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
                              cout<<"HEAD: "<<head<<endl<<endl;
                              drawLabyrinth(drawlab, xStartAdv, yStartAdv);
                              moves+=1;
                              
                                  if(myfile.is_open()){
                                     myfile<<moves<<". X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
                                  }        
                              }
                         else if (canAdvance(LEFT, head, xStartAdv, yStartAdv) == true){
                              
                              cout<<"LEFT"<<endl;
                              cout<<"HEAD: "<<head<<endl;
                              Advance(LEFT, head, xStartAdv, yStartAdv);
                              cout<<"X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
                              cout<<"HEAD: "<<head<<endl<<endl;
                              drawLabyrinth(drawlab, xStartAdv, yStartAdv);
                              moves+=1;
                              
                                  if(myfile.is_open()){
                                     myfile <<moves<<". X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
                                  }
                              }
                              
                         else{
                              smooth180(head);
                              drawLabyrinth(drawlab, xStartAdv, yStartAdv);
                              moves+=1;
                              
                                  if(myfile.is_open()){
                                     myfile <<moves<<". X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
                                  }
                         }
}

myfile.close();
cout<<"FINAL X and Y Position: "<<xStartAdv<<", "<<yStartAdv<<endl;
cout<<"TOTAL MOVES: "<<moves<<endl;
system("pause");
}
/*--------------------------------Functions----------------------------------*/
/*---F1---*/
void Advance(const string &thedir, string &head, int &x, int &y){
     
     if(head == DOWN){
             
             if(thedir == AHEAD) { head = DOWN; y++;}
             if(thedir == RIGHT) { head = LEFT; x--;}
             if(thedir == LEFT) { head = RIGHT; x++;}
     }    
     else if(head == UP){
          
          if(thedir == AHEAD) y--;
          if(thedir == RIGHT) { head = RIGHT; x++;}
          if(thedir == LEFT) { head = LEFT; x--;}
     }
     else if(head == RIGHT){
          
          if(thedir == AHEAD) x++;
          if(thedir == RIGHT) { head = DOWN; y++;}
          if(thedir == LEFT) { head = UP; y--;}
     }
     else if(head == LEFT){
          if(thedir == AHEAD) x--;
          if(thedir == RIGHT) { head = UP; y--;}
          if(thedir == LEFT) { head = DOWN; y++;}
     }
}
 
/*---F2---*/
void smooth180(string &head){
     if (head == UP) {head = DOWN; return;}
     if (head == DOWN) {head = UP; return;}
     if (head == RIGHT) {head = LEFT; return;}
     if (head == LEFT) {head = RIGHT; return;}
}
 
/*---F3---*/
bool canAdvance(const string &thedir, string &head, int &x, int &y){
     
 string posProperties (labyrinth[y][x]);
 string compare;

        if(head == DOWN){
                
                if(thedir == AHEAD) compare = 'D';
                if(thedir == RIGHT) compare = 'L';
                if(thedir == LEFT) compare = 'R';
        }
        else if(head == UP){
             
             if(thedir == AHEAD) compare = 'U';
             if(thedir == RIGHT) compare = 'R';
             if(thedir == LEFT) compare = 'L';
        }
        else if(head == RIGHT){
             
             if(thedir == AHEAD) compare = 'R';
             if(thedir == RIGHT) compare = 'D';
             if(thedir == LEFT) compare = 'U';
        }
        
        else if(head == LEFT){
             
             if(thedir == AHEAD) compare = 'L';
             if(thedir == RIGHT) compare = 'U';
             if(thedir == LEFT) compare = 'D';
        }

 string::size_type loc = posProperties.find( compare, 0 );
 
                   if( loc != string::npos ){
                       return true;
                   }
                   else{
                        return false;
                   }
}

/*---F4---*/
void drawLabyrinth(char **lab, int xpos, int ypos){
     
     for(int i=0;i<DIMX;i++){
                      for(int j=0;j<DIMY;j++){
                              if(i==xpos && j==ypos){
                                         lab[i][j]='x';
                              }
                      }
              }
              
     for(int i=0;i<DIMX;i++){
                      for(int j=0;j<DIMY;j++){
                                         cout<<lab[j][i];
                      }
                      cout<<endl;
              }
      
cout<<endl;
cout<<endl;
}

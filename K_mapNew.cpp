#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

ifstream infile;
char judge;

void Switch_Judge( char  to_judge);
inline void reset();
int A_signal=-1,B_signal=-1,C_signal=-1,D_signal=-1;
void KMAP_Changer(int,int,int,int);

int K_MAP[4][4]={0};//initialize all 0

int main()
{   
    
    infile.open("input.txt",ios::in);
    
    while (1)//when file is at the end -->(infile>>judge=0) while-loop break out
    {
    if(infile>>judge)//not end yet
    {  
        Switch_Judge(judge);
    }
    else//ended(infile>>judge==0)
    {   break;}
    }
    KMAP_Changer(A_signal,B_signal,C_signal,D_signal); //for last patern
    cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;
    reset();   
    cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;

   
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {   cout<<K_MAP[i][j]<<' ';}
        cout<<endl;
    }

    system("PAUSE");
    return 0;
}

void Switch_Judge( char  to_judge)
{
switch (to_judge)
{
case 'a':
    A_signal=1;
    if(infile>>judge)//a is the last element  
    {
    if(judge=='\'')
    {A_signal=0;}
    else
    {Switch_Judge(judge);}//recursive
    }

    break;
case 'b':
    B_signal=1;
    infile>>judge;
    if(judge=='\'')
    {B_signal=0;}
    else
    {Switch_Judge(judge);}//recursive
    break;
case 'c':
    C_signal=1;
    infile>>judge;
    if(judge=='\'')
    {C_signal=0;}
    else
    {Switch_Judge(judge);}//recursive
    break;
case 'd':
    D_signal=1;
    infile>>judge;
    if(judge=='\'')
    {D_signal=0;}
    else
    {Switch_Judge(judge);}//recursive
    break;
case '('://don't care
    break;
case ')':
    break;
case '\''://the form of char 'prime' is \'
    break;
case '+':
    KMAP_Changer(A_signal,B_signal,C_signal,D_signal);
    //test
    cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;
    reset();
    //test
    cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;
    
    break;
default:
    cout<<"input format error!";
    break;
}
}

inline void reset()//每個patern 改完kmap要reset
{   A_signal=-1;
    B_signal=-1;
    C_signal=-1;
    D_signal=-1;
}

void KMAP_Changer(int a,int b,int c,int d)//pass A-D_signal into the function
{
    int row_num=0;
    int row[4]={0};//store row_index of kmap to change 
    int column_num=0;
    int column[4]={0};
    if((a!=(-1))&&(b!=(-1)))
    {   column_num=1;
        if((a==0)&&(b==0))
        column[0]=0;//
        if((a==0)&&(b==1))
        column[0]=1;
        if((a==1)&&(b==0))
        column[0]=3;
        if((a==1)&&(b==1))
        column[0]=2; 
    }

    if((a==(-1)&&b!=(-1))||(a!=(-1)&&b==(-1)))
    {   column_num=2;
        if((a==0)&&(b==(-1))) //00 01
        {column[0]=0;
         column[1]=1;}
        if((a==1)&&(b==(-1)))//10 11
        {column[0]=2;
         column[1]=3;}
        if((a==(-1))&&(b==0))//00 10
        {column[0]=0;
         column[1]=3;}
        if((a==(-1))&&(b==1))//11 01
        {column[0]=1;
         column[1]=2;}
    }

    if((a==(-1))&&(b==(-1)))
    {   column_num=4;
        column[0]={0}; column[1]={1}; column[2]={2};  column[3]={3};
    }
//******************************************************
    if((c!=(-1))&&(d!=(-1)))
    {   row_num=1;
        if((c==0)&&(d==0))
        row[0]=0;//
        if((c==0)&&(d==1))
        row[0]=1;
        if((c==1)&&(d==0))
        row[0]=3;
        if((c==1)&&(d==1))
        row[0]=2; 
    }

    if((c==(-1)&&d!=(-1))||(c!=(-1)&&d==(-1)))
    {   row_num=2;
        if((c==0)&&(d==(-1))) //00 01
        {row[0]=0;
         row[1]=1;}
        if((c==1)&&(d==(-1)))//10 11
        {row[0]=2;
         row[1]=3;}
        if((c==(-1))&&(d==0))//00 10
        {row[0]=0;
         row[1]=3;}
        if((c==(-1))&&(d==1))//11 01
        {row[0]=1;
         row[1]=2;}
    }

    if((c==(-1))&&(d==(-1)))
    {   row_num=4;
        row[0]={0}; row[1]={1}; row[2]={2};  row[3]={3};
    }

    for(int i=0;i<row_num;i++)
    {
        for(int j=0;j<column_num;j++)
        {
            K_MAP[row[i]][column[j]]=1;
        }
    }
}


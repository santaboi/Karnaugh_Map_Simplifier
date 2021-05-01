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
void Sim_loop(struct minterm *,struct minterm *,int);
bool minterm_comparer(struct minterm *,struct minterm *,int,int);// same minterm return 1!!
int one_num=0;
int useful_size=0;
int useless_size=0;
//***********************
struct minterm
{
    int binary[4];
    int status=(-1);
};

//*************************

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
    //cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;//debug use
    reset();   
    //cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;//debug use
    

     cout<<"===========K Kap=========="<<endl;
    cout<<"  \\AB|                   "<<endl;
    cout<<"CD\\  | 00 | 01 | 11 | 10 "<<endl;
     cout<<"-----+----+----+----+-----"<<endl;
    for(int i=0;i<4;i++)
    {
        cout<<"     |    |    |    |    |"<<endl;
        switch(i)
            {
                case 0:
                cout<<"  00 |";
                break;
                case 1:
                cout<<"  01 |";
                break;
                case 2:
                cout<<"  11 |";
                break;
                case 3:
                cout<<"  10 |";
                break;
            }
        for(int j=0;j<4;j++)
        {
            cout<<"  "<<K_MAP[i][j]<<" |";
            if(K_MAP[i][j]==1)
            one_num++;
        }
        cout<<endl<<"     |    |    |    |    |"<<endl;
        cout<<"-----+----+----+----+-----"<<endl;
    }

    //one_num=minterm number
struct minterm *cur_ptr=new struct minterm[one_num];
    //status reset
    /*
    for(int i=0;i<one_num;i++)
    {   cur_ptr[i].status=(-1);}
    */
struct minterm *new_ptr=new struct minterm[one_num];//比較完 存現有值
    //status reset
    /*
    for(int i=0;i<one_num;i++)
    {   new_ptr[i].status=(-1);}
    */
    int index=0;
    for(int j=0;j<4;j++) 
    {
        for(int i=0;i<4;i++)
        {
            if(K_MAP[i][j]==1)
            {   
                
                switch (j)
                {
                case 0://first column
                    if(i==0)//0000
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={0};}
                    if(i==1)//0001
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={1};}
                    if(i==2)//0011
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={1};}
                    if(i==3)//0010
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={0};}
                    break;
                case 1://second column
                    if(i==0)//0100
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={0};}
                    if(i==1)//0101
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={1};}
                    if(i==2)//0111
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={1};}
                    if(i==3)//0110
                    {cur_ptr[index].binary[0]={0};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={0};}
                    break;
                case 2://third column
                    if(i==0)//1100
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={0};}
                    if(i==1)//1101
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={1};}
                    if(i==2)//1111
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={1};}
                    if(i==3)//1110
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={1};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={0};}
                    break;
                case 3://fourth column
                    if(i==0)//1000
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={0};}
                    if(i==1)//1001
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={0};
                    cur_ptr[index].binary[3]={1};}
                    if(i==2)//1011
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={1};}
                    if(i==3)//1010
                    {cur_ptr[index].binary[0]={1};
                    cur_ptr[index].binary[1]={0};
                    cur_ptr[index].binary[2]={1};
                    cur_ptr[index].binary[3]={0};}
                    break;
                default:
                    break;
                }    

                index++;
            }
        }
    }
   //cur_ptr[one_number]裡面已經建立完所有patern 的binary數值
    struct minterm * useful=cur_ptr;
    struct minterm * useless=new_ptr;
    struct minterm * temp_swap=NULL;

    
    //test
    useful_size=one_num;
    Sim_loop(useful,useless,useful_size);
        //swap
        temp_swap=useful;
        useful=useless;
        useless=temp_swap;
    Sim_loop(useful,useless,useful_size);
        //swap
        temp_swap=useful;
        useful=useless;
        useless=temp_swap;
    Sim_loop(useful,useless,useful_size);
        //swap
        temp_swap=useful;
        useful=useless;
        useless=temp_swap;    
    Sim_loop(useful,useless,useful_size);
        //swap
        temp_swap=useful;
        useful=useless;
        useless=temp_swap;



    /*
    useful_size=one_num;
    while(1)
    {
        Sim_loop(useful,useless,useful_size);
        //swap
        temp_swap=useful;
        useful=useless;
        useless=temp_swap;
        if(minterm_comparer(useful,useless,useful_size,useless_size))
        {//not end(minterm not all equal)
            break;
        }
    }
    //break useful指道就是我們要的
    */


    delete [] cur_ptr;
    delete[] new_ptr;
    infile.close();

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
    if(infile>>judge)
    {
    if(judge=='\'')
    {B_signal=0;}
    else
    {Switch_Judge(judge);}//recursive
    }
    break;
case 'c':
    C_signal=1;
    if(infile>>judge)
    {
    if(judge=='\'')
    {C_signal=0;}
    else
    {Switch_Judge(judge);}//recursive
    }
    break;
case 'd':
    D_signal=1;
    if(infile>>judge)
    {
    if(judge=='\'')
    {D_signal=0;}
    else
    {Switch_Judge(judge);}//recursive
    }
    break;
case '('://don't care
    break;
case ')':
    break;
case '\''://the form of char 'prime' is \'
    break;
case '+':
    KMAP_Changer(A_signal,B_signal,C_signal,D_signal);
    //cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;//debug use
    reset();
    //cout<<A_signal<<B_signal<<C_signal<<D_signal<<endl;//debug use
    
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

void Sim_loop(struct minterm *to_change,struct minterm *to_create,int num_one)
{                             //cur                     new           useful_size

    int new_ind=0;
    useless_size=num_one;
    for(int i=0;i<(num_one-1);i++)
    {
        for(int j=i+1;j<num_one;j++)
        {
            int differ=0;
            for(int ind=0;ind<4;ind++)//differ是一組ind(0123)共用的值
            {
                
                if(to_change[i].binary[ind]==to_change[j].binary[ind])
                {   
                    to_create[new_ind].binary[ind]=to_change[i].binary[ind];
                }
                else if(to_change[i].binary[ind]!=to_change[j].binary[ind])//不一樣就改(-1)不論幾個
                {
                    to_create[new_ind].binary[ind]=(-1);
                    differ++;
                }

                if((ind==3)&&(differ==1))//ij merge successfully (if failed ,new_ind沒++ 下一輪會把不要的洗掉)
                {   
                    to_change[i].status=1;
                    to_change[j].status=1;
                    new_ind++;
                    
                }
                
            }
        }
    }
    

    for(int i=0;i<one_num;i++)//check status
    {   if(to_change[i].status==(-1))
        {   to_create[useful_size].binary[0]=to_change[i].binary[0];
            to_create[useful_size].binary[1]=to_change[i].binary[1];
            to_create[useful_size].binary[2]=to_change[i].binary[2];
            to_create[useful_size].binary[3]=to_change[i].binary[3];
            new_ind++;
        }
    }

    //for testing use
    for(int i=0;i<num_one;i++)
    {   
        cout<<to_change[i].binary[0]<<to_change[i].binary[1]<<to_change[i].binary[2]<<to_change[i].binary[3]<<' '
        <<"(status "<<to_change[i].status<<" )";
    }
    cout<<endl;

    for(int i=0;i<new_ind;i++)
    {   cout<<to_create[i].binary[0]<<to_create[i].binary[1]<<to_create[i].binary[2]<<to_create[i].binary[3]<<' '
        <<"(status "<<to_create[i].status<<" )";}
    cout<<endl;


    //status reset
    for(int i=0;i<useful_size;i++)
    {   to_change[i].status=(-1);}
    for(int i=0;i<useful_size;i++)
    {   to_create[i].status=(-1);}
    

    


    useful_size=new_ind;

    

    
    //new_ind 是正確element的index +1
    //取正確的值只取長度為new_ind的(捨去最後一個)
}


bool minterm_comparer(struct minterm *a,struct minterm *b,int a_size,int b_size)
{
    if(a_size!=b_size)
    {   return false;}
    else//a_size==b_size
    {
        int state=1;
        for(int i=0;i<a_size;i++)
        {   
            for(int j=0;j<4;j++)
            {   
                if(a[i].binary[j]!=b[i].binary[j])
                state=state*0;
            }
        }
        return state;
        
    }
}







//**********************************queen macusky simplification************************************************************
    
    /*
    int new_ind=0;
    for(int i=0;i<(one_num-1);i++)
    {
        for(int j=i+1;j<one_num;j++)
        {
            int differ=0;
            for(int ind=0;ind<4;ind++)//differ是一組ind(0123)共用的值
            {
                
                if(cur_ptr[i].binary[ind]==cur_ptr[j].binary[ind])
                {   
                    new_ptr[new_ind].binary[ind]=cur_ptr[i].binary[ind];
                }
                else if(cur_ptr[i].binary[ind]!=cur_ptr[j].binary[ind])//不一樣就改(-1)不論幾個
                {
                    new_ptr[new_ind].binary[ind]=(-1);
                    differ++;
                }

                if((ind==3)&&(differ==1))//ij merge successfully (if failed ,new_ind沒++ 下一輪會把不要的洗掉)
                {   
                    cur_ptr[i].status=1;
                    cur_ptr[j].status=1;
                    new_ind++;
                    
                }
                
            }
        }
    }
    

    for(int i=0;i<one_num;i++)//check status
    {   if(cur_ptr[i].status==(-1))
        {   new_ptr[new_ind].binary[0]=cur_ptr[i].binary[0];
            new_ptr[new_ind].binary[1]=cur_ptr[i].binary[1];
            new_ptr[new_ind].binary[2]=cur_ptr[i].binary[2];
            new_ptr[new_ind].binary[3]=cur_ptr[i].binary[3];
            new_ind++;
        }
    }

    //status reset
    for(int i=0;i<one_num;i++)
    {   cur_ptr[i].status=(-1);}
    for(int i=0;i<one_num;i++)
    {   new_ptr[i].status=(-1);}
    //status reset


    
    */
    
    
    //new_ind 是正確element的index +1
    //取正確的值只取長度為new_ind的(捨去最後一個)
    

    
        
//******************************************************************************

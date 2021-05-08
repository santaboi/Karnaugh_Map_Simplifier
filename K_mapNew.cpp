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
    vector<int> decimal_vec;//用vector size即可
};

//*************************

int K_MAP[4][4]={0};//initialize all 0

void alpha_print(struct minterm );

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
struct minterm *cur_ptr=new struct minterm[one_num*3];
    //status reset
    /*
    for(int i=0;i<one_num;i++)
    {   cur_ptr[i].status=(-1);}
    */
struct minterm *new_ptr=new struct minterm[one_num*3];//比較完 存現有值
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

    //initialize decimal num
    for(int i=0;i<one_num;i++)
    {   
        int decimal=0;
        decimal=cur_ptr[i].binary[0]*8+cur_ptr[i].binary[1]*4+cur_ptr[i].binary[2]*2+cur_ptr[i].binary[3]*1;
        cur_ptr[i].decimal_vec.push_back(decimal);
    }


    struct minterm * useful=cur_ptr;
    struct minterm * useless=new_ptr;
    struct minterm * temp_swap=NULL;

   

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
    //!!!!!!!!!!!!!!!!目前useful  與useful_size 指到就是化簡完成的 但是還有重複的
    
    //test
    for(int i=0;i<useful_size;i++)
    {   
        cout<<"number"<<i<<" is ";
        for(int j=0;j<useful[i].decimal_vec.size();j++)
        {   cout<<useful[i].decimal_vec[j]<<"  ";}
        cout<<endl;
    }


    //把重複搞掉
    vector<int> index_needed;
    index_needed.push_back(0);//0一定是必要的index
    for(int i=1;i<useful_size;i++)
    {
        int judge=0;
        for(int j=0;j<i;j++)
        {
            if(!(useful[i].binary[0]==useful[j].binary[0]&&
            useful[i].binary[1]==useful[j].binary[1]&&
            useful[i].binary[2]==useful[j].binary[2]&&
            useful[i].binary[3]==useful[j].binary[3]))
            {   judge++;}                 
        }
        if(judge==i)
        {   index_needed.push_back(i);}
    }
    //index 存著所有prime implicant 的index 沒有重複數值了!!!!!!!!!!!!!!!!!!!!!
    


        //testing index_needed***************************************************************
        /*
        for(int i=0;i<index_needed.size();i++)
        {
        cout<<useful[index_needed[i]].binary[0]<<useful[index_needed[i]].binary[1]
        <<useful[index_needed[i]].binary[2]<<useful[index_needed[i]].binary[3];

        for(int j=0;j<useful[index_needed[i]].decimal_vec.size();j++)
        {      
            cout<<useful[index_needed[i]].decimal_vec[j]<<" ";
        }
        cout<<endl;
        }
        */
        //testing index_needed***************************************************************
    
    //finding essential prime implicants
    vector<int> prime_table(16,0);

    for(int i=0;i<index_needed.size();i++)
    {
        for(int j=0;j<useful[index_needed[i]].decimal_vec.size();j++)
        prime_table[useful[index_needed[i]].decimal_vec[j]]++;
    }

    //test
    for (int i = 0; i <16; i++)
    {
        cout<<i<<" "<<prime_table[i]<<endl;
    }
    //test


    vector<int> cover_once;//存只有essential 會有cover的值
    cover_once.clear();
    for (int i = 0; i <16; i++)
    {
        if(prime_table[i]==1)//哪個index 只有被cover once
        {   
            cover_once.push_back(i);//i 是只有essential 有cover的值
        }
    }
    
    //左邊側欄的所有P
    vector<struct minterm> prime_implicant(index_needed.size());
    
    for (int i = 0; i < index_needed.size(); i++)
    {
        prime_implicant[i]=useful[index_needed[i]];
    }
    
        /*testing
        cout<<prime_implicant.size()<<index_needed.size()<<endl;
        for (int i = 0; i < prime_implicant.size(); i++)
        {
        cout<<prime_implicant[i].binary[0]<<prime_implicant[i].binary[1]
        <<prime_implicant[i].binary[2]<<prime_implicant[i].binary[3]<<endl;
        
        }
        */
    


    vector<int> essential_index;


    if(!(cover_once.empty()))//有essential(內非空)
    {  
        int once_ind=0;
        for (int i = 0; i < prime_implicant.size(); i++)
        {
            int yesno=0;
            for(int j=0;j<prime_implicant[i].decimal_vec.size();j++)
            {
                if(prime_implicant[i].decimal_vec[j]==cover_once[once_ind])
                {   yesno++;}
            }
            if(yesno!=0)//表prime_implicant[i]是essential!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            {   
                essential_index.push_back(i);
                for(int n=0;n<prime_implicant[i].decimal_vec.size();n++)
                prime_table[prime_implicant[i].decimal_vec[n]]=0;
                once_ind++;
            }
            yesno=0;
            if(once_ind==cover_once.size())
            {   break;}
        }
        
        //test
        //cout<<"essential_index"<<essential_index[0]<<"  "<<essential_index[1]<<endl;


    }

        //test
        
        for (int i = 0; i <16; i++)
        {
        cout<<i<<" "<<prime_table[i]<<endl;
        }
        
        //test


    //沒有essential 或有essential都可以
    //prime table不為零的index為尚未cover的minterm
    vector<int> uncover_min;
    
    for (int i = 0; i < 16; i++)
    {
        if(prime_table[i]!=0)
        {   uncover_min.push_back(i);}
    }

    vector<int> patriks_term [16];
    //最多 uncover_min.size()個 有值

    for (int i = 0; i < 16; i++)
    {
        patriks_term [i].clear();
    }
    

    //uncover_min 存有所有uncover的minterm
    for (int i = 0; i <uncover_min.size(); i++)//uncover_min traverse(橫)
    {
        for(int j=0;j <prime_implicant.size(); j++)//prime implicant traverse(直)
        {   
            for(int n=0;n <prime_implicant[j].decimal_vec.size();n++)//decimal vector traverse
            {
                if(prime_implicant[j].decimal_vec[n]==uncover_min[i])
                {   patriks_term[i].push_back(j);}
            }
        }
    }
    //重要的是找到哪幾個prime implicant 集合再一起
    //patricks_term內現有 uncover_min.size()個 "sum term" 要相乘
    //每個sum 有patriks_term[i].size()個 implicant
    cout<<"test";
    cout<<patriks_term[0].size()<<endl;
    cout<<patriks_term[1].size()<<endl;
    int product_num=1;
    for (int i = 0; i < uncover_min.size(); i++)
    {
        product_num=product_num*patriks_term[i].size();
    }
    
    vector<int> product_list [5000];//所有可能的product term
    //陣列一定要清乾淨
    //product_list->resize(product_num);
    product_list->clear();
    
    for (int i = 0; i < product_num; i++)//陣列一定要清乾淨不然裡面會有垃圾
    {
        product_list[i].clear();
    }
    //如果每個product不同長會自動補零號(補在前面)
    //cout<<"product_list [0][0]"<<product_list [0][0]<<endl;
    //*****************(old)此段patrick 爆開有點問題!!!!********************************************
    /*
    //cout<<"uncover_min.size()"<<uncover_min.size()<<endl;
    for(int sum_ind=0;sum_ind< uncover_min.size();sum_ind++)//有幾個() 相乘在一起
    {   
        int product_ind=0;
        while(!(product_ind>=product_num))//相等才BREAK
        {   
            for(int i=0;i< patriks_term[sum_ind].size();i++)
            {    
                product_list[product_ind].push_back(patriks_term[sum_ind][i]);
                product_ind++;//index
            }
        }
        
    }
    */
    //*****************(old)此段patrick 爆開有點問題!!!!********************************************
    //*****************(new)此段patrick 爆開有點問題!!!!********************************************

    vector<int> pushed_times;
    pushed_times.clear();
    int temp;
    for (int j = 0; j < (uncover_min.size()-1); j++) //size5 j 0123
    {
        temp=product_num;
        for (int i = j; i <(uncover_min.size()-1) ; i++)//j=0 0123  j=1  123    j=2  23   j=3 3
        {
            temp=temp/(patriks_term[i].size());
            pushed_times.push_back(temp);
        }
        
    }
    //pushed_times index 對應到patriks_term

    //(new) product_list[][]的initialize
    for (int i = 0; i < uncover_min.size(); i++)
    {
        int push_counter=0;
        if(i==(uncover_min.size()-1))
        {  
            while (1)
            {
                for (int n = 0; n < patriks_term[i].size(); n++)
                {
                    product_list[push_counter].push_back(patriks_term[i][n]);
                    push_counter++;
                }
                if(push_counter>=product_num) break;
            }
            
            
        }
        else
        {
            while(1)
            {
                for (int j = 0; j < patriks_term[i].size(); j++)
                {
                    for (int m = 0; m < pushed_times[i]; m++)
                    {
                        product_list[push_counter].push_back(patriks_term[i][j]);
                        push_counter++;
                    }
                    
                }
                if(push_counter>=product_num) break;
            }
        }
    }
    


    //*****************(new)此段patrick 爆開有點問題!!!!********************************************


    //test
    
        cout<<endl;
        for(int i=0;i<product_list[0].size();i++)
        {   cout<<product_list[0][i];}
        cout<<endl;
        for(int i=0;i<product_list[1].size();i++)
        {   cout<<product_list[1][i];}
        cout<<endl;
        for(int i=0;i<product_list[2].size();i++)
        {   cout<<product_list[2][i];}
        cout<<endl;
        for(int i=0;i<product_list[3].size();i++)
        {   cout<<product_list[3][i];}
        cout<<endl;
    
    //都會一樣長(會自動補零)
    cout <<"product_list[0].size()"<< product_list[0].size() << endl;
    cout <<  "product_list[1].size()"<<product_list[1].size() << endl;
    cout << "product_list[2].size()"<< product_list[2].size() << endl;
    cout <<  "product_list[3].size()"<<product_list[3].size() << endl;
    
    //test

    


    //!!!!檢查過了
    //bestcases
    //每個product list 存的是包含的prime_implicant index(越少越好)
    int shortest=1000;
    vector<int> p_num;//每個term 裡有幾個implicant
    p_num.clear();
    vector<int> counter(20,0);
    for (int i = 0; i < product_num; i++)
    {
        int total=0;
        for(int j=0;j<product_list[i].size();j++)
        {   switch (product_list[i][j])
            {
                case 0:
                counter[0]=1;
                break;
            case 1:
                counter[1]=1;
                break;
            case 2:
                counter[2]=1;
                break;
            case 3:
                counter[3]=1;
                break;
            case 4:
                counter[4]=1;
                break;
            case 5:
                counter[5]=1;
                break;
            case 6:
                counter[6]=1;
                break;
            case 7:
                counter[7]=1;
                break;
            case 8:
                counter[8]=1;
                break;
            case 9:
                counter[9]=1;
                break;
            case 10:
                counter[10]=1;
                break;
            case 11:
                counter[11]=1;
                break;
            case 12:
                counter[12]=1;
                break;
            case 13:
                counter[13]=1;
                break;
            case 14:
                counter[14]=1;
                break;
            case 15:
                counter[15]=1;
                break;
            case 16:
                counter[16]=1;
                break;
            case 17:
                counter[17]=1;
                break;
            case 18:
                counter[18]=1;
                break;
            case 19:
                counter[19]=1;
                break;
            case 20:
                counter[20]=1;
                break;
        
            default:
                break;
            }
        }
        for(int i=0;i<20;i++)
        {   
            total=total+counter[i];
        }
        p_num.push_back(total);
        if(i==0)
        {   shortest=total;}
        else
        {   if(total<shortest)
                shortest=total;        
        }
        for(int i=0;i<20;i++)
        {   counter[i]=0;}
    }
    cout<<"shortest"<<shortest<<endl;
    cout<<p_num[0]<<endl<<p_num[1]<<endl<<p_num[2]<<endl<<p_num[3]<<endl<<p_num[4]<<endl;
    
    
    /*(舊版)
    for (int i = 0; i < product_num; i++)
    {
        
        int total=1;
        for(int j=1;j<product_list[i].size();j++)
        {   
            //j=1 n=0
            //j=2 n=0,1
            int unique=1;
            
            for (int n = 0; n < j; n++)
            {
                if(product_list[i][n]==product_list[i][j])
                {unique=unique*0;}
                cout<<unique<<endl;
            }
            if(unique)
            total++;
            //p_num.push_back(total);
            //p_num 的index 對應到product_list的index
        }
        p_num.push_back(total);
        //這邊total已經是此product的different term數量
        if(total<shortest)
        shortest=total;
    }
    //test
    cout<<"shortest"<<shortest<<endl;
    cout<<p_num[0]<<endl<<p_num[1]<<endl<<p_num[2]<<endl<<p_num[13]<<endl<<p_num[24]<<endl;
    */



    //以下尚未debug
    //有幾項shortest term
    int num_of_shortest=0;
    vector<int> shortest_index;
    shortest_index.clear();
    for (int i = 0; i < product_num ; i++)
    {
        if(p_num[i]==shortest)
        {
        shortest_index.push_back(i);
        num_of_shortest++;
        }
    }
    //test
    //cout<<num_of_shortest<<endl;
    //cout<<shortest_index[0]<<endl<<shortest_index[1]<<endl<<shortest_index[2]<<endl<<shortest_index[3]<<endl;
    //******************************
    //      (product_list)
    //num_of_shortest 要取的數量
    //shortest_index 要取的index (會有重複)
    //******************************
          
    
    //就找第一個當隨機解 product_list[shortest_index[0]];
    //product_list[shortest_index[0]].size() 存各種index
    //vector<struct minterm> prime_implicant(index_needed.size());
    
    
    //struct minterm
    //{   
    //int binary[4];
    //int status=(-1);
    //vector<int> decimal_vec;//用vector size即可
    //};
    
    //是否有essential
    //vector<int> essential_index; 存有essential 的index

    //if()//kmap 全滿
    //{

    //}

    //else//kmap 沒有全滿(正常狀況)
    //{
    int group_num=1;
    if(!(cover_once.empty()))//有essential(內非空)
    {   
        for (int i = 0; i < essential_index.size(); i++)
        {
            cout<<"group"<<group_num<<":[";
            for (int j = 0; j < prime_implicant[essential_index[i]].decimal_vec.size(); j++)
            {
                cout<<prime_implicant[essential_index[i]].decimal_vec[j];
                if(j==(prime_implicant[essential_index[i]].decimal_vec.size()-1))
                cout<<"]"<<endl;
                else
                cout<<',';
            }
            cout<<"simplification of group"<<group_num<<"->";   
            alpha_print(prime_implicant[essential_index[i]]);
            cout<<endl;
            group_num++;
        }
        
        
    }
    

    //essential 做完接 無essential
    //product_list 是二維   product_list[shortest_index[0]][i]
    //cout<<"product_list[shortest_index[0]].size()"<<product_list[shortest_index[0]].size()<<endl;
    for(int i=0;i < product_list[shortest_index[0]].size();i++)
    {   
        cout<<"group"<<group_num<<":[";
        for (int j = 0; j < prime_implicant[product_list[shortest_index[0]][i]].decimal_vec.size(); j++)
            {
                cout<<prime_implicant[product_list[shortest_index[0]][i]].decimal_vec[j];
                if(j==(prime_implicant[product_list[shortest_index[0]][i]].decimal_vec.size()-1))
                cout<<"]"<<endl;
                else
                cout<<',';
            }
        cout<<"simplification of group"<<group_num<<"->";   
            alpha_print(prime_implicant[product_list[shortest_index[0]][i]]);
            cout<<endl;
            group_num++;
    }




    //}
    



    //***********************找出所有最佳解方法******************************************************************
    /*
    //判斷相加相乘有沒有都一樣的(判斷重複)
    //sum_multiply 第一格放sum 第二格放multiply
    vector<int> sum_multiply [100] ;
    sum_multiply->resize(product_num);//product list 的size
    for (int i = 0; i < product_num; i++)//陣列一定要清乾淨不然裡面會有垃圾
    {
        sum_multiply[i].clear();
    }

        //error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        /*
        sum_multiply[shortest_index[0]]=0;//initial sum
        sum_multiply[shortest_index[0]][1]=1;
        sum_multiply[shortest_index[1]][0]=0;//initial sum
        sum_multiply[shortest_index[1]][1]=1;

        cout<<sum_multiply[shortest_index[0]][0]<<//initial sum
        sum_multiply[shortest_index[0]][1]<<
        sum_multiply[shortest_index[1]][0]<<//initial sum
     sum_multiply[shortest_index[1]][1];
        */
    /*
    for (int i = 0; i < num_of_shortest; i++)
    {   
        sum_multiply[shortest_index[i]].push_back(0);//initial sum
        sum_multiply[shortest_index[i]].push_back(1);//initial mutiply [0,1]
        for (int j = 0; j <product_list[shortest_index[i]].size() ; j++)
        {
            
            sum_multiply[shortest_index[i]][0]=sum_multiply[shortest_index[i]][0]+product_list[shortest_index[i]][j];
            sum_multiply[shortest_index[i]][1]=sum_multiply[shortest_index[i]][1]*product_list[shortest_index[i]][j];
        }
    }
    */

    //test
    /*
    for (int i = 0; i < shortest_index.size(); i++)
    {
        cout<<"index"<<shortest_index[i]<<"sum"<<sum_multiply[shortest_index[i]][0];
        cout<<"index"<<shortest_index[i]<<"multiply"<<sum_multiply[shortest_index[i]][1];
    }
    */
    //sum_multiply 裡面也只有其中幾個index有值(對應到product_list 的index)
    //取值by shortest_index[i] 共有num_of_shortest 個

    
    











        //最終的結果
        /*
         vector<int> essential2 [10];
        essential2->resize(num_of_shortest);
        for (int i = 0; i < num_of_shortest; i++)//陣列一定要清乾淨不然裡面會有垃圾
        {
        essential2[i].clear();
        }
        */
    
    //************************************************************************************



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
    useless_size=num_one;//這次傳入的useful_size是下次的useless_size
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
                    //只有merge 成功的才要改decimal**********************************************************
                    to_create[new_ind].decimal_vec.clear();
                    for(int a=0;a<to_change[i].decimal_vec.size();a++)
                    {   
                        to_create[new_ind].decimal_vec.push_back(to_change[i].decimal_vec[a]);
                    }
                    for(int b=0;b<to_change[j].decimal_vec.size();b++)
                    {   
                        to_create[new_ind].decimal_vec.push_back(to_change[j].decimal_vec[b]);
                    }
                    //以上改decimal**********************************************************
                    
                    new_ind++;
                }
                
            }
        }
    }
    

    for(int i=0;i<num_one;i++)//check status
    {   if(to_change[i].status==(-1))
        {   to_create[new_ind].binary[0]=to_change[i].binary[0];
            to_create[new_ind].binary[1]=to_change[i].binary[1];
            to_create[new_ind].binary[2]=to_change[i].binary[2];
            to_create[new_ind].binary[3]=to_change[i].binary[3];
            //decimal
            to_create[new_ind].decimal_vec.clear();
            to_create[new_ind].decimal_vec.assign(to_change[i].decimal_vec.begin(), to_change[i].decimal_vec.end()); 

            new_ind++;
        }
    }

    //for testing use
    
    for(int i=0;i<num_one;i++)
    {   
        cout<<to_change[i].binary[0]<<to_change[i].binary[1]<<to_change[i].binary[2]<<to_change[i].binary[3]<<"->";
        

        cout<<to_change[i].decimal_vec.size()<<':';
        for(int j=0;j<to_change[i].decimal_vec.size();j++)
        {      
            cout<<to_change[i].decimal_vec[j]<<" ";
        }
    
    }
    cout<<endl;

    for(int i=0;i<new_ind;i++)
    {   cout<<to_create[i].binary[0]<<to_create[i].binary[1]<<to_create[i].binary[2]<<to_create[i].binary[3]<<"->";
        
        cout<<to_create[i].decimal_vec.size()<<':';
        for(int j=0;j<to_create[i].decimal_vec.size();j++)
        {      
            cout<<to_create[i].decimal_vec[j]<<" ";
        }
    
    
    }
    cout<<endl;
    

    //status reset
    for(int i=0;i<one_num;i++)
    {   to_change[i].status=(-1);}
    for(int i=0;i<one_num;i++)
    {   to_create[i].status=(-1);}
    

    


    useful_size=new_ind;
}

    

    



bool minterm_comparer(struct minterm *a,struct minterm *b,int a_size,int b_size)
//                              use_ful          use_less useful_size useless_size
//第一次                                                 第一次完new_ind    one_num
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


void alpha_print(struct minterm to_print )
{ 
    if(to_print.binary[0]==0)
        cout<<"a'";
    if(to_print.binary[0]==1)
        cout<<"a";
    if(to_print.binary[1]==0)
        cout<<"b'";
    if(to_print.binary[1]==1)
        cout<<"b";
    if(to_print.binary[2]==0)
        cout<<"c'";
    if(to_print.binary[2]==1)
        cout<<"c";
    if(to_print.binary[3]==0)
        cout<<"d'";
    if(to_print.binary[3]==1)
        cout<<"d";

    cout<<endl;
}





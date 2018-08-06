#include<iostream>
#include"Sudoku.h"
#include<fstream>
#include<stdlib.h>
#include<QDebug>
using namespace std;

Sudoku::Sudoku()
{

}

void Sudoku::input_setmap(int arr[])
{
    for(int i=0;i<81;++i)
        map[i] = arr[i];
}

bool Sudoku::checkUnity(int arr[])
{
 int arr_unity[9]; // counters

 for(int i=0; i<9; ++i)
 arr_unity[i] = 0; // initialize
 for(int i=0; i<9; ++i)
 ++arr_unity[arr[i]-1]; // count
 for(int i=0; i<9; ++i)
 if(arr_unity[i] != 1) // all element
 return false; // must be 1
 return true;
}

bool Sudoku::check_correct()
    {
        bool check_result;
         int check_arr[9];
         int location;
        for(int i=0; i<81; i+=9) // check rows
             {
                 for(int j=0; j<9; ++j)
                     check_arr[j] = map[i+j];
                 check_result = checkUnity(check_arr);
                 if(check_result == false)
                     return false;
                 }
         for(int i=0; i<9; ++i) // check columns
             {
                 for(int j=0; j<9; ++j)
                     check_arr[j] = map[i+9*j];
                 check_result = checkUnity(check_arr);
                 if(check_result == false)
                     return false;
                }

             for(int i=0; i<9; ++i) // check cells
             {
                 for(int j=0; j<9; ++j)
                     {
                         location = 27*(i/3) + 3*(i%3) +9*(j/3) + (j%3);
                         check_arr[j] = map[location];
                         }
                 check_result = checkUnity(check_arr);
                 if(check_result == false)
                     return false;
                 }
         return true;
         }

void Sudoku::print_map()
{
    int i=0;
    int count=0;
    while(i<81)
    {
        cout<<map[i]<<" ";
        ++i;
        if((i%3)==0)
        {
            cout<<" ";
            count++;
        }
        if(count == 3)
        {
            cout<<endl;
            count-=3;
        }
        if((i/9==3&&i%9==0)||(i/9==6&&i%9==0))
            cout<<endl;

    }
}

void Sudoku:: set_element(int i ,int value)
{
    map[i]=value;
}
int Sudoku:: get_first_zero()
{
    for(int i=0;i<81;++i)
    {
        if(map[i] == 0)
            return i;
    }
    return -1;
}

bool Sudoku::check_solve_row(int firstZero)
{
 int arr[9]={0};
 int count = (firstZero/9)*9;
 int range = count+9;
// cout<<firstZero<<endl;
 for(count;count < range ;++count)
 {
     if(map[count]==0)
         continue;
     else
       arr[map[count]-1]++;
 }



 for(int j=0;j<9;++j)
 {
     if(arr[j] >=2)
         return false;
 }
 return true;

}

bool Sudoku:: check_solve_column(int firstZero)
{
    int arr[9]={0};
    int count =(firstZero%9);
    int range = (count+72);
    for(count;count<range;count+=9)
    {
        if(map[count] ==0)
            continue;
        else
            arr[map[count]-1]++;


    }
/*	for(int j=0;j<9;++j)
    {
        while((arr[j]-1) < 0)
            j++;
        if(j>=9)
            break;
        arr_unity[arr[j]-1]++;
    }*/
    for(int j=0;j<9;++j)
    {
        if(arr[j]>=2)
            return false;
    }
    return true;
}

bool Sudoku::check_solve_cell(int firstZero)
{
    int arr[9]={0};
    int x=firstZero%9;
    int y=firstZero/9;
    int xx=x/3;
    int yy=y/3;
    int location= xx*3 + yy*27;
    for(int i=0; i<27; i+=9) // check cells5 t
    {
     for(int j=0; j<3; ++j)
     {
                 if(map[location+i+j]!=0)
                 arr[map[location+i+j]-1]++;
     }
    }

     for(int i=0;i<9;++i)
     {
         if(arr[i] >=2)
             return false;
     }

    return true;
}





void Sudoku::produce_sudoku()
{
    srandom(time(NULL));
    int blank;
    for(int i=0;i<9;++i)
    {
        blank = (random()%9+1);

        map[i] = blank;
        while(check_solve_row(i) == false)
        {
            blank = (random()%9+1);
            map[i] = blank;
        }

    }

}
void Sudoku:: generate_quiz(int num)
{
    int blank_position;
    for(int i=0;i<num;++i)
    {
        blank_position = random()%81;
        map[blank_position] =0;
    }

}
bool Sudoku::solvesolve(Sudoku question,Sudoku & answer)
{
    int firstZero;
    firstZero = question.get_first_zero();
    if(firstZero == -1)
     { // end condition
         if(question.check_correct())
         {
         answer = question;
         return true;
         }
         else
         return false;
     }
    else
     {
         for(int num=1; num<=9; ++num)
         {
            question.set_element(firstZero, num);
            if(question.check_solve_row(firstZero) == false)
                continue;
            if(question.check_solve_column(firstZero) == false)
                continue;
            if(question.check_solve_cell(firstZero) == false)
                continue;
            if(solvesolve(question, answer))
                         return true;
         }
                 return false;
     }
}

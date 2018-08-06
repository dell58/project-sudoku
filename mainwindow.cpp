#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sudoku.h"
#include <QPushButton>
#include<QSignalMapper>
#include<QAction>
#include<QAbstractButton>
#include<QKeyEvent>
#include<QString>
#include<QDebug>
#include<QLabel>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Sudoku.exe"));
    for(int i=0;i<9;i++)//generate button
    {
      for(int j=0;j<9;++j)
      {
        button[i*9+j] = new QPushButton(this);
        button[i*9+j]->setGeometry(50*(j+1),50*(i+1),50,50);
        button[i*9+j]->setFont(QFont("Ubuntu",18));
      }
    }
    //change button color
    int location;
    for(int i=0; i<27; i+=9)
    {

     for(int j=0; j<3; ++j)
     {
           location = 0;
           button[location+i+j]->setStyleSheet("background-color:#FFBB66");
     }
    }
    for(int i=0; i<27; i+=9)
    {
     for(int j=0; j<3; ++j)
     {
           location = 6;
           button[location+i+j]->setStyleSheet("background-color:#FFBB66");
     }
    }
    for(int i=0; i<27; i+=9)
    {
     for(int j=0; j<3; ++j)
     {
           location = 30;
           button[location+i+j]->setStyleSheet("background-color:#FFBB66");
     }
    }
    for(int i=0; i<27; i+=9)
    {
     for(int j=0; j<3; ++j)
     {
           location = 54;
           button[location+i+j]->setStyleSheet("background-color:#FFBB66");
     }
    }
    for(int i=0; i<27; i+=9)
    {
     for(int j=0; j<3; ++j)
     {
           location = 60;
           button[location+i+j]->setStyleSheet("background-color:#FFBB66");
     }
    }
    for(int i=0;i<81;++i)//init  bool check_number
    {
        check_number[i]=true;
    }


    easy=new QPushButton(this);
    easy->setGeometry(600,50,200,50);
    easy->setFont(QFont("Ubuntu",13));
    easy->setText("Easy");
    easy->setStyleSheet("background-color:#FFBB66");
    midium=new QPushButton(this);
    midium->setGeometry(600,150,200,50);
    midium->setFont(QFont("Ubuntu",13));
    midium->setText("Midium");
    midium->setStyleSheet("background-color:#FFBB66");
    hard=new QPushButton(this);
    hard->setGeometry(600,250,200,50);
    hard->setFont(QFont("Ubuntu",13));
    hard->setText("Hard");
    hard->setStyleSheet("background-color:#FFBB66");
    finish=new QPushButton(this);
    finish->setGeometry(600,450,200,50);
    finish->setFont(QFont("Ubuntu",13));
    finish->setText("Finish");
    finish->setStyleSheet("background-color:#FFBB66");
    start=new QPushButton(this);
    start->setGeometry(600,350,200,50);
    start->setFont(QFont("Ubuntu",13));
    start->setText("Start");
    start->setStyleSheet("background-color:#FFBB66");
    solve=new QPushButton(this);
    solve->setGeometry(600,550,200,50);
    solve->setFont(QFont("Ubuntu",13));
    solve->setText("Answer");
    solve->setStyleSheet("background-color:#FFBB66");
   // wrong =new QLabel(this);
    right_wrong =new QLabel(this);
    //noans =new QLabel(this);
    connect(easy,SIGNAL(clicked(bool)),this,SLOT(generate_easy()));
    connect(midium,SIGNAL(clicked(bool)),this,SLOT(generate_midium()));
    connect(hard,SIGNAL(clicked(bool)),this,SLOT(generate_hard()));
    connect(finish,SIGNAL(clicked(bool)),this,SLOT(finish_quiz()));

    connect(start,SIGNAL(clicked(bool)),this,SLOT(start_quiz()));
    //connect(this,SIGNAL(produce()),this,SLOT(produce_quiz()));
    connect(this,SIGNAL(print_arr()),this,SLOT(print_mmap()));//print the map
    connect(solve,SIGNAL(clicked(bool)),this,SLOT(solve_quiz()));

    
   /////////////////////////////////////////////////////////////////////key in the number
    QSignalMapper *mapsignal =new QSignalMapper(this);
    for(int i=0;i<81;++i)
    {
        connect(button[i],SIGNAL(clicked(bool)),mapsignal,SLOT(map()));
        mapsignal->setMapping(button[i],i);
    }
    connect(mapsignal,SIGNAL(mapped(int)),this,SLOT(printMsg(int)));//get the position of the pushbutton on map
    connect(this,SIGNAL(set_map(int,int)),this,SLOT(set_mapslot(int,int)));//send the input number into setText
    ///////////////////////////////////////////////////////////////////

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printMsg(int i)//give the location of the input number
{
    position = i;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_1 && check_number[position]==true) emit set_map(1,position);
    if(event->key() == Qt::Key_2 && check_number[position]==true) emit set_map(2,position);
    if(event->key() == Qt::Key_3 && check_number[position]==true) emit set_map(3,position);
    if(event->key() == Qt::Key_4 && check_number[position]==true) emit set_map(4,position);
    if(event->key() == Qt::Key_5 && check_number[position]==true) emit set_map(5,position);
    if(event->key() == Qt::Key_6 && check_number[position]==true) emit set_map(6,position);
    if(event->key() == Qt::Key_7 && check_number[position]==true) emit set_map(7,position);
    if(event->key() == Qt::Key_8 && check_number[position]==true) emit set_map(8,position);
    if(event->key() == Qt::Key_9 && check_number[position]==true) emit set_map(9,position);
}


void MainWindow::set_mapslot(int input,int position)
{

    QString string;
    string = QString::number(input);
    button[position]->setText(string);
}

int  MainWindow::get_mapnumber(int position)//get the map data
{
    QString map_string;//the number on map
    int input_number;
    map_string = button[position]->text();
    if(map_string=="")
        return 0;
    bool ok;
    input_number=map_string.toInt(&ok,10);
    return input_number;

}
void MainWindow ::map_array()
{
    for(int i=0;i<81;++i)
    {
        sudoku_array[i] = get_mapnumber(i);
    }
    //emit produce();//slot->produce_quiz();

}

/*void  MainWindow::produce_quiz()
{
    Sudoku ans;
    Sudoku ques;
    ques.input_setmap(sudoku_array);
    if(sudo.solvesolve(ques,ans))
    {
        ans.generate_quiz(40);
        for(int i=0;i<81;++i)
        {
            sudoku_array[i]= ans.map[i];
        }
        emit print_arr();//slot->print_mmap()
    }
}
*/
void MainWindow::print_mmap()
{
    set_zero();
    for(int i=0;i<81;i++)
    {

         if(sudoku_array[i]==0)
             continue;

         set_map(sudoku_array[i],i);
    }
}

void MainWindow:: generate_easy()
{
    set_zero();
    Sudoku ques,ans;
    ques.produce_sudoku();

    if(sudo.solvesolve(ques,ans))
    {

        ans.generate_quiz(15);

        for(int i=0;i<81;++i)
        {
            sudoku_array[i]= ans.map[i];
        }
        emit print_arr();//slot->print_mmap()
    }


}
void MainWindow:: generate_midium()
{
    set_zero();
    Sudoku ques,ans;
    ques.produce_sudoku();
    if(sudo.solvesolve(ques,ans))
    {
        ans.generate_quiz(30);
        for(int i=0;i<81;++i)
        {
            sudoku_array[i]= ans.map[i];
        }
        emit print_arr();//slot->print_mmap()
    }


}



void MainWindow:: generate_hard()
{
    set_zero();
    Sudoku ques,ans;
    ques.produce_sudoku();
    if(sudo.solvesolve(ques,ans))
    {
        ans.generate_quiz(60);
        for(int i=0;i<81;++i)
        {
            sudoku_array[i]= ans.map[i];
        }
        emit print_arr();//slot->print_mmap()
    }


}
void MainWindow:: set_zero()
{
    for(int i=0;i<81;i++)
    {
        button[i]->setText("");
    }
}
void MainWindow::solve_quiz()
{
    map_array();
    Sudoku ques,ans;
    ques.input_setmap(sudoku_array);
    if(sudo.solvesolve(ques,ans))
    {
        for(int i=0;i<81;++i)
        {
            sudoku_array[i]= ans.map[i];
        }
        emit print_arr();//slot->print_mmap()
    }
    else
    {
       // noans =new QLabel(this);
        right_wrong->setGeometry(400,450,200,200);
        right_wrong->setFont(QFont("Ubuntu",20));
        right_wrong->setText(tr("No answer!"));
        right_wrong->setAlignment(Qt::AlignCenter);
    }


}
void MainWindow::finish_quiz()
{
    map_array();
    Sudoku ques;
    ques.input_setmap(sudoku_array);
    if(ques.check_correct()==true)
    {
        //right =new QLabel(this);
        right_wrong->setGeometry(400,500,100,100);
        right_wrong->setFont(QFont("Ubuntu",20));
        right_wrong->setText(tr("Right!"));
        right_wrong->setAlignment(Qt::AlignCenter);
    }
    else
    {
       // wrong =new QLabel(this);
        right_wrong->setGeometry(400,500,100,100);
        right_wrong->setFont(QFont("Ubuntu",20));
        right_wrong->setText(tr("Wrong!"));
        right_wrong->setAlignment(Qt::AlignCenter);
    }



}
void MainWindow::start_quiz()
{
   // for(int i=0;i<81;++i)
        //check_number[i]=true;
    for(int i=0;i<81;++i)
    {
        if(button[i]->text()!="")
            check_number[i]=false;

    }

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"Sudoku.h"
#include <QMainWindow>
#include <QPushButton>
#include<QSignalMapper>
#include<QAction>
#include<QAbstractButton>
#include<QKeyEvent>
#include<QLabel>
#include<QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

signals:
    void set_map(int ,int );
    //void produce();
    void print_arr();

private slots:
    void printMsg(int);//set position
    void keyPressEvent(QKeyEvent *event);//input the number from keyboard
    void set_mapslot(int , int);//set the number in sudoku and show it
    int get_mapnumber(int);//get the number on the map
    void map_array();
    //void produce_quiz();//generate the quiz
    void print_mmap();//print out the quiz
    void generate_easy();//easy button
    void generate_midium();//midium button
    void generate_hard();//hard button
    void set_zero();//set all the space ->""
    void solve_quiz();//answer button
    void start_quiz();//start button
    void finish_quiz();//finish button



private:
    Ui::MainWindow *ui;
    QPushButton *button[81];
    QPushButton *easy;
    QPushButton *midium;
    QPushButton *hard;
    QPushButton *start;
    QPushButton *solve;
    QPushButton *finish;
    QLabel *right_wrong;

   // QLabel *noans;
    int position;
    int sudoku_array[81];
    bool check_number[81];
    Sudoku sudo;


};

#endif // MAINWINDOW_H

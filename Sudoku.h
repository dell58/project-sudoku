#ifndef SUDOKU_H
#define SUDOKU_H


using namespace std;

class Sudoku{
    public:
        Sudoku();
        void input_setmap(int arr[]);//input the keyboard number
        bool check_correct();//check all the sudoku
        void print_map();//print the map
        void set_element(int i,int value);
        int  get_first_zero();
        bool check_solve_row(int firstZero);
        bool check_solve_column(int firstZero);
        bool check_solve_cell(int firstZero);
        void produce_sudoku();//generate a sudoku
        void generate_quiz(int num);//generate a quiz  num==blank number int the quiz
        int map[81]={0};
        bool solvesolve(Sudoku,Sudoku&);

    private:
        bool checkUnity(int arr[]);//func to check unity
        //int map[81];

};

#endif // SUDOKU_H

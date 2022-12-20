#include<iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
/*
Ход работы программы:
1. создал текстовый файл формата: размер матрицы(след матрицы бывает только у квадратной), пустая строка, записаны элементы матрицы друг за другом
2. считаваем размер матрицы и записываем ее размер, информацию о ней, если она верхнетреугольная, то кайф, иначе ищем дальше матрицу
3. записываем в новый файл
*/


struct Matrix//структура, которая хранит в себе имя и кол-во раз сколько встретилось слово
{
private:
    bool is_it_ok = true;//верхнетреугольная?
    int size;//размер матрицы
    vector<int> matrix_elements;//элементы
public:
    //конструктор
    Matrix(int size, vector<int> matrix_elements) : size(size), matrix_elements(matrix_elements) {
        //проверка что верхнетреугольная
        for (int i = 0; i < size; i++) {//номер строки
            for (int j = 0; j < size; j++) { //номер столбца
                if (i > j) {
                    int z = matrix_elements[i * size + j];
                    if (z != 0) is_it_ok = false;
                }
            }
        }
    
    };
    Matrix() = delete;//чтобы нельзя было ссоздать объект без всего


    bool get_flag() {//выдаст кол-во которое оно встречается
        return is_it_ok;
    }
    int get_size() {//выдаст кол-во которое оно встречается
        return size;
    }
    vector<int> get_element() {//выдаст кол-во которое оно встречается
        return matrix_elements;
    }
};


bool comp(Matrix a, Matrix b) {//компаратор, нужен для определния как будет проходить сортировка
    return a.get_size() < b.get_size();
}




Matrix read_matrix(ifstream& in) {
    string word;
    int size;
    vector<int> matrix_elements;
    //читаем матрицу
    if (getline(in, word))
    {
        size = stoi(word);
        for (int i = 0; i < size * size; i++) {
            getline(in, word);
            matrix_elements.push_back(stoi(word));
        }
    }

    return Matrix(size,matrix_elements);
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Matrix> list_of_matrix;
    string word;
    ifstream in("matrix.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        //считывание матрицы
        while (getline(in, word)) {

            //считываем одну матрицу
            Matrix new_matrix = read_matrix(in);
            if (new_matrix.get_flag()) {
                list_of_matrix.push_back(new_matrix);
            }
        }
    }
    in.close();     // закрываем файл
    //записываем ответ
    ofstream out;          // поток для записи
    out.open("answer.txt"); // окрываем файл для записи
    if (list_of_matrix.empty()) {
        out << "Does not exist.";
    }
    else {
        Matrix answer = *max_element(list_of_matrix.begin(), list_of_matrix.end(), comp);
        int size = answer.get_size();
        vector<int> matrix_elements = answer.get_element();
        out << "Matrix have size: " << size << std::endl;
        out << "Matrix:" << std::endl;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                out << matrix_elements[i * size + j] << "\t";
            }
            out << endl;
        }
    }
    out.close();
    return 0;
}
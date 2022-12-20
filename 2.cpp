#include<iostream>
#include <vector>
#include <algorithm>//для сортировки
#include <fstream>
#include <string>
using namespace std;
/*
Ход работы программы:
1. создал текстовый файл формата: пустая строка, размер матрицы(след матрицы бывает только у квадратной),  записаны элементы матрицы друг за другом
2. считаваем размер матрицы и записываем ее размер, информацию о ней
3. считаем след, сохраняем как максимальный, если след матрицы больше -> переписываем информацию сохраненной матрицы, иначе читаем дальше
4. записываем в новый файл
*/


struct Matrix//структура, которая хранит в себе имя и кол-во раз сколько встретилось слово
{
private:
    int size;//размер матрицы
    int matrix_trace = 0;//след матрицы
    vector<int> matrix_elements;//элементы
public:
    //конструктор
    Matrix(int size, vector<int> matrix_elements) : size(size),  matrix_elements(matrix_elements){
        for (int i = 1; i <= size; i++) {//считаю след матрицы
            matrix_trace += matrix_elements[i * i - 1];
        }
    };
    Matrix() = delete;//чтобы нельзя было ссоздать объект без всего

    int get_size() {//выдаст кол-во которое оно встречается
        return size;
    }
    int get_trace() {//выдаст кол-во которое оно встречается
        return matrix_trace;
    }
    vector<int> get_element() {//выдаст кол-во которое оно встречается
        return matrix_elements;
    }
};

void writeanswer(Matrix a) {
    std::ofstream out;          // поток для записи
    out.open("answer.txt"); // окрываем файл для записи

    out << "Matrix with max trace: "<< a.get_trace() <<" have size: " << a.get_size() << std::endl;
    out << "Matrix:" << std::endl;

    vector<int> matrix_elements = a.get_element();
    int size = a.get_size();
    for (int i = 0; i < size;i++) {//вывод самой матрицы
        for (int j = 0; j < size; j++) {
            out << matrix_elements[i * size + j] << "\t";
        }
        out << endl;
    }
    out.close();
}


Matrix read_matrix(ifstream& in) {
    string word;
    int size;
    vector<int> matrix_elements;
    if (getline(in, word))
    {
        size = stoi(word);//перевожу в число
        for (int i = 0; i < size * size; i++) {//записываю элементы матрицы в массив
            getline(in, word);
            matrix_elements.push_back(stoi(word));
        }
    }
    return Matrix(size, matrix_elements);
}

bool comp(Matrix a, Matrix b) {//компаратор, нужен для определния как будет проходить сортировка
    return a.get_trace() < b.get_trace();
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
            Matrix new_matrix= read_matrix(in);
            list_of_matrix.push_back(new_matrix);
        }
    }
    in.close();     // закрываем файл
    //записываем ответ
    Matrix answer = *max_element(list_of_matrix.begin(), list_of_matrix.end(), comp);
    writeanswer(answer);
    return 0;
}
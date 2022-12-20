#include<iostream>
#include <vector>
#include <algorithm>//��� ����������
#include <fstream>
#include <string>
using namespace std;
/*
��� ������ ���������:
1. ������ ��������� ���� �������: ������ ������, ������ �������(���� ������� ������ ������ � ����������),  �������� �������� ������� ���� �� ������
2. ��������� ������ ������� � ���������� �� ������, ���������� � ���
3. ������� ����, ��������� ��� ������������, ���� ���� ������� ������ -> ������������ ���������� ����������� �������, ����� ������ ������
4. ���������� � ����� ����
*/


struct Matrix//���������, ������� ������ � ���� ��� � ���-�� ��� ������� ����������� �����
{
private:
    int size;//������ �������
    int matrix_trace = 0;//���� �������
    vector<int> matrix_elements;//��������
public:
    //�����������
    Matrix(int size, vector<int> matrix_elements) : size(size),  matrix_elements(matrix_elements){
        for (int i = 1; i <= size; i++) {//������ ���� �������
            matrix_trace += matrix_elements[i * i - 1];
        }
    };
    Matrix() = delete;//����� ������ ���� �������� ������ ��� �����

    int get_size() {//������ ���-�� ������� ��� �����������
        return size;
    }
    int get_trace() {//������ ���-�� ������� ��� �����������
        return matrix_trace;
    }
    vector<int> get_element() {//������ ���-�� ������� ��� �����������
        return matrix_elements;
    }
};

void writeanswer(Matrix a) {
    std::ofstream out;          // ����� ��� ������
    out.open("answer.txt"); // �������� ���� ��� ������

    out << "Matrix with max trace: "<< a.get_trace() <<" have size: " << a.get_size() << std::endl;
    out << "Matrix:" << std::endl;

    vector<int> matrix_elements = a.get_element();
    int size = a.get_size();
    for (int i = 0; i < size;i++) {//����� ����� �������
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
        size = stoi(word);//�������� � �����
        for (int i = 0; i < size * size; i++) {//��������� �������� ������� � ������
            getline(in, word);
            matrix_elements.push_back(stoi(word));
        }
    }
    return Matrix(size, matrix_elements);
}

bool comp(Matrix a, Matrix b) {//����������, ����� ��� ���������� ��� ����� ��������� ����������
    return a.get_trace() < b.get_trace();
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Matrix> list_of_matrix;
    string word;
    ifstream in("matrix.txt"); // �������� ���� ��� ������
    if (in.is_open())
    {
        //���������� �������
        while (getline(in, word)) {
            //��������� ���� �������
            Matrix new_matrix= read_matrix(in);
            list_of_matrix.push_back(new_matrix);
        }
    }
    in.close();     // ��������� ����
    //���������� �����
    Matrix answer = *max_element(list_of_matrix.begin(), list_of_matrix.end(), comp);
    writeanswer(answer);
    return 0;
}
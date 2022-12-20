#include<iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
/*
��� ������ ���������:
1. ������ ��������� ���� �������: ������ �������(���� ������� ������ ������ � ����������), ������ ������, �������� �������� ������� ���� �� ������
2. ��������� ������ ������� � ���������� �� ������, ���������� � ���, ���� ��� �����������������, �� ����, ����� ���� ������ �������
3. ���������� � ����� ����
*/


struct Matrix//���������, ������� ������ � ���� ��� � ���-�� ��� ������� ����������� �����
{
private:
    bool is_it_ok = true;//�����������������?
    int size;//������ �������
    vector<int> matrix_elements;//��������
public:
    //�����������
    Matrix(int size, vector<int> matrix_elements) : size(size), matrix_elements(matrix_elements) {
        //�������� ��� �����������������
        for (int i = 0; i < size; i++) {//����� ������
            for (int j = 0; j < size; j++) { //����� �������
                if (i > j) {
                    int z = matrix_elements[i * size + j];
                    if (z != 0) is_it_ok = false;
                }
            }
        }
    
    };
    Matrix() = delete;//����� ������ ���� �������� ������ ��� �����


    bool get_flag() {//������ ���-�� ������� ��� �����������
        return is_it_ok;
    }
    int get_size() {//������ ���-�� ������� ��� �����������
        return size;
    }
    vector<int> get_element() {//������ ���-�� ������� ��� �����������
        return matrix_elements;
    }
};


bool comp(Matrix a, Matrix b) {//����������, ����� ��� ���������� ��� ����� ��������� ����������
    return a.get_size() < b.get_size();
}




Matrix read_matrix(ifstream& in) {
    string word;
    int size;
    vector<int> matrix_elements;
    //������ �������
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
    ifstream in("matrix.txt"); // �������� ���� ��� ������
    if (in.is_open())
    {
        //���������� �������
        while (getline(in, word)) {

            //��������� ���� �������
            Matrix new_matrix = read_matrix(in);
            if (new_matrix.get_flag()) {
                list_of_matrix.push_back(new_matrix);
            }
        }
    }
    in.close();     // ��������� ����
    //���������� �����
    ofstream out;          // ����� ��� ������
    out.open("answer.txt"); // �������� ���� ��� ������
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
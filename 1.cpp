#include<iostream>
#include <vector>//��� �������
#include <fstream>//��� �������� �����
#include <algorithm>//��� ����������
#include <string>//������
using namespace std;
/*
��� ������ ���������:
1. ��������� �������� Reservedfile ������ ��� ���� � ��������� ������ ���(0,�����)
2. ����������� �������� Text file ���-�� ��������� ������� ����� � ��������� � ����
3. �������� � �����
4. ��������� � reserved �������� writesorted
*/



struct Word_Count//���������, ������� ������ � ���� ��� � ���-�� ��� ������� ����������� �����
{
private:
    string word;//���� �����
    int count = 0;//������� ��� ��� �����������
public:
    Word_Count(string word) : word(word) {};//�����������
    Word_Count() = delete;//����� ������ ���� �������� ������ ��� �����
    void operator++(int) {//���������� �� 1 �������
        count += 1;
    }

    string getName(){//������ �����
        return word;
    }
    int getcount(){//������ ���-�� ������� ��� �����������
        return count;
    }
};

vector<Word_Count> Reservedfile(){
    vector<Word_Count>read_file;
    string word;
    ifstream in("reservedwords.txt"); // �������� ���� ��� ������
    if (in.is_open())
    {
        while (getline(in, word))//���� ���� �������� �� in ������ ����� � word
        {
            read_file.push_back(Word_Count(word));//����� ������ ���� (0,�����)
        }
    }
    in.close();     // ��������� ����
    return read_file;
}

void count_words(vector<Word_Count>& words) {
    string word;
    ifstream in("text.txt"); // �������� ���� ��� ������
    if (in.is_open())
    {
        while (getline(in, word))
        {
            for (auto& n: words) {//��� � ������� ���� � ������ ������ 
                if (n.getName() == word) {//(�����: �����)
                    n++;
                    break;
                }
            }
        }
    }
    in.close();     // ��������� ����
}

void writesorted(vector<Word_Count>read_file) {
    std::ofstream out;          // ����� ��� ������
    out.open("reservedwords.txt"); // �������� ���� ��� ������
    for (auto& i: read_file) {
        if (out.is_open()) {
            out << i.getName() << std::endl;
        }
    }
    out.close();
}


bool comp(Word_Count a, Word_Count b) {//����������, ����� ��� ���������� ��� ����� ��������� ����������
    return a.getcount() > b.getcount();
}

int main() {
    setlocale(LC_ALL, "Russian");//�++ ���� ������� ����
    vector<Word_Count> words = Reservedfile();
    count_words(words);
    sort(words.begin(), words.end(),comp);//�������� ������
    writesorted(words);
    for (auto item : words) {
        cout << "{" << item.getName() << ","
            << item.getcount() << "}" << endl;;
    }
    return 0;
}
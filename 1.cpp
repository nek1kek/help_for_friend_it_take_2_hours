#include<iostream>
#include <vector>//для массива
#include <fstream>//для открытия файло
#include <algorithm>//для сортировки
#include <string>//строки
using namespace std;
/*
Ход работы программы:
1. считаываю функцией Reservedfile нужным нам файл и возвращаю вектор пар(0,слово)
2. подсчитываю функцией Text file кол-во вхождений каждого слова и записываю в пару
3. сортирую в мейне
4. записываю в reserved функцией writesorted
*/



struct Word_Count//структура, которая хранит в себе имя и кол-во раз сколько встретилось слово
{
private:
    string word;//само слово
    int count = 0;//сколько раз оно встречалось
public:
    Word_Count(string word) : word(word) {};//конструктор
    Word_Count() = delete;//чтобы нельзя было ссоздать объект без слова
    void operator++(int) {//увеличение на 1 элемент
        count += 1;
    }

    string getName(){//выдаст слово
        return word;
    }
    int getcount(){//выдаст кол-во которое оно встречается
        return count;
    }
};

vector<Word_Count> Reservedfile(){
    vector<Word_Count>read_file;
    string word;
    ifstream in("reservedwords.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, word))//пока могу получить из in строку кладу в word
        {
            read_file.push_back(Word_Count(word));//кладу массив пару (0,слово)
        }
    }
    in.close();     // закрываем файл
    return read_file;
}

void count_words(vector<Word_Count>& words) {
    string word;
    ifstream in("text.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, word))
        {
            for (auto& n: words) {//ищу в массиве пару с данным именем 
                if (n.getName() == word) {//(число: слово)
                    n++;
                    break;
                }
            }
        }
    }
    in.close();     // закрываем файл
}

void writesorted(vector<Word_Count>read_file) {
    std::ofstream out;          // поток для записи
    out.open("reservedwords.txt"); // окрываем файл для записи
    for (auto& i: read_file) {
        if (out.is_open()) {
            out << i.getName() << std::endl;
        }
    }
    out.close();
}


bool comp(Word_Count a, Word_Count b) {//компаратор, нужен для определния как будет проходить сортировка
    return a.getcount() > b.getcount();
}

int main() {
    setlocale(LC_ALL, "Russian");//с++ знал русский язык
    vector<Word_Count> words = Reservedfile();
    count_words(words);
    sort(words.begin(), words.end(),comp);//сортирую вектор
    writesorted(words);
    for (auto item : words) {
        cout << "{" << item.getName() << ","
            << item.getcount() << "}" << endl;;
    }
    return 0;
}
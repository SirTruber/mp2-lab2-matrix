// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <cstdlib>
#include "tmatrix.h"

#define type float // не придумал как обрабатывать ввод типа пользователем
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

bool USE_MANUAL_INPUT = false;
enum CHOISE {EXIT,MUL_SCAL,MUL_VEC,MUL,ADD,SUB};
int min_el = -100;
int max_el = 100;
//enum DATA_TYPE {NO,INT,DOUBLE,FLOAT};
//---------------------------------------------------------------------------
type rnd() {
    return (min_el + rand() % (100 * (max_el - min_el)) / static_cast<type>(100));
}
void menu(TDynamicMatrix<type> a, size_t size) {

    CHOISE ch = EXIT;

    cout << "1.УМНОЖИТЬ НА ЧИСЛО"
        << endl << "2.УМНОЖИТЬ НА ВЕКТОР"
        << endl << "3.УМНОЖИТЬ НА МАТРИЦУ"
        << endl << "4.ПРИБАВИТЬ МАТРИЦУ"
        << endl << "5.ВЫЧЕСТЬ МАТРИЦУ"
        << endl << "0.ВЫХОД"
        << endl << endl;
    scanf_s("%d", &ch);
    switch (ch)
    {
    case EXIT:
        exit(0);
        break;
    case MUL_SCAL:
    {
        type scal = 0;

        if (USE_MANUAL_INPUT == true)
        {
            cout << "Введите скаляр"
                << endl;
            cin >> scal;
        }
        else
        {
            scal = rnd();
        }
        cout << "Матрица:"<<
            endl << a << 
            endl << "Скаляр" << 
            endl << endl << scal << endl << 
            endl << "Результат" << 
            endl << a * scal << 
            endl ;
        break;
    }
    case MUL_VEC:
    {
        TDynamicVector<type> vec(size);
        if (USE_MANUAL_INPUT == true)
        {
            cout << "Введите вектор"
                << endl;
            cin >> vec;
        }
        else
        {
            for (size_t i = 0; i < size; i++) {
                vec[i] = rnd();
            }
        }
        cout << "Матрица:" <<
            endl << a <<
            endl << "Вектор" <<
            endl << vec <<
            endl << "Результат" <<
            endl << a * vec <<
            endl;
        break;
    }
    case MUL:
    {
        TDynamicMatrix<type> b(size);
        if (USE_MANUAL_INPUT == true)
        {
            cout << "Введите матрицу"
                << endl;
            cin >> b;
        }
        else
        {
            for (size_t i = 0; i < size; i++) {
                for (size_t j = 0; j < size; j++) {
                    b[i][j] = rnd();
                }
            }
        }
        cout << "Матрица 1 :" <<
            endl << a <<
            endl << "Матрица 2 :" <<
            endl << b <<
            endl << "Результат :" <<
            endl << a * b <<
            endl;
        break;
    }
    case ADD:
    {
        TDynamicMatrix<type> b(size);
        if (USE_MANUAL_INPUT == true)
        {
            cout << "Введите матрицу"
                << endl;
            cin >> b;
        }
        else
        {
            for (size_t i = 0; i < size; i++) {
                for (size_t j = 0; j < size; j++) {
                    b[i][j] = rnd();
                }
            }
        }
        cout << "Матрица 1 :" <<
            endl << a <<
            endl << "Матрица 2 :" <<
            endl << b <<
            endl << "Результат :" <<
            endl << a + b <<
            endl;
        break;
    }
    case SUB:
    {
        TDynamicMatrix<type> b(size);
        if (USE_MANUAL_INPUT == true)
        {
            cout << "Введите матрицу"
                << endl;
            cin >> b;
        }
        else
        {
            for (size_t i = 0; i < size; i++) {
                for (size_t j = 0; j < size; j++) {
                    b[i][j] = rnd();
                }
            }
        }
        cout << "Матрица 1 :" <<
            endl << a <<
            endl << "Матрица 2 :" <<
            endl << b <<
            endl << "Результат :" <<
            endl << a - b <<
            endl;
        break;
    }
    default:
        cout << "ОШИБОЧНЫЙ ВВОД!" << endl;
        break;
    }
    system("PAUSE");
}

void main()
{
    size_t size = 0;

    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    cout << "Введите размер матрицы"
        << endl;
    scanf("%d", &size);
    TDynamicMatrix<type> a(size);
    if (USE_MANUAL_INPUT == true)
    {
        cout << "Введите матрицу" << endl;
        cin >> a;
    }
    else
    {
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                a[i][j] = rnd();
            }
        }
    }
    system("CLS");
    while (1) {
        cout << "Тестирование класс работы с матрицами"
            << endl << "Размер матрицы:" << size 
            << endl << "Тип данных: " << TOSTRING(type)
            << endl << endl;
        menu(a, size);
        system("CLS");
    }
}
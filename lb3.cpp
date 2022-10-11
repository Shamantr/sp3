#include <iostream>
#include <ctime>
#include <random>
#include <string>

using namespace std;


extern "C" {
	const int sz = 10; //Размер массивов
	int sz_a = 10;
	int A[sz]; // Первый исходный массив
	int B[sz]; // Второй исходный массив
	int D[sz]; // Результирующий массив
	string a = " ";
	string b = " ";
};


int main() {
    srand(time(0)); // Инициализация ГПСЧ

    // Инициализация исходных массивов
    for (int i = 0; i < sz; ++i){
	A[i] = rand() % 50;
	a += to_string(A[i]) + "\t";

	B[i] = rand() % 50;
	b += to_string(B[i]) + "\t";

	D[i] = 0;
    }

    // Вывод исходных массивов
    cout << " A:" << a << endl;
    cout << " B:" << b << endl;

    // Ассемблерная вставка
    __asm(R"(
	    .intel_syntax noprefix;

	    mov esi, 0;            // Адресный регистр
	    mov dl, 0;		   // Счётчик
	    l_st:
	    mov eax, A[esi];	   // Взятие A[i]
	    mov ebx, B[esi];       // Взятие B[i]
	    cmp eax, ebx;          // A[i] > B[i] ?
	    jg greater;
	    mov D[esi], ebx;       // B[i] -> D[i]
	    jmp l_m;               // Обход альтернативы
	    greater:
	    mov D[esi], eax;       // A[i] -> D[i]
	    l_m:
	    add esi, 4;            // Сдвиг отн. адреса на 1 эл. массива
	    add dl, 1;             // Увеличение счётчика
	    cmp dl, BYTE PTR sz_a; // Проверка счётчика
	    jl l_st;               // КЦ если равен пределу

	    .att_syntax noprefix;
	)"
    );

    // Вывод результирующего массива
    cout << " D: ";
    for (int i = 0; i < sz; ++i){
	cout << D[i] << "\t";
    }
    cout << endl;

    return 0;
}

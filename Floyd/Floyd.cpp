#include <iostream>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

class Algorytm
{
public:
    Algorytm(); // конструктор по умолчанию
    ~Algorytm(); // деструктор
    void Print(bool arr); // функция вывода матрицы путей/значений, в зависимости от значения полученого аргумента
    void NodeIni(); // инициализация массивов хранящих все пути/значения
    void Calculations();
    void SetConection(int FirstNode, int SecondNode, double value); // добавление связи между передаными узлами и расстояния между ними
    void SaveFirstGraf(); // сохранение первых версий каждой из таблиц
    void ShowFirstGraf(bool ways); // показ первой версии одной из таблиц
private:
    double** DirectionValues; // массив, который хранит кратчайшее расстояние, которое потребуется для перемещения из одного узла в другой, где индексы соотвествуют номерам узлов  ля получения значения для конкретной пары
    string** AllWays; // массив, который хранит полный кратчайший путь между преодолеваемыемы узлами, где индексы соотвествуют номерам узлов для получения значения для конкретной пары
    int NodeCount; // общее количество узлов в графе
    string FirstWays; // переменная для хранения первого полученого массива маршрутов
    string FirstValues; // переменная для хранения первого полученого массива расстояний между каждым из узлов
};

Algorytm::Algorytm()
{
    cout << "Type how many nodes you need:";
    cin >> NodeCount;
    DirectionValues = new double* [NodeCount];
    AllWays = new string* [NodeCount];
    for (auto i = 0; i < NodeCount; i++)
        DirectionValues[i] = new double[NodeCount], AllWays[i] = new string[NodeCount];
}

Algorytm::~Algorytm()
{
    for (auto i = 0; i < NodeCount; i++)
        delete[] DirectionValues[i], delete[] AllWays[i];
    delete[] DirectionValues, delete[] AllWays;
}

void Algorytm::Print(bool values)
{
    for (auto i = 0; i < NodeCount; i++)
    {
        cout << i + 1 << " ";
        for (auto j = 0;  j < NodeCount;  j++)
        {
            if (values)
                cout << DirectionValues[i][j] << " #" << j + 1 << "# ";
            else
                cout << AllWays[i][j] << " #" << j + 1 << "# ";
        }
        cout << endl;
    }
    cin >> values;
}

void Algorytm::NodeIni()
{
    for (auto i = 0; i < NodeCount; i++)
    {
        for (auto j = 0; j < NodeCount; j++)
        {
            if (i == j)
            {
                DirectionValues[i][j] = 0; // если индексы одинаковые это ознает что никуда перемещаться не нужно и соотвественно расстояние равно 0
                AllWays[i][j] = to_string(i + 1); // в массив с путями записывает только начальный узел, так как он так же является конечным в данной паре
            }
            else
            {
                DirectionValues[i][j] = numeric_limits<double>::infinity(); // в другом случае инициализируем все бесконечностью означающей что связи между узлами не существует
                AllWays[i][j] = ""; // в массиве с путями ничего не записываем, это означает что для данной пары не предусмотрен никакой путь
            }
        }
    }
}

void Algorytm::Calculations()
{
    for (auto k = 0; k < NodeCount; k++)
    {
        for (auto i = 0; i < NodeCount; i++)
        {
            for (auto j = 0; j < NodeCount; j++)
            {
                if (DirectionValues[i][j] > DirectionValues[i][k] + DirectionValues[k][j]) // проверка является ли длина конечного расстояния старого пути больше чем нового найденого 
                {
                    // в случае если новый найденый путь является короче чем предыдущий - элемент текущей итерации перезаписывается
                    DirectionValues[i][j] = DirectionValues[i][k] + DirectionValues[k][j];
                    // конечный узел пути равен переменной j + 1 которая отвечает за первый выбраный узел в текущей итерации по координате х
                    // + 1 так индексация массива начинается с 0 а узлы начинаются с 1
                    AllWays[i][j] = AllWays[i][k] + " -> " + to_string(j + 1);
                }
            }
        }
    }
}

void Algorytm::SetConection(int FirstNode, int SecondNode, double value)
{
    if (FirstNode > 0 && FirstNode <= NodeCount && SecondNode > 0 && SecondNode <= NodeCount)
    {
        // устанавливаем полученое значение для обоих заданых узлов
        DirectionValues[FirstNode - 1][SecondNode - 1] = value;
        DirectionValues[SecondNode - 1][FirstNode - 1] = value;
        // устанавливаем путь для обоих заданых узлов 
        AllWays[FirstNode - 1][SecondNode - 1] = to_string(FirstNode) + " -> " + to_string(SecondNode);
        AllWays[SecondNode - 1][FirstNode - 1] = to_string(SecondNode) + " -> " + to_string(FirstNode);
    }
    else // если номера полученных узлов выходит за диапазоп всех доступных узлов
        cout << endl << "Incorrect data!";
}
void Algorytm::SaveFirstGraf()
{
    for (auto i = 0; i < NodeCount; i++)
    {
        FirstValues += to_string(i + 1) + " ";
        FirstWays += to_string(i + 1) + " ";
        for (auto j = 0; j < NodeCount; j++)
        {
                FirstValues += to_string(DirectionValues[i][j]) + " #" + to_string(j + 1) + "# ";
                FirstWays += AllWays[i][j] + " #" + to_string(j + 1) + "# ";
        }
        FirstValues += "\n";
        FirstWays += "\n";
    }
}
void Algorytm::ShowFirstGraf(bool ways)
{
    if (ways)
        cout << "First version of minimal ways matrix for every node pairs:\n" << FirstWays << endl;
    else
        cout << "First version of minimal values matrix for every node pairs:\n" << FirstValues << endl;
}
class Menu
{
public:
    Menu(); // В констукторе динамически выделяем память для объекта графа и выполняем инициализацию его массивов
    ~Menu(); // деструктор
    void PrintWays(); // вывод матрицы растояний
    void PrintValues();// вывод матрицы путей
    void NewAlgorytm(); // удаление старого графа и создание нового экземпляра
    void AddConection(); // добавление связи между заданными узлами
    void ShortestWay(); // рассчет кратчайщих путей и вывод соотвствующего в зависимости от заданного начального и конечного узлов
    bool ShowMenu(); // метод показа меню для взаимодействия с программой
private:
    Algorytm* MainAlgorytm; // поле графа
};

Menu::Menu()
{
    MainAlgorytm = new Algorytm();
    MainAlgorytm->NodeIni();
}

Menu::~Menu()
{
    delete MainAlgorytm;
}

void Menu::PrintWays()
{
    system("cls");
    MainAlgorytm->Print(0);
}

void Menu::PrintValues()
{
    system("cls");
    MainAlgorytm->Print(1);
}

void Menu::NewAlgorytm()
{
    system("cls");
    delete MainAlgorytm;
    MainAlgorytm = new Algorytm();
    MainAlgorytm->NodeIni();
    cout << "You succsecfully create new graf";
}

void Menu::AddConection()
{
    int first_node, second_node;
    double value;
    system("cls");
    do
    {
        cout << "Type number of the first node to conect(Type 0 to exit):";
        cin >> first_node;
        if (first_node == 0)
            break;
        cout << endl << "Type number of the second node to connect with first(Type 0 to exit):";
        cin >> second_node;
        if (second_node == 0)
            break;
        cout << endl << "Good. Last more step - type value between this two nodes(Type 0 to exit):";
        cin >> value;
        if (value == 0)
            break;
        cout << endl << "Your connection succsecfully added";
        MainAlgorytm->SetConection(first_node, second_node, value);
        cout << endl;
    } while (true); // повторяем ввод данных пока пользователь не захочет прекратить добавление новых связей
    MainAlgorytm->SaveFirstGraf();
    Sleep(1000);
}

void Menu::ShortestWay()
{
    MainAlgorytm->Calculations();
    system("cls");
    cout << "The shortest ways for each of nodes: " << endl; // отображения все кратчайших путей в виде таблицы 
    MainAlgorytm->Print(0);
    MainAlgorytm->ShowFirstGraf(1);
    cout << "\nThe value for ways of each of nodes: " << endl; // отображения расстояния между всеми узлами в виде таблицы
    MainAlgorytm->Print(1);
    MainAlgorytm->ShowFirstGraf(0);
}

bool Menu::ShowMenu()
{
    short answer;
    system("cls");
    cout << 5 / 2 << endl;
    cout << "1 - Create new graf; \n2 - Add connection; \n3 - Show all current ways matrix; \n4 - Show current value matrix; \n5 - Calculate shortest way; \n0 - exit;\n";
    cin >> answer;
    if (answer == 1)
        NewAlgorytm();
    else if (answer == 2)
        AddConection();
    else if (answer == 3)
        PrintWays();
    else if (answer == 4)
        PrintValues();
    else if (answer == 5)
        ShortestWay();
    else
    {
        cout << endl << "Thanks for using, bye!";
        Sleep(1000);
        return true;
    }
    return false;
}

int main()
{
    Menu m;
    do
    {
    } while (m.ShowMenu() != true); // вызов метода меню пока пользователь не выйдет из него
}

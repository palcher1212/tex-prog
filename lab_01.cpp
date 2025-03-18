#include <iostream>
#include <string>
using namespace std;

//представляет автомобиль : год выпуска, сколько дтп и что сломано.
class Semerka {
public:
    int year;
    double skolkodtp;
    string chtoslomanno;

    // Конструктор для инициализации объекта Semerka
    Semerka(int y, double dtp, string slomanno) : year(y), skolkodtp(dtp), chtoslomanno(slomanno) {}
};

//узел в связном списке, указатель на объект  и указатель на следующий узел.
class Element {
public:
    Semerka* data;
    Element* next;

    //конструктор для инициализации узла семерки
    Element(Semerka* semerkaObj) : data(semerkaObj), next(nullptr) {}
};

// связный список узлов, содержащих объекты Semerka.
class boevaiklassika {
private:
    Element* head;  // указатель на первый узел 
public:
    //конструктор для инициализации пустого списка
    boevaiklassika() : head(nullptr) {}

    // вывод всех автомобилей 
    void display() {
        Element* temp = head;
        while (temp) {
            cout << temp->data->year << " " << temp->data->skolkodtp << " " << temp->data->chtoslomanno << endl;
            temp = temp->next;
        }
    }

    // добавление по  индексу
    void insert(int index, Semerka* semerkaObj) {
        if (index == 0) {
            addFirst(semerkaObj);  //если индекс 0
            return;
        }
        Element* temp = head;
        for (int i = 0; temp && i < index - 1; i++)
            temp = temp->next;
        if (!temp) return;
        Element* newElement = new Element(semerkaObj);
        newElement->next = temp->next;
        temp->next = newElement;
    }

    // добавление в конец списка
    void append(Semerka* semerkaObj) {
        Element* newElement = new Element(semerkaObj);
        if (!head) {
            head = newElement;  //если список пуст, новый узел становится первым
            return;
        }
        Element* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newElement;
    }

    //добавление в начало списка
    void addFirst(Semerka* semerkaObj) {
        Element* newElement = new Element(semerkaObj);
        newElement->next = head;
        head = newElement;
    }

    //удаление по указанному индексу
    void remove(int index) {
        if (!head) return;
        if (index == 0) {
            Element* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Element* temp = head;
        for (int i = 0; temp->next && i < index - 1; i++)
            temp = temp->next;
        if (!temp->next) return;
        Element* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
};

// мейн
int main() {
    setlocale(LC_ALL," ");
    boevaiklassika list;
    while (true) {
        int choice;
        cout << "1. Напечатать все\n2. Добавить по индексу\n3. Добавить в конец\n4. Добавить в начало\n5. Удалить по индексу\n0. Выход\nВыбор: ";
        cin >> choice;
        if (choice == 0) break;
        if (choice == 1) list.display();
        else if (choice == 2) {
            int index, year;
            double dtp;
            string slomanno;
            cout << "Введите индекс, год, сколько дтп, что сломано: ";
            cin >> index >> year >> dtp >> slomanno;
            list.insert(index, new Semerka(year, dtp, slomanno));
        }
        else if (choice == 3) {
            int year;
            double dtp;
            string slomanno;
            cout << "Введите год, сколько дтп, что сломано: ";
            cin >> year >> dtp >> slomanno;
            list.append(new Semerka(year, dtp, slomanno));
        }
        else if (choice == 4) {
            int year;
            double dtp;
            string slomanno;
            cout << "Введите год, сколько дтп, что сломано: ";
            cin >> year >> dtp >> slomanno;
            list.addFirst(new Semerka(year, dtp, slomanno));
        }
        else if (choice == 5) {
            int index;
            cout << "Введите индекс: ";
0            cin >> index;
            list.remove(index);
        }
    }
}

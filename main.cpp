#include <iostream>
using namespace std;

struct Node       //Структура являющаяся звеном списка
{
    Node()
    {
        x = 0;
        y = 0;
        next = nullptr;
        prev = nullptr;
    }
    Node(int a, int b)
    {
        x = a;
        y = b;
        next = nullptr;
        prev = nullptr;
    }
    int x;
    int y;     //Значение x будет передаваться в список
    Node *next,*prev; //Указатели на адреса следующего и предыдущего элементов списка
};


struct List   //Создаем тип данных Список
{
    Node *head;
    Node *tail;  //Указатели на адреса начала списка и его конца
    List() {
        head = tail = nullptr;
    }
};


void add( List *list, int x, int y )
{
    Node *temp = new Node(); // Выделение памяти под новый элемент структуры
    temp->next = nullptr;       // Указываем, что изначально по следующему адресу пусто
    temp->x = x;
    temp->y = y;             // Записываем значение в структуру

    if ( list->head != nullptr ) // Если список не пуст
    {
        temp->prev = list->tail; // Указываем адрес на предыдущий элемент в соотв. поле
        list->tail->next = temp; // Указываем адрес следующего за хвостом элемента
        list->tail = temp;       //Меняем адрес хвоста
    }
    else //Если список пустой
    {
        temp->prev = nullptr; // Предыдущий элемент указывает в пустоту
        list->head = list->tail = temp;    // Голова=Хвост=тот элемент, что сейчас добавили
    }
}


void print( List * list )
{
    Node * temp = list->head;  // Временно указываем на адрес первого элемента
    while( temp != nullptr )      // Пока не встретим пустое значение
    {
        cout << "(" << temp->x << ";" << temp->y << ")" << " "; //Выводим значение на экран
        cout << "\n";
        temp = temp->next;     //Смена адреса на адрес следующего элемента
    }
}



Node* search_node_end (List *list, int x, int y)  // 3
{
    Node *temp = list->tail;
    while (temp) {
        if (temp->x == x & temp->y == y) {
            return temp;
        }
        temp = temp->prev;
    }
    return temp;
}



    Node* search_node_beginning (List *list, int x, int y)  // 3
    {
        Node *temp = list->head;
        while (temp) {
            if (temp->x == x & temp->y == y) {
                return temp;
            }
            temp = temp->next;
        }
        return temp;
    }



void insert (List *list, Node *node, int i)  // 4
{
    Node *temp = list->head;
    while ((i > 1) && (temp)) {
        temp= temp->next;
        i--;
    }
    if (temp) {
        if (list->tail == temp) {
            list->tail = node;
        }
        if (list->head == temp) {
            list->head = node;
        }
        node->prev = temp->prev;
        node->next = temp;
        if (temp->prev != nullptr) {
            temp->prev->next = node;
        }
        temp->prev = node;
    } else {
        add(list, node->x, node->y);
    }
}

void  delete_from_list(List *list, int i)  // 5
{
    Node *temp = list->head;
    while ((i > 1) && (temp)) {
        temp= temp->next;
        i--;
    }
    if (temp != nullptr) {
        if (list->tail == temp) {
            list->tail = temp->prev;
        }
        if (list->head == temp) {
            list->head = temp->next;
        }
        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        }
        if(temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }
        delete temp;
    }
}

Node* first_equal(List*list) {
    Node *temp = list->head;
    while (temp) {
        if (temp->x == temp->y) {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

int main () {
    List list = List();
    for (int i = 0; i < 10; i++) {
        add(&list, rand()%10, rand()%10); //Заполняем список 20 случайными значениями
    }
    print(&list);
    cout << "\n";
    Node *bnode = search_node_beginning(&list, 7, 3);
    cout << "Searching from the beginning. Previous point:(" << bnode->prev->x << ";" << bnode->prev->y<<")";
    cout << "Next point:(" << bnode->next->x << ";" << bnode->next->y << ")";
    cout<< "\n";
    Node *enode = search_node_end(&list, 7, 3); // 3
    cout << "Searching from the end. Previous point:(" << enode->prev->x << ";" << enode->prev->y<<")";
    cout << "Next point:(" << enode->next->x << ";" << enode->next->y << ")";
    cout<< "\n";
    int a, b, d;
    cout << "Input the point you would like to add and the place:";
    cin >> a;
    cin>>b;
    cin>>d;
    cout<< "\n";
    Node InsertNode = Node(a,b);
    insert(&list, &InsertNode, d);
    print(&list);
    int c;
    cout<< "Input the place of the point you want to delete:";
    cin >> c;
    cout<<"\n";
    delete_from_list(&list, c);
    print(&list);
    Node* EqualNode = first_equal(&list);
    cout << "A point with x=y:(" << EqualNode->x<<";"<<EqualNode->y<<")";
    cout<<"\n";
    cout<<"Previous point:(" << EqualNode->prev->x << ";" << EqualNode->prev->y<<")";
    cout<< "\n";
    cout << "Next point:(" << EqualNode->next->x << ";" << EqualNode->next->y << ")";}

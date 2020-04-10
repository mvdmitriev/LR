#include "stdafx.h"
#include "iostream"
#include "string"

using namespace std;

class Monitor
{
protected:
	int id, width, height;

public:
	virtual bool scompare(const Monitor& monik2) {
		return (height == monik2.height && width == monik2.width);
	}

	virtual void pprint() {
		cout << "ID: " << id << endl
			<< "Разрешение: " << width << "x" << height << endl;
	}

	virtual void pread() {
		cout << "ID: "; scanf("%d", &id);
		cout << "Ширина экрана: "; scanf("%d", &width);
		cout << "Высота экрана: "; scanf("%d", &height);
	}

	virtual bool comparid(const int& _id) {
		return (id == _id);
	}

	Monitor()
	{
		this->id = 0;
		this->width = 0;
		this->height = 0;
	}

	Monitor(int _id, int _width, int _height)
	{
		this->id = _id;
		this->width = _width;
		this->height = _height;
	}

	virtual bool operator== (const Monitor & monik2)
	{
		return this->scompare(monik2);
	}

	virtual bool operator== (const int & monik2)
	{
		return this->comparid(monik2);
	}
};

class Gamer_Monitor :virtual public Monitor
{
protected:
	int Rate;

public:
	void pprint() {
		Monitor::pprint();
		cout << "Частота: " << Rate << endl;
	}

	void pread() {
		Monitor::pread();
		cout << "Частота: "; scanf("%d", &Rate);
	}

	Gamer_Monitor() :Monitor()
	{
		Rate = 0;
	}

	Gamer_Monitor(int _id, int _width, int _height, int _rate) :Monitor(_id, _width, _height)
	{
		Rate = _rate;
	}
};

class TV :virtual public Monitor
{
protected:
	int db;

public:
	void pprint() {
		Monitor::pprint();
		cout << "Макс. громкость, дб: " << db << endl;
	}
	
	void pread() {
		Monitor::pread();
		cout << "Макс. громкость, дб: "; scanf("%d", &db);
	}

	TV() :Monitor()
	{
		db = 0;
	}

	TV(int _id, int _width, int _height, int _db) :Monitor(_id, _width, _height)
	{
		db = _db;
	}
};

class Smart_TV :public Gamer_Monitor, public TV
{
public:
	virtual void pprint() {
		Gamer_Monitor::pprint();
		cout << "Макс. громкость, дб: " << db << endl;
	}

	virtual void pread() {
		Gamer_Monitor::pread();
		cout << "Макс. громкость, дб: "; scanf("%d", &db);
	}

	Smart_TV() :Gamer_Monitor()
	{
		db = 0;
	}

	Smart_TV(int _id, int _width, int _height, int _rate, int _db) :Gamer_Monitor(_id, _width, _height, _rate)
	{
		db = _db;
	}
};

class Big_TV :public Smart_TV
{
private:
	bool big_sound;

public:
	virtual void pprint() {
		Smart_TV::pprint();
		cout << "Объёмный звук (1 - есть, 0 - нет): " << (int)big_sound << endl;
	}

	virtual void pread() {
		Smart_TV::pread();
		cout << "Объёмный звук (1 - есть, 0 - нет): "; scanf("%d", &big_sound);
	}

	Big_TV() :Smart_TV()
	{
		big_sound = 0;
	}

	Big_TV(int _id, int _width, int _height, int _rate, int _db, bool _bs) :Smart_TV(_id, _width, _height, _rate, _db)
	{
		big_sound = _bs;
	}
};

class Stec {
	//данные, скрытые от пользователя
private:
	struct Node {
		Monitor* data;
		Node* next;
	};
	Node* top;

	//методы для редактирования стэка
public:
	Stec()
	{
		this->top = NULL;
	}

	Stec(const Stec& paren)
	{
		this->top = paren.top;
	}

	~Stec()
	{
		top = NULL;
	}

	void push(Monitor* value) {
		Node* tmp = new Node;
		tmp->next = top;
		top = tmp;
		top->data = value;
	}

	void pop() {
		top = top->next;
	}

	bool empty() const {
		return top == NULL;
	}

	//перегруженные операторы
	Stec& operator = (const Stec& paren)
	{
		this->~Stec();
		this->top = paren.top;
	}

	friend ostream& operator << (ostream& out, const Stec& stek)
	{
		if (!stek.empty())
		{
			stek.top->data->pprint();
			out << endl << endl;
		}
		else out << "Полка пуста" << endl << endl;
		return out;
	}


	//методы для обработки стэка

	void poisk_count(Monitor* monik)
	{
		int i = 0;
		Node* tmp = top;
		while (tmp)
		{
			if (*tmp->data == *monik)
				i++;

			tmp = tmp->next;
		}
		if (i) cout << "Найдено мониторов: " << i << endl;
		else cout << "Мониторов не найдено" << endl;
	}
	
	void poisk_count(int _id)
	{
		int i = 0;
		Node* tmp = top;
		while (tmp)
		{
			if (*tmp->data == _id)
				i++;

			tmp = tmp->next;
		}
		if (i) cout << "Найдено мониторов: " << i << endl;
		else cout << "Мониторов не найдено" << endl;
	}

	void poisk_count(string namen)
	{
		int i = 0;
		Node* tmp = top;
		while (tmp)
		{
			if (typeid(*tmp->data).name() == namen)
				i++;

			tmp = tmp->next;
		}
		if (i) cout << "Найдено мониторов: " << i << endl;
		else cout << "Мониторов не найдено" << endl;
	}

	void poisk_first(Monitor* monik)
	{
		int i = 1;
		Node* tmp = top;
		bool fl = false;
		while (tmp && !fl)
		{
			if (*tmp->data == *monik)
			{
				fl = true;
				break;
			}
			else
			{
				i++;
				tmp = tmp->next;
			}
		}
		if (fl) cout << "Ближайший монитор на " << i << " позиции на полке" << endl;
		else cout << "Данного монитора на полке нет" << endl;
	}
	
	void poisk_first(int _id)
	{
		int i = 1;
		Node* tmp = top;
		bool fl = false;
		while (tmp)
		{
			if (*tmp->data == _id)
			{
				fl = true;
				break;
			}
			else
			{
				i++;
				tmp = tmp->next;
			}
		}
		if (fl) cout << "Ближайший монитор на " << i << " позиции на полке" << endl;
		else cout << "Данного монитора на полке нет" << endl;
	}

	void poisk_first(string namen)
	{
		int i = 1;
		Node* tmp = top;
		bool fl = false;
		while (tmp)
		{
			if (typeid(*tmp->data).name() == namen)
			{
				fl = true;
				break;
			}
			else
			{
				i++;
				tmp = tmp->next;
			}
		}
		if (fl) cout << "Ближайший монитор на " << i << " позиции на полке" << endl;
		else cout << "Данного монитора на полке нет" << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");

	Stec moniks;
	Gamer_Monitor razer(228, 1366, 768, 228);
	moniks.push(&razer);
	int doin = 1;

	while (doin > 0 && doin <= 6)
	{
		cout << "Выберите действие:" << endl
			<< "0 - выход" << endl
			<< "1 - положить устройство на полку" << endl
			<< "2 - снять устройство с полки" << endl
			<< "3 - поиск интересующего устройства" << endl
			<< "4 - подсчёт интересующих устройств" << endl
			<< "5 - просмотреть информацию о крайнем устройстве на полке" << endl
			<< "6 - убрать все устройства с полки" << endl;
		scanf("%d", &doin);

		switch (doin)
		{
		case 1:
		{
			cout << "Выберите тип устройства: " << endl
				<< "1 - Рабочий монитор" << endl
				<< "2 - Игровой монитор" << endl
				<< "3 - Телевизор" << endl
				<< "4 - Smart-TV" << endl
				<< "5 - Домашний кинотеатр" << endl
				<< "0 - Отмена" << endl << endl;
			int chs;
			scanf("%d", &chs);
			while (!(chs >= 0 && chs <= 5))
			{
				cout << "Введите корректный номер" << endl;
				scanf("%d", &chs);
			}
			if (chs == 1)
			{
				Monitor monik;
				monik.pread();
				moniks.push(&monik);
			}
			else if (chs == 2)
			{
				Gamer_Monitor monik;
				monik.pread();
				moniks.push(&monik);
			}
			else if (chs == 3)
			{
				TV monik;
				monik.pread();
				moniks.push(&monik);
			}
			else if (chs == 4)
			{
				Smart_TV monik;
				monik.pread();
				moniks.push(&monik);
			}
			else if (chs == 5)
			{
				Big_TV monik;
				monik.pread();
				moniks.push(&monik);
			}
			break;
		}

		case 2:
			if (moniks.empty()) { cout << "Полка пуста" << endl; system("pause"); }
			else
			{
				moniks.pop();
			}
			cout << endl;
			break;

		case 3: {
			if (moniks.empty()) cout << "Полка пуста" << endl;
			else
			{
				cout << "Выберите критерий: " << endl
					<< "1 - по id" << endl
					<< "2 - по типу" << endl
					<< "3 - по размеру" << endl
					<< "0 - Отмена" << endl << endl;
				int chs;
				scanf("%d", &chs);
				while (!(chs >= 0 && chs <= 3))
				{
					cout << "Введите корректный номер" << endl;
					scanf("%d", &chs);
				}
				if (chs == 1)
				{
					cout << "Введите id: ";
					int id;
					scanf("%d", &id);
					moniks.poisk_first(id);
				}
				else if (chs == 2)
				{
					cout << "Сравнить как: " << endl
						<< "1 - Рабочий монитор" << endl
						<< "2 - Игровой монитор" << endl
						<< "3 - Телевизор" << endl
						<< "4 - Smart-TV" << endl
						<< "5 - Домашний кинотеатр" << endl
						<< "0 - Отмена" << endl << endl;
					int chs;
					scanf("%d", &chs);
					while (!(chs >= 0 && chs <= 5))
					{
						cout << "Введите корректный номер" << endl;
						scanf("%d", &chs);
					}
					if (chs == 1)
					{
						moniks.poisk_first("class Monitor");
					}
					else if (chs == 2)
					{
						moniks.poisk_first("class Gamer_Monitor");
					}
					else if (chs == 3)
					{
						moniks.poisk_first("class TV");
					}
					else if (chs == 4)
					{
						moniks.poisk_first("class Smart_TV");
					}
					else if (chs == 5)
					{
						moniks.poisk_first("class Big_TV");
					}
				}
				else if (chs == 3)
				{
					Monitor monik;
					monik.pread();
					moniks.poisk_first(&monik);
				}
			}
			system("pause");
			cout << endl;
			break;
		}

		case 4: {
			if (moniks.empty()) cout << "Полка пуста" << endl;
			else
			{
				cout << "Выберите критерий: " << endl
					<< "1 - по id" << endl
					<< "2 - по типу" << endl
					<< "3 - по размеру" << endl
					<< "0 - Отмена" << endl << endl;
				int chs;
				scanf("%d", &chs);
				while (!(chs >= 0 && chs <= 3))
				{
					cout << "Введите корректный номер" << endl;
					scanf("%d", &chs);
				}
				if (chs == 0);
				else if (chs == 1)
				{
					cout << "Введите id: ";
					int id;
					scanf("%d", &id);
					moniks.poisk_count(id);
				}
				else if (chs == 2)
				{
					cout << "Выберите тип: " << endl
						<< "1 - Рабочий монитор" << endl
						<< "2 - Игровой монитор" << endl
						<< "3 - Телевизор" << endl
						<< "4 - Smart-TV" << endl
						<< "5 - Домашний кинотеатр" << endl
						<< "0 - Отмена" << endl << endl;
					int chs;
					scanf("%d", &chs);
					while (!(chs >= 0 && chs <= 5))
					{
						cout << "Введите корректный номер" << endl;
						scanf("%d", &chs);
					}
					if (chs == 1)
					{
						moniks.poisk_count("class Monitor");
					}
					else if (chs == 2)
					{
						moniks.poisk_count("class Gamer_Monitor");
					}
					else if (chs == 3)
					{
						moniks.poisk_count("class TV");
					}
					else if (chs == 4)
					{
						moniks.poisk_count("class Smart_TV");
					}
					else if (chs == 5)
					{
						moniks.poisk_count("class Big_TV");
					}
				}
				else if (chs == 3)
				{
					Monitor monik;
					monik.pread();
					moniks.poisk_count(&monik);
				}
			}
			system("pause");
			cout << endl;
			break;
		}

		case 5:
			cout << moniks;
			system("pause");
			cout << endl;
			break;

		case 6:
			moniks.~Stec();
			break;
		}
	}
	return 0;
}
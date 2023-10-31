#include "Header.h"

using namespace std;

void main_script()
{
	class Client client; //Перший об'єкт, розміщений в статичній пам'яті
	class Administator admin; //Другий об'єкт, розміщений в статичній пам'яті
	class Product *products = new Product[5]; //Масив 5 об'єктів, розміщених в динамічній пам'яті

	class Client::Credit_card credit_card; //Третій об'єкт, розміщений в статичній пам'яті

	credit_card.read_data(credit_card);
	products->read_data(products);

	int type1;

	cout << "Бажаєте ввійти як клієнт? (1)" << endl << "Бажаєте ввійти як адміністратор? (2)" << endl << endl << "Оберіть тип входу: ";

	type1 = check_type(2, 0);

	if (type1 == 0)
	{
		return_to_start();
		return;
	}

	if (type1 == 1)
	{
		cout << "Дійсність вашої кредитної картки: ";

		if (credit_card.get_access() == true)
		{
			cout << "Дісна" << endl;
			if (credit_card.get_money_on_card() == NULL)
			{
				cout << "Увага! Рахунок онульований" << endl;
			}
			else
			{
				cout << "Кількість грошей на кредитній картці: " << credit_card.get_money_on_card() << endl;
			}
			cout << "Кредитний ліміт: " << credit_card.get_credit_limit() << endl;
			cout << "Кредит: " << credit_card.get_credit() << endl << endl;
		}
		else
		{
			cout << "Заблокована" << endl;
			return_to_start();
			return;
		}

		int type;
		
		cout << "Бажаєте здійснити покупку (1), перевести гроші на іншу картку (2), заблокувати картку (3) чи анулювати рахунок (4)?" << endl;
		cout << "Введіть цифру: ";

		type = check_type(4, 0);

		if (type == 0)
		{
			return_to_start();
			return;
		}

		if (type == 1)
		{
			client.pay_for_the_order(credit_card, products);
		}

		if (type == 2)
		{
			client.make_payment_on_other_card(credit_card);
		}

		if (type == 3)
		{
			client.block_credit_card(credit_card);
		}

		if (type == 4)
		{
			client.annul_money(credit_card);
		}
	}

	if (type1 == 2)
	{
		int type;

		cout << "Бажаєте проініціалізувати картку клієнта (1), змінити стан доступу до картки (2), змінити список товарів (3) чи змінити один з товарів (4)?" << endl << endl;
		cout << "Чи може ви хочете відтестити додатковий метод в класі, який виділяє випадкову величину динамічної пам’ят, в якій буде розмзміщена множина значень на N елементів, після чого вони будуть відсортовані (5)?" << endl << endl;
		cout << "Ввеідть число: ";

		type = check_type(5, 0);

		if (type == 1)
		{
			admin.initialize_account(credit_card);
		}
		if (type == 2)
		{
			admin.block_credit_card(credit_card);
		}
		if (type == 3)
		{
			admin.initiliaze_products(products);
		}
		if (type == 4)
		{
			admin.change_product(products);
		}
		if (type == 5)
		{
			admin.addtional_method();
		}
	}

	/*for (int i = 0; i < 5; i++)
	{
		delete& products[i];
	}*/
}

void Client::pay_for_the_order(Credit_card cd, Product *pr) //Метод оплати замовлення (купівля товара) клієнтом за допомогою кратки
{
	int type1, type2;

	pr->print(pr);

	cout << "Введіть номер товару, який ви бажаєте придбати" << endl << "Введіть число: ";
	
	type1 = check_type(5, 1);
	
	if (type1 == 0)
	{
		return_to_start();
		return;
	}

	type1 -= 1;

	if (cd.get_money_on_card() == NULL)
	{
		cout << "Оплата з рахунку неможлива. Доступний варіант: в кредит (2)" << endl << "Оберіть тип оплати: ";
		type2 = check_type(1, 0);
	}
	else 
	{
		cout << "Оплата з рахунку (1) чи в кредит (2)?" << endl << "Оберіть тип оплати: ";
		type2 = check_type(2, 0);
	}

	if (type2 == 0)
	{
		return_to_start();
		return;
	}

	if (type2 == 1)
	{
		if (cd.get_money_on_card() < pr[type1].get_price()) //
		{
			cout << "Помилка! На вашому рахунку не достатньо грошей для оплати. Операція не була проведена" << endl;
		}
		else
		{
			cd.change_money_on_card(pr[type1].get_price());

			show_results_of_operation(cd, pr[type1].get_price(), 1);

			cd.save_data(cd);
		}
		return_to_start();
		return;
	}

	if (type2 == 2)
	{
		if (!(cd.get_credit() > cd.get_credit_limit()))
		{
			if (cd.get_credit() + pr[type1].get_price() > cd.get_credit_limit())
			{
				cout << "Попередження! При оформленні даного замовлення до велечини вашого кредиту буде додано значення, що призведе до перевищення кредитного ліміту." << endl << endl;
				cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

				type2 = check_type(2, 0);
				if (type2 == 1)
				{
					cd.change_credit(cd, pr[type1].get_price());

					show_results_of_operation(cd, pr[type1].get_price(), 1.0);

					cd.save_data(cd);
				}
				if (type2 == 2)
				{
					cout << "Операція не була проведена";
				}
			}
			else
			{
				cd.change_credit(cd, pr[type1].get_price());

				show_results_of_operation(cd, pr[type1].get_price(), 1.0);

				cd.save_data(cd);
			}
		}
		else
		{
			cout << "Попередження! Перевищення кредиту!" << endl << endl;
			cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

			type2 = check_type(2, 0);

			if (type2 == 1)
			{
				cd.change_credit(cd, pr[type1].get_price());

				show_results_of_operation(cd, pr[type1].get_price(), 1.0);

				cd.save_data(cd);
			}
			if (type2 == 2)
			{
				cout << "Операція не була проведена";
			}
		}
		
		return_to_start();
		return;
	}
}

void Client::make_payment_on_other_card(Credit_card cd)
{
	string card_number;

	cout << "Введіть номер картки на яку ви хочете перевести гроші (16 цифр): ";
	cin >> card_number;

	if (card_number.size() < 16)
	{
		do
		{
			cout << endl << "Будь-ласка, введіть коректний номер картки." << endl << endl << "Введіть номер картки: ";
			cin >> card_number;
		} while (card_number.size() != 16);
		cout << endl;
	}
	else
	{
		cout << endl;
	}

	int type;

	if (cd.get_money_on_card() == NULL)
	{
		cout << "Оплата з рахунку неможлива. Доступний варіант: в кредит (2)" << endl << endl << "Оберіть тип оплати: ";
		type = check_type(1, 0);
	}
	else
	{
		cout << "Оплата з рахунку (1) чи в кредит (2)?" << endl << endl << "Оберіть тип оплати: ";
		type = check_type(2, 0);
	}

	if (type == 0)
	{
		return_to_start();
		return;
	}

	int price;

	cout << "Введіть кількість грошей, яку ви хочете перевести на картку: " << endl;
	cout << "Введіть суму: ";
	price = check_int_corectness();
	cout << endl;

	if (type == 1)
	{
		if (cd.get_money_on_card() < price)
		{
			cout << "Помилка! На вашому рахунку не достатньо грошей для оплати. Операція не була проведена" << endl;
		}
		else
		{
			cd.change_money_on_card(price);

			show_results_of_operation(cd, price, 1);

		}
		return_to_start();
		return;
	}

	if (type == 2)
	{
		if (!(cd.get_credit() > cd.get_credit_limit()))
		{
			if (cd.get_credit() + price > cd.get_credit_limit())
			{
				cout << "Попередження! При оформленні даного замовлення до велечини вашого кредиту буде додано значення, що призведе до перевищення кредитного ліміту." << endl << endl;
				cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

				type = check_type(2, 0);
				if (type == 1)
				{
					cd.change_credit(cd, price);

					show_results_of_operation(cd, price, 1.0);


					cd.save_data(cd);
				}
				if (type == 2)
				{
					cout << "Операція не була проведена";
				}
			}
			else
			{
				cd.change_credit(cd, price);

				show_results_of_operation(cd, price, 1.0);

				cd.save_data(cd);
			}
		}
		else
		{
			cout << "Попередження! Перевищення кредиту!" << endl << endl;
			cout << "Все-одно продовжити? Так (1) Ні (2)" << endl << "Введіть цифру: ";

			type = check_type(2, 0);

			if (type == 1)
			{
				cd.change_credit(cd, price);

				show_results_of_operation(cd, price, 1.0);

				cd.save_data(cd);
			}
			if (type == 2)
			{
				cout << "Операція не була проведена";
			}
		}

		return_to_start();
		return;
	}
}

void Client::block_credit_card(Credit_card cd)
{
	cd.read_data(cd);

	int type;

	cout << "Бажаєте заблокувати картку? " << "Так (1) Ні (2)" << endl;
	cout << "Введіть цифру: ";

	type = check_type(2, 0);

	if (type == 1)
	{
		cd.change_access(false);
		cd.save_data(cd);

		cout << "Картка була успішно заблокована!" << endl;

		return_to_start();
		return;
	}

	cout << "Стан картки клієнта залишився без змін" << endl;

	return_to_start();
	return;
}

void Client::annul_money(Credit_card cd)
{
	cout << "Бажаєте анулювати рахунок? " << "Так (1) Ні (2)" << endl << endl;
	cout << "Введіть цифру: ";

	int type = check_type(2, 0);

	if (type == 1)
	{
		cd.set_money_on_card(NULL);

		cout << "Ваш рахунок було успішно онульовано!" << endl;
		cd.save_data(cd);
	}

	if (type == 2)
	{
		cout << "Стан рахунку залишився без змін";
	}

	return_to_start();
	return;
}

void Client::show_results_of_operation(Credit_card cd, int price, int type)
{
	cout << "Операція пройшла успішно!" << endl << endl << "З вашого рахунку було знято " << price << " гривень" << endl;
	cout << "Кількість грошей на рахунку: " << cd.get_money_on_card() << " гривень" << endl;
	cout << "Величина кредиту складає: " << cd.get_credit() << " гривень" << endl;
}

void Client::show_results_of_operation(Credit_card cd, int price, double type)
{
	cout << "Операція пройшла успішно!" << endl << endl << "До вашого кредиту було додано " << price << " гривень" << endl;
	cout << "Кількість грошей на рахунку: " << cd.get_money_on_card() << " гривень" << endl;
	cout << "Величина кредиту складає: " << cd.get_credit() << " гривень" << endl;
}

bool Client::Credit_card::get_access()
{
	return this->access;
}

void Client::Credit_card::change_access(bool state)
{
	this->access = state;
}

long long unsigned int Client::Credit_card::get_card_number()
{
	return this->card_number;
}

void Client::Credit_card::set_card_number(long long unsigned int card_number)
{
	this->card_number = card_number;
}

double Client::Credit_card::get_money_on_card()
{
	return this->money_on_card;
}

void Client::Credit_card::set_money_on_card(double money)
{
	this->money_on_card = money;
}

void Client::Credit_card::change_money_on_card(double money)
{
	this->money_on_card = this->money_on_card - money;
}

unsigned int Client::Credit_card::get_credit_limit()
{
	return this->credit_limit;
}

void Client::Credit_card::set_credit_limit(int credit_limit)
{
	this->credit_limit = credit_limit;
}

double Client::Credit_card::get_credit()
{
	return this->credit;
}

void Client::Credit_card::set_credit(double credit)
{
	this->credit = credit;
}

void Client::Credit_card::change_credit(Credit_card& cd, double price)
{
	this->credit = this->credit + price;
	cd.save_data(cd);
}

void Administator::initialize_account(Client::Credit_card cd)
{
	long long unsigned int card_number;
	int money, credit_limit, credit;

	cout << "Введіть номер карти клієнта: ";
	cin >> card_number;
	cd.set_card_number(card_number);

	cout << "Введіть кількість грошей на картці клієнта: ";
	cin >> money;
	cd.set_money_on_card(money);

	cout << "Введіть кредитний ліміт на картці клієнта: ";
	cin >> credit_limit;
	cd.set_credit_limit(credit_limit);

	cout << "Введіть початкову кількість кредиту клієнта: ";
	cin >> credit;
	cd.set_credit(credit);

	cd.change_access(true);

	cd.save_data(cd);

	cout << endl;

	return_to_start();
	return;
}

void Administator::block_credit_card(Client::Credit_card cd)
{
	cd.read_data(cd);
	
	int type;
	if (cd.get_access() == true)
	{
		cout << "Стан картки: доступна" << endl << "Перевтищення кридету: ";
		
		if (cd.get_credit() > cd.get_credit_limit())
		{
			cout << "Так" << endl << "Перевищення кредиту складає " << (cd.get_credit() - cd.get_credit_limit()) << " гривень" << endl << endl;
		}
		else
		{
			cout << "Ні" << endl << endl;
		}

		cout << "Бажаєте заблокувати картку? " << "Так (1) Ні (2)" << endl;
		cout << "Введіть цифру: ";

		type = check_type(2, 0);

		if (type == 1)
		{
			cd.change_access(false);
			cd.save_data(cd);

			cout << "Картка була успішно заблокована!" << endl << endl;

			return_to_start();
			return;
		}

		cout << "Стан картки клієнта залишився без змін" << endl;
		return_to_start();
		return;
	}
	if (cd.get_access() == false)
	{
		cout << "Стан картки: заблокована" << endl << endl << "Бажаєте відновити картку? " << "Так (1) Ні (2)" << endl;
		cout << "Введіть число: ";

		type = check_type(2, 0);

		if (type == 1)
		{
			cd.change_access(true);
			cd.save_data(cd);

			cout << "Картка була успішно відновлена!" << endl;

			return_to_start();
			return;
		}

		cout << "Стан картки клієнта залишився без змін" << endl;
		return_to_start();
		return;
	}	
}

void Administator::addtional_method() //Додатковий метод
{
	cout << "Введіть кількість елементів у масиві: ";
	int size = check_int_corectness();

	int *array = new int[size];

	cout << endl <<"[ ";
	for (int i = 0; i < size; i++)
	{
		cout << (array[i] = rand() % 100);
		cout << " ";
	}
	cout << "]" << endl << endl;

	bool swapped;
	for (int i = 0; i < size - 1; i++) 
	{
		swapped = false;
		for (int j = 0; j < size - i - 1; j++) 
		{
			if (array[j] > array[j + 1]) {
				swap(array[j], array[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
		{
			break;
		}
	}

	cout << "Відсортований масив" << endl << endl;

	cout << "[ ";
	for (int i = 0; i < size; i++)
	{
		cout << array[i];
		cout << " ";
	}
	cout << "]" << endl << endl;

	delete[] array;

	return_to_start();
	return;
}

void Client::Credit_card::save_data(Client::Credit_card &cd)
{
	ofstream file("files/Client.txt");
	file.write((char*)&cd, sizeof(Client::Credit_card));
	file.close();
}

void Client::Credit_card::read_data(Client::Credit_card &cd)
{
	ifstream file("files/Client.txt");
	file.read((char*)&cd, sizeof(Client::Credit_card));
	file.close();
}

void Product::save_data(Product *pr)
{
	ofstream file("files/Products.txt");
	for (int i = 0; i < 5; i++)
	{
		file.write((char*)&pr[i], sizeof(Product));
	}
	file.close();
}

void Product::read_data(Product *pr)
{
	ifstream file("files/Products.txt");
	for (int i = 0; i < 5; i++)
	{
		file.read((char*)&pr[i], sizeof(Product));
	}

	file.close();
}

int check_type(int way, int number)
{
	int type = 0;

	if (!(cin >> type))
	{
		do
		{
			cout << endl << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
			cin.clear();
			cin.ignore(1000, '\n');
		} while (!(cin >> type));
	}

	if (type == 0)
	{
		return 0;
	}

	if (way == 1)
	{
		if (type != 2)
		{
			do
			{
				cout << endl;
				cout << "Оплата з рахунку неможлива. Доступний варіант: в кредит (2)" << endl << endl << "Оберіть тип оплати: ";
				cin >> type;
			} while (type != 2);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 2)
	{
		if (type != 1 && type != 2)
		{
			do
			{
				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 3)
	{
		if (type != 1 && type != 2 && type != 3)
		{
			do
			{
				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 4)
	{
		if (type != 1 && type != 2 && type != 3 && type != 4)
		{
			do
			{
				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3 && type != 4);
			cout << endl;
		}
		else
		{
			cout << endl;
		}		
	}

	if (way == 5 && number == 0)
	{
		if (type != 1 && type != 2 && type != 3 && type != 4 && type != 5)
		{
			do
			{
				cout << endl;
				cout << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3 && type != 4 && type != 5);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}

	if (way == 5 && number == 1)
	{
		if (type != 1 && type != 2 && type != 3 && type != 4 && type != 5)
		{
			do
			{
				cout << endl;
				cout << "Товару під таким номером не існує. Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
				cin >> type;
			} while (type != 1 && type != 2 && type != 3 && type != 4 && type != 5);
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cin.clear();
	cin.ignore(1000, '\n');
	return type;
}

int check_int_corectness()
{
	int variable;

	if (!(cin >> variable))
	{
		do
		{
			cout << endl << "Будь-ласка, введіть коректне число" << endl << "Введіть число: ";
			cin.clear();
			cin.ignore(1000, '\n');
		} while (!(cin >> variable));
	}
	return variable;
}

void return_to_start()
{
	int type;

	restart_cin();

	cin.get();
	cin.get();

	cout << "Бажаєте повернутися до меню входу у систему?" << endl << "Так (1) Ні (2)" << endl << endl;
	cout << "Введіть цифру: ";

	type = check_type(2, 0);
	if (type == 0)
	{
		return;
	}

	if (type == 1)
	{
		system("cls");
		main_script();
	}
	if (type == 2)
	{
		cout << "Роботу програми було закінчено";
		cin.get();
		cin.get();
		return;
	}
}

void restart_cin()
{
	cin.clear();
	cin.ignore(1000, '\n');
}

void Administator::initiliaze_products(Product *pr) //Метод роботи з масивом об'єктів
{
	string name;
	int price;
	for (int i = 0; i < 5; i++)
	{
		if (i != 0)
		{
			cout << endl;
		}
		cout << "Введіть назву " << i + 1 << "-го товару: ";
		getline(cin, name);

		cout << "Введіть ціну " << i + 1 << "-го товару: ";
		price = check_int_corectness();

		pr[i].set_product(name, price);
		restart_cin();
	}
	pr->save_data(pr);

	return_to_start();
	return;
}

void Administator::change_product(Product *pr) //Метод роботи з масивом об'єктів
{
	pr->print(pr);

	cout << "Введіть номер товару, який ви бажаєте змінити: " << endl;
	cout << "Введіть цифру: ";

	int type = check_type(5, 1);

	if (type == 0)
	{
		return_to_start();
		return;
	}

	string name;
	int price;

	cout << "Введіть нову назву " << type << "-го товару: ";
	getline(cin, name);

	cout << "Введіть нову ціну " << type << "-го товару: ";
	price = check_int_corectness();

	pr[type-1].set_product(name, price);

	cout << endl << type << "-ий товар був успішно змінений!" << endl << endl;

	pr->save_data(pr);

	return_to_start();
	return;
}

void Product::set_product(string name, int price)
{
	strcpy(this->name, name.c_str());
	this->price = price;
}

double Product::get_price()
{
	return this->price;
}

void Product::print(Product *pr)
{
	size_t length = 0;

	for (int i = 0; i < 5; i++)
	{
		if(strlen(pr[i].name) > length)
		{
			length = strlen(pr[i].name);
		}
	}

	cout << "Перелік товарів:" << endl;

	cout << setw(3) << left << "N" << setw(length+3) << "Назва" << "Ціна" << endl << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << setw(3) << i + 1 << setw(length + 3) << pr[i].name << pr[i].price << endl << endl;
	}
}
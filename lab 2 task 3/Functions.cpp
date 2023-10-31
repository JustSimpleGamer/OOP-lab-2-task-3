#include "Header.h"

using namespace std;

void main_script()
{
	class Client client; //������ ��'���, ��������� � �������� ���'��
	class Administator admin; //������ ��'���, ��������� � �������� ���'��
	class Product *products = new Product[5]; //����� 5 ��'����, ��������� � �������� ���'��

	class Client::Credit_card credit_card; //����� ��'���, ��������� � �������� ���'��

	credit_card.read_data(credit_card);
	products->read_data(products);

	int type1;

	cout << "������ ����� �� �볺��? (1)" << endl << "������ ����� �� �����������? (2)" << endl << endl << "������ ��� �����: ";

	type1 = check_type(2, 0);

	if (type1 == 0)
	{
		return_to_start();
		return;
	}

	if (type1 == 1)
	{
		cout << "ĳ������ ���� �������� ������: ";

		if (credit_card.get_access() == true)
		{
			cout << "ĳ���" << endl;
			if (credit_card.get_money_on_card() == NULL)
			{
				cout << "�����! ������� �����������" << endl;
			}
			else
			{
				cout << "ʳ������ ������ �� �������� ������: " << credit_card.get_money_on_card() << endl;
			}
			cout << "��������� ���: " << credit_card.get_credit_limit() << endl;
			cout << "������: " << credit_card.get_credit() << endl << endl;
		}
		else
		{
			cout << "�����������" << endl;
			return_to_start();
			return;
		}

		int type;
		
		cout << "������ �������� ������� (1), ��������� ����� �� ���� ������ (2), ����������� ������ (3) �� ��������� ������� (4)?" << endl;
		cout << "������ �����: ";

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

		cout << "������ �������������� ������ �볺��� (1), ������ ���� ������� �� ������ (2), ������ ������ ������ (3) �� ������ ���� � ������ (4)?" << endl << endl;
		cout << "�� ���� �� ������ ��������� ���������� ����� � ����, ���� ������ ��������� �������� �������� �����, � ��� ���� ���������� ������� ������� �� N ��������, ���� ���� ���� ������ ���������� (5)?" << endl << endl;
		cout << "������ �����: ";

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

void Client::pay_for_the_order(Credit_card cd, Product *pr) //����� ������ ���������� (������ ������) �볺���� �� ��������� ������
{
	int type1, type2;

	pr->print(pr);

	cout << "������ ����� ������, ���� �� ������ ��������" << endl << "������ �����: ";
	
	type1 = check_type(5, 1);
	
	if (type1 == 0)
	{
		return_to_start();
		return;
	}

	type1 -= 1;

	if (cd.get_money_on_card() == NULL)
	{
		cout << "������ � ������� ���������. ��������� ������: � ������ (2)" << endl << "������ ��� ������: ";
		type2 = check_type(1, 0);
	}
	else 
	{
		cout << "������ � ������� (1) �� � ������ (2)?" << endl << "������ ��� ������: ";
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
			cout << "�������! �� ������ ������� �� ��������� ������ ��� ������. �������� �� ���� ���������" << endl;
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
				cout << "������������! ��� ��������� ������ ���������� �� �������� ������ ������� ���� ������ ��������, �� �������� �� ����������� ���������� ����." << endl << endl;
				cout << "���-���� ����������? ��� (1) ͳ (2)" << endl << "������ �����: ";

				type2 = check_type(2, 0);
				if (type2 == 1)
				{
					cd.change_credit(cd, pr[type1].get_price());

					show_results_of_operation(cd, pr[type1].get_price(), 1.0);

					cd.save_data(cd);
				}
				if (type2 == 2)
				{
					cout << "�������� �� ���� ���������";
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
			cout << "������������! ����������� �������!" << endl << endl;
			cout << "���-���� ����������? ��� (1) ͳ (2)" << endl << "������ �����: ";

			type2 = check_type(2, 0);

			if (type2 == 1)
			{
				cd.change_credit(cd, pr[type1].get_price());

				show_results_of_operation(cd, pr[type1].get_price(), 1.0);

				cd.save_data(cd);
			}
			if (type2 == 2)
			{
				cout << "�������� �� ���� ���������";
			}
		}
		
		return_to_start();
		return;
	}
}

void Client::make_payment_on_other_card(Credit_card cd)
{
	string card_number;

	cout << "������ ����� ������ �� ��� �� ������ ��������� ����� (16 ����): ";
	cin >> card_number;

	if (card_number.size() < 16)
	{
		do
		{
			cout << endl << "����-�����, ������ ��������� ����� ������." << endl << endl << "������ ����� ������: ";
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
		cout << "������ � ������� ���������. ��������� ������: � ������ (2)" << endl << endl << "������ ��� ������: ";
		type = check_type(1, 0);
	}
	else
	{
		cout << "������ � ������� (1) �� � ������ (2)?" << endl << endl << "������ ��� ������: ";
		type = check_type(2, 0);
	}

	if (type == 0)
	{
		return_to_start();
		return;
	}

	int price;

	cout << "������ ������� ������, ��� �� ������ ��������� �� ������: " << endl;
	cout << "������ ����: ";
	price = check_int_corectness();
	cout << endl;

	if (type == 1)
	{
		if (cd.get_money_on_card() < price)
		{
			cout << "�������! �� ������ ������� �� ��������� ������ ��� ������. �������� �� ���� ���������" << endl;
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
				cout << "������������! ��� ��������� ������ ���������� �� �������� ������ ������� ���� ������ ��������, �� �������� �� ����������� ���������� ����." << endl << endl;
				cout << "���-���� ����������? ��� (1) ͳ (2)" << endl << "������ �����: ";

				type = check_type(2, 0);
				if (type == 1)
				{
					cd.change_credit(cd, price);

					show_results_of_operation(cd, price, 1.0);


					cd.save_data(cd);
				}
				if (type == 2)
				{
					cout << "�������� �� ���� ���������";
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
			cout << "������������! ����������� �������!" << endl << endl;
			cout << "���-���� ����������? ��� (1) ͳ (2)" << endl << "������ �����: ";

			type = check_type(2, 0);

			if (type == 1)
			{
				cd.change_credit(cd, price);

				show_results_of_operation(cd, price, 1.0);

				cd.save_data(cd);
			}
			if (type == 2)
			{
				cout << "�������� �� ���� ���������";
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

	cout << "������ ����������� ������? " << "��� (1) ͳ (2)" << endl;
	cout << "������ �����: ";

	type = check_type(2, 0);

	if (type == 1)
	{
		cd.change_access(false);
		cd.save_data(cd);

		cout << "������ ���� ������ �����������!" << endl;

		return_to_start();
		return;
	}

	cout << "���� ������ �볺��� ��������� ��� ���" << endl;

	return_to_start();
	return;
}

void Client::annul_money(Credit_card cd)
{
	cout << "������ ��������� �������? " << "��� (1) ͳ (2)" << endl << endl;
	cout << "������ �����: ";

	int type = check_type(2, 0);

	if (type == 1)
	{
		cd.set_money_on_card(NULL);

		cout << "��� ������� ���� ������ ����������!" << endl;
		cd.save_data(cd);
	}

	if (type == 2)
	{
		cout << "���� ������� ��������� ��� ���";
	}

	return_to_start();
	return;
}

void Client::show_results_of_operation(Credit_card cd, int price, int type)
{
	cout << "�������� ������� ������!" << endl << endl << "� ������ ������� ���� ����� " << price << " �������" << endl;
	cout << "ʳ������ ������ �� �������: " << cd.get_money_on_card() << " �������" << endl;
	cout << "�������� ������� ������: " << cd.get_credit() << " �������" << endl;
}

void Client::show_results_of_operation(Credit_card cd, int price, double type)
{
	cout << "�������� ������� ������!" << endl << endl << "�� ������ ������� ���� ������ " << price << " �������" << endl;
	cout << "ʳ������ ������ �� �������: " << cd.get_money_on_card() << " �������" << endl;
	cout << "�������� ������� ������: " << cd.get_credit() << " �������" << endl;
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

	cout << "������ ����� ����� �볺���: ";
	cin >> card_number;
	cd.set_card_number(card_number);

	cout << "������ ������� ������ �� ������ �볺���: ";
	cin >> money;
	cd.set_money_on_card(money);

	cout << "������ ��������� ��� �� ������ �볺���: ";
	cin >> credit_limit;
	cd.set_credit_limit(credit_limit);

	cout << "������ ��������� ������� ������� �볺���: ";
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
		cout << "���� ������: ��������" << endl << "������������ �������: ";
		
		if (cd.get_credit() > cd.get_credit_limit())
		{
			cout << "���" << endl << "����������� ������� ������ " << (cd.get_credit() - cd.get_credit_limit()) << " �������" << endl << endl;
		}
		else
		{
			cout << "ͳ" << endl << endl;
		}

		cout << "������ ����������� ������? " << "��� (1) ͳ (2)" << endl;
		cout << "������ �����: ";

		type = check_type(2, 0);

		if (type == 1)
		{
			cd.change_access(false);
			cd.save_data(cd);

			cout << "������ ���� ������ �����������!" << endl << endl;

			return_to_start();
			return;
		}

		cout << "���� ������ �볺��� ��������� ��� ���" << endl;
		return_to_start();
		return;
	}
	if (cd.get_access() == false)
	{
		cout << "���� ������: �����������" << endl << endl << "������ �������� ������? " << "��� (1) ͳ (2)" << endl;
		cout << "������ �����: ";

		type = check_type(2, 0);

		if (type == 1)
		{
			cd.change_access(true);
			cd.save_data(cd);

			cout << "������ ���� ������ ���������!" << endl;

			return_to_start();
			return;
		}

		cout << "���� ������ �볺��� ��������� ��� ���" << endl;
		return_to_start();
		return;
	}	
}

void Administator::addtional_method() //���������� �����
{
	cout << "������ ������� �������� � �����: ";
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

	cout << "³����������� �����" << endl << endl;

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
			cout << endl << "����-�����, ������ �������� �����" << endl << "������ �����: ";
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
				cout << "������ � ������� ���������. ��������� ������: � ������ (2)" << endl << endl << "������ ��� ������: ";
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
				cout << "����-�����, ������ �������� �����" << endl << "������ �����: ";
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
				cout << "����-�����, ������ �������� �����" << endl << "������ �����: ";
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
				cout << "����-�����, ������ �������� �����" << endl << "������ �����: ";
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
				cout << "����-�����, ������ �������� �����" << endl << "������ �����: ";
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
				cout << "������ �� ����� ������� �� ����. ����-�����, ������ �������� �����" << endl << "������ �����: ";
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
			cout << endl << "����-�����, ������ �������� �����" << endl << "������ �����: ";
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

	cout << "������ ����������� �� ���� ����� � �������?" << endl << "��� (1) ͳ (2)" << endl << endl;
	cout << "������ �����: ";

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
		cout << "������ �������� ���� ��������";
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

void Administator::initiliaze_products(Product *pr) //����� ������ � ������� ��'����
{
	string name;
	int price;
	for (int i = 0; i < 5; i++)
	{
		if (i != 0)
		{
			cout << endl;
		}
		cout << "������ ����� " << i + 1 << "-�� ������: ";
		getline(cin, name);

		cout << "������ ���� " << i + 1 << "-�� ������: ";
		price = check_int_corectness();

		pr[i].set_product(name, price);
		restart_cin();
	}
	pr->save_data(pr);

	return_to_start();
	return;
}

void Administator::change_product(Product *pr) //����� ������ � ������� ��'����
{
	pr->print(pr);

	cout << "������ ����� ������, ���� �� ������ ������: " << endl;
	cout << "������ �����: ";

	int type = check_type(5, 1);

	if (type == 0)
	{
		return_to_start();
		return;
	}

	string name;
	int price;

	cout << "������ ���� ����� " << type << "-�� ������: ";
	getline(cin, name);

	cout << "������ ���� ���� " << type << "-�� ������: ";
	price = check_int_corectness();

	pr[type-1].set_product(name, price);

	cout << endl << type << "-�� ����� ��� ������ �������!" << endl << endl;

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

	cout << "������ ������:" << endl;

	cout << setw(3) << left << "N" << setw(length+3) << "�����" << "ֳ��" << endl << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << setw(3) << i + 1 << setw(length + 3) << pr[i].name << pr[i].price << endl << endl;
	}
}
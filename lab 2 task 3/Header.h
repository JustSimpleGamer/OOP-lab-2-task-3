#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Product
{
public:
	void set_product(string name, int price);
	double get_price();
	void print(Product *pr);
	void save_data(Product *pr); //Метод запису даних
	void read_data(Product *pr); //Метод зчитування даних
private:
	char name[64];
	double price;
};

class Client
{
public:
	class Credit_card
	{
	public:
		bool get_access();
		void change_access(bool state);

		long long unsigned int get_card_number();
		void set_card_number(long long unsigned int card_number);

		double get_money_on_card();
		void set_money_on_card(double money);
		void change_money_on_card(double money);

		unsigned int get_credit_limit();
		void set_credit_limit(int credit_limit);

		double get_credit();
		void set_credit(double credit);
		void change_credit(Credit_card &cd, double money);

		void save_data(Client::Credit_card& cd); //Метод запису даних
		void read_data(Client::Credit_card& cd); //Метод зчитування даних
	private:
		bool access;
		long long unsigned int card_number; 
		double money_on_card;
		unsigned int credit_limit;
		double credit;
	};
	void pay_for_the_order(Credit_card cd, Product *pr);
	void make_payment_on_other_card(Credit_card cd);
	void block_credit_card(Credit_card cd);
	void annul_money(Credit_card cd);
	void show_results_of_operation(Credit_card cd, int price, int type); //Перевантажений метод
	void show_results_of_operation(Credit_card cd, int price, double type); //Перевантажений метод
};

class Administator
{
public:
	void block_credit_card(Client::Credit_card cd);
	void initialize_account(Client::Credit_card cd);
	void initiliaze_products(Product *pr);
	void change_product(Product *pr);

	void addtional_method();
};
void main_script();

void return_to_start();
void restart_cin();

int check_type(int way, int number);
int check_int_corectness();

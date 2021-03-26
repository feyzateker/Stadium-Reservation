#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Header2.h"
using namespace std;

struct customer_info
{
	string block;
	string row;
	int colnum;
	customer_info(string x, string y, int z)
	{
		block=x;
		row= y;
		colnum=z;
	}
	customer_info(){}
};


void reserve_seat_by_row (string customer_name, string row_name, unordered_map<string, struct customer_info> &customer, unordered_map<string, MPQ<int>> &rows, unordered_map<string, unordered_map<string,vector<string>>>& stadium)
{
	if (customer.find(customer_name) != customer.end())
	{
		cout << "bu müþteri zaten var." << endl;
	}
	else if ((rows[row_name]).GetMax() != 0)
	{
		string block= rows[row_name].GetBlock();
		for(int i=0;i< stadium[block][row_name].size(); i++)
		{
			if (stadium[block][row_name][i] == "---") 
			{
				(stadium[block][row_name])[i]=customer_name;
				struct customer_info cus(block, row_name, i);
				customer[customer_name]= cus;
				break;
			}
		}
		int a= rows[row_name].GetMax();
		a--;
		rows[row_name].Remove(block);
		rows[row_name].insert(a, block);
	}
	else
		cout <<" boþ yer yok bu satýrda" << endl;
}

void reserve_seat (string customer_name, string block_name, string row_name, int column_number, unordered_map<string, struct customer_info> &customer, unordered_map<string, MPQ<int>> &rows, unordered_map<string, unordered_map<string,vector<string>>>& stadium)
{
	if(customer.find(customer_name) == customer.end())
	{
		if (stadium[block_name][row_name][column_number] == "---") 
		{
			stadium[block_name][row_name][column_number] = customer_name;
			customer_info cust(block_name, row_name, column_number);
			customer[customer_name] =cust; 
			int g = rows[row_name].GetValue(block_name);
			g--;
			rows[row_name].Remove(block_name);
			rows[row_name].insert(g, block_name);
		}
		else
			cout << "burasý dolu" << endl;
	}
	else
		cout << "bu  zaten var" << endl;
}

void get_seat (string customer_name, unordered_map<string, struct customer_info> &customer)
{
	if(customer.find(customer_name) != customer.end())
	{
		cout << " block " << customer[customer_name].block << " row" << customer[customer_name].row << "  col" << customer[customer_name].colnum << endl;
	}
	else
		cout << "böyle bir müþteri yok" << endl;
}

void cancel_reservation (string customer_name,unordered_map<string, struct customer_info> &customer, unordered_map<string, MPQ<int>> &rows, unordered_map<string, unordered_map<string,vector<string>>>& stadium)
{
	if(customer.find(customer_name) != customer.end())
	{
		stadium[customer[customer_name].block][customer[customer_name].row][customer[customer_name].colnum] = "---";
		int a= rows[customer[customer_name].row].GetValue(customer[customer_name].block);
		a++;
		rows[customer[customer_name].row].Remove(customer[customer_name].block);
		rows[customer[customer_name].row].insert(a, customer[customer_name].block);
		customer.erase(customer_name);
	}
	else
		cout << "böyle bir müteri yok"<< endl;

}

void print(unordered_map<string, unordered_map<string,vector<string>>> stadium)
{
	for(auto i:stadium)
	{
		cout << i.first << endl << "~~~~~~~" << endl;
		for(auto j: stadium[i.first])
		{
			cout << j.first << " : " ;
			for(int a=0; a< (j.second).size(); a++)
			{
				cout << j.second[a] << " " ;
			}
			cout << endl;
		}
	}
}


int main()
{
	unordered_map<string, struct customer_info> customer;
	unordered_map<string, unordered_map<string,vector<string>>> stadium;
	unordered_map<string, MPQ<int>> rows;
	string fileName= "inputs20.txt"; 
	ifstream input;
	input.open(fileName);
	if(input.fail())  // check the file name
	{
		cout<< "Cannot find a file named "<< fileName << endl;
	}
	string line;
	getline(input,line);
	stringstream aa(line);
	string block_name;
	vector<string> blocknamevector;
	while( aa>> block_name)
	{
		stadium[block_name];
		blocknamevector.push_back(block_name);
	}
	getline(input,line);
	stringstream bb(line);
	string row_name;

	while (bb>>row_name)
	{
		for(auto &i: stadium)
			stadium[i.first][row_name];
		//rows[row_name];
	}
	getline(input,line);
	stringstream cc(line);
	int col_number;
	cc>>col_number;
	vector<string> col;
	for(int a=0; a<col_number; a++)
		col.push_back("---");
	for(auto & i: stadium)
	{
		for(auto & j: stadium[i.first])
			stadium[i.first][j.first]= col;
	}
	for(auto & x: stadium[block_name])
	{
		int siz = blocknamevector.size();
		MPQ<int> heap(blocknamevector.size()+1);
		for (int l=0; l<blocknamevector.size(); l++)
		{
			string blk=blocknamevector[l];
			(heap.order_of_block)[blk] =l;
			heap.insert(col_number, blk);

		}
		rows[x.first]= heap ;
	}
	while(getline(input, line)  ) // read the file
	{
		stringstream ss(line);
		string input, customername, blockname, rowname;
		int colnum;
		ss>> input;
		if(input =="print")
			print(stadium);
		else if(input =="reserve_seat")
		{
			ss>>customername>>blockname>>rowname>>colnum;
			reserve_seat(customername, blockname, rowname, colnum, customer, rows,stadium);
		}
		else if(input== "reserve_seat_by_row")
		{
			ss>>customername>>rowname;
			reserve_seat_by_row(customername, rowname, customer, rows, stadium);
		}
		else if(input =="get_seat")
		{
			ss>>customername;
			get_seat(customername, customer);
		}
		else if(input== "cancel_reservation")
		{
			ss>>customername;
			cancel_reservation(customername, customer, rows,stadium);
		}

	}
	return 0;
}
/*
 * myclass.h
 *
 *  Created on: 19 рту. 2016 у.
 *      Author: 1
 */

#ifndef MYCLASS_MYCLASS_H_
#define MYCLASS_MYCLASS_H_
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

class  data_structure{

public:
	char* Data_array;
	int this_capacity;

	data_structure()
		{
			Data_array 		= 0;
			this_capacity 	= 0;
			privat_var		= 0;
			//blocks_cnt++;
		}

	/*
	~data_structure(){
		blocks_cnt--;
	}
	*/
private:
	int privat_var;
	static int blocks_cnt;

};
/*
data_structure::data_structure(void)
{
	Data_array = "";
	this_capacity = 0;
	//blocks_cnt++;
}
*/

extern vector<data_structure> vec;
void create_Data(int var);

#endif /* MYCLASS_MYCLASS_H_ */

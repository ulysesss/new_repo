/*
 * myclas.cpp
 *
 *  Created on: 19 рту. 2016 у.
 *      Author: 1
 */
#include "myclass.h"

vector<data_structure> vec;

void create_Data(int var){
	for(int i = 0 ;i < var; i++){
	data_structure tmp_dat;
	char buffer[0x20] = "[container data]";
	tmp_dat.Data_array = buffer;
	tmp_dat.this_capacity = sizeof(buffer);
	vec.push_back(tmp_dat);

	}

}



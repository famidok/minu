#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

void create_day_schema()
{
    time_t raw_time;
    time(&raw_time);

    struct tm *timeinfo;
    timeinfo = localtime(&raw_time);

	ofstream day_file("/opt/minu/days/0" + to_string(timeinfo->tm_mday) + "-0" + to_string(timeinfo->tm_mon + 1) + "-" + to_string(timeinfo->tm_year + 1900));

	if (day_file) {
		cout << "File created successfully!" << endl;
	} else {
		cout << "Can't create file!" << endl;
	}
}

int main(int argc, char *argv[])
{
    create_day_schema();
    return 0;
}

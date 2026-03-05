#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void create_day_schema()
{
    time_t raw_time;
    time(&raw_time);

    const struct tm* time_info = localtime(&raw_time);
    const string path = "/opt/minu/days/0" + to_string(time_info->tm_mday) + "-0" + to_string(time_info->tm_mon + 1) + "-" + to_string(time_info->tm_year + 1900);
    ofstream day_file(path);

    if (day_file) {
        cout << "File created successfully!" << endl;
        cout << "File path: " << path << endl;
    } else {
        cout << "Can't create file!" << endl;
    }
}

void help()
{
    cout << "Usage: minu [options]" << endl;
    cout << "Options:" << endl;
    cout << "\t--create_day\t\tCreates today's schema" << endl;
}

int main(int argc, char *argv[])
{
    map<string_view, function<void()>> commands = {
        {"--create_day", create_day_schema},
        {"--help", help}
    };

    if (argc == 1) {
        help();
    } else if (argc > 1 ) {
        const string_view arg = argv[1];
        if (commands.find(arg) != commands.end()) {
            commands.at(arg)();
        } else {
            cout << "Unknown Command!" << arg << endl;
            help();
        }
    }

    return 0;
}

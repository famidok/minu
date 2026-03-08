#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void create_day_schema(ofstream& day_file, const string& date)
{
    day_file << "DAILY TRACKER" << " - " << date << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Day Score: /10                  |         Goal Rate: /10" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Targets:" << endl;
    day_file << "[  ]:" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Engineering" << endl;
    day_file << "[  ] Work: +0 -0" << endl;
    day_file << "Notes:" << endl;
    day_file << "     ->" << endl;
    day_file << "[  ] Personal: +0 -0" << endl;
    day_file << "Notes:" << endl;
    day_file << "     ->" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Knowledge & Reading" << endl;
    day_file << "[  ] Classic:" << endl;
    day_file << "[  ] Technical:" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Idea & Backlog" << endl;
    day_file << "Idea:" << endl;
    day_file << "     ->" << endl;
    day_file << "Project:" << endl;
    day_file << "     ->" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Training & Health" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "[  ] Steps:                 | [  ] Exercises:" << endl;
    day_file << "[  ] Fast-Food [  ] Smoke [  ] Junk Food" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Language Lab" << endl;
    day_file << "[  ] English (Count: )" << endl;
    day_file << "     -" << endl;
    day_file << "[  ] Japanese (Count: )" << endl;
    day_file << "     -" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Finance" << endl;
    day_file << "[  ] Ticket (Total: )" << endl;
    day_file << "     -" << endl;
    day_file << "[  ] Credit Card (Total: )" << endl;
    day_file << "     -" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Tomorrow's Agenda:" << endl;
    day_file << "-" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Notes:" << endl;
    day_file << "-" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
}

void create_day()
{
    time_t raw_time;
    time(&raw_time);

    const tm* time_info = localtime(&raw_time);
    const string date = to_string(time_info->tm_mday) + "-0" + to_string(time_info->tm_mon + 1) + "-" + to_string(time_info->tm_year + 1900);
    const string path = "/opt/minu/days/0" + date;
    ofstream day_file(path);

    if (day_file.is_open()) {
        cout << "File created successfully!" << endl;
        cout << "File path: " << path << endl;
        create_day_schema(day_file, date);
        day_file.close();
    } else {
        cout << "Can't create file!" << endl;
    }
}

void edit_day(string_view day)
{
    string editor_input;
    string command;
    string path;

    if (!day.empty()) {
        path = "/opt/minu/days/" + string(day);

        ifstream f(path);
        if (!f.good()) {
            cout << "File does not exist => " << path << endl;
            return;
        }
    } else {
        time_t raw_time;
        time(&raw_time);
        const tm* time_info = localtime(&raw_time);
        const string date = to_string(time_info->tm_mday) + "-0" + to_string(time_info->tm_mon + 1) + "-" + to_string(time_info->tm_year + 1900);
        path = "/opt/minu/days/0" + date;
    }

    cout << "\nSelect your default editor...\n" << endl;
    cout << "Options:\n1-) Nano\n2-) Vim" << endl;
    cout << "[ Default editor is nano ]\n" << endl;
    cout << "Choice: ";
    getline(cin, editor_input);

    if (editor_input.empty() || editor_input == "1") {
        command = "nano " + path;
        system(command.c_str());
        cout << "Edited successfully! w/nano" << endl;
    } else if (editor_input == "2") {
        command = "vim " + path;
        system(command.c_str());
        cout << "Edited successfully! w/vim" << endl;
    }
}

void help()
{
    cout << "Usage: minu [options]" << endl;
    cout << "Options:" << endl;
    cout << "\t--create_day\t\t\tCreates today's schema" << endl;
    cout << "\t--edit_day <dd/mm/yy>\t\tEdits today's/exact day schema" << endl;
}

int main(int argc, char *argv[])
{
    map<string_view, function<void()>> commands = {
        {"--create_day", create_day},
        {"--help", help},
        {"--edit_day", [&]() {
                const string_view day = (argc > 2) ? argv[2] : "";
                edit_day(day);
        }}
    };

    if (argc == 1) {
        help();
    } else if (argc > 1 ) {
        const string_view arg = argv[1];
        if (commands.find(arg) != commands.end()) {
            commands.at(arg)();
        } else {
            cout << "Unknown Command => " << arg << "\n" << endl;
            help();
        }
    }

    return 0;
}

#include <complex>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <regex>

using namespace std;

string get_day(int offset = 0) {
    time_t t = time(nullptr);
    t += offset * 24 * 60 * 60;

    tm* timeinfo = localtime(&t);
    stringstream ss;
    ss << put_time(timeinfo, "%d-%m-%Y");
    return ss.str();
}

vector<string> get_tomorrow_agenda(vector<string>& agenda_list, const string& day) {
    string day_date;
    string path;
    const string tomorrow_agenda = "Tomorrow's Agenda:";
    const string end = "#---------------------------------------------------------#";
    bool found_agenda = false;
    bool finished = false;
    string line;

    if (!day.empty()) {
        int d, m, y;
        sscanf(day.c_str(), "%d-%d-%d", &d, &m, &y);
        d = d - 1;
        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%02d-%02d-%04d", d, m, y);
        day_date = buffer;
        path = "/opt/minu/days/" + day_date;

    } else {
        day_date = get_day(-1);
        path = "/opt/minu/days/" + day_date;
    }

    ifstream file(path);

    if (file.is_open()) {
        while (getline(file, line) && !finished) {

            if (!line.empty() && line.starts_with("[ T ]")) {
                string formatted_line = "[  ]: " + line.substr(7);
                agenda_list.push_back(formatted_line);
                continue;
            }

            if (!found_agenda) {
                if (line.find(tomorrow_agenda) != string::npos) {
                    found_agenda = true;
                }
                continue;
            }

            if (!line.empty() && line.starts_with("-") && line.length() > 2) {
                string formatted_line = "[  ]: " + line.substr(2);
                agenda_list.push_back(formatted_line);
            }

            if (line.find(end) != string::npos) {
                finished = true;
            }
        }
    } else {
        cerr << "Error opening file: " << path << endl;
        cout << ">> Can't find yesterday file, skipped. Starting with a fresh agenda." << endl;
    }

    file.close();
    return agenda_list;
}

void create_day_schema(ofstream& day_file, const string& date, const vector<string>& agenda_list)
{
    day_file << "DAILY TRACKER" << " - " << date << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Day Score: /10                  |         Goal Rate: /10" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Targets:" << endl;

    if (!agenda_list.empty()) {
        for (const string& item : agenda_list) {
            day_file << item << endl;
        }
    } else {
        day_file << "[  ]:" << endl;
    }

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
    day_file << "[  ] Cash (Total: )" << endl;
    day_file << "     -" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Tomorrow's Agenda:" << endl;
    day_file << "-" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
    day_file << "Notes:" << endl;
    day_file << "-" << endl;
    day_file << "#---------------------------------------------------------#" << endl;
}

void create_day(string day = "")
{
    string import, input, path;
    bool valid = false;
    vector<string> agenda_list;
    const string day_date = get_day(0);

    if (!day.empty()) {
        path = "/opt/minu/days/" + day;
    } else {
        path = "/opt/minu/days/" + day_date;
    }

    while (!valid) {
        cout << "Import yesterday's 'Tomorrow's Agenda'? [Y/n]: ";
        getline(cin, input);

        if (input.empty() || input[0] == 'y' || input[0] == 'Y') {
            cout << ">> Importing items..." << endl;
            get_tomorrow_agenda(agenda_list, day);
            valid = true;
        } else if (input[0] == 'n' || input[0] == 'N') {
            cout << ">> Skipped. Starting with a fresh agenda." << endl;
            valid = true;
        } else {
            cout << "Invalid input! Please press 'y' for Yes or 'n' for No." << endl;
        }
    }

    ofstream day_file(path);

    if (day_file.is_open()) {
        cout << "File created successfully!" << endl;
        cout << "File path: " << path << endl;
        create_day_schema(day_file, day_date, agenda_list);
        day_file.close();
    } else {
        cout << "Can't create file!" << endl;
    }
}

void edit_day(string day_arg = "")
{
    string editor_input;
    string command;
    string path;
    const regex date_pattern(R"(\d{2}[/-]\d{2}[/-]\d{4})");

    if (day_arg == "yesterday") {
        const string day_date = get_day(-1);
        path = "/opt/minu/days/" + day_date;
    } else if (day_arg == "tomorrow") {
        const string day_date = get_day(1);
        path = "/opt/minu/days/" + day_date;
    } else if (regex_match(day_arg, date_pattern)) {
        path = "/opt/minu/days/" + day_arg;
    } else {
        const string day_date = get_day(0);
        path = "/opt/minu/days/" + day_date;
    }

    ifstream f(path);

    if (!f.good()) {
        if (day_arg == "tomorrow") {
            cout << "Create next day!" << endl;
        }
        cout << "File does not exist => " << path << endl;
        return;
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
    } else {
        cout << "Invalid input!" << endl;
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
    const regex date_pattern(R"(\d{2}[/-]\d{2}[/-]\d{4})");
    map<string_view, function<void()>> commands = {
        {"--create_day", [&]() {
                if (argc > 2) {
                    const string arg = argv[2];
                    if (regex_match(arg, date_pattern)) {
                        create_day(arg);
                    } else {
                        cout << "Unknown Argument => " << arg << "\n" << endl;
                    }
                } else {
                    create_day();
                }
        }},
        {"--help", help},
        {"--edit_day", [&]() {
                if (argc > 2) {
                    const string arg = argv[2];
                    if (arg == "yesterday" || arg == "tomorrow" || regex_match(arg, date_pattern)) {
                        edit_day(arg);
                    } else {
                        cout << "Unknown Argument => " << arg << "\n" << endl;
                    }
                } else {
                    edit_day();
                }
        }},
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

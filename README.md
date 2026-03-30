# Minu

A minimalist CLI daily tracker for engineering, habits, and productivity.

## Installation

To compile and install **Minu** on your system, follow these steps:

```bash
mkdir build && cd build
cmake ..
make
sudo make install
cd ..

```

## Features

### Create Today's Entry

Generates a new daily tracking file based on a pre-defined schema in `/opt/minu/days/`.

```bash
sudo minu --create_day
```

### List Day Entries

To list all day entries,

```bash
minu --list_days
```

#### Example Output

```bash
$ sudo minu --list_days                                               
08-03-2026      10-03-2026      12-03-2026      14-03-2026      16-03-2026      18-03-2026      23-03-2026      25-03-2026      29-11-2021
09-03-2026      11-03-2026      13-03-2026      15-03-2026      17-03-2026      19-03-2026      24-03-2026      26-03-2026      backlogs
```

When creating a new day with minu --create_day, the system will ask if you want to import tasks from yesterday.

Minu scans your previous entry in two ways:
```bash
Targets:
[ T ]: This will be imported tomorrow!
[ + ]: This is finished and won't be imported.

...

Tomorrow's Agenda:
- This will also be imported!
```
### Edit an Entry

Opens the daily tracker in your preferred editor (**Nano** or **Vim**).

```bash
# Edit today's entry
sudo minu --edit_day

# Edit a specific date
sudo minu --edit_day <dd-mm-yyyy>
```

### Fetch Idea & Backlog

**Note:**  Each entry must be contained within a single line; do not use line breaks or multi-line formatting.

```bash
# To fetch
sudo minu --fetch_backlog
```
Compiles your ideas and projects into a centralized backlog file.

## Schema Overview

The generated schema provides a holistic view of your day:

* **Performance Metrics:** Quick scoring for Day Quality and Goal Completion.
* **Engineering Logs:** Track Work and Personal development with +/- diff counters.
* **Intellectual Growth:** Focused tracking for Classic and Technical reading.
* **Backlog & Ideation:** Dedicated space for brainstorming and project notes.
* **Health & Discipline:** Step counter, exercise logs, and bad habit tracking.
* **Language Lab:** Bilingual practice counters and vocabulary logs.
* **Finance:** Daily ticket and credit card expense tracking.

## Filled Mockup Example

Here is a generic example of a completed daily entry:

```text
DAILY TRACKER - 09-03-2026
#---------------------------------------------------------#
Day Score: 7/10                  |         Goal Rate: 8/10
#---------------------------------------------------------#
Targets:
[ + ]: Complete documentation for the eBPF program.
[ + ]: Buy groceries for the week
[ T ]: Finish the second chapter of the book
#---------------------------------------------------------#
Engineering
[ + ] Work: +120 -30
Notes:
     -> Implemented XDP_DROP for blacklisted IPs in the ingress hook.
     -> Refactored the BPF map lookups to reduce instruction count.
[ + ] Personal: +15 -2
Notes:
     -> Refactored the CLI argument parser.
     -> Fixed a linker error in the X module
#---------------------------------------------------------#
Knowledge & Reading
[ + ] Classic: "Nutuk" (Page 50-70)
[ + ] Technical: "Learning eBPF" (Chapter 4. The bpf() System Call)
#---------------------------------------------------------#
Idea & Backlog
Idea:
     -> Use AF_XDP for zero-copy packet processing in userspace.
Project:
     -> Firewall Project: Integrate rate limiting per client policy.
#---------------------------------------------------------#
Training & Health
#---------------------------------------------------------#
[ + ] Steps: 10,000           | [ + ] Exercises: 30 min Run
[ + ] Fast-Food [ - ] Smoke [ + ] Junk Food
#---------------------------------------------------------#
Language Lab
[ + ] English (Count: 3)
     - Idempotency, Determinism, Reentrancy
[ + ] Japanese (Count: 5)
     - Kuruma (Car), Gakkou (School), Mizu (Water), Hon (Book), Neko (Cat)
#---------------------------------------------------------#
Finance
[ + ] Ticket (Total: 15.50)
     - Lunch at the bistro.
[ + ] Credit Card (Total: 50.00)
     - Bought a new mechanical keyboard switch set.
#---------------------------------------------------------#
Tomorrow's Agenda:
- Debug the BPF verifier error in the tail-call implementation.
- Refactor the CMakeLists for better dependency management.
- Go to GYM.
#---------------------------------------------------------#
Notes:
- XDP performance is looking good, but need to test with 10Gbps traffic.
- Need to cut down on junk food.
#---------------------------------------------------------#
```

## Troubleshooting

If you encounter the following message:

```text
Can't create a file!
```

Ensure you have the necessary permissions for the `/opt/minu` directory. You can run the command with `sudo` or change the directory ownership:

```bash
sudo chown -R $USER /opt/minu
```

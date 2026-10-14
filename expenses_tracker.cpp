#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <cstdio>
#include <cctype>

using namespace std;

const string DATA_FILE = "expenses.txt";
const string TEMP_FILE = "expenses_temp.txt";

string readText(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);

    if (value.empty())
        throw invalid_argument("Input cannot be empty.");

    for (char& ch : value)
        if (ch == '|') ch = '/';

    return value;
}

int readInt(const string& prompt) {
    int value;
    cout << prompt;

    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Please enter a valid whole number.");
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double readAmount(const string& prompt) {
    double value;
    cout << prompt;

    if (!(cin >> value) || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Amount must be a valid number greater than zero.");
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string lowerText(string value) {
    transform(value.begin(), value.end(), value.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return value;
}

class Expense {
public:
    int id;
    double amount;
    string date, category, description, paymentMethod;

    Expense(int i, double a, string d, string c, string desc, string payment)
        : id(i), amount(a), date(d), category(c),
          description(desc), paymentMethod(payment) {}

    void save() const {
        ofstream file(DATA_FILE, ios::app);
        if (!file)
            throw runtime_error("Cannot open the expense data file.");

        file << id << '|'
             << fixed << setprecision(2) << amount << '|'
             << date << '|' << category << '|'
             << description << '|' << paymentMethod << '\n';
    }
};

class ExpenseTracker {
private:
    vector<Expense> loadExpenses() const {
        vector<Expense> expenses;
        ifstream file(DATA_FILE);

        if (!file) return expenses; // First run: no file exists yet.

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idText, amountText, date, category, description, payment;

            if (!getline(ss, idText, '|') ||
                !getline(ss, amountText, '|') ||
                !getline(ss, date, '|') ||
                !getline(ss, category, '|') ||
                !getline(ss, description, '|') ||
                !getline(ss, payment))
                continue;

            try {
                int id = stoi(idText);
                double amount = stod(amountText);
                expenses.emplace_back(id, amount, date, category,
                                       description, payment);
            } catch (...) {
                // Ignore malformed records rather than stopping the program.
            }
        }
        return expenses;
    }

    int nextId() const {
        int largest = 1000;
        for (const auto& expense : loadExpenses())
            largest = max(largest, expense.id);
        return largest + 1;
    }

    static void printHeader() {
        cout << left
             << setw(7) << "ID"
             << setw(12) << "DATE"
             << right << setw(12) << "AMOUNT"
             << left << "   " << setw(17) << "CATEGORY"
             << setw(24) << "DESCRIPTION"
             << "PAYMENT METHOD\n";
        cout << string(91, '-') << '\n';
    }

    static void printExpense(const Expense& e) {
        cout << left
             << setw(7) << e.id
             << setw(12) << e.date
             << right << setw(12) << fixed << setprecision(2) << e.amount
             << left << "   " << setw(17) << e.category
             << setw(24) << e.description
             << e.paymentMethod << '\n';
    }

    static bool containsIgnoreCase(const string& text, const string& query) {
        return lowerText(text).find(lowerText(query)) != string::npos;
    }

    bool rewriteExpenses(const vector<Expense>& expenses) const {
        ofstream out(TEMP_FILE);
        if (!out) return false;

        for (const auto& e : expenses) {
            out << e.id << '|'
                << fixed << setprecision(2) << e.amount << '|'
                << e.date << '|' << e.category << '|'
                << e.description << '|' << e.paymentMethod << '\n';
        }
        out.close();

        if (remove(DATA_FILE.c_str()) != 0 && ifstream(DATA_FILE).good()) {
            remove(TEMP_FILE.c_str());
            return false;
        }

        if (rename(TEMP_FILE.c_str(), DATA_FILE.c_str()) != 0) {
            return false;
        }
        return true;
    }

public:
    void addExpense() {
        cout << "\n===== ADD EXPENSE =====\n";
        double amount = readAmount("Amount (INR): ");
        string date = readText("Date (YYYY-MM-DD): ");
        string category = readText(
            "Category (Food/Travel/Shopping/Bills/Education/Health/Other): ");
        string description = readText("Description: ");
        string payment = readText("Payment method (Cash/UPI/Card/Other): ");

        Expense expense(nextId(), amount, date, category, description, payment);
        expense.save();

        cout << "\nExpense saved successfully. Expense ID: "
             << expense.id << "\n";
    }

    void viewExpenses() const {
        vector<Expense> expenses = loadExpenses();
        cout << "\n===== ALL EXPENSES =====\n";

        if (expenses.empty()) {
            cout << "No expenses found. Add your first expense to get started.\n";
            return;
        }

        printHeader();
        double total = 0;
        for (const auto& e : expenses) {
            printExpense(e);
            total += e.amount;
        }
        cout << string(91, '-') << '\n';
        cout << "Total expenses: INR " << fixed << setprecision(2)
             << total << " (" << expenses.size() << " records)\n";
    }

    void searchExpenses() const {
        string query = readText("Search by date, category, description, or payment method: ");
        vector<Expense> expenses = loadExpenses();
        bool found = false;
        double total = 0;

        cout << "\n===== SEARCH RESULTS =====\n";
        printHeader();
        for (const auto& e : expenses) {
            if (containsIgnoreCase(e.date, query) ||
                containsIgnoreCase(e.category, query) ||
                containsIgnoreCase(e.description, query) ||
                containsIgnoreCase(e.paymentMethod, query)) {
                printExpense(e);
                total += e.amount;
                found = true;
            }
        }

        if (!found) cout << "No matching expenses found.\n";
        else cout << "Matching total: INR " << fixed << setprecision(2) << total << '\n';
    }

    void categoryReport() const {
        vector<Expense> expenses = loadExpenses();
        if (expenses.empty()) {
            cout << "\nNo expenses available for a report.\n";
            return;
        }

        vector<pair<string, double>> totals;
        for (const auto& e : expenses) {
            auto it = find_if(totals.begin(), totals.end(),
                [&](const pair<string, double>& item) {
                    return lowerText(item.first) == lowerText(e.category);
                });
            if (it == totals.end())
                totals.push_back({e.category, e.amount});
            else
                it->second += e.amount;
        }

        sort(totals.begin(), totals.end(),
             [](const pair<string, double>& a, const pair<string, double>& b) {
                 return a.second > b.second;
             });

        double grandTotal = 0;
        for (const auto& item : totals) grandTotal += item.second;

        cout << "\n===== CATEGORY-WISE REPORT =====\n";
        cout << left << setw(24) << "CATEGORY"
             << right << setw(16) << "TOTAL (INR)"
             << setw(12) << "SHARE" << '\n';
        cout << string(52, '-') << '\n';

        for (const auto& item : totals) {
            double percent = grandTotal > 0 ? item.second * 100.0 / grandTotal : 0;
            cout << left << setw(24) << item.first
                 << right << setw(16) << fixed << setprecision(2) << item.second
                 << setw(11) << setprecision(1) << percent << "%\n";
        }
        cout << string(52, '-') << '\n';
        cout << left << setw(24) << "TOTAL"
             << right << setw(16) << fixed << setprecision(2) << grandTotal
             << setw(11) << "100.0%" << '\n';
    }

    void monthlyReport() const {
        string month = readText("Enter month (YYYY-MM): ");
        vector<Expense> expenses = loadExpenses();
        double total = 0;
        int count = 0;

        cout << "\n===== MONTHLY REPORT: " << month << " =====\n";
        printHeader();
        for (const auto& e : expenses) {
            if (e.date.size() >= 7 && e.date.substr(0, 7) == month) {
                printExpense(e);
                total += e.amount;
                ++count;
            }
        }

        if (count == 0) cout << "No expenses found for this month.\n";
        cout << string(91, '-') << '\n';
        cout << "Monthly total: INR " << fixed << setprecision(2)
             << total << " | Transactions: " << count << '\n';
    }

    void deleteExpense() {
        int targetId = readInt("Enter expense ID to delete: ");
        vector<Expense> expenses = loadExpenses();
        auto oldSize = expenses.size();

        expenses.erase(remove_if(expenses.begin(), expenses.end(),
            [&](const Expense& e) { return e.id == targetId; }), expenses.end());

        if (expenses.size() == oldSize) {
            cout << "Expense ID not found.\n";
            return;
        }

        if (!rewriteExpenses(expenses))
            throw runtime_error("Could not update the expense file.");

        cout << "Expense deleted successfully.\n";
    }

    void run() {
        while (true) {
            cout << "\n";
            cout << "============================================================\n";
            cout << "                      EXPENSE TRACKER\n";
            cout << "                 PERSONAL FINANCE MANAGER\n";
            cout << "============================================================\n";
            cout << "  1. Add Expense\n";
            cout << "  2. View All Expenses\n";
            cout << "  3. Search Expenses\n";
            cout << "  4. Category-wise Report\n";
            cout << "  5. Monthly Report\n";
            cout << "  6. Delete Expense\n";
            cout << "  0. Exit\n";
            cout << "============================================================\n";

            try {
                int choice = readInt("Choose an option: ");
                switch (choice) {
                    case 1: addExpense(); break;
                    case 2: viewExpenses(); break;
                    case 3: searchExpenses(); break;
                    case 4: categoryReport(); break;
                    case 5: monthlyReport(); break;
                    case 6: deleteExpense(); break;
                    case 0:
                        cout << "Thank you for using Expense Tracker!\n";
                        return;
                    default:
                        cout << "Invalid option. Please choose from 0 to 6.\n";
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << '\n';
            }
        }
    }
};

int main() {
    try {
        ExpenseTracker tracker;
        tracker.run();
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <optional>

struct Entry {
    std::string key;
    std::string value;
    bool occupied;
    bool deleted;

    Entry() : key(""), value(""), occupied(false), deleted(false) {}
};

class HashTable {
public:
    HashTable(int size) : table(size), numElements(0), loadFactorThreshold(0.7) {}

    bool insert(const std::string& key, const std::string& value) {
        if (static_cast<double>(numElements) / table.size() >= loadFactorThreshold) {
            resizeTable();
        }

        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1;

        while (table[index].occupied && !table[index].deleted && table[index].key != key) {
            index = (originalIndex + i * i) % table.size();
            i++;
            if (index == originalIndex) return false;
        }

        if (!table[index].occupied || table[index].deleted) {
            numElements++;
        }

        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
        table[index].deleted = false;
        return true;
    }

    std::optional<std::string> read(const std::string& key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1;

        while (table[index].occupied) {
            if (!table[index].deleted && table[index].key == key) {
                return table[index].value;
            }
            index = (originalIndex + i * i) % table.size();
            i++;
            if (index == originalIndex) break;
        }

        return std::nullopt;
    }

    bool update(const std::string& key, const std::string& newValue) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1;

        while (table[index].occupied) {
            if (!table[index].deleted && table[index].key == key) {
                table[index].value = newValue;
                return true;
            }
            index = (originalIndex + i * i) % table.size();
            i++;
            if (index == originalIndex) break;
        }

        return false;
    }

    bool remove(const std::string& key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 1;

        while (table[index].occupied) {
            if (!table[index].deleted && table[index].key == key) {
                table[index].deleted = true;
                numElements--;
                return true;
            }
            index = (originalIndex + i * i) % table.size();
            i++;
            if (index == originalIndex) break;
        }

        return false;
    }

    void printTable() const {
        std::cout << "Hash Table Contents:\n";
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].occupied && !table[i].deleted) {
                std::cout << "Index " << i << ": Key = " << table[i].key << ", Value = " << table[i].value << "\n";
            }
            else if (table[i].occupied && table[i].deleted) {
                std::cout << "Index " << i << ": <deleted>\n";
            }
            else {
                std::cout << "Index " << i << ": <empty>\n";
            }
        }
    }

private:
    std::vector<Entry> table;
    int numElements;
    double loadFactorThreshold;

    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % table.size();
        }
        return hash;
    }

    void resizeTable() {
        std::vector<Entry> oldTable = table;
        table.resize(oldTable.size() * 2);
        for (auto& entry : table) {
            entry = Entry();
        }
        numElements = 0;

        for (const auto& entry : oldTable) {
            if (entry.occupied && !entry.deleted) {
                insert(entry.key, entry.value);
            }
        }
    }
};

void printMenu() {
    std::cout << "\nSelect an operation:\n";
    std::cout << "1. Insert\n";
    std::cout << "2. Read\n";
    std::cout << "3. Update\n";
    std::cout << "4. Delete\n";
    std::cout << "5. Print Table\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    HashTable ht(10);
    int choice;
    std::string key, value;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Enter value: ";
            std::cin.ignore();
            std::getline(std::cin, value);
            if (ht.insert(key, value)) {
                std::cout << "Inserted successfully.\n";
            }
            else {
                std::cout << "Insertion failed.\n";
            }
            break;

        case 2:
            std::cout << "Enter key: ";
            std::cin >> key;
            if (auto result = ht.read(key); result.has_value()) {
                std::cout << "Value: " << result.value() << "\n";
            }
            else {
                std::cout << "Key not found.\n";
            }
            break;

        case 3:
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Enter new value: ";
            std::cin.ignore();
            std::getline(std::cin, value);
            if (ht.update(key, value)) {
                std::cout << "Updated successfully.\n";
            }
            else {
                std::cout << "Update failed.\n";
            }
            break;

        case 4:
            std::cout << "Enter key: ";
            std::cin >> key;
            if (ht.remove(key)) {
                std::cout << "Deleted successfully.\n";
            }
            else {
                std::cout << "Deletion failed.\n";
            }
            break;

        case 5:
            ht.printTable();
            break;

        case 6:
            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 6);

    return 0;
}

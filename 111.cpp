#include <bits/stdc++.h>
using namespace std;

// �����Ʒ�����ö������
enum class ProductCategory
{
    Foodstuffs,
    Electronics,
    Chemicals,
    Machinery,
    CulturalGoods,
    Textiles
};

// ������ö������ת��Ϊ�ַ���
string categoryToString(ProductCategory category)
{
    const map<ProductCategory, string> categoryNames = {
        {ProductCategory::Foodstuffs, "Foodstuffs"},
        {ProductCategory::Electronics, "Electronics"},
        {ProductCategory::Chemicals, "Chemicals"},
        {ProductCategory::Machinery, "Machinery and Equipment"},
        {ProductCategory::CulturalGoods, "Cultural Goods"},
        {ProductCategory::Textiles, "Textiles"}};
    auto it = categoryNames.find(category);
    if (it != categoryNames.end())
    {
        return it->second;
    }
    return "Unknown";
}

// ������Ʒ��
class Product
{
private:
    static int nextId; // ������һ�����õ�ID
    int id;
    string name;
    double price;
    ProductCategory category;                        // ��Ʒ����
    static map<ProductCategory, int> categoryCounts; // ÿ�ַ��������
    string storageCondition;
    string status;
    string location;

public:
    // ���캯��
    Product(string name, double price, ProductCategory category, string storageCondition, string status, string location) : id(nextId++), name(move(name)), price(price), category(category), storageCondition(move(storageCondition)), status(move(status)), location(move(location))
    {
        ++categoryCounts[category];
    }

    virtual ~Product()
    {
        // ����Ʒ������ʱ�����ٶ�Ӧ����ļ���
        if (categoryCounts.find(category) != categoryCounts.end() && categoryCounts[category] > 0)
        {
            categoryCounts[category]--;
        }
    }

    // ��ʾ��Ʒ��Ϣ
    virtual void display(ostream &os) const
    {
        os
            << "ID: " << id << ", Name: " << name << ", Price: " << fixed << setprecision(2) << price << "Yuan"
            << ", Storage Condition: " << storageCondition << ", Status: " << status
            << ", Location: " << location << endl;
        os << endl;
    }
    // ��ȡ���������
    string getCategoryName() const
    {
        return categoryToString(category);
    }

    static int getCategoryCount(ProductCategory cat)
    {
        return categoryCounts[cat];
    }

    // ��ȡ��ǰ����Ĳ�Ʒ����
    int getCategoryCount() const
    {
        return categoryCounts.at(category);
    }

    // ��ȡ����
    ProductCategory getCategory() const
    {
        return category;
    }
};

// ��ʼ����̬��Ա����
int Product::nextId = 1;
map<ProductCategory, int> Product::categoryCounts = {};

// ��������������Խ��� ProductCategory ö������
istream &operator>>(istream &is, ProductCategory &category)
{
    string token;
    is >> token;
    if (token == "Foodstuffs")
        category = ProductCategory::Foodstuffs;
    else if (token == "Electronics")
        category = ProductCategory::Electronics;
    // ... ���������ƥ�� ...
    else
        is.setstate(ios::failbit); // ������벻ƥ�䣬����ʧ��λ
    return is;
}
// ����<<�������Է������Product��Ϣ
ostream &operator<<(ostream &os, const Product &p)
{
    p.display(os);
    return os;
}

// �����Ʒ�࣬�̳���Product
class CategorizedProduct : public Product
{
public:
    // ���캯��
    CategorizedProduct(const string &name, double price, const ProductCategory &category, const string &storageCondition, const string &status, const string &location)
        : Product(name, price, category, storageCondition, status, location) {}
    // CategorizedProduct ������д display ��������Ӷ������ʾ��Ϣ�������Ҫ�Ļ�
};

// ������ϵͳ
class InventorySystem
{
private:
    vector<unique_ptr<Product>> products;

public:
    // ��Ӳ�Ʒ�����
    void addProduct(unique_ptr<Product> product)
    {
        products.push_back(move(product));
    }

    // ��ʾ���в�Ʒ��Ϣ5
    void displayAllProducts(ostream &os) const
    {
        map<ProductCategory, vector<const Product *>> categoryProducts;
        for (const auto &product : products)
        {
            categoryProducts[product->getCategory()].push_back(product.get());
        }

        os << "Inventory System contains " << products.size() << " products:" << endl;
        for (const auto &categoryPair : categoryProducts)
        {
            os << "Category: " << categoryToString(categoryPair.first) << ", Total: " << categoryPair.second.size() << endl;
            for (const auto &product : categoryPair.second)
            {
                product->display(os);
            }
            os << "-------------------------------------------------------------" << endl; // �ָ��ߣ������ɶ���
        }
    }
    // ������Ʒ�����ʾ��Ʒ
    void displayProductsByCategory(ProductCategory category, ostream &os) const
    {
        int count = 0;
        for (const auto &product : products)
        {
            if (product->getCategory() == category)
            {
                ++count;
            }
        }

        os << "Products in Category: " << categoryToString(category) << " (Total: " << count << ")" << endl;
        for (const auto &product : products)
        {
            if (product->getCategory() == category)
            {
                product->display(os);
            }
        }
        os << endl;
    }
    // ���ɿ�汨��
    void generateReport(ostream &os = cout) const
    {
        displayAllProducts(os);
    }
};

int main()
{
    InventorySystem inventory;

    ProductCategory Foodstuffs = ProductCategory::Foodstuffs;
    ProductCategory Electronics = ProductCategory::Electronics;
    ProductCategory Chemicals = ProductCategory::Chemicals;
    ProductCategory MachineryAndEquipment = ProductCategory::Machinery;
    ProductCategory CulturalGoods = ProductCategory::CulturalGoods;
    ProductCategory Textiles = ProductCategory::Textiles;

    // ϵͳԭʼ��Ϣ
    inventory.addProduct(make_unique<CategorizedProduct>("Apple", 0.30, Foodstuffs, "Room Temperature", "In Stock", "Local"));
    inventory.addProduct(make_unique<CategorizedProduct>("iPhone", 999.99, Electronics, "Room Temperature", "In Stock", "Local"));
    inventory.addProduct(make_unique<CategorizedProduct>("jiujing", 0.20, Chemicals, "Room Temperature", "In Stock", "Local"));
    inventory.addProduct(make_unique<CategorizedProduct>("Banana", 9.9, Foodstuffs, "Room Temperature", "In Stock", "Local"));

    cout << "Start  --  Enter 1" << endl;
    int choice;
    cin >> choice;
    // ���������ҵ��
    while (choice != 4)
    {

        cout << "Please select your business:" << endl
             << "1.Information Entry, enter 1" << endl
             << "2.Incoming classification, enter 2" << endl
             << "3.Inquiry, enter 3" << endl
             << "4.Exit, enter 4" << endl;
        int choice;
        cin >> choice;
        // 1.��Ϣ¼�룺
        if (choice == 1)
        {
            // �������ͣ�ʳƷ/���Ӳ�Ʒ/��ѧƷ/��е�豸/�Ļ���Ʒ/��֯Ʒ��
            // ��������������/���/�䶳/Σ��Ʒ��
            // ���۷���ʡ��/ʡ��/���⣻
            // ������Դ��ʡ��/ʡ��/���⡣
            cout << "name " << endl
                 << "/price   (Two digits after the decimal point)" << endl
                 << "/category   (Foodstuffs/Electronics/Chemicals/MachineryAndEquipment/CulturalGoods/Textiles) " << endl
                 << "/storageCondition   (Room temperature/refrigerated/frozen/dangerous goods) " << endl
                 << "/Source of goods   (Provincial/Out-of-province/Overseas) " << endl
                 << "/location   (Provincial/Out-of-province/Overseas)" << endl; // ����λ��
            string name = "";
            double price = 0.00;
            ProductCategory category;
            string storageCondition = ""; // �洢����woxiwang
            string status = "";           // ��������
            string location = "";         // ������Դ

            cin >> name >> price >> category >> storageCondition >> status >> location;
            // ȷ������� category �� ProductCategory ����
            if (cin.fail())
            {
                cerr << "Invalid input for category." << endl;
                return 1;
            }
            inventory.addProduct(make_unique<CategorizedProduct>(name, price, category, storageCondition, status, location));
            // ���ɿ�汨��
            cout << "Generating Inventory Report:" << endl;

            inventory.generateReport();

            // �����������ļ�
            ofstream outFile("inventory_report.txt");
            if (!outFile.is_open())
            {
                cerr << "Unable to open file for writing." << endl;
                return 1;
            }
            inventory.generateReport(outFile);
            outFile.close();
        }

        //

        // 3.��ѯ��
        else if (choice == 3)
        {
            // ��ѯ��ʽ
            cout << "Please enter the query type:" << endl;
            cout << "1. All cargo, enter 5 " << endl
                 << "2. Search by class name, enter 6" << endl;

            int choice2;
            cin >> choice2;

            // ��ʾȫ��
            if (choice2 == 5)
            {
                // // ��ʾ���в�Ʒ��Ϣ
                // cout << "All Products in Inventory:" << endl;
                // inventory.displayAllProducts(cout);

                // ���ɿ�汨��
                cout << "Generating Inventory Report:" << endl;
                inventory.generateReport();

                // �����������ļ�
                ofstream outFile("inventory_report.txt");
                if (!outFile.is_open())
                {
                    cerr << "Unable to open file for writing." << endl;
                    return 1;
                }
                inventory.generateReport(outFile);
                outFile.close();
            }
            // ��������
            else if (choice2 == 6)
            {
                // �û�������Ʒ����
                string categoryName;
                cout << "Enter product category name (Foodstuffs, Electronics, Chemicals, Machinery, CulturalGoods, Textiles): ";
                cin >> categoryName;
                if (cin.fail())
                {
                    cerr << "Invalid category name entered." << endl;
                    return 1;
                }
                ProductCategory selectedCategory;
                if (categoryName == "Foodstuffs")
                {
                    selectedCategory = Foodstuffs;
                }
                else if (categoryName == "Electronics")
                {
                    selectedCategory = Electronics;
                }
                else if (categoryName == "Chemicals")
                {
                    selectedCategory = Chemicals;
                }
                else if (categoryName == "Machinery")
                {
                    selectedCategory = MachineryAndEquipment;
                }
                else if (categoryName == "CulturalGoods")
                {
                    selectedCategory = CulturalGoods;
                }
                else if (categoryName == "Textiles")
                {
                    selectedCategory = Textiles;
                }
                else
                {
                    cout << "Invalid category name." << endl;
                    return 1;
                }

                // ��ʾָ�����Ĳ�Ʒ��Ϣ
                cout << "Products in Category: " << categoryName << endl;
                inventory.displayProductsByCategory(selectedCategory, cout);

                // ��ָ�����Ĳ�Ʒ��Ϣ������ļ�
                ofstream categoryOutFile(categoryName + "_report.txt");
                if (!categoryOutFile.is_open())
                {
                    cerr << "Unable to open file for writing." << endl;
                    return 1;
                }
                inventory.displayProductsByCategory(selectedCategory, categoryOutFile);
                categoryOutFile.close();
            }
        }

        // 4.�˳���
        else if (choice == 4)
        {
            cout << "Thank you for using the inventory system." << endl;
            return 0;
        }
    }
    return 0;
}

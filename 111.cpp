#include <bits/stdc++.h>
using namespace std;

// 定义产品分类的枚举类型
enum class ProductCategory
{
    Foodstuffs,
    Electronics,
    Chemicals,
    Machinery,
    CulturalGoods,
    Textiles
};

// 将分类枚举类型转换为字符串
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

// 基础产品类
class Product
{
private:
    static int nextId; // 跟踪下一个可用的ID
    int id;
    string name;
    double price;
    ProductCategory category;                        // 产品分类
    static map<ProductCategory, int> categoryCounts; // 每种分类的数量
    string storageCondition;
    string status;
    string location;

public:
    // 构造函数
    Product(string name, double price, ProductCategory category, string storageCondition, string status, string location) : id(nextId++), name(move(name)), price(price), category(category), storageCondition(move(storageCondition)), status(move(status)), location(move(location))
    {
        ++categoryCounts[category];
    }

    virtual ~Product()
    {
        // 当产品被销毁时，减少对应分类的计数
        if (categoryCounts.find(category) != categoryCounts.end() && categoryCounts[category] > 0)
        {
            categoryCounts[category]--;
        }
    }

    // 显示产品信息
    virtual void display(ostream &os) const
    {
        os
            << "ID: " << id << ", Name: " << name << ", Price: " << fixed << setprecision(2) << price << "Yuan"
            << ", Storage Condition: " << storageCondition << ", Status: " << status
            << ", Location: " << location << endl;
        os << endl;
    }
    // 获取分类的名称
    string getCategoryName() const
    {
        return categoryToString(category);
    }

    static int getCategoryCount(ProductCategory cat)
    {
        return categoryCounts[cat];
    }

    // 获取当前分类的产品数量
    int getCategoryCount() const
    {
        return categoryCounts.at(category);
    }

    // 获取分类
    ProductCategory getCategory() const
    {
        return category;
    }
};

// 初始化静态成员变量
int Product::nextId = 1;
map<ProductCategory, int> Product::categoryCounts = {};

// 重载输入操作符以接受 ProductCategory 枚举类型
istream &operator>>(istream &is, ProductCategory &category)
{
    string token;
    is >> token;
    if (token == "Foodstuffs")
        category = ProductCategory::Foodstuffs;
    else if (token == "Electronics")
        category = ProductCategory::Electronics;
    // ... 其他分类的匹配 ...
    else
        is.setstate(ios::failbit); // 如果输入不匹配，设置失败位
    return is;
}
// 重载<<操作符以方便输出Product信息
ostream &operator<<(ostream &os, const Product &p)
{
    p.display(os);
    return os;
}

// 分类产品类，继承自Product
class CategorizedProduct : public Product
{
public:
    // 构造函数
    CategorizedProduct(const string &name, double price, const ProductCategory &category, const string &storageCondition, const string &status, const string &location)
        : Product(name, price, category, storageCondition, status, location) {}
    // CategorizedProduct 可以重写 display 方法以添加额外的显示信息，如果需要的话
};

// 库存管理系统
class InventorySystem
{
private:
    vector<unique_ptr<Product>> products;

public:
    // 添加产品到库存
    void addProduct(unique_ptr<Product> product)
    {
        products.push_back(move(product));
    }

    // 显示所有产品信息5
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
            os << "-------------------------------------------------------------" << endl; // 分割线，提升可读性
        }
    }
    // 根据商品类别显示商品
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
    // 生成库存报告
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

    // 系统原始信息
    inventory.addProduct(make_unique<CategorizedProduct>("Apple", 0.30, Foodstuffs, "Room Temperature", "In Stock", "Local"));
    inventory.addProduct(make_unique<CategorizedProduct>("iPhone", 999.99, Electronics, "Room Temperature", "In Stock", "Local"));
    inventory.addProduct(make_unique<CategorizedProduct>("jiujing", 0.20, Chemicals, "Room Temperature", "In Stock", "Local"));
    inventory.addProduct(make_unique<CategorizedProduct>("Banana", 9.9, Foodstuffs, "Room Temperature", "In Stock", "Local"));

    cout << "Start  --  Enter 1" << endl;
    int choice;
    cin >> choice;
    // 请输入你的业务
    while (choice != 4)
    {

        cout << "Please select your business:" << endl
             << "1.Information Entry, enter 1" << endl
             << "2.Incoming classification, enter 2" << endl
             << "3.Inquiry, enter 3" << endl
             << "4.Exit, enter 4" << endl;
        int choice;
        cin >> choice;
        // 1.信息录入：
        if (choice == 1)
        {
            // 货物类型：食品/电子产品/化学品/机械设备/文化用品/纺织品；
            // 储存条件：室温/冷藏/冷冻/危险品；
            // 销售方向：省内/省外/海外；
            // 货物来源：省内/省外/海外。
            cout << "name " << endl
                 << "/price   (Two digits after the decimal point)" << endl
                 << "/category   (Foodstuffs/Electronics/Chemicals/MachineryAndEquipment/CulturalGoods/Textiles) " << endl
                 << "/storageCondition   (Room temperature/refrigerated/frozen/dangerous goods) " << endl
                 << "/Source of goods   (Provincial/Out-of-province/Overseas) " << endl
                 << "/location   (Provincial/Out-of-province/Overseas)" << endl; // 地理位置
            string name = "";
            double price = 0.00;
            ProductCategory category;
            string storageCondition = ""; // 存储条件woxiwang
            string status = "";           // 货物销售
            string location = "";         // 货物来源

            cin >> name >> price >> category >> storageCondition >> status >> location;
            // 确保输入的 category 是 ProductCategory 类型
            if (cin.fail())
            {
                cerr << "Invalid input for category." << endl;
                return 1;
            }
            inventory.addProduct(make_unique<CategorizedProduct>(name, price, category, storageCondition, status, location));
            // 生成库存报告
            cout << "Generating Inventory Report:" << endl;

            inventory.generateReport();

            // 将结果输出到文件
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

        // 3.查询：
        else if (choice == 3)
        {
            // 查询方式
            cout << "Please enter the query type:" << endl;
            cout << "1. All cargo, enter 5 " << endl
                 << "2. Search by class name, enter 6" << endl;

            int choice2;
            cin >> choice2;

            // 显示全部
            if (choice2 == 5)
            {
                // // 显示所有产品信息
                // cout << "All Products in Inventory:" << endl;
                // inventory.displayAllProducts(cout);

                // 生成库存报告
                cout << "Generating Inventory Report:" << endl;
                inventory.generateReport();

                // 将结果输出到文件
                ofstream outFile("inventory_report.txt");
                if (!outFile.is_open())
                {
                    cerr << "Unable to open file for writing." << endl;
                    return 1;
                }
                inventory.generateReport(outFile);
                outFile.close();
            }
            // 类名检索
            else if (choice2 == 6)
            {
                // 用户输入商品类名
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

                // 显示指定类别的产品信息
                cout << "Products in Category: " << categoryName << endl;
                inventory.displayProductsByCategory(selectedCategory, cout);

                // 将指定类别的产品信息输出到文件
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

        // 4.退出：
        else if (choice == 4)
        {
            cout << "Thank you for using the inventory system." << endl;
            return 0;
        }
    }
    return 0;
}

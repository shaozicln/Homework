#include <bits/stdc++.h>
using namespace std;

// 定义产品分类的枚举类型  食品、电子产品、化学品、机械产品、文化用品、纺织品
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
    string sale;
    string location;
    int quantity; // 商品数量

public:
    // 构造函数
    Product(string name, double price, ProductCategory category, string storageCondition, string sale, string location, int quantity) : id(nextId++), name(move(name)), price(price), category(category), storageCondition(move(storageCondition)), sale(move(sale)), location(move(location)), quantity(quantity)
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
            << ", Quantity: " << quantity
            << ", Storage Condition: " << storageCondition << ", Sale: " << sale
            << ", Location: " << location << endl;
        os << endl;
    }
    // 获取分类的名称
    string getCategoryName() const
    {
        return categoryToString(category);
    }

    static int getCategoryCount(ProductCategory c)
    {
        return categoryCounts[c];
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

    // 获取产品ID
    int getId() const
    {
        return id;
    }

    // 获取商品数量
    int getQuantity() const
    {
        return quantity;
    }

    // 更新产品信息
    void update(string name, double price, ProductCategory category, string storageCondition, string sale, string location, int quantity)
    {
        this->name = move(name);
        this->price = price;
        this->category = category;
        this->storageCondition = move(storageCondition);
        this->sale = move(sale);
        this->location = move(location);
        this->quantity = quantity;
    }
};

// 初始化静态成员变量
int Product::nextId = 1;
// categoryCounts 用于跟踪每个 ProductCategory 的计数。
// 每当创建一个新的 Product 对象时，对应的 ProductCategory 计数会递增。
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
    else if (token == "Chemicals")
        category = ProductCategory::Chemicals;
    else if (token == "MachineryAndEquipment")
        category = ProductCategory::Machinery;
    else if (token == "CulturalGoods")
        category = ProductCategory::CulturalGoods;
    else if (token == "Textiles")
        category = ProductCategory::Textiles;
    else
        is.setstate(ios::failbit); // 如果输入不匹配，设置流的失败状态
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
    CategorizedProduct(const string &name, double price, const ProductCategory &category, const string &storageCondition, const string &sale, const string &location, int quantity)
        : Product(name, price, category, storageCondition, sale, location, quantity) {}
};

// 库存管理系统
class InventorySystem
{
private:
    // Product 类型的 unique_ptr 智能指针
    vector<unique_ptr<Product>> products;

public:
    // 添加产品到库存
    void addProduct(unique_ptr<Product> product)
    {
        products.push_back(move(product));
    }

    // 显示所有产品信息
    void displayAllProducts(ostream &os) const
    {
        map<ProductCategory, vector<const Product *>> categoryProducts;
        for (const auto &product : products)
        {
            categoryProducts[product->getCategory()].push_back(product.get());
        }

        os << "Inventory System contains " << products.size() << " products:" << endl
           << endl;
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

    // 根据货物ID删除货物
    void removeProductById(int id)
    {
        auto it = find_if(products.begin(), products.end(), [id](const unique_ptr<Product> &product)
                          { return product->getId() == id; });

        if (it != products.end())
        {
            products.erase(it);
            cout << "Product with ID " << id << " has been removed." << endl;
        }
        else
        {
            cout << "Product with ID " << id << " not found." << endl;
        }
    }

    // 根据货物ID更新货物
    void updateProductById(int id, string name, double price, ProductCategory category, string storageCondition, string sale, string location, int quantity)
    {
        auto it = find_if(products.begin(), products.end(), [id](const unique_ptr<Product> &product)
                          { return product->getId() == id; });

        if (it != products.end())
        {
            (*it)->update(name, price, category, storageCondition, sale, location, quantity);
            cout << "Product with ID " << id << " has been updated." << endl;
        }
        else
        {
            cout << "Product with ID " << id << " not found." << endl;
        }
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

    // 仓库原物品
    inventory.addProduct(make_unique<CategorizedProduct>("Apple", 0.30, Foodstuffs, "refrigerated", "Out-of-province", "Provincial", 12000));
    inventory.addProduct(make_unique<CategorizedProduct>("Smartphone", 2999, Electronics, "Room-temperature", "Overseas", "Provincial", 3000));
    inventory.addProduct(make_unique<CategorizedProduct>("Cleaning-agent", 15, Chemicals, "Room-temperature", "Out-of-province", "Provincial", 4687));
    inventory.addProduct(make_unique<CategorizedProduct>("Bikes", 450, MachineryAndEquipment, "Room-Temperature", "Provincial", "Overseas", 500));
    inventory.addProduct(make_unique<CategorizedProduct>("Fountain-pen", 25, CulturalGoods, "Room-Temperature", "Provincial", "Provincial", 20000));
    inventory.addProduct(make_unique<CategorizedProduct>("T-shirt", 39.9, Textiles, "Room-Temperature", "Provincial", "Provincial", 3000));
    inventory.addProduct(make_unique<CategorizedProduct>("Laptops", 6999, Electronics, "Room-Temperature", "Province", "Out-of-province", 3200));
    inventory.addProduct(make_unique<CategorizedProduct>("Cookie", 9.9, Foodstuffs, "Room-Temperature", "Provincial", "Overseas", 8956));

    cout << "Start  --  Enter 1" << endl;
    int choice;
    cin >> choice;

    // 请输入你的业务
    while (choice != 5)
    {
        cout << "Please select your business:" << endl
             << "1.Information Entry, enter 1" << endl
             << "2.Remove Product by ID, enter 2" << endl
             << "3.Inquiry, enter 3" << endl
             << "4.Update Product by ID, enter 4" << endl
             << "5.Exit, enter 5" << endl;
        cin >> choice;

        // 1.信息录入：
        if (choice == 1)
        {
            // 货物类型：食品/电子产品/化学品/机械设备/文化用品/纺织品；
            // 储存条件：室温/冷藏/冷冻/危险品；
            // 销售方向：省内/省外/海外；
            // 货物来源：省内/省外/海外。
            cout << "/name  (English) " << endl
                 << "/price   (Two digits after the decimal point)" << endl
                 << "/category   (Foodstuffs/Electronics/Chemicals/MachineryAndEquipment/CulturalGoods/Textiles) " << endl
                 << "/storageCondition   (Room-temperature/refrigerated/frozen/dangerous-goods) " << endl
                 << "/sale   (Provincial/Out-of-province/Overseas) " << endl
                 << "/location   (Provincial/Out-of-province/Overseas)" << endl
                 << "/quantity   (Integer)" << endl;
            string name = "";
            double price = 0.00;
            ProductCategory category;
            string storageCondition = ""; // 存储条件
            string sale = "";           // 货物销售地点
            string location = "";         // 货物来源地点
            int quantity = 0;             // 商品数量

            cin >> name >> price >> category >> storageCondition >> sale >> location >> quantity;
            // 确保输入的 category 是 ProductCategory 类型
            if (cin.fail())
            {
                cerr << "Invalid input for category." << endl;
                return 1;
            }
            inventory.addProduct(make_unique<CategorizedProduct>(name, price, category, storageCondition, sale, location, quantity));
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

        // 2.根据货物ID删除货物
        else if (choice == 2)
        {
            int productId;
            cout << "Enter the ID of the product to remove: ";
            cin >> productId;
            inventory.removeProductById(productId);
        }

        // 3.查询：
        else if (choice == 3)
        {
            while (1)
            {

                cout << "Please enter the query type:" << endl;
                cout << "1. All cargo, enter 6 " << endl
                     << "2. Search by class name, enter 7" << endl
                     << "3. Return to last operation, enter 8" << endl;

                int choice2;
                cin >> choice2;

                // 6.显示全部
                if (choice2 == 6)
                {
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
                // 7.类名检索
                else if (choice2 == 7)
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
                // 8.返回上一级
                else if (choice2 == 8)
                {
                    break;
                }
            }
        }

        // 4.更新：
        else if (choice == 4)
        {
            int productId;
            cout << "Enter the ID of the product to update: ";
            cin >> productId;

            cout << "/name  (English) " << endl
                 << "/price   (Two digits after the decimal point)" << endl
                 << "/category   (Foodstuffs/Electronics/Chemicals/MachineryAndEquipment/CulturalGoods/Textiles) " << endl
                 << "/storageCondition   (Room-temperature/refrigerated/frozen/dangerous-goods) " << endl
                 << "/Source of goods   (Provincial/Out-of-province/Overseas) " << endl
                 << "/location   (Provincial/Out-of-province/Overseas)" << endl
                 << "/quantity   (Integer)" << endl;
            string name = "";
            double price = 0.00;
            ProductCategory category;
            string storageCondition = ""; // 存储条件
            string sale = "";           // 货物销售地点
            string location = "";         // 货物来源地点
            int quantity = 0;             // 商品数量

            cin >> name >> price >> category >> storageCondition >> sale >> location >> quantity;
            // 确保输入的 category 是 ProductCategory 类型
            if (cin.fail())
            {
                cerr << "Invalid input for category." << endl;
                return 1;
            }
            inventory.updateProductById(productId, name, price, category, storageCondition, sale, location, quantity);
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

        // 5.退出：
        else if (choice == 5)
        {
            cout << "Thank you for using the inventory system." << endl;
            return 0;
        }
    }

    return 0;
}

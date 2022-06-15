#include <iostream>

using std::cout;  using std::endl;

class Drink{
public:
    Drink() = default;
    Drink(std::string flavor) : _flavor(flavor) {}

    virtual void make() = 0;
    virtual ~Drink() = default;
private:
    std::string _flavor;
};


class Tea {
public:
    Tea() = default;

    Tea(std::string flavor) : Drink(flavor) {}

    virtual ~Tea() = default;

    void make() {
        cout << "Made tea" << endl;
    }
};

int main(int argc, char* argv[]) {
    return 0;
}
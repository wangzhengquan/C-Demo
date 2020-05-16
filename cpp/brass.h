// brass.h  -- bank account classes
#ifndef BRASS_H_
#define BRASS_H_
#include <string>


/**
 * If you redefine a base-class method in a derived class, the usual practice is to declare the base-class method as virtual. 
 * This makes the program choose the method version based on object type instead of the type of a reference or pointer. 
 * It’s also the usual practice to declare a virtual destructor for the base class.
 *
 * If a method in a base class will be redefined in a derived class, you should make it virtual. 
 * If the method should not be redefined, you should make it nonvirtual.
*/

// Brass Account Class
class Brass
{
private:
    std::string fullName;
    long acctNum;
    double balance;
public:
    Brass(const std::string & s = "Nullbody", long an = -1,
                double bal = 0.0);
    void Deposit(double amt);
    virtual void Withdraw(double amt);
    double Balance() const;
    virtual void ViewAcct() const;
    virtual ~Brass() {}
};

//Brass Plus Account Class
class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double owesBank;
public:
    BrassPlus(const std::string & s = "Nullbody", long an = -1,
            double bal = 0.0, double ml = 500,
            double r = 0.11125);
    BrassPlus(const Brass & ba, double ml = 500, 
		                        double r = 0.11125);
    virtual void ViewAcct()const;
    virtual void Withdraw(double amt);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; };
    void ResetOwes() { owesBank = 0; }
};

#endif

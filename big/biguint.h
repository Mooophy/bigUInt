#ifndef bigUInt_H
#define bigUInt_H

class bigUInt {
public:
    bigUInt();                  //default constructor: bigUInt d1;
    bigUInt(unsigned int n);    //bigUInt d2(1024);
    bigUInt(const char *s);     //bigUInt d3("099999999999999999999");
    bigUInt(const bigUInt &x);  //copy constructor
    ~bigUInt();                 //destructor

    void add(unsigned int n);   //adds n to this: d1.add(64);
    void add(const bigUInt &x); //adds another number to this: d1.add(d2);
    void increment();           //adds 1 to this: d1.increment();
    void print();               //prints this: d2.print();
                                //i.e. prints 99999999999999999999

    bigUInt operator+(const bigUInt &x);    //bigUInt d4 = d1+d2;
    bigUInt operator-(const bigUInt &x);    //bigUInt d5 = d3-d2;
    bigUInt & operator=(const bigUInt &x);  //d1 = d5;

    const char *get_p() const { //allows non-member functions (read) access to my string
        return p;
    }

private:
    char *p;
};

std::ostream & operator<<(std::ostream &out, const bigUInt &x); //cout << d1;

bigUInt factorial(unsigned n);


#endif // bigUInt_H

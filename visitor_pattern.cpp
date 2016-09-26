/*¬аш класс должен печатать (использу€ std::cout) текстовое представление арифметического выражени€. 
“.е. дл€ объекта класса Number он должен напечатать число, которое в нем хранитс€, а дл€ объекта класса 
BinaryOperation он должен напечатать левый операнд, затем операцию, а затем правый операнд.

”чтите, что операции + и - имеют меньший приоритет, чем операции * и /, т. е. возможно вам придетс€ 
печатать дополнительные круглые скобки, чтобы сохранить правильный пор€док операций.

 лассы иерархии Expression и абстрактный класс Visitor приведены в комментарии в шаблоне дл€ удобства.

ѕри проверке задани€ лишние пробелы или лишние скобки будут игнорироватьс€, т.е. вывод "1+2" эквивалентен 
выводу "( ( 1 )  +   ( 2 ) )", а вот вывод "1 + 2 * 3" не эквивалентен выводу "((1 + 2) * 3)". 
¬ы можете попытатьс€ минимизировать количество скобок в выводе, но это не требуетс€.
*/

/*
struct Number;
struct BinaryOperation;

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * operation) = 0;
    virtual ~Visitor() { }
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor * vistitor) const = 0;
    virtual ~Expression();
};

struct Number : Expression
{
    Number(double value);
    double evaluate() const;

    double get_value() const { return value; }

    void visit(Visitor * visitor) const { visitor->visitNumber(this); }

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right);
    ~BinaryOperation();
    double evaluate() const;

    Expression const * get_left() const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

    void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }

private:
    Expression const * left;
    Expression const * right;
    char op;
};
*/
//решение------------------------------------------------------------------------------------------------------
//€ ничего не пон€ла, но решила
#include <iostream>

struct PrintVisitor : Visitor {
    void visitNumber(Number const * number)
    {
        std::cout << number->get_value();
    }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        std::cout << "(";
        bop->get_left()->visit(this);
        std::cout << bop->get_op();
        bop->get_right()->visit(this);
        std::cout << ")";
    }
};
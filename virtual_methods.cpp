/*
� ���� ������� ��� ������������ ����������� �������� ������� Expression ��� ������������� �������������� ���������. 
����������, ��� ����� ���������� ��� ������: Expression � ������� ����� ��������, Number � ��� ������������� ����� 
� BinaryOperation � ����� ����������� �������� �������� (+, �-, * ��� /).

����� Number ������ ������� �������� ���� double.

����� BinaryOperation ������ ������� ��������� �� ����� � ������ ��������, ������� ���� �������� ��������������� �����������, 
� ����� ��� �������� (+, �-, * ��� /), ������� ����� ��� ���� ����������.

�� ���� ������� ������ ���� ����� evaluate, ������� ���������� �������� ���� double � �������� ���������������� ��������������� 
���������, ��������, �������� ���������� ���� Number � ��� �����, ������� �� ������, � ���� � ��� ���� ������ BinaryOperation � ��������� +, 
�� ����� ��������� �������� ������ � ������� �������� � ������� �� �����.

��������, ��������� 3 + 4.5 * 5 ����� ��������������� ��������� ���:*/
// ������� ������ ������� ��� ������������ 4.5 * 5
Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
// ����� ���������� ��� � ��������� ��� +
Expression * expr = new BinaryOperation(new Number(3), '+', sube);

// ��������� � ������� ���������: 25.5
std::cout << expr->evaluate() << std::endl;

// ��� ������������� *���* ���������� �������
// (��������, sube ����� ������ ��������� expr, ������� ��� ������� �� �����)
delete expr;

//�������----------------------------------------------------------------------------------------------------------------------------------------
struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}
    double evaluate() const
    {
        return value;
    }

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }
    double evaluate() const
    {
        switch(op)
        {
            case '+': return left->evaluate()+right->evaluate();
            case '*': return left->evaluate()*right->evaluate();
            case '-': return left->evaluate()-right->evaluate();
            case '/': return left->evaluate()/right->evaluate();
            default: break;
        }
    }
    
private:
    Expression const * left;
    Expression const * right;
    char op;
    
    ~BinaryOperation() 
    {
        delete left;
        delete right;
    }

};
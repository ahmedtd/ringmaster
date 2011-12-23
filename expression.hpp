
#ifndef EXPRESSION
#define EXPRESSION

/// Indicates the type of an expression
enum class expression_type
{
    /// The expression is a time expression
    time,

    /// The expression is a frequency expression
    frequency,

    /// The expression involves neither time nor frequency
    invariant
};

/// Exception thrown when a laplace or inverse laplace transform is unknown
class expression_unknown_transform_exception : public exception
{
public:
    expression_unknown_transform_exception(const string &what);
};

/// An expression is a symbolic representation of some quantity in terms of
/// voltages and currents between pins.  It may also involve time and frequency.
class expression
{
public:
    
    /// Get the type of the expression
    virtual expression_type type() const = 0;

    /// Convert this expression to a frequency-domain expression
    virtual unique_ptr<expression> to_frequency() const = 0;
    
    /// Convert this expression to a time-domain expression.
    virtual unique_ptr<expression> to_time() const = 0;
};  

/// An expression that represents a constant
class constant_expression : public expression
{
public:
    /// Construct the expression "1"
    constant_expression();

    /// Construct the expression "constant"
    constant_expression(double constant);

    virtual expression_type type() const override;
    
    virtual unique_ptr<expression> to_frequency() const override;
    
    virtual unique_ptr<expression> to_time() const override;
    
private:
    enum class mode
    {
        e,
        one,
        minus_one,
        arbitrary
    };
    
    /// Is this constant operating as a special or arbitrary value?
    mode mMode;
    
    /// If operating in arbitrary mode, this is the value of the constant.
    double mArbitraryVal;
};

/// An expression that represents an exponentiation "a^b"
class exponent_expression : public expression
{
public:
    exponent_expression(const expression &base, const expression &exponent);

    virtual expression_type type() const override;
    
    virtual unique_ptr<expression> to_frequency() const override;
    
    virtual unique_ptr<expression> to_time() const override;

    const unique_ptr<expression> mBase;
    const unique_ptr<expression> mExponent;
};

/// An expression that represents a sum "a + b + ..."
class sum_expression : public expression
{
public:
    sum_expression(const expression &left, const expression &right);
    sum_expression(const product_expression &left, const expression &right);

    const vector<const expression> mTerms;
};

/// An expression that represents a product "a*b"
class product_expression : public expression
{
public:
    product_expression(const expression &left, const expression &right);
    product_expression(const product_expression &left, const expression &right);

    virtual expression_type type() const override;
    virtual unique_ptr<expression> to_frequency() const override;
    virtual unique_ptr<expression> to_time() const override;

    const vector<const expression> mTerms;
};

/// An expression that represents a definite integral
class integral_expression : public expression
{
public:
    integral_expression(const expression &integrand,
                        const expression &lower,
                        const expression &upper);

    virtual expression_type type() const override;
    virtual unique_ptr<expression> to_frequency() const override;
    virtual unique_ptr<expression> to_time() const override;

    const expression mIntegrand;
    const expression mLower;
    const expression mUpper;
};

/// An expression that represents a time differentiation
class derivative_expression : public expression
{
public:
    derivative_expression(const expression &subject);

    virtual expression_type type() const override;
    virtual unique_ptr<expression> to_frequency() const override;
    virtual unique_ptr<expression> to_time() const override;
    
    const expression mSubject;
};

/// An expression representing an independent variable, either t or s
class independent_expression : public expression
{
public:
    independent_expression(const expression_type &type);

    virtual expression_type type() const override;
    virtual unique_ptr<expression> to_frequency() const override;
    virtual unique_ptr<expression> to_time() const override;
    
private:
    const expression_type mType;
};

/// An expression representing a voltage, whether as a function of time,
/// frequency, or invariant 
class voltage_expression : public expression
{
public:
    voltage_expression(const voltage &which, const expression_type &type);
    
    virtual expression_type type() const override;
    virtual unique_ptr<expression> to_frequency() const override;
    virtual unique_ptr<expression> to_time() const override;

    const voltage mWhich;
};

/// An expression representing a current, whether as a function of time,
/// frequency, or invariant
class current_expression : public expression
{
public:
    current_expression(const current &which, const expression_type &type);
    
    virtual expression_type type() const override;
    virtual unique_ptr<expression> to_frequency() const override;
    virtual unique_ptr<expression> to_time() const override;
    
    const current mWhich;
};    

#endif

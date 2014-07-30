/*
   Copyright (C) Oleg Ziakun
*/

#ifndef PROPERTY_H
#define PROPERTY_H

#include <memory>

#define PROPERTY_DECLARATION(name) name##_
#define PROPERTY_VARIABLE(name) name##Property

#define PROPERTY_REF outerClassNameRef

#define PROPERTY_CALL(name) m_##PROPERTY_REF.name

#define GET const Type &get() const;
#define SET const Type &set(const Type &other);

#define PROPERTY_GET(type, outerClassName, name) const type &outerClassName::PROPERTY_DECLARATION(name)::get() const
#define PROPERTY_SET(type, outerClassName, name) const type &outerClassName::PROPERTY_DECLARATION(name)::set(const type &other)

#define BUILD_PROPERTY_OPERATOR(operatorName) Property tmpProperty = *this; tmpProperty.value operatorName##= other.value; return tmpProperty

#define PROPERTY(type, name, outerClassName, ref,  ...) class PROPERTY_DECLARATION(name) : public Property<type> \
{ \
    public: \
    typedef type Type; \
    using Property::operator=; \
    PROPERTY_DECLARATION(name) (outerClassName &outerClass) : m_##PROPERTY_REF(outerClass) {} \
    PROPERTY_DECLARATION(name) &Ref () { return *this; } \
    private: \
    outerClassName &m_##PROPERTY_REF; \
    public: \
    __VA_ARGS__ \
    }; \
    std::unique_ptr<PROPERTY_DECLARATION(name)> PROPERTY_VARIABLE(name) = std::unique_ptr<PROPERTY_DECLARATION(name)>(new PROPERTY_DECLARATION(name)(ref)); \
    PROPERTY_DECLARATION(name) &name = PROPERTY_VARIABLE(name)->Ref()

template <typename T>
class Property
{
public:
    const T &operator () () const { return get(); }
    const T &operator ++ (){ return ++value; }
    const T &operator ++ (int){ return value++; }
    const T &operator -- (){ return --value; }
    const T &operator -- (int){ return value--; }
    bool operator == (const T &other) { return value == other; }
    bool operator == (const Property& other) { return value == other.value; }
    const T &operator = (const T &other) { return set(other); }
    const Property &operator = (const Property &other) { set(other.value); return *this; }
    const T operator + (const T &other) { return value + other; }
    const Property operator + (const Property &other) { BUILD_PROPERTY_OPERATOR(+); }
    const T &operator += (const T &other) { return value += other; }
    const Property &operator += (const Property &other) { value += other.value; return *this; }
    const T operator - (const T &other) { return value - other; }
    const Property operator - (const Property &other) { BUILD_PROPERTY_OPERATOR(-); }
    const T &operator -= (const T &other) { return value -= other; }
    const Property &operator -= (const Property &other) { value -= other.value; return *this; }
    const T operator * (const T &other) { return value * other; }
    const Property operator * (const Property &other) { BUILD_PROPERTY_OPERATOR(*); }
    const T &operator *= (const T &other) { return value *= other; }
    const Property &operator *= (const Property &other) { value *= other.value; return *this; }
    const T operator / (const T& other) { return value / other; }
    const Property operator / (const Property &other) { BUILD_PROPERTY_OPERATOR(/); }
    const T &operator /= (const T &other) { return value /= other; }
    const Property &operator /= (const Property &other) { value /= other.value; return *this; }
    const T operator & (const T &other) { return value & other; }
    const Property operator & (const Property &other) { BUILD_PROPERTY_OPERATOR(&); }
    const T operator | (const T &other) { return value | other; }
    const Property operator | (const Property &other) { BUILD_PROPERTY_OPERATOR(|); }
    const T& operator ~ () { return value = ~value; }
    const T operator ^ (const T &other) { return value ^ other; }
    const Property operator ^ (const Property &other) { BUILD_PROPERTY_OPERATOR(^); }
    const T &operator ^= (const T &other) { return value ^= other; }
    const Property &operator ^= (const Property &other) { value ^= other.value; return *this; }
    const T operator << (const T &other) { return value << other; }
    const Property operator << (const Property &other) { BUILD_PROPERTY_OPERATOR(<<); }
    const T &operator <<= (const T &other) { return value <<= other; }
    const Property &operator <<= (const Property &other) { value <<= other.value; return *this; }

protected:
    virtual const T &get() const { return value; }
    virtual const T &set(const T &other) { return value = other; }

protected:
    T value;
};

#endif // PROPERTY_H

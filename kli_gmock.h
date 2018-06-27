#include <gmock/gmock.h>

/*
https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md
 * */

class Inner
{

};

template <typename T=Inner>
class Outer
{
    const T t;

    Outer(const T& tt) // only works with reference
    : t{tt}
    {}

    int doSomething() const
    {
        int ret = 0;
        std::string s;
        ret = t.doS(&s);
        return ret;
    }

    bool copyValue(int* to, int from)
    {
        return t.setV(to, from);
    }
};

class MockInner
{
    MOCK_CONST_METHOD1(doSomething, int(void));
    MOCK_METHOD2(copyValue, bool(int*, int));
};


TEST(Test, WithMock)
{
    MockInner inner;
    Outer<MockInner> outer{inner};
    std::string s{"56"};
    int age = 90;

    EXPECT_CALL(inner, doS(_))
    .WillOnce(DoAll(SetArgPointee<0>(s), Return(age)));

    EXPECT_EQ(outer.doSomething(), age);
}



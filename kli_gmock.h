#include <gmock/gmock.h>

/*
https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md
 * */

Struct Msg
{
    void print() const {}
    
    const std::string& get() const {}

    int append(const int) {}                // overloads 
    
    int append(const std::string&) {}       // overloads 
};

class MockMsg 
{
    MOCK_CONST_METHOD0(print, void(void));
    
    MOCK_CONST_METHOD0(get, const std::string&(void));
   
    MOCK_METHOD1(append, int(const int));
    MOCK_METHOD1(append, int(const std::string&));
}

template <typename MSG=Msg>
class Job
{
    const MSG d_msg;

    Job(const MSG& msg) // only works with reference
    : d_msg{msg}
    {}

};


TEST(Test, WithMock)
{
    MockMsg msg;
    Job<MockMsg> job{msg};

    EXPECT_CALL(inner, doS(_))
    .WillOnce(DoAll(SetArgPointee<0>(s), Return(age)));

    EXPECT_EQ(outer.doSomething(), age);
}



#include <gmock/gmock.h>

/*
https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md
 * */

using namespace ::testing;
using ::testing::InSequence;
using ::testing::Matcher;
using ::testing::Return;
using ::testing::_;


Struct Msg
{
    void print() const {}
    
    const std::string& get() const {}
    
    bool set(std::string*) {}               // out parameter
    
    int append(const int) {}                // overloads 
    
    int append(const std::string&) {}       // overloads 
};

class MockMsg 
{
    MOCK_CONST_METHOD0(print, void(void));
    
    MOCK_CONST_METHOD0(get, const std::string&(void));
   
    MOCK_METHOD1(set, void(std::string));
    
    MOCK_METHOD1(append, int(const int));
    MOCK_METHOD1(append, int(const std::string&));
}

template <typename MSG=Msg>
class Job
{
    const MSG d_msg;
    const std::shared_ptr<MSG> d_msg_sp;
    
    Job(const MSG& msg) // only works with reference
    : d_msg{msg}
    {}
    
    Job(const std::shared_ptr<MSG>& msg) // only works with reference
    : d_msg_sp{msg}
    {}
    
    // any function...
};

// examples

TEST(Test, WithMock)
{
    MockMsg msg;
    Job<MockMsg> job{msg};
    
    
    // SetArgPointee
    std::string s;
    EXPECT_CALL(msg, set(_))
    .WillOnce(DoAll(SetArgPointee<0>(s), Return(true)));
    EXPECT_EQ(s, "");
    
    // InSequence, call will be expected in sequence 
    {
        InSequence s;
        EXPECT_CALL(msg, append(Matcher<const int>(_)))                // resolve function overloads
            .WillOnce(Return(0));
        EXPECT_CALL(msg, append(Matcher<const std::string&>(_)))
            .WillOnce(Return(0));
    }
    
    // shared pointer
    auto msg_sp = std::make_sahred<MockMsg>();
    Job<MockMsg> job2{msg};
    
    EXPECT_CALL(*msg_sp, set(_));
    
}



#include "gtest/gtest.h"
/*
https://github.com/google/googletest/blob/master/googletest/docs/primer.md
*/
using ::testing::Test;


// Basic Test
TEST(TestGtest, Comparison) {
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_THROW(throwError(), std::runtime_error);
}

// Test Fixtures: Using the Same Data Configuration for Multiple Tests
class QueueTest : public Test {
  protected:
    void SetUp() override{
        q0_.Enqueue(1);
    }

    void TearDown() override {}
    Queue<int> q0_;
};
}

TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_EQ(0, q0_.size());
}
/*
When invoked, the RUN_ALL_TESTS() macro:

Saves the state of all Google Test flags.
Creates a test fixture object for the first test.
Initializes it via SetUp().
Runs the test on the fixture object.
Cleans up the fixture via TearDown().
Deletes the fixture.
Restores the state of all Google Test flags.
Repeats the above steps for the next test, until all tests have run.
*/

// Text with Parameters
class TestWithOneParam : public ::testing::TestWithParam<std::string>
{

}

TEST_P(TestWithOneParam, Equal)
{
    // GIVEN
    std::string num = GetParam();

    // THEN
    EXPECT_EQ(myStoi(num), std::stoi(num));
}
INSTANTIATE_TEST_CASE_P(TestMyToStoi, TestWithOneParam, ::testing::Values(
    "23", "12", "45"
));


class TestMultiParams : public ::testing::TestWithParam<std::tuple<int, double, std::string>>
{}

TEST_P(TestWithOneParam, Combinations)
{
    int age;
    double time;
    std::string name;

    std::tie(age, time, name) = GetParam();
}

INSTANTIATE_TEST_CASE_P(TestParsersWithParams, TestConfigParser, ::testing::Values(
     std::make_tuple(1, 3.0, "hello"),
     std::make_tuple(10, 30.0, "world")
));


// Test with variant
using ID = std::variant<int, double, std::string>;
class TestVariant :  public ::testing::TestWithParam<ID>
{}

TEST_P(TestVariant, IsValidID)
{
    ID id = GetParam();
    EXPECT_TRUE(isValid(id));
}

INSTANTIATE_TEST_CASE_P(TestVariant, TestAnyType, ::testing::Values(
    ID{12}, ID{"23"}, ID{23.0}
));


// Typed test
template <typename T>
class EncodingStateTest : public ::testing::Test {
    using List = std::list<T> List;
    static T shared;
    T value;
};
using StateTypes = ::testing::
    Types<mobt::OrderState, mobt::RouteState, mobt::FillFundamental>;
TYPED_TEST_CASE(EncodingStateTest, EntityTypes);

TYPED_TEST(EncodingStateTest, SerializeDeserialize)
{
    // GIVEN
    Encoder          es;
    TypeParam        entityState;   // Access Type
    TypeParam n      = this->value; // access member attribute
    // To visit static members of the fixture, add the 'TestFixture::'
    // prefix.
    n += TestFixture::shared; // Access static member 
    // To refer to typedefs in the fixture, add the 'typename TestFixture::'
    // prefix.  The 'typename' is required to satisfy the compiler.
    typename TestFixture::List values;
    values.push_back(n);
}

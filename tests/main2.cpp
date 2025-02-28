#include "boost/ut.hpp"

using namespace boost::ut;

static suite<"TEST suite"> _ = []
{
    test("TEST test") = []
    {
        std::cout << "\ntest output to be captured" << std::endl;
        expect(false);
    };
};

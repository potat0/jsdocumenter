#include "precompile.h"

#include <boost/fusion/include/adapt_struct.hpp>
#include <iostream>
#include <fstream>
#include <string>

template <typename Iterator>
struct EcmaExecutor : public boost::spirit::qi::grammar<Iterator, unsigned()>
{
    public:
        EcmaExecutor() 
            : EcmaExecutor::base_type(program)
        {
            program = boost::spirit::qi::uint_;
        }

        boost::spirit::qi::rule<Iterator, unsigned()> program;
};

int main(int argc, char* argv[])
{
    std::ifstream in("test.js", std::ios::in | std::ios::binary);
    if(in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());

        EcmaExecutor<std::string::const_iterator> executor;
        unsigned program;
        std::string::const_iterator start = contents.begin();
        std::string::const_iterator end = contents.end();
        boost::spirit::qi::parse(start, end, executor, program);
    }

    return 0;
}

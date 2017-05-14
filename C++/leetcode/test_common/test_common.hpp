#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP 

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/filesystem.hpp>
#include <boost/functional/hash.hpp>

#include <tuple>
#include <vector>
#include <string>
#include <array>
#include <utility>

namespace bdata = boost::unit_test::data;
namespace bf = boost::filesystem;
using namespace std::string_literals;


namespace std {
    template<> struct hash<bf::path> {
        size_t operator()(const bf::path& p) const {
            return bf::hash_value(p);
        }
    };
} 

std::vector<std::pair<bf::path, bf::path>> get_all_test_filepaths(
        const bf::path& target_path = bf::current_path(),
        const std::string& input_prefix = "input",
        const std::string& output_prefix = "output"
        );

template<typename read_input_fn_t, typename read_output_fn_t>
class NumberedTestsFromFiles {
    private:
        read_input_fn_t read_input_fn;
        read_output_fn_t read_output_fn;
        std::vector<std::pair<bf::path, bf::path>> all_test_paths;
    public:

        enum { arity = 1 };
            typedef decltype(read_input_fn(std::declval<const char *>())) input_type;
            typedef decltype(read_output_fn(std::declval<const char *>())) output_type;
            typedef std::tuple<input_type, output_type> test_pair;
        struct iterator {
            iterator(const NumberedTestsFromFiles& outer) : outer(outer), test_it(outer.all_test_paths.begin()) {
                ++*this;
            }

            test_pair operator*() const { 
                return t; 
            }

            void operator++() {
                input_type&& input = outer.read_input_fn(test_it->first.string().c_str());
                output_type&& output = outer.read_output_fn(test_it->second.string().c_str());
                t = make_pair(input, output);
                ++test_it;
            }

        private:
            const NumberedTestsFromFiles& outer;
            std::vector<std::pair<bf::path, bf::path>>::const_iterator test_it;
            test_pair t;
        };

        NumberedTestsFromFiles(read_input_fn_t read_input_fn, read_output_fn_t read_output_fn)
            : read_input_fn(read_input_fn), read_output_fn(read_output_fn),
            all_test_paths(get_all_test_filepaths()) {}

        bdata::size_t size() const { return all_test_paths.size(); }
        iterator begin() const { return iterator(*this); }
};

template<typename... T>
NumberedTestsFromFiles<T...> make_tests(T&&... instance) {
  return NumberedTestsFromFiles<T...>(std::forward<T>(instance)...);
}

namespace boost { namespace unit_test { namespace data { namespace monomorphic {
    // registering NumberedTestsFromFiles as a proper dataset
    template <typename read_input_fn_t, typename read_output_fn_t>
        struct is_dataset<NumberedTestsFromFiles<read_input_fn_t, read_output_fn_t>> : boost::mpl::true_ {};
}}}}


#endif /* TEST_COMMON_HPP */

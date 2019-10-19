#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <boost/filesystem.hpp>
#include <boost/functional/hash.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

#include <array>
#include <exception>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace bdata = boost::unit_test::data;
namespace bf = boost::filesystem;
using namespace std::string_literals;

struct TestFilePaths {
  bf::path input_path;
  bf::path output_path;
};

namespace std {
template <> struct hash<bf::path> {
  size_t operator()(const bf::path &p) const { return bf::hash_value(p); }
};
} // namespace std

std::vector<TestFilePaths>
get_all_test_filepaths(const bf::path &target_path = bf::current_path(),
                       const std::string &input_prefix = "input",
                       const std::string &output_prefix = "output");

template <typename read_input_fn_t, typename read_output_fn_t>
class NumberedTestsFromFiles {
private:
  read_input_fn_t read_input_fn;
  read_output_fn_t read_output_fn;
  std::vector<TestFilePaths> all_test_paths;

public:
  enum { arity = 1 };
  typedef decltype(read_input_fn(std::declval<const char *>())) input_type;
  typedef decltype(read_output_fn(std::declval<const char *>())) output_type;
  struct test_data {
    TestFilePaths test_fp;
    input_type input;   // make sure this is operator<< printable
    output_type output; // make sure this is operator<< printable
    friend std::ostream &operator<<(std::ostream &out, const test_data &td) {
      out << "input_path: " << td.test_fp.input_path << "; ";
      out << "output_path: " << td.test_fp.output_path << "; ";
      out << "input: " << td.input << "; ";
      out << "output: " << td.output;
      return out;
    }
  };
  struct iterator {
    iterator(const NumberedTestsFromFiles &outer)
        : outer(outer), test_it(outer.all_test_paths.begin()) {
      ++*this;
    }

    test_data operator*() const { return m_currDataPair; }

    void operator++() {
      if (test_it == outer.all_test_paths.end()) {
        return;
      }
      std::string f;
      try {
        f = test_it->input_path.string();
        input_type input =
            outer.read_input_fn(test_it->input_path.string().c_str());
        f = test_it->output_path.string();
        output_type output =
            outer.read_output_fn(test_it->output_path.string().c_str());
        m_currDataPair = {*test_it, input, output};
      } catch (std::exception &e) {
        throw std::invalid_argument(f + ": " + e.what());
      }
      ++test_it;
    }

  private:
    const NumberedTestsFromFiles &outer;
    std::vector<TestFilePaths>::const_iterator test_it;
    test_data m_currDataPair;
  };

  NumberedTestsFromFiles(read_input_fn_t read_input_fn,
                         read_output_fn_t read_output_fn)
      : read_input_fn(read_input_fn), read_output_fn(read_output_fn),
        all_test_paths(get_all_test_filepaths()) {}

  bdata::size_t size() const { return all_test_paths.size(); }
  iterator begin() const { return iterator(*this); }
};

namespace boost {
namespace unit_test {
namespace data {
namespace monomorphic {
// registering NumberedTestsFromFiles as a proper dataset
template <typename read_input_fn_t, typename read_output_fn_t>
struct is_dataset<NumberedTestsFromFiles<read_input_fn_t, read_output_fn_t>>
    : boost::mpl::true_ {};
} // namespace monomorphic
} // namespace data
} // namespace unit_test
} // namespace boost

#endif /* TEST_COMMON_HPP */

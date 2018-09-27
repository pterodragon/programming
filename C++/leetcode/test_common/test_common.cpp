#include <boost/regex.hpp>
#include <boost/test/unit_test.hpp>

#include "test_common.hpp"
#include <unordered_set>

std::vector<TestFilePaths>
get_all_test_filepaths(const bf::path &target_path,
                       const std::string &input_prefix,
                       const std::string &output_prefix) {
  std::unordered_set<bf::path> input_paths;
  std::unordered_set<bf::path> output_paths;
  std::vector<TestFilePaths> test_fps;
  auto input_paths_regex = boost::regex(input_prefix + R"_(.*\.txt)_"s);
  auto output_paths_regex = boost::regex(output_prefix + R"_(.*\.txt)_"s);
  boost::smatch what;
  auto process_regex_match_file =
      [&what](const std::string &filename, const boost::regex &regex,
              std::unordered_set<bf::path> &set_to_insert) {
        if (boost::regex_match(filename, what, regex))
          set_to_insert.insert(filename);
      };
  for (auto dir_it : bf::directory_iterator(target_path)) {
    if (!bf::is_regular_file(dir_it.status()))
      continue;
    auto filename = dir_it.path().filename().string();
    process_regex_match_file(filename, input_paths_regex, input_paths);
    process_regex_match_file(filename, output_paths_regex, output_paths);
  }
  for (const auto &input_path : input_paths) {
    const auto &corresponding_output_path =
        output_prefix +
        input_path.filename().string().substr(input_prefix.length());
    const auto &output_path_it = output_paths.find(corresponding_output_path);
    if (output_path_it != output_paths.end()) {
      test_fps.push_back({input_path, corresponding_output_path});
    }
  }
  return test_fps;
}

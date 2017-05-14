#include <boost/test/unit_test.hpp>
#include <boost/regex.hpp>

#include "test_common.hpp"
#include <unordered_set>

namespace bf = boost::filesystem;

std::vector<std::pair<bf::path, bf::path>> get_all_test_filepaths(
        const bf::path& target_path,
        const std::string& input_prefix,
        const std::string& output_prefix) {
    std::unordered_set<bf::path> input_paths;
    std::unordered_set<bf::path> output_paths;
    std::vector<std::pair<bf::path, bf::path>> input_output_filepath_pairs;
    typedef bf::directory_iterator d_it;
    d_it end_itr;
    auto input_paths_regex = boost::regex(input_prefix + R"_(.*\.txt)_"s);
    auto output_paths_regex = boost::regex(output_prefix + R"_(.*\.txt)_"s);
    boost::smatch what;
    auto process_regex_match_file = [&what] (const std::string& filename, const boost::regex& regex, 
            std::unordered_set<bf::path>& set_to_insert) {
        if (boost::regex_match(filename, what, regex)) set_to_insert.insert(filename);
    };
    for (d_it i(target_path); i != end_itr; ++i) {
        if (!bf::is_regular_file(i->status())) continue;
        auto filename = i->path().filename().string();
        process_regex_match_file(filename, input_paths_regex, input_paths);
        process_regex_match_file(filename, output_paths_regex, output_paths);
    }
    for (const auto& p : input_paths) {
        const auto& corresponding_output_path =
            output_prefix + p.filename().string().substr(input_prefix.length());
        const auto& output_path_it = output_paths.find(corresponding_output_path);
        if (output_path_it != output_paths.end()) {
            input_output_filepath_pairs.push_back({p, *output_path_it});
        }
    }
    return input_output_filepath_pairs;
}


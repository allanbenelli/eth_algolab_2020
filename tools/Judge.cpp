#include "Judge.h"

#include <ctime>
#include <chrono>
#include <sstream>
#include <iostream>
#include <charconv>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string.hpp>

namespace algolab {

class CaptureCout {
 public:
  std::streambuf* sbuf;
  std::stringstream stream;

  CaptureCout() : sbuf(std::cout.rdbuf()) {
    std::cout.rdbuf(stream.rdbuf());
  }

  ~CaptureCout() {
    std::cout.rdbuf(sbuf);
  }
};

class FileWrap {
 public:
  std::ifstream file;
  FileWrap() {
    file = static_cast<std::basic_ifstream<char>>(nullptr);
  }

  explicit FileWrap(const std::string& file): file{file} {
    // nothing more to do
  }

  std::ifstream& fileref() {
    return file;
  }

  ~FileWrap() {
    if(this->file) this->file.close();
  }
};

/**
   * Runs the testcase specified by [filename].in and compares the outputs to [filename].out.
   * Also measures if the runtime took longer than [milliseconds] ms.
   * */
void runSingleTest(const std::function<void(std::istream&)>& logic, std::string&& filename, size_t milliseconds = 0) {
  std::cout << ">>>>>> Running testset from file " << filename << ".[in/out] <<<<<<" << std::endl;
  // Prepare to read from file
  FileWrap wrap{filename + ".in"};

  // Capture program output
  auto cout = std::make_unique<CaptureCout>();

  // Time measurement starts
  auto start = std::chrono::high_resolution_clock::now();

  // Run the logic
  logic(wrap.fileref());

  // Time measurement ends
  auto end = std::chrono::high_resolution_clock::now();
  // how much time did it take?
  std::chrono::nanoseconds elapsed = end - start;
  auto elapsedmicros = (elapsed.count() / 1000);

  // Read expected output
  FileWrap outfile{filename + ".out"};

  std::stringstream filebuffer;
  filebuffer << outfile.fileref().rdbuf();
  std::string expected = filebuffer.str();

  // Compare the output to the correct one
  std::string actual = cout->stream.str();
  bool correct = actual == expected;

  // Finish std::cout capture to print our messages to the 'real' std::cout
  cout.reset();

  // Print results
  std::cout << "Run on [" << filename << "] took " << elapsedmicros << "µs." << std::endl;
  if (milliseconds > 0)
    std::cout << "This was " << (elapsedmicros / 1000 <= milliseconds ? "within" : "OVER") << " the TIMELIMIT of "
              << milliseconds << "ms" << std::endl;
  if (correct) {
    std::cout << "CORRECT output." << std::endl;
  } else {
    std::cout << "WRONG output. Showing diff (\033[;32mexpected\033[;39m | \033[;31mactual\033[;39m):\n";
    std::vector<std::string> exp{};
    std::vector<std::string> acc{};
    boost::split(exp, expected, boost::is_any_of("\n"));
    boost::split(acc, actual, boost::is_any_of("\n"));
    size_t ml = 0;
    for (auto& s : exp) ml = std::max(ml, s.size());
    for (uint32_t u = 0; u + 1 < exp.size(); ++u) {
      bool diff = exp[u] != acc[u];
      if (diff) std::cout << "\033[;32m";
      std::cout << std::string(ml - exp[u].size(), ' ') << exp[u];
      if (diff) std::cout << "\033[;39m";
      std::cout << " | ";
      if (diff) std::cout << "\033[;31m";
      std::cout << acc[u] << "\033[;39m" << std::endl;
    }
  }
  std::cout << ">>>>>> End of Test <<<<<<" << std::endl;
}

/**
 * Finds all tests within specified path (empty path -> assume we are in /path/to/src and tests in /path/to/public).
 *
 * Executes all tests, considering the specified runtime. This runtime is stored in a file called TIMELIMIT.
 * If it does not exist yet, it will be created and populated with 0 entries.
 *
 * Note: while measuring runtime, consider that your machine might be slower or faster than code expert's backend.
 * */
void Judge::runTests(const std::function<void(std::istream&)>& logic, std::string&& testPath) {
  auto path = testPath.empty() ? boost::filesystem::current_path().parent_path().append("public") : testPath;
  std::unordered_map<std::string, uint64_t> limits{};

  // read the timelimits
  if (!(boost::filesystem::exists(path.append("TIMELIMIT")))) {
    boost::filesystem::ofstream timelimits{path};
    // append a 0 TL, if file did not exist
    for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(path.parent_path()), {})) {
      if (entry.path().extension() == "in") {
        timelimits << entry.path().stem() << ":0" << "\n";
        limits[entry.path().stem().string()] = 0;
      }
    }
    timelimits.close();
  } else {
    std::ifstream timelimit{path.string()};
    std::string current_line;

    while (std::getline(timelimit, current_line)) {
      // the part after the ':' ...
      uint64_t colonpos = current_line.find(':');
      std::string thelim = current_line.substr(colonpos + 1);
      // ... represents the timelimit for this testcase file
      uint64_t limit = 0;
      std::from_chars(thelim.data(), thelim.data() + thelim.size(), limit);
      limits[current_line.substr(0, colonpos)] = limit;
    }
  }

  for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(path.parent_path()), {})) {
    // Skip any non-input files to not run the same test twice
    if (!(entry.path().extension() == ".in")) continue;
    // Get absolute file path, but only to the "stem", i.e. /path/to/user_test instead of /path/to/user_test.in
    std::string testset = entry.path().parent_path().append(entry.path().stem().string()).string();
    auto limit = limits[entry.path().stem().string()];
    runSingleTest(logic, std::move(testset), limit);
  }
}
} // namespace algolab

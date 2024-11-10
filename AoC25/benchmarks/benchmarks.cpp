#include <benchmark/benchmark.h>
#include <string>

using namespace std;

extern string day1(const string&);

static void BM_day1(benchmark::State& state) {
  for (auto _ : state) {
      auto result = day1("input");
      benchmark::DoNotOptimize(result);
  }
}

// Run benchmarks
BENCHMARK(BM_day1);



BENCHMARK_MAIN();

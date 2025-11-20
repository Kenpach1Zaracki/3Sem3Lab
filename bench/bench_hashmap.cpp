#include <benchmark/benchmark.h>
#include "hash.h"

static void BM_HashMapSet(benchmark::State& state) {
    for (auto _ : state) {
        HashMap m;
        for (int i = 0; i < state.range(0); ++i) {
            m.set("key" + std::to_string(i), "val");
        }
        benchmark::DoNotOptimize(m);
    }
}
BENCHMARK(BM_HashMapSet)->Range(8, 1 << 12);

static void BM_HashMapGet(benchmark::State& state) {
    HashMap m;
    for (int i = 0; i < state.range(0); ++i) {
        m.set("key" + std::to_string(i), "val");
    }
    std::string out;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            m.get("key" + std::to_string(i), out);
        }
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_HashMapGet)->Range(8, 1 << 12);

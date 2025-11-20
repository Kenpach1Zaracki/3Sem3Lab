#include <benchmark/benchmark.h>
#include "massive.h"

static void BM_HashSetInsert(benchmark::State& state) {
    for (auto _ : state) {
        HashSet s;
        for (int i = 0; i < state.range(0); ++i) {
            s.insert("val" + std::to_string(i));
        }
        benchmark::DoNotOptimize(s);
    }
}
BENCHMARK(BM_HashSetInsert)->Range(8, 1 << 12);

static void BM_HashSetContains(benchmark::State& state) {
    HashSet s;
    for (int i = 0; i < state.range(0); ++i) {
        s.insert("val" + std::to_string(i));
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            benchmark::DoNotOptimize(s.contains("val" + std::to_string(i)));
        }
    }
}
BENCHMARK(BM_HashSetContains)->Range(8, 1 << 12);

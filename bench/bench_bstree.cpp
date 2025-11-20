#include <benchmark/benchmark.h>
#include "bstree.h"

static void BM_BSTreeInsert(benchmark::State& state) {
    for (auto _ : state) {
        BSTree t;
        for (int i = 0; i < state.range(0); ++i) {
            t.insert(std::to_string(i));
        }
        benchmark::DoNotOptimize(t);
    }
}
BENCHMARK(BM_BSTreeInsert)->Range(8, 1 << 12);

static void BM_BSTreeContains(benchmark::State& state) {
    BSTree t;
    for (int i = 0; i < state.range(0); ++i) {
        t.insert(std::to_string(i));
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            benchmark::DoNotOptimize(t.contains(std::to_string(i)));
        }
    }
}
BENCHMARK(BM_BSTreeContains)->Range(8, 1 << 12);

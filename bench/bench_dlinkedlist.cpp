#include <benchmark/benchmark.h>
#include "twolink.h"

static void BM_DLinkedListPushBack(benchmark::State& state) {
    for (auto _ : state) {
        DLinkedList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.push_back("value");
        }
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_DLinkedListPushBack)->Range(8, 1 << 12);

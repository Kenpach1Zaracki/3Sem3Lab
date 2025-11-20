#include <benchmark/benchmark.h>
#include "onel.h"

static void BM_LinkedListPushBack(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.push_back("value");
        }
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_LinkedListPushBack)->Range(8, 1 << 12);

static void BM_LinkedListPushFront(benchmark::State& state) {
    for (auto _ : state) {
        LinkedList list;
        for (int i = 0; i < state.range(0); ++i) {
            list.push_front("value");
        }
        benchmark::DoNotOptimize(list);
    }
}
BENCHMARK(BM_LinkedListPushFront)->Range(8, 1 << 12);

#include <benchmark/benchmark.h>
#include "queue.h"

static void BM_QueuePushPop(benchmark::State& state) {
    for (auto _ : state) {
        Queue q;
        for (int i = 0; i < state.range(0); ++i) {
            q.push("value");
        }
        std::string out;
        while (!q.empty()) {
            q.pop(&out);
        }
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_QueuePushPop)->Range(8, 1 << 12);

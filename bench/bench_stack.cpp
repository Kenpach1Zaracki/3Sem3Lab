#include <benchmark/benchmark.h>
#include "stack.h"

static void BM_StackPushPop(benchmark::State& state) {
    for (auto _ : state) {
        Stack st;
        for (int i = 0; i < state.range(0); ++i) {
            st.push("value");
        }
        std::string out;
        while (!st.empty()) {
            st.pop(&out);
        }
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_StackPushPop)->Range(8, 1 << 12);

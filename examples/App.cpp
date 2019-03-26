// jaeger client adapted from https://github.com/jaegertracing/jaeger-client-cpp
// quicksort code adapted from https://www.geeksforgeeks.org/quick-sort/

#include <iostream> 
#include <yaml-cpp/yaml.h> 
#include <jaegertracing/Tracer.h>
#include <bits/stdc++.h>

namespace {

    void setUpTracer(const char * configFilePath) {
        auto configYAML = YAML::LoadFile(configFilePath);
        auto config = jaegertracing::Config::parse(configYAML);
        auto tracer = jaegertracing::Tracer::make(
            "sorting-service", config, jaegertracing::logging::consoleLogger());
        opentracing::Tracer::InitGlobal(
            std::static_pointer_cast <opentracing::Tracer> (tracer));
    }

    void swap(int* a, int* b, 
        const std::unique_ptr <opentracing::Span> & parentSpan) {
        auto span = opentracing::Tracer::Global() -> StartSpan(
            "swap", {
                opentracing::ChildOf( &parentSpan -> context())
            });
        int t = *a;
        *a = *b;
        *b = t;
    }

    int partition(int arr[], int low, int high,
        const std::unique_ptr <opentracing::Span> & parentSpan) {
        auto span = opentracing::Tracer::Global() -> StartSpan(
            "partition", {
                opentracing::ChildOf( &parentSpan -> context())
            });

        int pivot = arr[high]; // pivot 
        int i = (low - 1); // Index of smaller element 

        for (int j = low; j <= high - 1; j++) {
            // If current element is smaller than or 
            // equal to pivot 
            if (arr[j] <= pivot) {
                i++; // increment index of smaller element 
                swap( &arr[i], &arr[j], span);
            }
        }
        swap( &arr[i + 1], &arr[high], span);
        return (i + 1);
    }

    void quickSort(int arr[], int low, int high) {
        auto span = opentracing::Tracer::Global() -> StartSpan("quickSort");

        if (low < high) {
            /* pi is partitioning index, arr[p] is now 
            at right place */
            int pi = partition(arr, low, high, span);

            // Separately sort elements before 
            // partition and after partition 
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }

    }

} // anonymous namespace

int main(int argc, char * argv[]) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <config-yaml-path>\n";
        return 1;
    }
    setUpTracer(argv[1]);

    int arr[] = {10,7,8,9,1,5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);

    /*
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    */

    // Not stricly necessary to close tracer, but might flush any buffered
    // spans. See more details in opentracing::Tracer::Close() documentation.
    opentracing::Tracer::Global() -> Close();
    return 0;
}

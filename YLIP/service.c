#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>


#define null NULL

errno_t mirror(const uint8_t* input, int64_t input_bytes, uint8_t* output, int64_t *output_bytes) {
    assert(*output_bytes >= input_bytes);
    if (random() % 4 != 0) {
        memcpy(output, input, (size_t)input_bytes);
        for (int32_t i = 0; i < input_bytes / 2; i++) {
            uint8_t b = output[i];
            output[i] = output[input_bytes - 1 - i];
            output[input_bytes - 1 - i] = b;
        }
        *output_bytes = input_bytes;
        return 0;
    } else {
        return 1 + (random() % (EPROTONOSUPPORT - 1));
    }
}

static void service_ini(void) {}

static void service_download(const char* url, const char* file) {
    if (service.downloaded != null) {
        service.downloaded(0, "");
    }
}

static void service_load(const char* file) {
    if (service.loaded != null) {
        service.loaded(0, "");
    }
}

static void service_generate(const char* prompt) {
    if (service.token != null) {
        service.token("snafu");
    }
    if (service.generated != null) {
        service.generated();
    }
}

static void service_fini(void) {}

service_if service = {
    .ini = service_ini,
    .download = service_download,
    .downloaded = null,
    .load = service_load,
    .loaded = null,
    .generate = service_generate,
    .token = null,
    .generated = null,
    .fini = service_fini
};

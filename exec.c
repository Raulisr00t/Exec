#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libtcc.h>

void tcc_error(void *opaque, const char *msg) {
    fprintf(stderr, "[TCC ERROR] %s\n", msg);
}

void exec(const char* code) {
    TCCState *state = tcc_new();
    
    if (!state) {
        fprintf(stderr, "[!] Failed to create TCC state\n");
        return;
    }

    tcc_set_error_func(state, NULL, tcc_error);
    tcc_set_output_type(state, TCC_OUTPUT_MEMORY);

    tcc_add_symbol(state, "printf", printf);
    tcc_add_symbol(state, "exit", exit);

    char actual_code[4096];

    snprintf(actual_code, sizeof(actual_code),
             "#include <stdio.h>\n"
             "void run() {\n%s\n}\n", code);

    printf("Code :\n%s\n", actual_code);

    if (tcc_compile_string(state, actual_code) == -1) {
        fprintf(stderr, "[!] Compilation error\n");
        tcc_delete(state);
        return;
    }

    int size = tcc_relocate(state, NULL);
 
    printf("[DEBUG] relocation size = %d\n", size);

    if (size <= 0) {
        fprintf(stderr, "[!] Relocation size calculation failed\n");
        tcc_delete(state);
        return;
    }

    // Allocate Dynamic memory for execution
    void *memory = malloc(size);

    if (!memory) {
        fprintf(stderr, "[!] Out of memory\n");
        tcc_delete(state);
        return;
    }

    if (tcc_relocate(state, memory) < 0) {
        fprintf(stderr, "[!] Relocation failed\n");
        free(memory);
        tcc_delete(state);
        return;
    }

    void (*execute)() = tcc_get_symbol(state, "run");
 
    if (!execute) {
        fprintf(stderr, "[!] Cannot find 'run' symbol\n");
        free(memory);
        tcc_delete(state);
        return;
    }

    run_func();

    free(memory);
 
    tcc_delete(state);
}

int main() {
    const char* code = "printf(\"Hello From Raul ..\n What do you think about JIT in C?\");";
    exec(code);

    return 0;
}

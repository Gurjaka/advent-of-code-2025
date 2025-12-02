#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <linux/limits.h>
#include <unistd.h>

typedef struct {
    char dir_name[NAME_MAX];
    char solution_path[NAME_MAX];
    char header_path[NAME_MAX];
    char input_path[NAME_MAX];
} DIR_CONTENT;

DIR_CONTENT files_fmt(int day)  ;
int write_template(char *fpath, const char *template);
int create_day_header(int day_num, const char *filepath);
int fetch_puzzle_content(int day_num, const char *dir_name, const char *session_cookie);
int generate_markdown_from_html(const char *html_path, const char *md_path);

int main(void)
{
    FILE *cookies;
    cookies = fopen("./cookies.txt", "r");

    if (cookies == NULL) {
        fprintf(stderr, "Couldn't open ./cookies.txt\n");
        fprintf(stderr, "The session cookie is required to fetch personalized input.\n");
        return EXIT_FAILURE;
    }
    char session_cookie[LINE_MAX];
    (void)fgets(session_cookie, LINE_MAX, cookies);

    const char *solution_template = {
        "#include <stdio.h>\n"
        "#include <stdlib.h>\n"
        "#include <string.h>\n"
        "\n"
        "/**\n"
        " * @brief Function to solve Part 1.\n"
        " * @param input_path The path to the puzzle input file.\n"
        " * @return The calculated result for Part 1.\n"
        " */\n"
        "long solve_part1(const char *input_path)\n"
        "{\n"
        "    // --- Placeholder Implementation ---\n"
        "    FILE *file = fopen(input_path, \"r\");\n"
        "    if (!file) {\n"
        "        perror(\"Error opening file\");\n"
        "        return 0;\n"
        "    }\n"
        "    // ... Read file and process logic here\n"
        "    fclose(file);\n"
        "    return 0;\n"
        "}\n"
        "\n"
        "/**\n"
        " * @brief Function to solve Part 2.\n"
        " * @param input_path The path to the puzzle input file.\n"
        " * @return The calculated result for Part 2.\n"
        " */\n"
        "long solve_part2(const char *input_path)\n"
        "{\n"
        "    // --- Placeholder Implementation ---\n"
        "    return 0;\n"
        "}\n"
        "\n"
        "int main(int argc, char *argv[])\n"
        "{\n"
        "    const char *input_file = \"input.txt\";\n"
        "\n"
        "    printf(\"\\n--- Processing Day ---\\n\");\n"
        "    long result1 = solve_part1(input_file);\n"
        "    long result2 = solve_part2(input_file);\n"
        "\n"
        "    printf(\"Part 1 Result: %ld\\n\", result1);\n"
        "    printf(\"Part 2 Result: %ld\\n\", result2);\n"
        "\n"
        "    return EXIT_SUCCESS;\n"
        "}\n"
    };


    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir() failed\n");
        return EXIT_FAILURE;
    }

    int day = 0;
    int current_day_num = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (sscanf(entry->d_name, "day%2d", &current_day_num) == 1) {
            if (current_day_num > day)
                day = current_day_num;
        }
    }
    closedir(dir);

    day++;

    DIR_CONTENT content = files_fmt(day);

    if (mkdir(content.dir_name, 0755) != 0) {
        perror("Unable to create a directory\n");
        return EXIT_FAILURE;
    }

    if (write_template(content.solution_path, solution_template)) {
        fprintf(stderr, "Failed to create header file at: %s", content.header_path);
        return EXIT_FAILURE;
    }

    if (create_day_header(day, content.header_path)) {
        fprintf(stderr, "Failed to create header file at: %s", content.header_path);
        return EXIT_FAILURE;
    }

    if (fetch_puzzle_content(day, content.dir_name, session_cookie) != 0) {
        fprintf(stderr, "\nSetup failed due to network errors. Cleaning up...\n");
        return EXIT_FAILURE;
    }

    printf("\nSetup for %s complete. Happy coding, %s!\n", content.dir_name, getlogin());

    return EXIT_SUCCESS;
}

DIR_CONTENT files_fmt(int day)
{
    DIR_CONTENT format;
    snprintf(format.dir_name, NAME_MAX, "day%02d", day);
    snprintf(format.solution_path, NAME_MAX, "%s/main.c", format.dir_name);
    snprintf(format.header_path, NAME_MAX, "include/%s.h", format.dir_name);

    return format;
}

int write_template(char *fpath, const char *template)
{
    FILE *file; 
    file = fopen(fpath, "w");

    if (file == NULL) {
        fprintf(stderr, "Couldn't open file: %s\n", fpath);
        return -1;
    }

    if (fputs(template, file) == EOF) {
        fprintf(stderr, "Can't write to file %s\n", fpath);
        fclose(file);
        return -1;
    }

    fclose(file);

    return 0;
}

int create_day_header(int day_num, const char *filepath)
{
    char guard_macro[16];

    snprintf(guard_macro, sizeof(guard_macro), "DAY%02d_H", day_num);

    FILE *f = fopen(filepath, "w");
    if (f == NULL) {
        perror("Error creating header file");
        return 1;
    }

    fprintf(f, "#ifndef %s\n", guard_macro);
    fprintf(f, "    #define %s\n", guard_macro);
    fprintf(f, "\n");
    fprintf(f, "// Function prototypes\n");
    fprintf(f, "long solve_part1(const char *input_path);\n");
    fprintf(f, "long solve_part2(const char *input_path);\n");
    fprintf(f, "\n");
    fprintf(f, "#endif // %s\n", guard_macro);

    fclose(f);
    printf("Created header: %s\n", filepath);
    return 0;
}

int fetch_puzzle_content(int day_num, const char *dir_name, const char *session_cookie)
{
    char input_cmd[NAME_MAX * 2];
    char html_cmd[NAME_MAX * 2];

    printf("\n--- Fetching Puzzle Content ---\n");

    snprintf(input_cmd, sizeof(input_cmd),
             "curl -s --fail --cookie \"session=%s\" https://adventofcode.com/2025/day/%d/input -o %s/input.txt",
             session_cookie, day_num, dir_name);

    printf("Fetching input... ");
    if (system(input_cmd) != 0) {
        fprintf(stderr, "\nERROR: Failed to download input.\n");
        fprintf(stderr, "       Check if the session cookie is correct and valid for Day %d.\n", day_num);
        return -1;
    }
    printf("Input downloaded.\n");

    return 0;
}
